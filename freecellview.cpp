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
#include <QDebug>

FreecellView::FreecellView(QWidget * parent, FreecellDoc * doc)
:  QWidget(parent)
    , svg(QString(":/cards2.svg"), this)
    , mouseX(-1)
    , mouseY(-1)
{
    setMinimumSize(480, 640);

    parent_class = (Freecell *) parent;
    game_active = false;

    connect(doc, SIGNAL(documentChanged()), this, SLOT(slotDocumentChanged()));

    cards.clear();
    card_selected = false;

    renderCards();
}

FreecellView::~FreecellView()
{
}

void FreecellView::renderCards()
{
    cardLeft = 4;
    cardTop = 4;

    int newWidth = (width() - 2 * cardLeft) / 8;
    int newHeight = height() / 8;

    if (cardWidth == newWidth && cardHeight == newHeight)
        return;

    cardWidth = newWidth;
    cardHeight = newHeight;

    for (int i = 0; i < 54; i++) {
        QPixmap pix = QPixmap(cardWidth, cardHeight);
        pix.fill(Qt::transparent);
        QPainter p(&pix);

        QString elemName;
        if (i < 52) {
            int number = (51 - i) / 4 + 2;
            switch (number) {
            case 11:
                elemName = "J";
                break;
            case 12:
                elemName = "Q";
                break;
            case 13:
                elemName = "K";
                break;
            case 14:
                elemName = "A";
                break;
            default:
                elemName = QString::number(number);
                break;
            }
            switch (i % 4)      // color
            {
            case 0:
                elemName += "C";
                break;
            case 1:
                elemName += "S";
                break;
            case 2:
                elemName += "H";
                break;
            default:
                elemName += "D";
                break;
            }
        } else if (i == 52) {
            elemName = "EMPTY1";
        } else {
            elemName = "EMPTY2";
        }

        svg.render(&p, elemName, QRectF(4, 4, cardWidth - 8, cardHeight - 8));
        cardpics[i] = pix;
    }
}

void FreecellView::resizeEvent(QResizeEvent * event)
{
    renderCards();
}

void FreecellView::mousePressEvent(QMouseEvent * e)
{
    if (!game_active)
        return;

    int mx = e->x(), my = e->y();
    mouseX = mx;
    mouseY = my;
    int y, x, n;

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

    if (y > -1 && x > -1) {
        selected_card.x = x;
        if ((selected_card.y = cards.getNumCardsAtCol(x) - 1) >= 0) {
            selected_card.where = FIELD;
            card_selected = true;
        }
    }
    //clicked on a cell
    if (y == -1 && x < *(parent_class->opt.num_freecells) && x >= 0) {
        selected_card.x = x;
        selected_card.y = y;
        selected_card.where = BOX;
        if (cards.getBoxCard(x) != NO_CARD)
            card_selected = true;
    }

    update(mouseX - cardWidth, 0, cardWidth * 2, height());
}

void FreecellView::mouseMoveEvent(QMouseEvent * e)
{
    int oldX = mouseX;
    int oldY = mouseY;
    mouseX = e->x();
    mouseY = e->y();

    update(oldX - cardWidth / 2, oldY - cardHeight / 2, cardWidth, cardHeight);
    update(mouseX - cardWidth / 2, mouseY - cardHeight / 2, cardWidth,
           cardHeight);
}

void FreecellView::mouseReleaseEvent(QMouseEvent * e)
{
    mouseX = -1;
    mouseY = -1;

    if (!card_selected)
        return;

    int mx = e->x(), my = e->y();
    int y, x;

    // get card coordiates
    getCardPosition(mx, my, &x, &y);

    if (y > -1 && x > -1) {
        if (selected_card.where == FIELD) {
            y = cards.getNumCardsAtCol(x);
            cards.moveCard(selected_card.x, selected_card.y, x, y);
        } else if (selected_card.where == BOX) {
            y = cards.getNumCardsAtCol(x);
            cards.moveCardFromBox(selected_card.x, x, y);
        }
    }
    //clicked on a cell
    if (y == -1 && x < *(parent_class->opt.num_freecells) && x >= 0) {
        if (selected_card.where == FIELD) {
            cards.moveCard(selected_card.x, selected_card.y, x);
        }
    }

    if (y == -1 && x > 3) {
        if (selected_card.where == BOX) {
            if (cards.moveCard(selected_card.x, x) == 0) {
                rest--;
            }
        }
        if (selected_card.where == FIELD) {
            if (cards.moveCard(selected_card.x, selected_card.y, x) == 0) {
                rest--;
            }
        }
    }

    if (rest > 0 && !card_selected)
        checkAutoMoves();

    if (rest == 0) {
        game_active = false;
        parent_class->slotProtocolStop();
        parent_class->won();
    }

    if (checkTurns() == 0) {
        game_active = false;
        parent_class->slotProtocolStop();
        parent_class->lost();
    }

    card_selected = false;
    update();
}

