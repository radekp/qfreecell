/***************************************************************************
                          cards.h  -  description
                             -------------------
    begin                : Thu Jul 6 2000
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

#ifndef CARDS_H
#define CARDS_H

/**
  *@author Daniel Etzold
  */

class Cards
{
public:
    Cards();
    ~Cards();

    int getNumCardsAtCol(int x);
    void clear();
    void init(int);
    int getCard(int x, int y);
    int getBoxCard(int x);
    int moveCard(int sx, int sy, int dx, int dy);
    int moveCard(int sx, int sy, int box);
    int moveCard(int bleft, int bright);
    int moveCardFromBox(int b, int dx, int dy);
    int getCardColor(int x, int y);
    int getCardColor(int b);
  /**  */
    bool checkMove(int sx, int sy, int dx, int dy);
  /**  */
    bool checkMoveFromBox(int b, int x, int y);
  /**  */
    bool checkMoveToBox(int sx, int sy, int b);
  /**  */
    bool checkMove(int bleft, int bright);
  /**  */
    int getNumFreecells(int num_maxfreecells);

private:
    int box[8];
    int cardarray[8][15];
};

#endif
