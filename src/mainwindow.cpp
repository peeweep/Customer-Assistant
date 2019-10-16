//
// Created by peeweep on 2019-10-15.
//
#include "mainwindow.h"
#include <QMenuBar>
#include "about.h"
#include "preference.h"
MainWindow::MainWindow(QWidget* parent) {
  // Set title and icon
  QString title = "Customer Assistant";
  this->setWindowTitle(title);
  this->setWindowIcon(QPixmap(":/logo.png"));

  // enable MenuBar
  QMenuBar* qMenuBar = menuBar();
  setMenuBar(qMenuBar);

  // Add menu "start" in  Menubar
  QMenu* menuStart = qMenuBar->addMenu("Start");

  // Add action "Edit Preference" under "start" menu
  QAction* actionPreference = menuStart->addAction("Edit Preference");
  // show preference When click "Close"
  Preference* preference = new Preference(menuStart);
  connect(actionPreference, &QAction::triggered, [=]() { preference->show(); });

  // Add action "Close" under "start" menu
  QAction* actionClose = menuStart->addAction("Close");
  // Close Program When click "Close"
  connect(actionClose, &QAction::triggered, [=]() { this->close(); });

  // Add menu "About"
  QMenu* menuAbout = qMenuBar->addMenu("About");
  // Add action "About" under "About" menu
  QAction* actionAbout = menuAbout->addAction("About");
  // show About When click "About"
  About* about = new About(menuAbout);
  connect(actionAbout, &QAction::triggered, [=]() { about->exec(); });
}
MainWindow::~MainWindow() {}