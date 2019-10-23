//
// Created by peeweep on 2019-10-15.
//
#include "preference.h"
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QLayout>
#include <QLineEdit>
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
//    connect(widgetCoupon1, SIGNAL(returnIndexString(QString text);),
//            [=]() { qDebug() << "text"; });

  //  Coupon 2
  CouponList* widgetCoupon2 = new CouponList(widgetCouponList);

  //  Coupon 3
  CouponList* widgetCoupon3 = new CouponList(widgetCouponList);

  //  Coupon 4
  CouponList* widgetCoupon4 = new CouponList(widgetCouponList);

  //  Coupon 5
  CouponList* widgetCoupon5 = new CouponList(widgetCouponList);

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
    //    cleanTmpFile();
    qDebug() << "Save";
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
  this->show();
}

Preference::~Preference() {}
QComboBox* Preference::copyComboBoxItem(QComboBox* qComboBox) {
  QComboBox* comboBox = new QComboBox(qComboBox->parentWidget());
  for (int i = 0; i < qComboBox->count(); ++i) {
    comboBox->addItem(qComboBox->itemText(i));
  }
  return comboBox;
}
int Preference::getLongestItem(QComboBox* qComboBox) {
  int max = 0;
  for (int i = 0; i < qComboBox->count(); ++i) {
    max = qComboBox->itemText(i).length() > max
              ? qComboBox->itemText(i).length()
              : max;
  }
  return max;
}
void Preference::cleanTmpFile() {
  // remove *.tmp file
  QDir        dir(QDir::currentPath());
  QStringList filters("*.tmp");
  dir.setFilter(QDir::Files | QDir::NoSymLinks);
  dir.setNameFilters(filters);
  for (int i = 0; i < dir.entryList().count(); ++i) {
    QFile::remove(dir.entryInfoList()[0].absoluteFilePath());
  }
}
