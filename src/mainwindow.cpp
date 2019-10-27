//
// Created by peeweep on 2019-10-15.
//
#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QTableWidget>
#include "about.h"
#include "preference.h"
MainWindow::MainWindow(QWidget* parent) {
  // Set title and icon
  QString title = "Customer Assistant";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));
  this->resize(1000, 720);

  // enable MenuBar
  QMenuBar* qMenuBar = menuBar();
  setMenuBar(qMenuBar);

  // Add menu "start" in  Menubar
  QMenu* menuStart = qMenuBar->addMenu("Start");

  // Add action "Edit Preference" under "start" menu
  QAction* actionPreference = menuStart->addAction("Edit Preference");
  // show preference When click "Close"
  Preference* preference = new Preference(menuStart);
  connect(actionPreference, &QAction::triggered, [=]() { preference->show(); });

  // Add action "Close" under "start" menu
  QAction* actionClose = menuStart->addAction("Close");
  // Close Program When click "Close"
  connect(actionClose, &QAction::triggered, [=]() { this->close(); });

  // Add menu "About"
  QMenu* menuAbout = qMenuBar->addMenu("About");
  // Add action "About" under "About" menu
  QAction* actionAbout = menuAbout->addAction("About");
  // show About When click "About"
  About* about = new About(menuAbout);
  connect(actionAbout, &QAction::triggered, [=]() { about->exec(); });

  QWidget*      centralWidget = new QWidget(this);
  QVBoxLayout*  qvBoxLayout   = new QVBoxLayout(centralWidget);
  QTableWidget* qTableWidget  = new QTableWidget(centralWidget);
  QLabel*       qLabel        = new QLabel("label", centralWidget);

  // get ColumnCount
  QFile* qFile =
      new QFile(QCoreApplication::applicationDirPath() + "/config.json");
  qFile->open(QIODevice::ReadOnly | QIODevice::Text);
  QString       qString       = qFile->readAll();
  QJsonDocument qJsonDocument = QJsonDocument::fromJson(qString.toUtf8());
  int           columnCount   = qJsonDocument.array().count();
  qFile->close();

  qTableWidget->setColumnCount(columnCount + 3);
  qTableWidget->setRowCount(1);
  QLineEdit lineEdit;

  qTableWidget->verticalHeader()->hide();
  qTableWidget->setHorizontalHeaderItem(0,
                                        new QTableWidgetItem(QString("Price")));
  qTableWidget->setHorizontalHeaderItem(5,
                                        new QTableWidgetItem(QString("红包")));
  qTableWidget->setItem(0, 5, new QTableWidgetItem(QString("0")));
  qTableWidget->setHorizontalHeaderItem(6,
                                        new QTableWidgetItem(QString("尾款")));
  for (int i = 0; i < columnCount; ++i) {
    QJsonObject result = qJsonDocument.array().at(i).toObject();

    QTableWidgetItem* qTableWidgetItemCouponName =
        new QTableWidgetItem(QString(result.value("name").toString()));
    qTableWidget->setHorizontalHeaderItem(i + 1, qTableWidgetItemCouponName);
    QTableWidgetItem* qTableWidgetItemCoupon =
        new QTableWidgetItem(QString(result.value("front").toString() + "-" +
                                     result.value("behind").toString()));
    qTableWidgetItemCoupon->setFlags(qTableWidgetItemCoupon->flags() &
                                     ~Qt::ItemIsEditable);
    qTableWidget->setItem(0, i + 1, qTableWidgetItemCoupon);
  }

  connect(qTableWidget, &QTableWidget::itemChanged, [=]() {
    qTableWidget->blockSignals(true);

    if (!isDigitString(qTableWidget->item(0, 0)->text())) {
      QMessageBox::warning(qTableWidget, "warning", "It isn't a int!");
      return;
    }

    // remove  "店铺优惠券" and "秒杀优惠券"
    QVector<int> shopCouponColumn(qTableWidget->horizontalHeader()->count());
    shopCouponColumn[0] = 0;
    QVector<int> vectorBehind;
    QVector<int> vectorFront;
    int          sumOtherCoupon = 0;
    int          price          = qTableWidget->item(0, 0)->text().toInt();
    for (int i = 1; i < shopCouponColumn.size() - 2; ++i) {
      QString headerItemName = qTableWidget->horizontalHeaderItem(i)->text();
      if (headerItemName == "店铺优惠券" or headerItemName == "秒杀优惠券")
        shopCouponColumn[i] = i;
      else {
        QJsonObject result      = qJsonDocument.array().at(i - 1).toObject();
        int         valueFront  = result.value("front").toString().toInt();
        int         valueBehind = result.value("behind").toString().toInt();
        vectorFront.append(valueFront);
        vectorBehind.append(valueBehind);
        if (headerItemName == "购物津贴")
          sumOtherCoupon += (price / valueFront) * valueBehind;
        else if (headerItemName == "定金膨胀")
          sumOtherCoupon += valueBehind;
      }
    }
    shopCouponColumn.removeAll(0);
    for (int i = 0; i < shopCouponColumn.size(); ++i) {
      qTableWidget->removeColumn(shopCouponColumn[i] - i);
    }
    for (int j = 0; j < vectorBehind.count(); ++j) {
      qTableWidget->setItem(
          0, j + 1,
          new QTableWidgetItem(QString::number(vectorFront[j]) + "-" +
                               QString::number(vectorBehind[j])));
    }
    QVector<int>     listFront(columnCount);
    QVector<int>     listBehind(columnCount);
    QVector<QString> maxCoupon = getMaxShopCoupon(qJsonDocument, price);

    qTableWidget->insertColumn(1);
    qTableWidget->setHorizontalHeaderItem(1,
                                          new QTableWidgetItem(maxCoupon[0]));
    qTableWidget->setItem(
        0, 1, new QTableWidgetItem(maxCoupon[1] + "-" + maxCoupon[2]));

    int redPack = qTableWidget->item(0, 4)->text().toInt();
    int endPay  = price - maxCoupon[2].toInt() - sumOtherCoupon - redPack;
    qTableWidget->setItem(0, qTableWidget->columnCount() - 1,
                          new QTableWidgetItem(QString::number(endPay)));

    qTableWidget->blockSignals(false);
  });

  qvBoxLayout->addWidget(qTableWidget);
  qvBoxLayout->addWidget(qLabel);

  this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

