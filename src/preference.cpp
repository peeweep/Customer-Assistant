//
// Created by peeweep on 2019-10-15.
//
#include "preference.h"
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolButton>
#include "couponList.h"
#include "errorDialog.h"
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
  QWidget*     widgetCoupon1      = new QWidget(widgetCouponList);
  QHBoxLayout* qhBoxLayoutCoupon1 = new QHBoxLayout(widgetCoupon1);
  QToolButton* qToolButton1       = new QToolButton(widgetCoupon1);
  QComboBox*   comboBox1          = new QComboBox(widgetCoupon1);
  QLabel*      lblCoupon1_1       = new QLabel("label_1", widgetCoupon1);
  QLineEdit*   lineEditCoupon1_1  = new QLineEdit(widgetCoupon1);
  QLabel*      lblCoupon1_2       = new QLabel("label_2", widgetCoupon1);
  QLineEdit*   lineEditCoupon1_2  = new QLineEdit(widgetCoupon1);

  qToolButton1->setIcon(QPixmap(":/plus.png"));

  comboBox1->addItem(nullptr);
  comboBox1->addItem("店铺优惠券");
  comboBox1->addItem("天猫品类券");
  comboBox1->addItem("购物津贴");
  comboBox1->addItem("预售付定金");
  comboBox1->addItem("秒杀优惠券(不与店铺优惠券叠加)");
  comboBox1->setSizeAdjustPolicy(QComboBox::AdjustToContents);

  qhBoxLayoutCoupon1->addWidget(qToolButton1);
  qhBoxLayoutCoupon1->addWidget(comboBox1);
  qhBoxLayoutCoupon1->addWidget(lblCoupon1_1);
  qhBoxLayoutCoupon1->addWidget(lineEditCoupon1_1);
  qhBoxLayoutCoupon1->addWidget(lblCoupon1_2);
  qhBoxLayoutCoupon1->addWidget(lineEditCoupon1_2);

  // Check value
  connect(qToolButton1, &QToolButton::clicked, [=]() {
    if (comboBox1->currentText() == "" || lineEditCoupon1_1->text() == "" ||
        lineEditCoupon1_2->text() == "") {
      ErrorDialog* diaError = new ErrorDialog("Incomplete", qToolButton1);
      diaError->exec();
    } else if ((lineEditCoupon1_1->text()).toInt() <
               lineEditCoupon1_2->text().toInt()) {
      ErrorDialog* diaError = new ErrorDialog(
          "The number in front is not greater than the number in the back",
          qToolButton1);
      diaError->exec();
    } else {
      QLabel* lblCouponNum1 = new QLabel(qToolButton1);
      QLabel* lblCouponNum2 = new QLabel(qToolButton1);
      lblCouponNum1->setText(lineEditCoupon1_1->text());
      lblCouponNum2->setText(lineEditCoupon1_2->text());
      qhBoxLayoutCoupon1->replaceWidget(lineEditCoupon1_1, lblCouponNum1);
      qhBoxLayoutCoupon1->replaceWidget(lineEditCoupon1_2, lblCouponNum2);
      qhBoxLayoutCoupon1->removeWidget(qToolButton1);
      qhBoxLayoutCoupon1->removeWidget(lineEditCoupon1_1);
      qhBoxLayoutCoupon1->removeWidget(lineEditCoupon1_2);
      delete lineEditCoupon1_1;
      delete lineEditCoupon1_2;
    }
  });

  //  Coupon 2

CouponList * widgetCoupon2 = new CouponList(widgetCouponList);
  //  QWidget*     widgetCoupon2      = new QWidget(widgetCouponList);
