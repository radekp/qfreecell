/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---                

            Last generated: Fri Jul 14 12:52:10 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "cselectgamedlg.h"

void  CSelectGameDlg::initDialog(){
  this->resize(200,120);
  this->setMinimumSize(0,0);
  this->setFocus();
  QGroupBox_1= new QGroupBox(this);
  QGroupBox_1->setGeometry(10,10,180,100);
  QGroupBox_1->setMinimumSize(0,0);
  QGroupBox_1->setTitle("");

  QPushButton_1= new QPushButton(this);
  QPushButton_1->setGeometry(20,70,70,23);
  QPushButton_1->setMinimumSize(0,0);
  QPushButton_1->setText("OK");

  QLabel_1= new QLabel(this);
  QLabel_1->setGeometry(20,30,50,23);
  QLabel_1->setMinimumSize(0,0);
  QLabel_1->setText("Game:");

  QSpinBox_1= new QSpinBox(this);
  QSpinBox_1->setGeometry(70,30,70,23);
  QSpinBox_1->setMinimumSize(0,0);
  QSpinBox_1->setRange(1,50000);

  QPushButton_ABORT= new QPushButton(this);
  QPushButton_ABORT->setGeometry(110,70,70,23);
  QPushButton_ABORT->setMinimumSize(0,0);
  QPushButton_ABORT->setText("Abort");

}