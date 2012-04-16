/***************************************************************************
                          cards.cpp  -  description
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

#include "cards.h"
#include "main.h"

#include <stdlib.h>

Cards::Cards()
{
}

Cards::~Cards()
{
}

//+====================================================================
//
// int Cards::getCard(int x, int y)
//
//-====================================================================

int Cards::getCard(int x, int y)
{
    return cardarray[x][y];
}

//+====================================================================
//
// int Cards::getBoxCard(int x)
//
//-====================================================================

int Cards::getBoxCard(int x)
{
    return box[x];
}

//+====================================================================
//
// int Cards::getNumCardsAtCol(int col)
//
//-====================================================================

int Cards::getNumCardsAtCol(int col)
{
    int i = 0;
    while (cardarray[col][i] != NO_CARD)
        i++;
    return i;
}

//+====================================================================
//
// void Cards::clear()
//
//-====================================================================

void Cards::clear()
{
    int i, j;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 15; j++)
            cardarray[i][j] = NO_CARD;

    for (i = 0; i < 8; i++)
        box[i] = NO_CARD;
}

//+====================================================================
//
// void Cards::init()
//
//-====================================================================

void Cards::init(int gamenumber)
{
    int i, j;
    int array[52];
    int wLeft = 52;

    for (i = 0; i < 8; i++)
        box[i] = NO_CARD;

    for (i = 0; i < 52; i++)
        array[i] = i;

    srand(gamenumber);

    for (i = 0; i < 52; i++) {
        j = rand() % wLeft;
        cardarray[(i % 8)][i / 8] = array[j];
        array[j] = array[--wLeft];
    }

}

//+====================================================================
//
// void Cards::moveCard(int sx, int sy, int dx, int dy)
//
//-====================================================================

int Cards::moveCard(int sx, int sy, int dx, int dy)
{
    int color1 = 0, color2 = 0;
    int t = 0;

    if (cardarray[sx][sy] == NO_CARD)
        return -1;

    if (dy > 0)
        t = cardarray[sx][sy] / 4 - cardarray[dx][dy - 1] / 4;

    color1 = getCardColor(sx, sy);
    color2 = getCardColor(dx, dy - 1);

    if (((color1 != color2) && (t == 1)) || dy == 0) {
        cardarray[dx][dy] = cardarray[sx][sy];
        cardarray[sx][sy] = NO_CARD;

        return 0;
    }

    return -1;
}

//+====================================================================
//
// int Cards::moveCard(int sx, int sy, int b)
//
//-====================================================================

int Cards::moveCard(int sx, int sy, int b)
{
    int c = cardarray[sx][sy];

    if (c == NO_CARD)
        return -1;

    if (b < 4)
        if (box[b] == NO_CARD) {
            box[b] = c;
            cardarray[sx][sy] = NO_CARD;

            return 0;
        }

    if (b > 3)
        if (((box[b] == NO_CARD) && (c < 4)) ||
            (box[b] - c == 4) ||
            ((box[b] < 4) && (c >= 48) && (box[b] % 4 == c % 4))
            )
            // ACE = 0..3; 2 = 48..51
        {
            box[b] = c;
            cardarray[sx][sy] = NO_CARD;

            return 0;
        }

    return -1;
}

//+====================================================================
//
// int Cards::moveCard(int bleft, int bright)
//
//-====================================================================

int Cards::moveCard(int bleft, int bright)
{
    int c = box[bleft];

    if (c != NO_CARD)
        if (((box[bright] == NO_CARD) && (c < 4)) ||
            (box[bright] - box[bleft] == 4) ||
            ((box[bright] < 4) && (box[bleft] >= 48)
             && (box[bright] % 4 == box[bleft] % 4))
            )
            // ACE = 0..3; 2 = 48..51
        {
            box[bright] = box[bleft];
            box[bleft] = NO_CARD;

            return 0;
        }

    return -1;
}

//+====================================================================
//
// int Cards::moveCardFromBox(int box, int x, int y)
//
//-====================================================================

int Cards::moveCardFromBox(int b, int x, int y)
{
    int color1 = 0, color2 = 0;
    int t = 0;

    if (box[b] == NO_CARD)
        return -1;

    if (y > 0)
        t = box[b] / 4 - cardarray[x][y - 1] / 4;

    color1 = getCardColor(b);
    color2 = getCardColor(x, y - 1);

    if (((color1 != color2) && (t == 1)) || y == 0) {
        cardarray[x][y] = box[b];
        box[b] = NO_CARD;

        return 0;
    }

    return -1;
}

//+====================================================================
//
// int Cards::getCardColor(int x, int y)
//
//-====================================================================

int Cards::getCardColor(int x, int y)
{
    int c = cardarray[x][y];

    if (c % 4 == 0 || (c - 1) % 4 == 0)
        return CARD_RED;
    return CARD_BLACK;
}

//+====================================================================
//
// int Cards::getCardColor(int b)
//
//-====================================================================

int Cards::getCardColor(int b)
{
    int c = box[b];

    if (c == NO_CARD)
        return -1;

    if (c % 4 == 0 || (c - 1) % 4 == 0)
        return CARD_RED;
    return CARD_BLACK;
}

/**  */
bool Cards::checkMoveFromBox(int b, int x, int y)
{
    int color1 = 0, color2 = 0;
    int t = 0;

    if (box[b] == NO_CARD)
        return false;

    if (y == 0 && cardarray[x][y] == NO_CARD)
        return true;

    if (y > 0)
        t = box[b] / 4 - cardarray[x][y - 1] / 4;

    color1 = getCardColor(b);
    color2 = getCardColor(x, y - 1);

    if (((color1 != color2) && (t == 1)) && y > 0)
        return true;

    return false;
}

/**  */
bool Cards::checkMove(int sx, int sy, int dx, int dy)
{
    int color1 = 0, color2 = 0;
    int t = 0;

    if (cardarray[sx][sy] == NO_CARD)
        return -1;

    if (dy > 0)
        t = cardarray[sx][sy] / 4 - cardarray[dx][dy - 1] / 4;

    color1 = getCardColor(sx, sy);
    color2 = getCardColor(dx, dy - 1);

    if (((color1 != color2) && (t == 1)) && dy > 0)
        return true;

    return false;
}

/**  */
bool Cards::checkMoveToBox(int sx, int sy, int b)
{
    int c = cardarray[sx][sy];

    if (c == NO_CARD)
        return -1;

    if (b < 4)
        if (box[b] == NO_CARD)
            return true;

    if (b > 3)
        if (((box[b] == NO_CARD) && (c < 4)) ||
            (box[b] - c == 4) ||
            ((box[b] < 4) && (c >= 48) && (box[b] % 4 == c % 4))
            )
            // ACE = 0..3; 2 = 48..51
            return true;

    return false;
}

/**  */
bool Cards::checkMove(int bleft, int bright)
{
    int c = box[bleft];

    if (((box[bright] == NO_CARD) && (c < 4)) ||
        (box[bright] - box[bleft] == 4) ||
        ((box[bright] < 4) && (box[bleft] >= 48)
         && (box[bright] % 4 == box[bleft] % 4))
        )
        // ACE = 0..3; 2 = 48..51
        return true;

    return false;
}

/**  */
int Cards::getNumFreecells(int num_maxfreecells)
{
    int r = 0;

    for (int i = 0; i < num_maxfreecells; i++)
        if (box[i] == NO_CARD)
            r++;

    return r;
}