//  QHBoxLayout* qhBoxLayoutCoupon2 = new QHBoxLayout(widgetCoupon2);
//  QComboBox*   comboBox2          = copyComboBoxItem(comboBox1);
//  QLabel*      lblCoupon2_1       = new QLabel("label_1", widgetCoupon2);
//  QLineEdit*   lineEditCoupon2_1  = new QLineEdit(widgetCoupon2);
//  QLabel*      lblCoupon2_2       = new QLabel("label_2", widgetCoupon2);
//  QLineEdit*   lineEditCoupon2_2  = new QLineEdit(widgetCoupon2);
//
//  qhBoxLayoutCoupon2->addWidget(comboBox2);
//  qhBoxLayoutCoupon2->addWidget(lblCoupon2_1);
//  qhBoxLayoutCoupon2->addWidget(lineEditCoupon2_1);
//  qhBoxLayoutCoupon2->addWidget(lblCoupon2_2);
//  qhBoxLayoutCoupon2->addWidget(lineEditCoupon2_2);

  //  Coupon 3
  QWidget*     widgetCoupon3      = new QWidget(widgetCouponList);
  QHBoxLayout* qhBoxLayoutCoupon3 = new QHBoxLayout(widgetCoupon3);
  QComboBox*   comboBox3          = copyComboBoxItem(comboBox1);
  QLabel*      lblCoupon3_1       = new QLabel("label_1", widgetCoupon3);
  QLineEdit*   lineEditCoupon3_1  = new QLineEdit(widgetCoupon3);
  QLabel*      lblCoupon3_2       = new QLabel("label_2", widgetCoupon3);
  QLineEdit*   lineEditCoupon3_2  = new QLineEdit(widgetCoupon3);

  qhBoxLayoutCoupon3->addWidget(comboBox3);
  qhBoxLayoutCoupon3->addWidget(lblCoupon3_1);
  qhBoxLayoutCoupon3->addWidget(lineEditCoupon3_1);
  qhBoxLayoutCoupon3->addWidget(lblCoupon3_2);
  qhBoxLayoutCoupon3->addWidget(lineEditCoupon3_2);

  //  Coupon 4
  QWidget*     widgetCoupon4      = new QWidget(widgetCouponList);
  QHBoxLayout* qhBoxLayoutCoupon4 = new QHBoxLayout(widgetCoupon4);
  QComboBox*   comboBox4          = copyComboBoxItem(comboBox1);
  QLabel*      lblCoupon4_1       = new QLabel("label_1", widgetCoupon4);
  QLineEdit*   lineEditCoupon4_1  = new QLineEdit(widgetCoupon4);
  QLabel*      lblCoupon4_2       = new QLabel("label_2", widgetCoupon4);
  QLineEdit*   lineEditCoupon4_2  = new QLineEdit(widgetCoupon4);

  qhBoxLayoutCoupon4->addWidget(comboBox4);
  qhBoxLayoutCoupon4->addWidget(lblCoupon4_1);
  qhBoxLayoutCoupon4->addWidget(lineEditCoupon4_1);
  qhBoxLayoutCoupon4->addWidget(lblCoupon4_2);
  qhBoxLayoutCoupon4->addWidget(lineEditCoupon4_2);

  //  Coupon 5
  QWidget*     widgetCoupon5      = new QWidget(widgetCouponList);
  QHBoxLayout* qhBoxLayoutCoupon5 = new QHBoxLayout(widgetCoupon5);
  QComboBox*   comboBox5          = copyComboBoxItem(comboBox1);
  QLabel*      lblCoupon5_1       = new QLabel("label_1", widgetCoupon5);
  QLineEdit*   lineEditCoupon5_1  = new QLineEdit(widgetCoupon5);
  QLabel*      lblCoupon5_2       = new QLabel("label_2", widgetCoupon5);
  QLineEdit*   lineEditCoupon5_2  = new QLineEdit(widgetCoupon5);

  qhBoxLayoutCoupon5->addWidget(comboBox5);
  qhBoxLayoutCoupon5->addWidget(lblCoupon5_1);
  qhBoxLayoutCoupon5->addWidget(lineEditCoupon5_1);
  qhBoxLayoutCoupon5->addWidget(lblCoupon5_2);
  qhBoxLayoutCoupon5->addWidget(lineEditCoupon5_2);

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