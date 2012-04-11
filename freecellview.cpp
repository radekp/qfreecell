/***************************************************************************
                          freecellview.cpp  -  description
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

#include "freecellview.h"
#include "cards.h"
#include "main.h"
#include "freecell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "qpainter.h"
#include <QMouseEvent>

FreecellView::FreecellView(QWidget * parent, FreecellDoc * doc):QWidget(parent)
{
    char buffer[100];
    int i;

    setMinimumSize(800, 600);
    setMaximumSize(800, 600);
    parent_class = (Freecell *) parent;
    game_active = false;

  /** connect doc with the view*/
    connect(doc, SIGNAL(documentChanged()), this, SLOT(slotDocumentChanged()));

    // load background

    //setBackgroundColor(QColor(0,0,0));

    if (*(parent_class->opt.background_enabled))
        if (background_picture.load(parent_class->opt.background_file))
            *(parent_class->opt.background_enabled) = true;
        else
            *(parent_class->opt.background_enabled) = false;

    if (!*(parent_class->opt.background_enabled))
//    setBackgroundColor(*(parent_class->opt.background_color));

        // load cells

        empty.load(parent_class->opt.empty_file);

    // load cards

    for (i = 1; i <= 52; i++) {
        sprintf(buffer, "%s/cards/%i.bmp", parent_class->directory, i);
        cardpics[i - 1].load(buffer);
    }

    cards.clear();
    card_selected = false;
}

FreecellView::~FreecellView()
{
}

//+====================================================================
//
// void FreeCellView::mousePressEvent(QMouseEvent *e)
//
//-====================================================================

