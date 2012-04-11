/***************************************************************************
                          lostdlg.cpp  -  description
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
#include "lostdlg.h"

LostDlg::LostDlg(QWidget *parent, const char *name, bool modal) : QDialog(parent,name,modal){
	move(POS_X, POS_Y);
	setCaption("Loser");
	initDialog();
	connect(QPushButton_1, SIGNAL(clicked()), this, SLOT(accept()));
}

LostDlg::~LostDlg(){
}
