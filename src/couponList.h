//
// Created by peeweep on 2019-10-18.
//

#ifndef CUSTOMER_ASSISTANT_COUPONLIST_H
#define CUSTOMER_ASSISTANT_COUPONLIST_H
#include <QWidget>
class CouponList : public QWidget {
  Q_OBJECT
 public:
  CouponList(QString label_1, QString label_2, QWidget* parent = nullptr);
  ~CouponList();
};

#endif  // CUSTOMER_ASSISTANT_COUPONLIST_H