void FreecellView::mousePressEvent(QMouseEvent * e)
{
    QPainter p(this);

    int mx = e->x(), my = e->y();
    int y, x, n;
    int i;

    // get card coordiates
    getCardPosition(mx, my, &x, &y);

    // column ?
    if (y > -1) {
        n = cards.getNumCardsAtCol(x);  // get number of cards
        if (y < (n - 1) || y > (n - 1))
            y = n - 1;
        if (n == 0)
            y = 0;
    }
    // clicked on card which is already selected ?
    if (x == selected_card.x && y == selected_card.y && card_selected && x >= 0
        && game_active) {
        // remove selection of this card
        card_selected = 0;
        if (selected_card.where == FIELD)
            p.drawPixmap(20 + x * 90, 160 + y * 25,
                         cardpics[cards.getCard(x, y)], 0, 0, CARD_WIDTH - 1,
                         CARD_HEIGHT);
        else if (selected_card.where == BOX)
            p.drawPixmap(20 + 80 * x + (x / 4) * 70 + 1, 41,
                         cardpics[cards.getBoxCard(x)]);
    }

    else if (game_active)
        switch (e->button()) {
        case Qt::LeftButton:

            if (y > -1 && x > -1) {
                if (!card_selected) {
                    selected_card.x = x;
                    if ((selected_card.y = cards.getNumCardsAtCol(x) - 1) >= 0) {
                        selected_card.where = FIELD;
                        card_selected = true;
                    }
                } else {
                    if (selected_card.where == FIELD) {
                        y = cards.getNumCardsAtCol(x);
                        if (cards.
                            moveCard(selected_card.x, selected_card.y, x,
                                     y) == 0) {
                            card_selected = false;

                            //draw cards
                            drawMovingCard(selected_card.x, selected_card.y, x,
                                           y, &p);
                        }
                    }

                    if (selected_card.where == BOX) {
                        y = cards.getNumCardsAtCol(x);
                        if (cards.moveCardFromBox(selected_card.x, x, y) == 0) {
                            card_selected = false;

                            //draw cards
                            drawMovingCard(selected_card.x, -1, x, y, &p);
                        }
                    }

                }
            }
            //clicked on a cell

            if (y == -1 && x < *(parent_class->opt.num_freecells) && x >= 0) {
                if (!card_selected) {
                    selected_card.x = x;
                    selected_card.y = y;
                    selected_card.where = BOX;
                    if (cards.getBoxCard(x) != NO_CARD)
                        card_selected = true;
                } else {
                    if (selected_card.x == x && selected_card.where == BOX)
                        card_selected = false;
                    else if (selected_card.where == FIELD) {
                        if (cards.
                            moveCard(selected_card.x, selected_card.y,
                                     x) == 0) {
                            card_selected = false;

                            //draw cards
                            drawMovingCard(selected_card.x, selected_card.y, x,
                                           -1, &p);
                        }
                    }
                }
            }

            if (y == -1 && x > 3)
                if (card_selected) {
                    if (selected_card.where == BOX)
                        if (cards.moveCard(selected_card.x, x) == 0) {
                            card_selected = false;
                            rest--;
                            drawMovingCard(selected_card.x, selected_card.y, x,
                                           -1, &p);
                        }

                    if (selected_card.where == FIELD)
                        if (cards.
                            moveCard(selected_card.x, selected_card.y,
                                     x) == 0) {
                            card_selected = false;
                            rest--;
                            //draw cards
                            drawMovingCard(selected_card.x, selected_card.y, x,
                                           -1, &p);
                        }
                }

            break;

        case Qt::RightButton:

            // column ?

            if (y > -1 && x > -1) {
                // check cells on the left
                for (i = 0; i < *(parent_class->opt.num_freecells); i++)
                    if (cards.moveCard(x, y, i) == 0) {
                        drawMovingCard(x, y, i, -1, &p);
                        break;
                    }
                // if no cells are free on the left sife check right cells
                int freecells = 0;
                for (i = 0; i < *(parent_class->opt.num_freecells); i++)
                    if (cards.getBoxCard(i) == NO_CARD)
                        freecells++;

                bool putit = false;

                if (freecells == 0)
                    for (i = 4; i <= 7; i++) {
                        if (cards.moveCard(x, y, i) == 0 && !putit) {
                            rest--;
                            putit = true;
                            drawMovingCard(x, y, i, -1, &p);
                        }
                    }

            } else
                //clicked on a card in a cell

            if (y == -1 && x < *(parent_class->opt.num_freecells) && x >= 0)
                for (i = 4; i <= 7; i++)
                    //draw cards
                    if (cards.moveCard(x, i) == 0) {
                        rest--;
                        drawMovingCard(x, -1, i, -1, &p);
                        break;
                    }

            break;

        }

    if (card_selected)
        selectCard(selected_card.x, selected_card.y, &p);

    if (rest > 0 && game_active && !card_selected)
        checkAutoMoves(&p);

    if (rest == 0 && game_active) {
        game_active = false;
        p.end();
        parent_class->slotProtocolStop();
        parent_class->won();
    }

    if (checkTurns() == 0 && game_active) {
        game_active = false;
        p.end();
        parent_class->slotProtocolStop();
        parent_class->lost();
    }
    update();
}

void FreecellView::paintEvent(QPaintEvent * event)
{
    int i, j;
    QPixmap pixmap(size().width(), size().height());
    QPainter p(this);
    //QPainter draw(this);

    if (!*(parent_class->opt.background_enabled))
        p.fillRect(event->rect().x(), event->rect().y(),
                   event->rect().width(), event->rect().height(),
                   QBrush(QColor(0, 128, 0)));
    else
        p.drawPixmap(event->rect().x(), event->rect().y(), background_picture,
                     event->rect().x(), event->rect().y(),
                     event->rect().width(), event->rect().height());

    // clear cells

    for (i = 0; i < 8; i++)
        if (i < *(parent_class->opt.num_freecells) || i > 3)
            p.drawPixmap(20 + 80 * i + (i / 4) * 70, 40, empty);

    // draw columns

    for (i = 0; i < 8; i++)
        for (j = 0; j < 15; j++)
            if (cards.getCard(i, j) != NO_CARD)
                if (20 + i * 90 + CARD_WIDTH > (event->rect()).left())
                    p.drawPixmap(20 + i * 90, 160 + j * 25,
                                 cardpics[cards.getCard(i, j)], 0, 0,
                                 CARD_WIDTH - 1, CARD_HEIGHT);

    // draw cells

    for (i = 0; i < 8; i++)
        if (i < *(parent_class->opt.num_freecells) || i > 3)
            if (cards.getBoxCard(i) != NO_CARD)
                if (20 + 80 * i + (i / 4) * 70 + 1 + CARD_WIDTH >
                    (event->rect()).left())
                    p.drawPixmap(20 + 80 * i + (i / 4) * 70 + 1, 41,
                                 cardpics[cards.getBoxCard(i)], 0, 0,
                                 CARD_WIDTH - 1, CARD_HEIGHT);

    if (card_selected)
        selectCard(selected_card.x, selected_card.y, &p);

    if (parent_class->protocol_fd != NULL) {
        p.setPen(QColor(0, 255, 0));
        p.drawText(5, 595, "Protocol enabled");
    }
//        draw.drawPixmap( event->rect().x(), event->rect().y(),    pixmap,
//                                                                                event->rect().x(), event->rect().y(),
//                                                                                event->rect().width(), event->rect().height() );
}

