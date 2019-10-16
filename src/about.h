//
// Created by peeweep on 2019-10-15.
//

#ifndef CUSTOMER_ASSISTANT_ABOUT_H
#define CUSTOMER_ASSISTANT_ABOUT_H
#include <QDialog>

class About : public QDialog {
  Q_OBJECT
 public:
  About(QWidget *parent = nullptr);
  ~About();
};

#endif  // CUSTOMER_ASSISTANT_ABOUT_H