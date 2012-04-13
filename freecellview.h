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
  void mouseDoubleClickEvent(QMouseEvent *e);
  /**  */
  int checkTurns();
  /**  */
  void drawMovingCard(int sx, int sy, int dx, int dy, QPainter *p);
  /**  */
  void moveCard(int x1, int y1, int x2, int y2, QPixmap card);
  /**  */
  void selectCard(int x, int y, QPainter *p);
  /**  */
  void checkAutoMoves(QPainter *p);
  
  Cards cards;
	int   card_selected;
  /**  */
  int rest;
  /**  */
  bool game_active;
  /**  */
  class Freecell* parent_class;
		
  protected slots:

  void slotDocumentChanged();
  
	private: // Private attributes
  	
  /** images of cards */
  QPixmap cardpics[52];

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

};

#endif


