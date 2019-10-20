//
// Created by peeweep on 2019-10-18.
//

#include "couponList.h"
#include <QComboBox>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolButton>
#include "errorDialog.h"
CouponList::CouponList(QString label_1, QString label_2, QWidget* parent) {
  QWidget*     widgetCoupon      = new QWidget(this);
  QHBoxLayout* qhBoxLayoutCoupon = new QHBoxLayout(widgetCoupon);
  QToolButton* qToolButton       = new QToolButton(widgetCoupon);
  QComboBox*   comboBox          = new QComboBox(widgetCoupon);
  QLabel*      lblCoupon_1       = new QLabel(label_1, widgetCoupon);
  QLineEdit*   lineEditCoupon_1  = new QLineEdit(widgetCoupon);
  QLabel*      lblCoupon_2       = new QLabel(label_2, widgetCoupon);
  QLineEdit*   lineEditCoupon_2  = new QLineEdit(widgetCoupon);

  qToolButton->setIcon(QPixmap(":/plus.png"));

  comboBox->addItem(nullptr);
  comboBox->addItem("店铺优惠券");
  comboBox->addItem("天猫品类券");
  comboBox->addItem("购物津贴");
  comboBox->addItem("预售付定金");
  comboBox->addItem("秒杀优惠券(不与店铺优惠券叠加)");
  comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

  qhBoxLayoutCoupon->addWidget(qToolButton);
  qhBoxLayoutCoupon->addWidget(comboBox);
  qhBoxLayoutCoupon->addWidget(lblCoupon_1);
  qhBoxLayoutCoupon->addWidget(lineEditCoupon_1);
  qhBoxLayoutCoupon->addWidget(lblCoupon_2);
  qhBoxLayoutCoupon->addWidget(lineEditCoupon_2);

  // Check value
  connect(qToolButton, &QToolButton::clicked, [=]() {
    if (comboBox->currentText() == "" || lineEditCoupon_1->text() == "" ||
        lineEditCoupon_2->text() == "") {
      ErrorDialog* diaError = new ErrorDialog("Incomplete", qToolButton);
      diaError->exec();
    } else if ((lineEditCoupon_1->text()).toInt() <
               lineEditCoupon_2->text().toInt()) {
      ErrorDialog* diaError = new ErrorDialog(
          "The number in front is not greater than the number in the back",
          qToolButton);
      diaError->exec();
    } else {
      QLabel* lblCouponNum1 = new QLabel(qToolButton);
      QLabel* lblCouponNum2 = new QLabel(qToolButton);
      lblCouponNum1->setText(lineEditCoupon_1->text());
      lblCouponNum2->setText(lineEditCoupon_2->text());
      qhBoxLayoutCoupon->replaceWidget(lineEditCoupon_1, lblCouponNum1);
      qhBoxLayoutCoupon->replaceWidget(lineEditCoupon_2, lblCouponNum2);
      qhBoxLayoutCoupon->removeWidget(qToolButton);
      qhBoxLayoutCoupon->removeWidget(lineEditCoupon_1);
      qhBoxLayoutCoupon->removeWidget(lineEditCoupon_2);
      delete lineEditCoupon_1;
      delete lineEditCoupon_2;
      comboBox->setDisabled(true);
    }
  });
}

CouponList::~CouponList() {}
