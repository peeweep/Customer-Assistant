//
// Created by peeweep on 2019-10-15.
//
#ifndef CUSTOMER_ASSISTANT_PREFERENCE_H
#define CUSTOMER_ASSISTANT_PREFERENCE_H
#include <QComboBox>
#include <QWidget>
class Preference : public QWidget {
  Q_OBJECT
 public:
  Preference(QWidget *parent = nullptr);
  ~Preference();

  // Copy comboBox item
  static QComboBox *copyComboBoxItem(QComboBox *qComboBox);
  // get longest item
  int getLongestItem(QComboBox *qComboBox);
  //  Clean *.tmp
  void cleanTmpFile();
};
#endif  // CUSTOMER_ASSISTANT_PREFERENCE_H
