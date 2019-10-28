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
  this->resize(1400, 720);

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
  QLabel*       qLabel = new QLabel("peeweep at 0x0 dot ee", centralWidget);

  // get ColumnCount
  QFile* qFile =
      new QFile(QCoreApplication::applicationDirPath() + "/config.json");
  qFile->open(QIODevice::ReadOnly | QIODevice::Text);
  QString       qString       = qFile->readAll();
  QJsonDocument qJsonDocument = QJsonDocument::fromJson(qString.toUtf8());
  int           jsonCount     = qJsonDocument.array().count();
  qFile->close();
  // HorizontalHeader: 预售价格 couponNames 红包 尾款 到手价
  qTableWidget->setColumnCount(jsonCount + 4);
  qTableWidget->setRowCount(1);
  QLineEdit lineEdit;

  qTableWidget->verticalHeader()->hide();
  // Begin set HorizontalHeader
  qTableWidget->setHorizontalHeaderItem(
      0, new QTableWidgetItem(QString("预售价格")));
  int columnRedPack = jsonCount + 1;
  qTableWidget->setHorizontalHeaderItem(columnRedPack,
                                        new QTableWidgetItem(QString("红包")));
  qTableWidget->setItem(0, columnRedPack, new QTableWidgetItem(QString("0")));
  int columnEndPay = columnRedPack + 1;
  qTableWidget->setHorizontalHeaderItem(columnEndPay,
                                        new QTableWidgetItem(QString("尾款")));
  int columnHandPrice = columnRedPack + 2;
  qTableWidget->setHorizontalHeaderItem(
      columnHandPrice, new QTableWidgetItem(QString("到手价")));
  // Finish set HorizontalHeader

  for (int i = 1; i <= jsonCount; ++i) {
    QJsonObject result = qJsonDocument.array().at(i - 1).toObject();

    // set HorizontalHeader
    QTableWidgetItem* qTableWidgetItemCouponName =
        new QTableWidgetItem(QString(result.value("name").toString()));
    qTableWidget->setHorizontalHeaderItem(i, qTableWidgetItemCouponName);
    // set Coupon value: Qstring(3000-300)
    QTableWidgetItem* qTableWidgetItemCoupon =
        new QTableWidgetItem(QString(result.value("front").toString() + "-" +
                                     result.value("behind").toString()));
    qTableWidgetItemCoupon->setFlags(qTableWidgetItemCoupon->flags() &
                                     ~Qt::ItemIsEditable);
    qTableWidget->setItem(0, i, qTableWidgetItemCoupon);
  }

  connect(qTableWidget, &QTableWidget::itemChanged, [=]() {
    qTableWidget->blockSignals(true);
    // check (0,0) value
    if (qTableWidget->item(0, 0) == 0x0) {
      QMessageBox::warning(qTableWidget, "warning", "输入正确的预售价格!");
      qTableWidget->blockSignals(false);
      return;
    } else if (!isDigitString(qTableWidget->item(0, 0)->text())) {
      QMessageBox::warning(qTableWidget, "warning", "输入正确的预售价格!");
      return;
    } else if (qTableWidget->item(0, 0)->text().toInt() <
               qTableWidget->item(0, columnRedPack)->text().toInt()) {
      QMessageBox::warning(qTableWidget, "warning",
                           "红包比商品额度还大，检查一下");
      return;
    }

    // behind numbers vector
    QVector<int> vectorBehind;
    // front numbers vector
    QVector<int> vectorFront;
    // All coupons except RedPack, Qvector{津贴,定金,定金膨胀后}
    QVector<int> allCouponsExceptRedPack(3);
    // get input price value
    int price = qTableWidget->item(0, 0)->text().toInt();

    // remove  "店铺优惠券" and "秒杀优惠券"
    //   Search from index 1 to index column

    QVector<int> columnShopCoupon(qTableWidget->columnCount() - 3);
    //    columnShopCoupon[0] = 0;
    for (int i = 1; i <= qTableWidget->columnCount() - 4; ++i) {
      QString headerItemName = qTableWidget->horizontalHeaderItem(i)->text();
      if (headerItemName == "店铺优惠券" or headerItemName == "秒杀优惠券")
        columnShopCoupon[i] = i;
      else {
        QJsonObject result      = qJsonDocument.array().at(i - 1).toObject();
        int         valueFront  = result.value("front").toString().toInt();
        int         valueBehind = result.value("behind").toString().toInt();
        vectorFront.append(valueFront);
        vectorBehind.append(valueBehind);
        if (headerItemName == "购物津贴") {
          allCouponsExceptRedPack[0] = (price / valueFront) * valueBehind;
        } else if (headerItemName == "定金膨胀") {
          allCouponsExceptRedPack[1] = valueFront;
          allCouponsExceptRedPack[2] = valueBehind;
        }
      }
    }
    columnShopCoupon.removeAll(0);
    for (int i = 0; i < columnShopCoupon.size(); ++i) {
      qTableWidget->removeColumn(columnShopCoupon[i] - i);
    }
    for (int j = 0; j < vectorBehind.count(); ++j) {
      qTableWidget->setItem(
          0, j + 1,
          new QTableWidgetItem(QString::number(vectorFront[j]) + "-" +
                               QString::number(vectorBehind[j])));
    }
    // get maxCoupon from all "店铺优惠券" and "秒杀优惠券"
    // maxCoupon:  QVector("秒杀优惠券", "3000", "300")
    QVector<QString> maxCoupon = getMaxShopCoupon(qJsonDocument, price);

    // begin setup shopCoupon On index 1
    qTableWidget->insertColumn(1);
    qTableWidget->setHorizontalHeaderItem(1,
                                          new QTableWidgetItem(maxCoupon[0]));
    QString shopCouponContent = maxCoupon[1] + "-" + maxCoupon[2];
    qTableWidget->setItem(0, 1, new QTableWidgetItem(shopCouponContent));
    // end setup shopCoupon

    int columnCount   = qTableWidget->columnCount();
    int columnRedPack = columnCount - 3;
    int redPack       = qTableWidget->item(0, columnRedPack)->text().toInt();
    // 付尾款 = 预售价格 - 优惠券 - 津贴 - 定金膨胀后
    int endPay = price - maxCoupon[2].toInt() - allCouponsExceptRedPack[0] -
                 allCouponsExceptRedPack[2];
    int columnEndPay = columnCount - 2;
    qTableWidget->setItem(0, columnEndPay,
                          new QTableWidgetItem(QString::number(endPay)));

    // 到手价 = 预售价格 - 优惠券 - 津贴 - （定金膨胀后 - 定金) - 红包
    int handPrice = price - maxCoupon[2].toInt() - allCouponsExceptRedPack[0] -
                    (allCouponsExceptRedPack[2] - allCouponsExceptRedPack[1]) -
                    redPack;
    int columnHandPrice = columnCount - 1;
    qTableWidget->setItem(0, columnHandPrice,
                          new QTableWidgetItem(QString::number(handPrice)));

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
