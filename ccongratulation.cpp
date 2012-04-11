/***************************************************************************
                          ccongratulation.cpp  -  description
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
#include "ccongratulation.h"

CCongratulation::CCongratulation(QWidget *parent, const char *name) : QDialog(parent){
	move(POS_X, POS_Y);
	initDialog();
	connect(QPushButton_OK, SIGNAL(clicked()), this, SLOT(accept()));
}

CCongratulation::~CCongratulation(){
}
