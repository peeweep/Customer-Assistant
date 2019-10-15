//
// Created by peeweep on 2019-10-15.
//
#include "preference.h"
#include <QIcon>
#include <QMenuBar>
Preference::Preference(QWidget* parent) {
  // Set title and icon
  QString title = "Edit Preference";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));
}
Preference::~Preference() {}
