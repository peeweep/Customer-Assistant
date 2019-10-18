//
// Created by peeweep on 2019-10-18.
//

#include "couponList.h"
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolButton>
#include "errorDialog.h"
CouponList::CouponList(QWidget* parent) {
  QWidget*     widgetCoupon1      = new QWidget(this);
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


}

CouponList::~CouponList() {}
