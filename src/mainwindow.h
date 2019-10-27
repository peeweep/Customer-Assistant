//
// Created by peeweep on 2019-10-15.
//
#ifndef CUSTOMER_ASSISTANT_MAINWINDOW_H
#define CUSTOMER_ASSISTANT_MAINWINDOW_H
#include <QMainWindow>
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  bool isDigitString(const QString& src);
  QVector<QString> getMaxShopCoupon(QJsonDocument qJsonDocument, int intPrice);
};

#endif  // CUSTOMER_ASSISTANT_MAINWINDOW_H