void FreecellView::slotDocumentChanged()
{
    //TODO update the view

}

/**  */
void FreecellView::mouseDoubleClickEvent(QMouseEvent * e)
{
}

/** mx, my = mouse position
x, y = card position (0,0 ...)
if y=-1 => box selected
if x=-1 => invalid card */

void FreecellView::getCardPosition(int mx, int my, int *x, int *y)
{
    *x = *y = -1;

    // clicked on column ?
    if (((mx > 20 && mx < 90) || (mx > 110 && mx < 180) ||
         (mx > 200 && mx < 270) || (mx > 290 && mx < 360) ||
         (mx > 380 && mx < 450) || (mx > 470 && mx < 540) ||
         (mx > 560 && mx < 630) || (mx > 650 && mx < 720)) && my > 160) {
        *y = (my - 160) / 25;
        *x = (mx - 20) / 90;
    }
    // clicked on cells 0..3
    if (((mx > 20 && mx < 90) || (mx > 100 && mx < 170)
         || (mx > 180 && mx < 250) || (mx > 260 && mx < 330)) && (my > 40
                                                                  && my <
                                                                  140)) {
        *x = (mx - 20) / 80;
        *y = -1;
    }
    // clicked on cells 4..7
    if (((mx > 430 && mx < 500) || (mx > 510 && mx < 580)
         || (mx > 590 && mx < 660) || (mx > 670 && mx < 740)) && (my > 40
                                                                  && my <
                                                                  140)) {
        *x = (mx - 410) / 80 + 4;
        *y = -1;
    }

}

/**  */
int FreecellView::checkTurns()
{
    int i, j, n, turns = 0;

    // count possible turns from cells to column

    for (i = 0; i < *(parent_class->opt.num_freecells); i++)
        if (cards.getBoxCard(i) != NO_CARD)
            for (j = 0; j < 8; j++) {
                n = cards.getNumCardsAtCol(j);
                if (cards.checkMoveFromBox(i, j, n))
                    turns++;
            }
    // count possible turns from column to column

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (j != i) {
                int cards_i = cards.getNumCardsAtCol(i);
                int cards_j = cards.getNumCardsAtCol(j);
                if (cards_i > 0)
                    if (cards_j == 0
                        && !cards.checkMove(i, cards_i - 1, i, cards_i - 1))
                        turns++;
                    else if (cards.checkMove(i, cards_i - 1, j, cards_j)
                             && !cards.checkMove(i, cards_i - 1, i,
                                                 cards_i - 1))
                        turns++;
            }
    // count possible turns from column to cells                    

    for (i = 0; i < 8; i++)
        if (cards.getNumCardsAtCol(i) > 0)
            for (j = 0; j < 8; j++)
                if (j < *(parent_class->opt.num_freecells) || j > 3)
                    if (cards.
                        checkMoveToBox(i, cards.getNumCardsAtCol(i) - 1, j))
                        turns++;

    // count possible turns from cell to cell

    for (i = 0; i < *(parent_class->opt.num_freecells); i++)
        if (cards.getBoxCard(i) != NO_CARD)
            for (j = 4; j < 8; j++)
                if (cards.checkMove(i, j))
                    turns++;

    return turns;
}

