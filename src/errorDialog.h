//
// Created by peeweep on 2019-10-18.
//

#ifndef CUSTOMER_ASSISTANT_ERRORDIALOG_H
#define CUSTOMER_ASSISTANT_ERRORDIALOG_H
#include <QDialog>
class ErrorDialog : public QDialog {
  Q_OBJECT
 public:
  ErrorDialog(const QString strError, QWidget* parent = nullptr);
  ~ErrorDialog();
};

#endif  // CUSTOMER_ASSISTANT_ERRORDIALOG_H
