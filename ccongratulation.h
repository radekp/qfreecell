/***************************************************************************
                          ccongratulation.h  -  description
                             -------------------
    begin                : Sat Jul 8 2000
    copyright            : (C) 2000 by Daniel Etzold
    email                : dan@etzi.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CCONGRATULATION_H
#define CCONGRATULATION_H

//Generated area. DO NOT EDIT!!!(begin)
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
//Generated area. DO NOT EDIT!!!(end)

#include <qdialog.h>
#include "main.h"

/**
  *@author Daniel Etzold
  */

class CCongratulation : public QDialog  {
   Q_OBJECT
public: 
	CCongratulation(QWidget *parent=0, const char *name=0);
	~CCongratulation();

protected: 
	void initDialog();
	//Generated area. DO NOT EDIT!!!(begin)
	QGroupBox *QGroupBox_1;
	QLabel *QLabel_1;
	QLabel *QLabel_2;
	QPushButton *QPushButton_OK;
	//Generated area. DO NOT EDIT!!!(end)

private: 
};

#endif
