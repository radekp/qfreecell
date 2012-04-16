/***************************************************************************
                          freecelldoc.cpp  -  description
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

#include "freecelldoc.h"

FreecellDoc::FreecellDoc()
{
    modified = false;
}

FreecellDoc::~FreecellDoc()
{
}

void FreecellDoc::newDoc()
{
}

bool FreecellDoc::save()
{
    return true;
}

bool FreecellDoc::saveAs(const QString & filename)
{
    return true;
}

bool FreecellDoc::load(const QString & filename)
{
    emit documentChanged();
    return true;
}

bool FreecellDoc::isModified() const
{
    return modified;
}