/**  */
void FreecellView::drawMovingCard(int sx, int sy, int dx, int dy, QPainter * p)
{

    int nx, ny, x, y;

    moves++;

    if (parent_class->protocol_fd != NULL) {
        char l[] = { "abcdefgh12345678" };
        char d[] = { 0, 0, 0 };

        if (sy == -1)
            d[0] = l[sx];
        else
            d[0] = l[sx + 8];
        if (dy == -1)
            d[1] = l[dx];
        else
            d[1] = l[dx + 8];
        fprintf(parent_class->protocol_fd, "%s ", d);
        if (moves % 10 == 0)
            fprintf(parent_class->protocol_fd, "\n");
    }

    switch (sy) {
    case -1:                   // move card from cell...

        x = 20 + 80 * sx + (sx / 4) * 70;
        y = 41;

        // clear cell       
        p->drawPixmap(20 + 80 * sx + (sx / 4) * 70, 40, empty);

        switch (dy) {
        case -1:               // ...to cell
            nx = 20 + 80 * dx + (dx / 4) * 70 + 1;
            ny = 41;
            moveCard(x, y, nx, ny, cardpics[cards.getBoxCard(dx)]);
            break;

        default:               // ...to column
            nx = 20 + dx * 90;
            ny = 160 + dy * 25;
            moveCard(x, y, nx, ny, cardpics[cards.getCard(dx, dy)]);
            break;
        }
        break;

    default:                   // move card from column...

        x = 20 + sx * 90;
        y = 160 + sy * 25;

        if (!*(parent_class->opt.background_enabled))
            p->fillRect(20 + sx * 90, 160 + sy * 25, CARD_WIDTH - 1,
                        CARD_HEIGHT, QBrush(QColor(0, 128, 0)));
        else
            p->drawPixmap(20 + sx * 90, 160 + sy * 25, background_picture,
                          20 + sx * 90, 160 + sy * 25, CARD_WIDTH - 1,
                          CARD_HEIGHT);
        if (sy - 1 >= 0)
            if (cards.getCard(sx, sy - 1) != NO_CARD)
                p->drawPixmap(20 + sx * 90, 160 + (sy - 1) * 25,
                              cardpics[cards.getCard(sx, sy - 1)], 0, 0,
                              CARD_WIDTH - 1, CARD_HEIGHT);

        switch (dy) {
        case -1:               // ...to cell
            nx = 20 + 80 * dx + (dx / 4) * 70 + 1;
            ny = 41;
            moveCard(x, y, nx, ny, cardpics[cards.getBoxCard(dx)]);
            break;

        default:               // ...to column
            nx = 20 + dx * 90;
            ny = 160 + dy * 25;
            moveCard(x, y, nx, ny, cardpics[cards.getCard(dx, dy)]);
            break;

        }
        break;
    }

}

/**  */
void FreecellView::moveCard(int x1, int y1, int x2, int y2, QPixmap card)
{

    QPixmap screen(CARD_WIDTH + 1, CARD_HEIGHT + 1);

    int c = 20;                 // number of steps
    int ox = x1 + (x2 - x1) / c, oy = y1 + (y2 - y1) / c;
    int px, py;
    int i;

    // save background
//  bitBlt((QPaintDevice*)&screen, 0, 0, this, ox, oy, CARD_WIDTH, CARD_HEIGHT);

    for (i = 1; i <= c; i++) {
        px = x1 + i * (x2 - x1) / c;
        py = y1 + i * (y2 - y1) / c;

        // restore background
//      bitBlt(this, ox, oy, (QPaintDevice*)&screen, 0, 0, CARD_WIDTH, CARD_HEIGHT);

        // save background
//      bitBlt((QPaintDevice*)&screen, 0, 0, this, px, py, CARD_WIDTH, CARD_HEIGHT);

        // draw card on screen
//      bitBlt(this, px, py, (QPaintDevice*)&card, 0, 0, CARD_WIDTH-1, CARD_HEIGHT);

        ox = x1 + i * (x2 - x1) / c;
        oy = y1 + i * (y2 - y1) / c;
    }
}

