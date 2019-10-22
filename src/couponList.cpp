//
// Created by peeweep on 2019-10-18.
//
#include "couponList.h"
#include <QComboBox>
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
  comboBox->addItem("店铺优惠券");
  comboBox->addItem("天猫品类券");
  comboBox->addItem("购物津贴");
  comboBox->addItem("预售付定金");
  comboBox->addItem("秒杀优惠券(不与店铺优惠券叠加)");
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
    } else if ((lineEditNumberFront->text()).toInt() <
               lineEditNumberBehind->text().toInt()) {
      QMessageBox::warning(
          this, "error!",
          "The number in front is not greater than the number in the back");
    } else {
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
      QJsonArray* jsonArray   = new QJsonArray();
      QJsonArray  qJsonArray;
      qJsonArray.append(qJsonObject);
      QJsonDocument* jsonDocument = new QJsonDocument(qJsonArray);
      qDebug() << qJsonObject;

      // write id/name/front/behind to ./${id}.json.tmp

      QFile      tmpFile(QDir::homePath() + QString("/%1.json.tmp").arg(id));
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
      QFile*     idFile     = new QFile(QDir::homePath() + "/id.tmp");
      QFileInfo* idFileInfo = new QFileInfo(*idFile);
      if (idFile->open(QIODevice::Append)) {
        QTextStream stream(idFile);
        stream << id << "\n";
        idFile->close();
      } else {
        // cant rw
        qDebug() << QString("%1 File open error").arg(idFileInfo->fileName());
      }
    }
  });
}
CouponList::~CouponList() {}
