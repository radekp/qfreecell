/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---                

            Last generated: Fri Jul 14 12:52:15 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "ccongratulation.h"

void  CCongratulation::initDialog(){
  this->resize(220,130);
  this->setMinimumSize(0,0);
  QGroupBox_1= new QGroupBox(this);
  QGroupBox_1->setGeometry(10,10,200,110);
  QGroupBox_1->setMinimumSize(0,0);
  QGroupBox_1->setTitle("");

  QLabel_1= new QLabel(this);
  QLabel_1->setGeometry(60,20,110,23);
  QLabel_1->setMinimumSize(0,0);
  QLabel_1->setText("Congratulations!");

  QLabel_2= new QLabel(this);
  QLabel_2->setGeometry(30,40,160,23);
  QLabel_2->setMinimumSize(0,0);
  QLabel_2->setText("You have won this game!");

  QPushButton_OK= new QPushButton(this);
  QPushButton_OK->setGeometry(70,80,70,23);
  QPushButton_OK->setMinimumSize(0,0);
  QPushButton_OK->setText("OK");

}
