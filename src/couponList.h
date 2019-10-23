//
// Created by peeweep on 2019-10-18.
//

#ifndef CUSTOMER_ASSISTANT_COUPONLIST_H
#define CUSTOMER_ASSISTANT_COUPONLIST_H
#include <QFile>
#include <QWidget>
class CouponList : public QWidget {
  Q_OBJECT
 public:
  CouponList(QWidget* parent = nullptr);
  ~CouponList();
  QStringList getItemName(QFile* idFile);
};

#endif  // CUSTOMER_ASSISTANT_COUPONLIST_H
