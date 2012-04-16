/***************************************************************************
                          coptions.h  -  description
                             -------------------
    begin                : Fri Jul 14 2000
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

#ifndef COPTIONS_H
#define COPTIONS_H

//Generated area. DO NOT EDIT!!!(begin)
#include <qwidget.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qscrollbar.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qspinbox.h>
//Generated area. DO NOT EDIT!!!(end)

#include <qdialog.h>
#include <qdir.h>
#include "main.h"
#include "freecell.h"

/**
  *@author Daniel Etzold
  */

class COptions : public QDialog
{
  /**  */
    void paintEvent(QPaintEvent * e);
     Q_OBJECT
public:
     COptions(QWidget * parent = 0, const char *name = 0, void *o = 0);
    ~COptions();
  /**  */
    QDir dir;

protected:
    void initDialog();
    //Generated area. DO NOT EDIT!!!(begin)
    QGroupBox *QGroupBox_1;
    QLabel *QLabel_1;
    QPushButton *QPushButton_OK;
    QScrollBar *QScrollBar_EMPTY;
    QPushButton *QPushButton_CANCEL;
    QRadioButton *QRadioButton_FILE;
    QLineEdit *QLineEdit_BACKGROUND;
    QRadioButton *QRadioButton_COLOR;
    QPushButton *QPushButton_SELECTFILE;
    QWidget *QWidget_COLORWIDGET;
    QLabel *QLabel_2;
    QSpinBox *QSpinBox_NUMFREECELLS;
    //Generated area. DO NOT EDIT!!!(end)

private:

public:                        // Public attributes
  /**  */
     QPixmap current_empty;
  /**  */
    int selected;
  /**  */
    char buffer[200];

    struct options
    {
        char *empty_file;
        char *background_file;
        QColor *background_color;
        bool *background_enabled;
        int *num_freecells;
        int *spinbox_freecells_min;
    } opt;

public slots:                  // Public slots
  /**  */
  /**  */
    void ok();
    void newEmpty(int i);
  /**  */
    void slotRadioFile();
  /**  */
    void slotRadioColor();
  /**  */
    void slotSelectFile();
  /**  */
    void slotSelectColor();
private:                       // Private attributes
  /**  */
     Freecell * parent_class;
};

#endif
