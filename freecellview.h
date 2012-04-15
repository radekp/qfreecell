/***************************************************************************
                          freecellview.h  -  description
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

#ifndef FREECELLVIEW_H
#define FREECELLVIEW_H

// include files for QT
#include <qwidget.h>
#include <qpixmap.h>
#include <QSvgRenderer>

// application specific includes
#include "freecelldoc.h"
#include "cards.h"

/**
 * This class provides an incomplete base for your application view. 
 */

class FreecellView : public QWidget
{
    Q_OBJECT
public:

    FreecellView(QWidget *parent=0, FreecellDoc* doc=0);
    ~FreecellView();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    void getCardPosition(int mx, int my, int *x, int *y);
    void resizeEvent ( QResizeEvent * event );
    bool event(QEvent *);
    void enterFullScreen();
    int checkTurns();
    void checkAutoMoves();
    Cards cards;
    int card_selected;
    int rest;
    bool game_active;
    class Freecell* parent_class;

private:

    QSvgRenderer svg;

    /** images of cards */
    QPixmap cardpics[52];

    int cardWidth, cardHeight;
    int spaceWidth, spaceHeight;
    int cardLeft;

public:
    /** empty field */
    QPixmap empty;
    /**  */
    QPixmap background_picture;
    /**  */
    int moves;

    /** holds information about the selected cards */
    struct { int x, y, where; } selected_card;

    int mouseX, mouseY;

    void renderCards();
};

#endif
