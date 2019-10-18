//
// Created by peeweep on 2019-10-18.
//

#include "errorDialog.h"
#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QSpacerItem>
ErrorDialog::ErrorDialog(const QString strError, QWidget* parent) {
  QPushButton* btnError    = new QPushButton(strError, this);
  QHBoxLayout* layoutError = new QHBoxLayout(this);
  QSpacerItem* spacerItem  = new QSpacerItem(20, 20, QSizePolicy::Expanding);

  layoutError->addSpacerItem(spacerItem);
  layoutError->addWidget(btnError);
  layoutError->addSpacerItem(spacerItem);

  this->setFixedSize(400, 200);
  this->setWindowTitle("error");
  connect(btnError, &QPushButton::clicked, [=]() { this->close(); });
}

ErrorDialog::~ErrorDialog() {}