bool MainWindow::isDigitString(const QString& src) {
  const char* s = src.toUtf8().data();
  while (*s && *s >= '0' && *s <= '9') s++;
  return !bool(*s);
}

QVector<QString> MainWindow::getMaxShopCoupon(QJsonDocument qJsonDocument,
                                              int           intPrice) {
  int                       columnCount = qJsonDocument.array().count();
  QVector<QVector<QString>> shopCoupons;
  shopCoupons.resize(columnCount);
  for (int i = 0; i < columnCount; i++) {
    shopCoupons[i].resize(3);
    QJsonObject result     = qJsonDocument.array().at(i).toObject();
    QString     couponName = result.value("name").toString();
    if (couponName == "店铺优惠券" or couponName == "秒杀优惠券") {
      if (intPrice >= result.value("front").toString().toInt()) {
        shopCoupons[i] = {couponName, result.value("front").toString(),
                          result.value("behind").toString()};
      }
    }
  }
  //  remove QVector("", "", "")
  shopCoupons.removeAll(QVector<QString>(3, ""));
  //  qDebug() << shopCoupons;
  //  QVector(
  //    QVector("店铺优惠券", "2000", "100"),
  //    QVector("秒杀优惠券", "3000", "300")
  //    )

  int              max = 0;
  QVector<QString> maxCoupon(3);
  for (int j = 0; j < shopCoupons.size(); ++j) {
    if (shopCoupons[j][2].toInt() > max) {
      max = shopCoupons[j][2].toInt();
      for (int k = 0; k < 3; ++k) {
        maxCoupon[k] = shopCoupons[j][k];
      }
    }
  }

  //  QVector("秒杀优惠券", "3000", "300")
  return maxCoupon;
}
