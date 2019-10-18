//
// Created by peeweep on 2019-10-15.
//
#include "about.h"

#include <QBoxLayout>
#include <QFile>
#include <QIcon>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>
About::About(QWidget *parent) {
  // Set title and icon
  QString title = "About";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));
  this->resize(570, 480);

  QVBoxLayout *default_Layout = new QVBoxLayout(this);
  this->setLayout(default_Layout);

  // About/Source Code
  QTabWidget *tabWidget = new QTabWidget(this);
  QWidget *   tabAbout  = new QWidget(tabWidget);
  tabWidget->addTab(tabAbout, "About");
  tabAbout->setFixedWidth(this->width());
  QLabel *lblAbout = new QLabel(tabAbout);
  lblAbout->setText(
      "Customer Assistant @ MIT LICENSE\n"
      "peeweep <peeweep@0x0.ee>");

  QWidget *tabSource = new QWidget(tabWidget);
  QLabel * lblSource = new QLabel(tabSource);
  lblSource->setText(
      "<a "
      "href=https://github.com/peeweep/Customer-Assistant>peeweep/"
      "Customer-Assistant</a>");
  lblSource->setOpenExternalLinks(true);
  tabWidget->addTab(tabSource, "Source Code");

  // horizontalSpacer ButtonOK horizontalSpacer
  QWidget *    widget_OK  = new QWidget(this);
  QHBoxLayout *hLayout_OK = new QHBoxLayout(widget_OK);

  QSpacerItem *qSpacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding);

  QPushButton *btnOK = new QPushButton("OK", parent = widget_OK);
  connect(btnOK, &QPushButton::clicked, [=]() { this->close(); });

  hLayout_OK->addSpacerItem(qSpacerItem);
  hLayout_OK->addWidget(btnOK);
  hLayout_OK->addSpacerItem(qSpacerItem);

  default_Layout->addWidget(tabWidget);
  default_Layout->addWidget(widget_OK);
}
About::~About() {}