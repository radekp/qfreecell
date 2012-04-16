/***************************************************************************
                          cstatistics.h  -  description
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

#ifndef CSTATISTICS_H
#define CSTATISTICS_H

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

class CStatistics : public QDialog
{
    Q_OBJECT
public:
    CStatistics(QWidget * parent = 0, const char *name = 0, bool modal = true);
    ~CStatistics();

    struct stat
    {
        int won_all;
        int lost_all;
        int won_session;
        int lost_session;
    } statistics;

  /**  */
    void addWon();
    void addLost();
  /**  */
    void updateStatistics();

protected:
    void initDialog();
    //Generated area. DO NOT EDIT!!!(begin)
    QGroupBox *QGroupBox_1;
    QLabel *QLabel_1;
    QLabel *QLabel_2;
    QPushButton *QPushButton_OK;
    QPushButton *QPushButton_RESET;
    QLabel *QLabel_3;
    QLabel *QLabel_4;
    QLabel *QLabel_5;
    QLabel *QLabel_WonAll;
    QLabel *QLabel_LostAll;
    QLabel *QLabel_WonSession;
    QLabel *QLabel_LostSession;
    QLabel *QLabel_WonAllPercent;
    QLabel *QLabel_WonSessionPercent;
    //Generated area. DO NOT EDIT!!!(end)

private:
public slots:                  // Public slots
  /**  */
    void reset();
public:                        // Public attributes
  /**  */
     class Freecell * parent_class;
};

#endif
