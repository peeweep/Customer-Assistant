//
// Created by peeweep on 2019-10-15.
//
#include "mainwindow.h"
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
  QString configFilePath = QDir::currentPath() + "/config.json";
  QFile*  qFile          = new QFile(configFilePath);
  qFile->open(QIODevice::ReadOnly | QIODevice::Text);
  QString       qString       = qFile->readAll();
  QJsonDocument qJsonDocument = QJsonDocument::fromJson(qString.toUtf8());
  int           columnCount   = qJsonDocument.array().count();
  qFile->close();

  qTableWidget->setColumnCount(columnCount + 2);
  qTableWidget->setRowCount(2);
  QLineEdit         lineEdit;
  QTableWidgetItem* qTableWidgetItem = new QTableWidgetItem(QString("0,1"));

  qTableWidget->verticalHeader()->hide();
  qTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("")));
  qTableWidget->setItem(0, 0, new QTableWidgetItem(QString("Price")));
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

    if (!isDigitString(qTableWidget->item(1, 0)->text())) {
      QMessageBox::warning(qTableWidget, "warning", "It isn't a int!");
    } else {
      QVector<int> listFront(columnCount);
      QVector<int> listBehind(columnCount);
      QVector<int> listResult(columnCount);
      for (int i = 0; i < columnCount; ++i) {
        QJsonObject result = qJsonDocument.array().at(i).toObject();
        listFront[i]       = result.value("front").toInt();
        listBehind[i]      = result.value("behind").toInt();
        if (result.value("name").toString() == "定金膨胀") {
          listResult[i] =
              result.value("behind").toInt() - result.value("front").toInt();
        } else {
          listResult[i] =
              result.value("front").toInt() - result.value("behind").toInt();
        }
      }
      for (int i = 0; i < columnCount; ++i) {
        QTableWidgetItem* qTableWidgetItemNumber =
            new QTableWidgetItem(QString::number(listResult[i]));
        qTableWidgetItemNumber->setFlags(qTableWidgetItemNumber->flags() &
                                         ~Qt::ItemIsEditable);
        qTableWidget->setItem(1, i + 1, qTableWidgetItemNumber);
      }
    }

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
