//
// Created by peeweep on 2019-10-15.
//
#include "about.h"
#include <QIcon>
About::About(QWidget* parent) {
  // Set title and icon
  QString title = "About";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));
}
About::~About() {}