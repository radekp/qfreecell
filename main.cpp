/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Don Jul  6 21:34:04 CEST 2000
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

#ifdef QTOPIA

#include <qtopiaapplication.h>
#include "freecell.h"

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET,Freecell)
QTOPIA_MAIN

#else

#include <QtGui/QApplication>
#include "freecell.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Freecell w;
    w.show();
    return a.exec();
}

#endif
