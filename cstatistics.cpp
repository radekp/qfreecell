/***************************************************************************
                          cstatistics.cpp  -  description
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
#include "cstatistics.h"
#include <stdio.h>
#include "freecell.h"

#include <stdlib.h>

CStatistics::CStatistics(QWidget *parent, const char *name, bool modal)
: QDialog(0, name, modal){
	setCaption("Statistics");
	initDialog();
	move(POS_X, POS_Y);
	connect(QPushButton_OK, SIGNAL(clicked()), this, SLOT(accept()));
	connect(QPushButton_RESET, SIGNAL(clicked()), this, SLOT(reset()));

	FILE *f;
	char buff1[200], buff2[200];
	int  i;

	parent_class = (Freecell*)parent;
		
	//Init statistics

  statistics.won_all = 0;
  statistics.lost_all = 0;
  statistics.won_session = 0;
  statistics.lost_session = 0;

	sprintf(buff1, "%s/statistics", parent_class->directory);
	f = fopen(buff1, "r");
	
	if(f!=NULL)
	{
  	//read won statistics
  	i = fscanf(f, "%s %s", buff1, buff2);
  	if(i!=0) statistics.won_all = atoi(buff2);
  	
  	//read lost statistics
  	i = fscanf(f, "%s %s", buff1, buff2);
  	if(i!=0) statistics.lost_all = atoi(buff2);
  	
  	fclose(f);
	}

	updateStatistics();
}

CStatistics::~CStatistics()
{
	FILE *f;
	char buffer[200];

	sprintf(buffer, "%s/statistics", parent_class->directory);
	f = fopen(buffer, "w");
	
	if(f!=NULL)
	{
		fprintf(f, "won  %i\nlost %i\n", statistics.won_all, statistics.lost_all);
  	fclose(f);
	}
}

/**  */
void CStatistics::addWon()
{
	statistics.won_all++;
	statistics.won_session++;
	
	updateStatistics();
}


/**  */
void CStatistics::addLost()
{
	statistics.lost_all++;
	statistics.lost_session++;
	
	updateStatistics();
}


/**  */
void CStatistics::reset()
{
	statistics.won_all = 0;
	statistics.won_session = 0;
	statistics.lost_all = 0;
	statistics.lost_session = 0;

	updateStatistics();
}

/**  */
void CStatistics::updateStatistics()
{
	char buffer[100];
	int  games;
	
	sprintf(buffer, "%i", statistics.won_all);
	QLabel_WonAll->setText(buffer);
	
	sprintf(buffer, "%i", statistics.won_session);
	QLabel_WonSession->setText(buffer);
	
	sprintf(buffer, "%i", statistics.lost_all);
	QLabel_LostAll->setText(buffer);
	
	sprintf(buffer, "%i", statistics.lost_session);
	QLabel_LostSession->setText(buffer);
	
	games = statistics.won_all + statistics.lost_all;
	if(games>0)
	{
		sprintf(buffer, "%.2f%%",(float)statistics.won_all/games*100);
		QLabel_WonAllPercent->setText(buffer);
	}
	else QLabel_WonAllPercent->setText("0%");
	
	games = statistics.won_session + statistics.lost_session;
	if(games>0)
	{
		sprintf(buffer, "%.2f%%",(float)statistics.won_session/games*100);
		QLabel_WonSessionPercent->setText(buffer);
	}
	else QLabel_WonSessionPercent->setText("0%");
}
