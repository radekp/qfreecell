/***************************************************************************
                          coptions.cpp  -  description
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
#include "coptions.h"
#include "main.h"
#include "freecell.h"

#include <qdir.h>
#include <qstrlist.h>

COptions::COptions(QWidget *parent, const char *name, void *o)
: QDialog(parent, name, true){
	
	unsigned int i;
	char         buffer[100];
	
	setCaption("Options");
	move(POS_X, POS_Y);
	initDialog();
	connect(QPushButton_CANCEL, SIGNAL(clicked()), this, SLOT(reject()));
	connect(QScrollBar_EMPTY, SIGNAL(valueChanged(int)), this, SLOT(newEmpty(int)));
	connect(QPushButton_OK, SIGNAL(clicked()), this, SLOT(ok()));
			
	connect(QRadioButton_COLOR, SIGNAL(clicked()), this, SLOT(slotRadioColor()));
	connect(QRadioButton_FILE, SIGNAL(clicked()), this, SLOT(slotRadioFile()));
	//connect(QPushButton_SELECTCOLOR, SIGNAL(clicked()), this, SLOT(slotSelectColor()));
	connect(QPushButton_SELECTFILE, SIGNAL(clicked()), this, SLOT(slotSelectFile()));
	
	memcpy(&opt, (struct options*)o, sizeof(opt));

	parent_class = (Freecell*)parent;

	QSpinBox_NUMFREECELLS->setValue(*opt.num_freecells);
	QSpinBox_NUMFREECELLS->setRange(*opt.spinbox_freecells_min, 4);
	
	if(*opt.background_enabled)
	{
		QRadioButton_FILE->setChecked(true);
		QRadioButton_COLOR->setChecked(false);
		QLineEdit_BACKGROUND->setText(opt.background_file);
	}
	else
	{
		QRadioButton_FILE->setChecked(false);
		QRadioButton_COLOR->setChecked(true);
	}

	QWidget_COLORWIDGET->setBackgroundColor(*opt.background_color);
	QLineEdit_BACKGROUND->setText(opt.background_file);
	
	// read card layouts for cells
	sprintf(buffer, "%s/freecells", ((Freecell*)parent)->directory);
	dir.setPath(buffer);
	dir.setNameFilter("*.bmp");
		
	selected = 0;
	for(i=0;i<dir.count();i++)
	{
		sprintf(buffer, "%s/%s", dir.absPath().data(), dir[i]);
		if(strcmp(buffer, opt.empty_file)==0) selected = i;
	}
	
	sprintf(opt.empty_file, "%s/%s", dir.absPath().data(), dir[selected]);
	current_empty.load(opt.empty_file);
	
	if(dir.count()-1>0)
		QScrollBar_EMPTY->setRange(0, dir.count()-1);
	else QScrollBar_EMPTY->setRange(0, 0);
	QScrollBar_EMPTY->setValue(selected);
}

COptions::~COptions(){
}

/**  */
void COptions::paintEvent(QPaintEvent *e){
	QPainter k(this);
	k.drawPixmap(10, 30, current_empty);
}

/**  */
void COptions::newEmpty(int i){
	selected = i;	
	sprintf(opt.empty_file, "%s/%s", dir.absPath().data(), dir[i]);
	current_empty.load(opt.empty_file);
	
	QPainter k(this);
	k.drawPixmap(10, 30, current_empty);
}

/**  */
void COptions::ok(){
	strcpy(opt.background_file, QLineEdit_BACKGROUND->text());
	*opt.background_enabled = QRadioButton_FILE->isChecked();
	*opt.num_freecells = QSpinBox_NUMFREECELLS->value();
		
	FILE *f;
	char buffer[200];
	
	sprintf(buffer, "%s/configuration", parent_class->directory);
	f = fopen(buffer, "w");
	if(f!=NULL)
	{
		fprintf(f, "background picture=%s\n", opt.background_file);
		fprintf(f, "freecell=%s\n", opt.empty_file);
		if(*opt.background_enabled)
			fprintf(f, "background enabled=1\n");
		else
			fprintf(f, "background enabled=0\n");
		fclose(f);
	}
	
	accept();
}

/**  */
void COptions::slotRadioColor(){
	if(QRadioButton_COLOR->isChecked()) QRadioButton_FILE->setChecked(false);
		else QRadioButton_FILE->setChecked(true);
}

/**  */
void COptions::slotRadioFile(){
	if(QRadioButton_FILE->isChecked()) QRadioButton_COLOR->setChecked(false);
		else QRadioButton_COLOR->setChecked(true);
}

/**  */
void COptions::slotSelectColor(){
	
}

/**  */
void COptions::slotSelectFile(){
	
	sprintf(buffer, "%s/backgrounds", parent_class->directory);	
	
	QString f = QFileDialog::getOpenFileName(buffer, "*.bmp", this );
	
	if ( !f.isEmpty() ) {
		QLineEdit_BACKGROUND->setText(f);
		strcpy(opt.background_file, QLineEdit_BACKGROUND->text());
		
		QRadioButton_FILE->setChecked(true);
		QRadioButton_COLOR->setChecked(false);
	}
}
