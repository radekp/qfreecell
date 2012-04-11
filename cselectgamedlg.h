/***************************************************************************
                          cselectgamedlg.h  -  description
                             -------------------
    begin                : Fri Jul 7 2000
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

#ifndef CSELECTGAMEDLG_H
#define CSELECTGAMEDLG_H

//Generated area. DO NOT EDIT!!!(begin)
#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>
//Generated area. DO NOT EDIT!!!(end)

#include <qdialog.h>
#include "main.h"

/**
  *@author Daniel Etzold
  */

class CSelectGameDlg : public QDialog  {
   Q_OBJECT
public: 
	CSelectGameDlg(QWidget *parent=0, const char *name=0);
	~CSelectGameDlg();

  /**  */
  int getGamenumber();
  /**  */
  void setGamenumber(int game);

public slots: // Public slots
  /**  */
  /**  */
  void abort();
  void buttonPressed();
protected: 
	void initDialog();
public: // Public attributes
  /**  */
  int gamenumber;
	//Generated area. DO NOT EDIT!!!(begin)
	QGroupBox *QGroupBox_1;
	QPushButton *QPushButton_1;
	QLabel *QLabel_1;
	QSpinBox *QSpinBox_1;
	QPushButton *QPushButton_ABORT;
	//Generated area. DO NOT EDIT!!!(end)

private: 
};

#endif