/**  */
void FreecellView::selectCard(int x, int y, QPainter * p)
{

    int x1;
    int y1;

    if (y == -1)                // cell
    {
        x1 = 20 + 80 * x + (x / 4) * 70 + 1;
        y1 = 41;
    } else                      // column
    {
        x1 = 20 + 90 * x;
        y1 = 160 + y * 25;
    }

    // draw red rectangle

    if (y != 0 || x < *(parent_class->opt.num_freecells) || x > 3) {
        p->setPen(QColor(255, 0, 0));
        p->drawRect(x1, y1, CARD_WIDTH - 2, CARD_HEIGHT - 1);
        p->drawRect(x1 + 1, y1 + 1, CARD_WIDTH - 4, CARD_HEIGHT - 3);
    }
}

/**  */
void FreecellView::checkAutoMoves(QPainter * p)
{

    int i, j, k, moves;
    int c, o[4];

    bool move;

    do {
        moves = 0;

        for (i = 0; i < 8; i++)
            if (cards.getNumCardsAtCol(i) > 0)
                for (j = 4; j < 8; j++)
                    if (cards.
                        checkMoveToBox(i, cards.getNumCardsAtCol(i) - 1, j)) {
                        move = true;

                        c = cards.getCard(i, cards.getNumCardsAtCol(i) - 1) / 4;
                        for (k = 4; k < 8; k++)
                            if (cards.getBoxCard(k) == NO_CARD)
                                o[k - 4] = -1;
                            else
                                o[k - 4] = cards.getBoxCard(k) / 4;

                        if ((o[0] == NO_CARD || o[1] == NO_CARD
                             || o[2] == NO_CARD || o[3] == NO_CARD || o[0] == 0
                             || o[1] == 0 || o[2] == 0 || o[3] == 0) && (c < 12
                                                                         && c >
                                                                         0))
                            move = false;
                        else if (c < 12 && c > 0)   // 3..King
                        {
                            for (k = 0; k < 4; k++)
                                if (k != j)
                                    if (o[k] > c + 1)
                                        move = false;
                        }

                        if (move)   // 0 = "A", 12 = "2"
                        {
                            cards.moveCard(i, cards.getNumCardsAtCol(i) - 1, j);
                            drawMovingCard(i, cards.getNumCardsAtCol(i), j, -1,
                                           p);
                            rest--;
                            moves++;
                            break;
                        }
                    }

        for (i = 0; i < 4; i++)
            if (cards.getBoxCard(i) != NO_CARD)
                for (j = 4; j < 8; j++)
                    if (cards.checkMove(i, j)) {
                        move = true;

                        c = cards.getBoxCard(i) / 4;

                        for (k = 4; k < 8; k++)
                            if (cards.getBoxCard(k) == NO_CARD)
                                o[k - 4] = -1;
                            else
                                o[k - 4] = cards.getBoxCard(k) / 4;

                        if ((o[0] == NO_CARD || o[1] == NO_CARD
                             || o[2] == NO_CARD || o[3] == NO_CARD || o[0] == 0
                             || o[1] == 0 || o[2] == 0 || o[3] == 0) && (c < 12
                                                                         && c >
                                                                         0))
                            move = false;
                        else if (c < 12 && c > 0)   // 3..King
                        {
                            for (k = 0; k < 4; k++)
                                if (k != j)
                                    if (o[k] > c + 1)
                                        move = false;
                        }

                        if (move)   // 0 = "A", 12 = "2"
                        {
                            cards.moveCard(i, j);
                            drawMovingCard(i, -1, j, -1, p);
                            rest--;
                            moves++;
                            break;
                        }
                    }

    } while (moves > 0);

}