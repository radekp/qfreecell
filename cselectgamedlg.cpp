/***************************************************************************
                          cselectgamedlg.cpp  -  description
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
#include "cselectgamedlg.h"
#include <stdlib.h>

CSelectGameDlg::CSelectGameDlg(QWidget *parent, const char *name) : QDialog(parent){
	move(POS_X, POS_Y);
	initDialog();
	connect(QPushButton_1, SIGNAL(clicked()), this, SLOT(buttonPressed()));
	connect(QPushButton_ABORT, SIGNAL(clicked()), this, SLOT(abort()));
}

CSelectGameDlg::~CSelectGameDlg(){
}

/**  */
int CSelectGameDlg::getGamenumber()
{
return gamenumber;
}

/**  */
void CSelectGameDlg::buttonPressed()
{
        gamenumber = QSpinBox_1->value();
	accept();
}

/**  */
void CSelectGameDlg::setGamenumber(int game)
{
	gamenumber = game;
}

/**  */
void CSelectGameDlg::abort(){
	reject();
}
