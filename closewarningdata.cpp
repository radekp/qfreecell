/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---                

            Last generated: Fri Jul 14 12:52:21 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "closewarning.h"

void  CLoseWarning::initDialog(){
  this->resize(190,110);
  this->setMinimumSize(0,0);
  QGroupBox_1= new QGroupBox(this,"NoName");
  QGroupBox_1->setGeometry(10,10,170,90);
  QGroupBox_1->setMinimumSize(0,0);
  QGroupBox_1->setTitle("");

  QLabel_1= new QLabel(this,"NoName");
  QLabel_1->setGeometry(20,20,150,23);
  QLabel_1->setMinimumSize(0,0);
  QLabel_1->setText("You will lose this game!");

  QPushButton_YES= new QPushButton(this,"NoName");
  QPushButton_YES->setGeometry(20,60,60,23);
  QPushButton_YES->setMinimumSize(0,0);
  QPushButton_YES->setText("Yes!");

  QPushButton_UPS= new QPushButton(this,"NoName");
  QPushButton_UPS->setGeometry(100,60,60,23);
  QPushButton_UPS->setMinimumSize(0,0);
  QPushButton_UPS->setText("Ups");

}
