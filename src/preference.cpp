//
// Created by peeweep on 2019-10-15.
//
#include "preference.h"
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLayout>
#include <QCoreApplication>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpacerItem>
#include "couponList.h"
Preference::Preference(QWidget* parent) {
  // Set title and icon
  QString title = "Edit Preference";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));
  this->resize(1000, 1000);
  //  this->resize(570, 480);

  QWidget*     widgetDefault      = new QWidget(this);
  QVBoxLayout* qvBoxLayoutDefault = new QVBoxLayout(widgetDefault);

  // Choose Coupons
  QWidget*     widgetCouponList      = new QWidget(widgetDefault);
  QVBoxLayout* qvBoxLayoutCouponList = new QVBoxLayout(widgetCouponList);

  //  Coupon 1
  CouponList* widgetCoupon1 = new CouponList(widgetCouponList);

  //  Coupon 2
  CouponList* widgetCoupon2 = new CouponList(widgetCouponList);

  //  Coupon 3
  CouponList* widgetCoupon3 = new CouponList(widgetCouponList);

  //  Coupon 4
  CouponList* widgetCoupon4 = new CouponList(widgetCouponList);

  //  Coupon 5
  CouponList* widgetCoupon5 = new CouponList(widgetCouponList);

  //  Coupon 6
  CouponList* widgetCoupon6 = new CouponList(widgetCouponList);

  //  Coupon 7
  CouponList* widgetCoupon7 = new CouponList(widgetCouponList);

  //  Coupon 8
  CouponList* widgetCoupon8 = new CouponList(widgetCouponList);

  //  Coupon 9
  CouponList* widgetCoupon9 = new CouponList(widgetCouponList);

  //  Coupon 10
  CouponList* widgetCoupon10 = new CouponList(widgetCouponList);

  qvBoxLayoutCouponList->addWidget(widgetCoupon1);
  qvBoxLayoutCouponList->addWidget(widgetCoupon2);
  qvBoxLayoutCouponList->addWidget(widgetCoupon3);
  qvBoxLayoutCouponList->addWidget(widgetCoupon4);
  qvBoxLayoutCouponList->addWidget(widgetCoupon5);

  // SpacerItem SaveButton SpacerItem CancelButton SpacerItem
  QWidget*     widgetAction      = new QWidget(this);
  QHBoxLayout* qhBoxLayoutAction = new QHBoxLayout(widgetAction);
  QSpacerItem* qSpacerItem    = new QSpacerItem(20, 20, QSizePolicy::Expanding);
  QPushButton* btnSave        = new QPushButton("Save", widgetAction);
  QSpacerItem* qSpacerItemMid = new QSpacerItem(20, 20);
  QPushButton* btnCancel      = new QPushButton("Cancel", widgetAction);
  connect(btnSave, &QPushButton::clicked, [=]() {
    mergeJson();
    //    cleanTmpFile();
  });
  connect(btnCancel, &QPushButton::clicked, [=]() { this->close(); });

  qhBoxLayoutAction->addSpacerItem(qSpacerItem);
  qhBoxLayoutAction->addWidget(btnSave);
  qhBoxLayoutAction->addSpacerItem(qSpacerItemMid);
  qhBoxLayoutAction->addWidget(btnCancel);
  qhBoxLayoutAction->addSpacerItem(qSpacerItem);

  qvBoxLayoutDefault->addWidget(widgetCouponList);
  qvBoxLayoutDefault->addWidget(widgetAction);
  this->setLayout(qvBoxLayoutDefault);
  //  this->show();
}

Preference::~Preference() {}

void Preference::cleanTmpFile() {
  // remove *.tmp file
  QDir        dir(QCoreApplication::applicationDirPath());
  QStringList filters("*.tmp");
  dir.setFilter(QDir::Files | QDir::NoSymLinks);
  dir.setNameFilters(filters);
  for (int i = 0; i < dir.entryList().count(); ++i) {
    qDebug() << "remove " << dir.entryInfoList()[i].absoluteFilePath();
    QFile::remove(dir.entryInfoList()[i].absoluteFilePath());
  }
  qDebug() << "Clean";
}

void Preference::mergeJson() {
  //   Filter *.json.tmp
  QDir        dir(QCoreApplication::applicationDirPath());
  QStringList filters("*.json.tmp");
  dir.setFilter(QDir::Files | QDir::NoSymLinks);
  dir.setNameFilters(filters);
  QJsonArray qJsonArray;

  // get all content in *.json.tmp and delete it
  for (int i = 0; i < dir.entryList().count(); ++i) {
    qDebug() << "current: " << dir.entryInfoList()[i].absoluteFilePath();
    QFile* qFile = new QFile(dir.entryInfoList()[i].absoluteFilePath());
    if (qFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
      QString       qString       = qFile->readAll();
      QJsonDocument qJsonDocument = QJsonDocument::fromJson(qString.toUtf8());
      QJsonObject   result        = qJsonDocument.array().at(0).toObject();
      qDebug() << "result: " << result;
      qJsonArray.append(result);
      qDebug() << "qJsonArray: " << qJsonArray;
    } else {
      QMessageBox::warning(this, "warning",
                           QString("Does not have read permission for %1")
                               .arg(dir.entryInfoList()[i].absoluteFilePath()));
    }
    qFile->remove();
  }

  // delete id.tmp
  QFile* qFile = new QFile(QCoreApplication::applicationDirPath() + "/id.tmp");
  qFile->remove();

  // Save json to config.json
  //   [{arg1:arg,arg2:arg},{arg1:arg,arg2:arg}]
  QJsonDocument* jsonDocument = new QJsonDocument(qJsonArray);
  qDebug() << jsonDocument;
  qDebug() << jsonDocument->toJson();
  if (jsonDocument->toJson() == "[\n]\n") {
    QMessageBox::warning(this, "warning", "No new settings");
  } else {
    //    QJsonObject result = jsonDocument->object();
    //    qDebug() << result;
    QString configFilePath = QCoreApplication::applicationDirPath() + "/config.json";
    QFile*  qFile          = new QFile(configFilePath);
    if (qFile->open(QIODevice::WriteOnly)) {
      qFile->write(jsonDocument->toJson());
      qFile->close();
      qDebug() << "Save";
    } else {
      QMessageBox::warning(
          this, "warning",
          QString("Does not have write permission for %1").arg(configFilePath));
    }
  }
}