bool FreecellView::event(QEvent * event)
{
#ifdef QTOPIA
    if (event->type() == QEvent::WindowDeactivate) {
        lower();
    } else if (event->type() == QEvent::WindowActivate) {
        QString title = windowTitle();
        setWindowTitle(QLatin1String("_allow_on_top_"));
        raise();
        setWindowTitle(title);
    }
#endif
    return QWidget::event(event);
}

void FreecellView::enterFullScreen()
{
#ifdef QTOPIA
    // Show editor view in full screen
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    raise();
#endif
}

void FreecellView::drawCard(QPainter & p, QPaintEvent * e, int x, int y,
                            int card)
{
    QRect cardRect(x, y, cardWidth, cardHeight);
    if (cardRect.intersect(e->rect()).isEmpty())
        return;
    p.drawPixmap(x, y, cardpics[card]);
}

void FreecellView::paintEvent(QPaintEvent * e)
{
    int i, j;
    QPainter p(this);

    p.fillRect(e->rect(), Qt::darkGreen);

    // clear cells
    for (i = 0; i < 8; i++)
        if (i < *(parent_class->opt.num_freecells) || i > 3)
            drawCard(p, e, cardLeft + cardWidth * i, cardTop, i < 4 ? 52 : 53);

    // draw columns
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 15; j++) {
            if (cards.getCard(i, j) == NO_CARD)
                continue;
            if (card_selected && selected_card.x == i && selected_card.y == j)
                continue;
            drawCard(p, e, cardLeft + i * cardWidth,
                     cardTop + cardHeight + (j * cardHeight) / 3,
                     cards.getCard(i, j));
        }
    }

    // draw cells
    for (i = 0; i < 8; i++) {
        if (i < *(parent_class->opt.num_freecells) || i > 3) {
            if (cards.getBoxCard(i) == NO_CARD)
                continue;
            if (card_selected && i == selected_card.x && selected_card.y == -1)
                continue;
            drawCard(p, e, cardLeft + cardWidth * i, cardTop,
                     cards.getBoxCard(i));
        }
    }

    if (card_selected) {
        if (mouseX >= 0 && mouseY >= 0) {
            int card;

            if (selected_card.y == -1) {
                card = cards.getBoxCard(selected_card.x);
            } else {
                card = cards.getCard(selected_card.x, selected_card.y);
            }

            drawCard(p, e, mouseX - cardWidth / 2, mouseY - cardHeight / 2,
                     card);
        }
    }
}

/** mx, my = mouse position
x, y = card position (0,0 ...)
if y=-1 => box selected
if x=-1 => invalid card */

void FreecellView::getCardPosition(int mx, int my, int *x, int *y)
{
    *x = *y = -1;

    if (my < cardTop + cardHeight)
        *y = -1;
    else
        *y = (my - cardHeight - cardTop) / cardHeight;

    *x = mx / cardWidth;
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
                    if (cards.checkMoveToBox
                        (i, cards.getNumCardsAtCol(i) - 1, j))
                        turns++;

    // count possible turns from cell to cell

    for (i = 0; i < *(parent_class->opt.num_freecells); i++)
        if (cards.getBoxCard(i) != NO_CARD)
            for (j = 4; j < 8; j++)
                if (cards.checkMove(i, j))
                    turns++;

    return turns;
}

void FreecellView::checkAutoMoves()
{

    int i, j, k, moves;
    int c, o[4];

    bool move;

    do {
        moves = 0;

        for (i = 0; i < 8; i++)
            if (cards.getNumCardsAtCol(i) > 0)
                for (j = 4; j < 8; j++)
                    if (cards.checkMoveToBox
                        (i, cards.getNumCardsAtCol(i) - 1, j)) {
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
                            rest--;
                            moves++;
                            break;
                        }
                    }

    } while (moves > 0);
}

void FreecellView::slotDocumentChanged()
{
    update();
}
