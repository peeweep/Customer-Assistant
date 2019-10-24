//
// Created by peeweep on 2019-10-18.
//
#include "couponList.h"
#include <QApplication>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>
CouponList::CouponList(QWidget* parent) {
  QWidget*     widgetCoupon         = new QWidget(this);
  QHBoxLayout* qhBoxLayoutCoupon    = new QHBoxLayout(widgetCoupon);
  QToolButton* qToolButton          = new QToolButton(widgetCoupon);
  QComboBox*   comboBox             = new QComboBox(widgetCoupon);
  QLineEdit*   lineEditNumberFront  = new QLineEdit(widgetCoupon);
  QLabel*      lblCoupon            = new QLabel("-", widgetCoupon);
  QLineEdit*   lineEditNumberBehind = new QLineEdit(widgetCoupon);
  qToolButton->setIcon(QPixmap(":/plus.png"));
  comboBox->addItem(nullptr);
  QFile* idFile = new QFile(QCoreApplication::applicationDirPath() + "/id.tmp");
  //  QFileInfo* idFileInfo = new QFileInfo(*idFile);

  // Filter exist coupon name in id.tmp and get remaining name
  QStringList nameList = getItemName(idFile);
  comboBox->addItems(nameList);
  //  ("","购物津贴", "预售付定金", "秒杀优惠券")
  comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  qhBoxLayoutCoupon->addWidget(qToolButton);
  qhBoxLayoutCoupon->addWidget(comboBox);
  qhBoxLayoutCoupon->addWidget(lineEditNumberFront);
  qhBoxLayoutCoupon->addWidget(lblCoupon);
  qhBoxLayoutCoupon->addWidget(lineEditNumberBehind);
  connect(qToolButton, &QToolButton::clicked, [=]() {
    if (comboBox->currentText() == "" || lineEditNumberFront->text() == "" ||
        lineEditNumberBehind->text() == "") {
      QMessageBox::warning(this, "Incomplete", "The number is incomplete");
    } else {
      if (comboBox->currentText() != "定金膨胀") {
        if (lineEditNumberFront->text().toInt() <
            lineEditNumberBehind->text().toInt()) {
          QMessageBox::warning(
              this, "error!",
              "The number in front is not greater than the number in the back");
          return;
        }
      } else if (comboBox->currentText() == "定金膨胀") {
        if (lineEditNumberFront->text().toInt() >
            lineEditNumberBehind->text().toInt()) {
          QMessageBox::warning(
              this, "error!",
              "The number in back is not greater than the number in the front");
          return;
        }
      }
      QLabel* lblCouponNum1 = new QLabel(qToolButton);
      QLabel* lblCouponNum2 = new QLabel(qToolButton);
      lblCouponNum1->setText(lineEditNumberFront->text());
      lblCouponNum2->setText(lineEditNumberBehind->text());
      qhBoxLayoutCoupon->replaceWidget(lineEditNumberFront, lblCouponNum1);
      qhBoxLayoutCoupon->replaceWidget(lineEditNumberBehind, lblCouponNum2);
      qhBoxLayoutCoupon->removeWidget(qToolButton);
      qhBoxLayoutCoupon->removeWidget(lineEditNumberFront);
      qhBoxLayoutCoupon->removeWidget(lineEditNumberBehind);
      delete lineEditNumberFront;
      delete lineEditNumberBehind;
      comboBox->setDisabled(true);
      int     id     = comboBox->currentIndex();
      QString idName = comboBox->currentText();
      int     front  = lblCouponNum1->text().toInt();
      int     behind = lblCouponNum2->text().toInt();

      QJsonObject qJsonObject = {{{"id", QString::number(id)},
                                  {"name", idName},
                                  {"front", QString::number(front)},
                                  {"behind", QString::number(behind)}}};
      QJsonArray  qJsonArray;
      qJsonArray.append(qJsonObject);
      QJsonDocument* jsonDocument = new QJsonDocument(qJsonArray);
      qDebug() << qJsonObject;
      // write id/name/front/behind to ./${time}.json.tmp
      QFile tmpFile(
          QCoreApplication::applicationDirPath() +
          QString("/%1.json.tmp")
              .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
      QFileInfo* tmpFileInfo = new QFileInfo(tmpFile);
      if (tmpFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        tmpFile.write(jsonDocument->toJson());
        tmpFile.close();
      } else {
        QMessageBox::warning(
            this, "error!",
            QString("%1 File open error").arg(tmpFileInfo->absoluteFilePath()));
      }

      // append id to id.tmp
      QFileInfo* idFileInfo = new QFileInfo(*idFile);
      if (idFile->open(QIODevice::Append)) {
        QTextStream stream(idFile);
        stream << idName << "\n";
        idFile->close();
      }
    }
  });
}
CouponList::~CouponList() {}
QStringList CouponList::getItemName(QFile* idFile) {
  if (idFile->open(QIODevice::ReadWrite)) {
    // read content from id.tmp, write to idFileNameList
    QTextStream stream(idFile);
    QString     idFileName     = stream.readAll();
    QStringList idFileNameList = idFileName.split("\n");
    // ("天猫品类券", "店铺优惠券", "")
    idFileNameList.removeLast();
    QVector<int> nameListFilter;
    QStringList  nameList = {"店铺优惠券", "天猫品类券", "购物津贴", "定金膨胀",
                            "秒杀优惠券"};

    if (idFileNameList.count() < nameList.count()) {
      for (int i = 0; i < nameList.count(); ++i) {
        for (int j = 0; j < idFileNameList.count(); ++j) {
          if (idFileNameList[j] == nameList[i]) {
            nameListFilter.append(i);
          }
        }
      }
    }
    //    QVector(0, 1)
    for (int k = 0; k < nameListFilter.count(); ++k) {
      nameList.replace(nameListFilter[k], "");
    }
    //    ("", "", "购物津贴", "预售付定金", "秒杀优惠券")
    nameList.removeAll("");
    //    ("购物津贴", "预售付定金", "秒杀优惠券")
    return nameList;
  } else {
    QFileInfo* qFileInfo = new QFileInfo(*idFile);
    QMessageBox::warning(
        this, "error!",
        QString("%1 File open error").arg(qFileInfo->absoluteFilePath()));
    exit(0);
  }
}
