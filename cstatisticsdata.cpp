/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---                

            Last generated: Fri Jul 14 13:55:26 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "cstatistics.h"

void  CStatistics::initDialog(){
  this->resize(220,230);
  this->setMinimumSize(0,0);
  QGroupBox_1= new QGroupBox(this);
  QGroupBox_1->setGeometry(10,10,200,180);
  QGroupBox_1->setMinimumSize(0,0);
  QGroupBox_1->setTitle("");

  QLabel_1= new QLabel(this);
  QLabel_1->setGeometry(20,20,40,23);
  QLabel_1->setMinimumSize(0,0);
  QLabel_1->setText("Won:");

  QLabel_2= new QLabel(this);
  QLabel_2->setGeometry(20,50,40,23);
  QLabel_2->setMinimumSize(0,0);
  QLabel_2->setText("Lost:");

  QPushButton_OK= new QPushButton(this);
  QPushButton_OK->setGeometry(10,200,60,23);
  QPushButton_OK->setMinimumSize(0,0);
  QPushButton_OK->setText("OK");

  QPushButton_RESET= new QPushButton(this);
  QPushButton_RESET->setGeometry(150,200,60,23);
  QPushButton_RESET->setMinimumSize(0,0);
  QPushButton_RESET->setText("Reset");

  QLabel_3= new QLabel(this);
  QLabel_3->setGeometry(20,90,100,23);
  QLabel_3->setMinimumSize(0,0);
  QLabel_3->setText("This session");

  QLabel_4= new QLabel(this);
  QLabel_4->setGeometry(20,120,40,23);
  QLabel_4->setMinimumSize(0,0);
  QLabel_4->setText("Won:");

  QLabel_5= new QLabel(this);
  QLabel_5->setGeometry(20,150,40,23);
  QLabel_5->setMinimumSize(0,0);
  QLabel_5->setText("Lost:");

  QLabel_WonAll= new QLabel(this);
  QLabel_WonAll->setGeometry(90,20,40,23);
  QLabel_WonAll->setMinimumSize(0,0);
  QLabel_WonAll->setText("0");

  QLabel_LostAll= new QLabel(this);
  QLabel_LostAll->setGeometry(90,50,50,23);
  QLabel_LostAll->setMinimumSize(0,0);
  QLabel_LostAll->setText("0");

  QLabel_WonSession= new QLabel(this);
  QLabel_WonSession->setGeometry(90,120,50,23);
  QLabel_WonSession->setMinimumSize(0,0);
  QLabel_WonSession->setText("0");

  QLabel_LostSession= new QLabel(this);
  QLabel_LostSession->setGeometry(90,150,50,23);
  QLabel_LostSession->setMinimumSize(0,0);
  QLabel_LostSession->setText("0");

  QLabel_WonAllPercent= new QLabel(this);
  QLabel_WonAllPercent->setGeometry(150,20,50,23);
  QLabel_WonAllPercent->setMinimumSize(0,0);
  QLabel_WonAllPercent->setText("0%");

  QLabel_WonSessionPercent= new QLabel(this);
  QLabel_WonSessionPercent->setGeometry(150,120,50,23);
  QLabel_WonSessionPercent->setMinimumSize(0,0);
  QLabel_WonSessionPercent->setText("0%");

}
