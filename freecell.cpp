/***************************************************************************
                          freecell.cpp  -  description
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

#include "freecell.h"
//#include "filesave.xpm"
//#include "fileopen.xpm"
#include "filenew.xpm"

#include "freecellview.h"
#include "cselectgamedlg.h"
#include "cstatistics.h"
#include "ccongratulation.h"
#include "lostdlg.h"
#include "closewarning.h"
#include "coptions.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <qdialog.h>
#include <qfile.h>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>

#include <math.h>

#ifdef QTOPIA
#include <QtopiaServiceRequest>
#endif

Freecell::Freecell(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
    , rotation(90)
{
	FILE *f;

	// create ~/.qfreecell	
        QDir d("/tmp");
	char buffer[200];
	
	// save location of binary
	d.cdUp();
        strcpy(game_directory, (d.path()).toLatin1().data());
	
        strcpy(directory, QDir::homePath().toLatin1().data());
        strcat(directory, "/.qfreecell");
	
	d.setPath(directory);
	if(!d.exists()) // create directories if not exists
	{
		printf("Creating ~/.qfreecell...\n");
		d.mkdir(directory);
		sprintf(buffer, "%s/protocols", directory);
    }
	
	//Init statistics

	pstatistics = new CStatistics(this, "", false);
	protocol_file = new QString();
	protocol_fd = NULL;
	
	// first set configuration to default	
	opt.empty_file = new char[200];
	opt.background_file = new char[200];
	opt.background_enabled = new bool;
	opt.background_color = new QColor(0, 128, 0);
	opt.num_freecells = new int;
	opt.spinbox_freecells_min = new int;
	
	// set picture filename of freecells
	strcpy(opt.empty_file, directory);
	strcat(opt.empty_file, "/freecells/");
	strcat(opt.empty_file, DEFAULT_FREECELL);
	
	// set background filename
	strcpy(opt.background_file, directory);
	strcat(opt.background_file, "/backgrounds/");
	strcat(opt.background_file, DEFAULT_BACKGROUND);
	
	// enable backgrounds
	*opt.background_enabled = true;

	// set number of free cells to 4
	*opt.num_freecells = 4;
	
	//////////////////////////////
	// now read configuration file

	sprintf(buffer, "%s/configuration",directory);
	f = fopen(buffer, "r");
	if(f!=NULL)
	{
		unsigned int i;
		while(fgets(buffer, 200, f)!=NULL)
		{
			i=0;
			while(buffer[i++]!='\0') if(buffer[i-1]=='\n') buffer[i-1]='\0';
			for(i=0;i<strlen(buffer);i++)	if(buffer[i]=='=') break;
			
			if(memcmp(buffer,"background picture",18)==0) strcpy(opt.background_file, buffer+i+1);
			if(memcmp(buffer,"freecell",8)==0) strcpy(opt.empty_file, buffer+i+1);
			if(memcmp(buffer,"background enabled",18)==0)
				if(buffer[i+1]=='1') *opt.background_enabled = true;
					else *opt.background_enabled = false;
		}
		fclose(f);
	}
	
  ///////////////////////////////////////////////////////////////////
  // call inits to invoke all other construction parts
  initMenuBar();
  initToolBar();
  initStatusBar();

  initDoc();
  initView();

  slotFileNew();
}

Freecell::~Freecell()
{
    if(rotation == 0) {
        slotFileRotate();       // rotate to 0 when ending
    }
}

void Freecell::initMenuBar()
{
  ///////////////////////////////////////////////////////////////////
  // MENUBAR

  ///////////////////////////////////////////////////////////////////
  // menuBar entry fileMenu

#ifdef QTOPIA
    fileMenu = QSoftMenuBar::menuFor(this);
    fileMenu->addAction("");
#else
    fileMenu = menuBar()->addMenu("&File");
#endif

  fileMenu->addAction("Rotate", this, SLOT(slotFileRotate()));
  fileMenu->addAction("New Game", this, SLOT(slotFileNew()));
  fileMenu->addAction("Select Game", this, SLOT(slotFileSelect()));
  fileMenu->addAction("Statistic", this, SLOT(slotFileStatistic()));
  fileMenu->addAction("Options", this, SLOT(slotFileOptions()));
  fileMenu->addAction("Exit", this, SLOT(slotFileQuit()));

  ///////////////////////////////////////////////////////////////////
  // menuBar entry protocolMenu
  protocolMenu=new QMenu();
  protocolMenu->addAction("Start Protocol", this, SLOT(slotProtocolStart()));
  protocolMenu->addAction("Stop Protocol", this, SLOT(slotProtocolStop()));
	
  ///////////////////////////////////////////////////////////////////
  // menuBar entry viewMenu
  //viewMenu=new QPopupMenu();
  //viewMenu->setCheckable(true);
  //viewMenu->insertItem("Tool&bar", this, SLOT(slotViewToolBar()), 0, ID_VIEW_TOOLBAR);
  //viewMenu->insertItem("&Statusbar", this, SLOT(slotViewStatusBar()), 0, ID_VIEW_STATUSBAR);

  //viewMenu->setItemChecked(ID_VIEW_TOOLBAR, true);
  //viewMenu->setItemChecked(ID_VIEW_STATUSBAR, true);

  ///////////////////////////////////////////////////////////////////
  // EDIT YOUR APPLICATION SPECIFIC MENUENTRIES HERE
  
  ///////////////////////////////////////////////////////////////////
  // menuBar entry helpMenu
  helpMenu=new QMenu();
  helpMenu->addAction("About...", this, SLOT(slotHelpAbout()));


  ///////////////////////////////////////////////////////////////////
  // MENUBAR CONFIGURATION
  // set menuBar() the current menuBar 

//  menuBar()->insertItem("&File", fileMenu);
//  menuBar()->insertItem("&Protocol", protocolMenu);
//
//  menuBar()->insertSeparator();
//  menuBar()->insertItem("&Help", helpMenu);
  
  ///////////////////////////////////////////////////////////////////
  // CONNECT THE SUBMENU SLOTS WITH SIGNALS

  connect(fileMenu, SIGNAL(highlighted(int)), SLOT(statusCallback(int)));
  connect(protocolMenu, SIGNAL(highlighted(int)), SLOT(statusCallback(int)));
  connect(helpMenu, SIGNAL(highlighted(int)), SLOT(statusCallback(int)));
  
}

void Freecell::initToolBar()
{
}

void Freecell::initStatusBar()
{
}

void Freecell::initDoc()
{
   doc=new FreecellDoc();
}

void Freecell::initView()
{ 
  view=new FreecellView(this, doc);
  setCentralWidget(view);
  view->enterFullScreen();
}

bool Freecell::queryExit()
{
  int exit=QMessageBox::information(this, "Quit...",
                                    "Do your really want to quit?",
                                    QMessageBox::Ok, QMessageBox::Cancel);

  if (exit==1)
  {

  }
  else
  {

  };

  return (exit==1);
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void Freecell::slotFileNew()
{
	int  i;
	char buffer[100];
	
  doc->newDoc();

  i = 1;
	if(view->game_active)
		if(newGameWarning()==QDialog::Accepted)	
		{
			i = 1;
			pstatistics->addLost();
		} else i = 0;
	
	if(i==1)
	{
   	srand(time(NULL));

   	current_game = rand()%MAX_GAMES;
    	
   	view->cards.clear();
   	view->cards.init(current_game);
   	view->card_selected = false;
   	view->rest = REST_INIT;
   	view->game_active = true;
	 	view->moves = 0;
	 	
	 	slotProtocolStop();
                view->repaint();
   }
    	
}



void Freecell::slotFileSelect()
{
	char buffer[100];
	int i;
		
	CSelectGameDlg dlg(this);

 	if(dlg.exec()==QDialog::Accepted)
	{	
   	i = 1;
   	if(view->game_active)
   		if(newGameWarning()==QDialog::Accepted)
   		{
   			i = 1;
   			pstatistics->addLost();
   		} else i = 0;

   	if(i==1)
   	{    		
 	   	view->cards.clear();
   	 	view->cards.init(dlg.getGamenumber());		
   		view->card_selected = false;
 	   	view->rest = REST_INIT;
   	 	view->game_active = true;
			view->moves = 0;
			        	
 	   	current_game = dlg.getGamenumber();
		 	
		 	slotProtocolStop();
                        view->repaint();
   	}
  }
 	
}


void Freecell::slotFileStatistic()
{
	if(pstatistics==NULL) pstatistics = new CStatistics(this, "", false);
	pstatistics->show();
}


void Freecell::slotFileQuit()
{ 
	if(view->game_active)
	{	
		if(newGameWarning()==QDialog::Accepted)	
		{
			pstatistics->addLost();
                        qApp->quit();
		}
	}
	else qApp->quit();
}


void Freecell::slotViewToolBar()
{
  ///////////////////////////////////////////////////////////////////
  // turn Toolbar on or off
  
  if (fileToolbar->isVisible())
  {
    fileToolbar->hide();
    //viewMenu->setItemChecked(ID_VIEW_TOOLBAR, false);
  } 
  else
  {
    fileToolbar->show();
    //viewMenu->setItemChecked(ID_VIEW_TOOLBAR, true);
  };

}

void Freecell::slotViewStatusBar()
{
  ///////////////////////////////////////////////////////////////////
  //turn Statusbar on or off
  
//  if (statusBar()->isVisible())
//  {
//    statusBar()->hide();
//    //viewMenu->setItemChecked(ID_VIEW_STATUSBAR, false);
//  }
//  else
//  {
//    statusBar()->show();
//    //viewMenu->setItemChecked(ID_VIEW_STATUSBAR, true);
//  }
  
  //statusBar()->message(IDS_STATUS_DEFAULT);
}

void Freecell::slotHelpAbout()
{
//  QMessageBox::about(this,"About...",
//                     IDS_APP_ABOUT );
}

void Freecell::slotStatusHelpMsg(const QString &text)
{
  ///////////////////////////////////////////////////////////////////
  // change status message of whole statusbar temporary (text, msec)
  //statusBar()->message(text, 2000);
}

void Freecell::statusCallback(int id_)
{
  switch (id_)
  {
    case ID_FILE_NEW:
         slotStatusHelpMsg("New Game");
         break;

    case ID_FILE_SELECT:
         slotStatusHelpMsg("Select Game");
         break;

    case ID_FILE_OPTIONS:
    		 slotStatusHelpMsg("Options");


    case ID_FILE_QUIT:
         slotStatusHelpMsg("Quits QFreeCell");
         break;

    case ID_HELP_ABOUT:
         slotStatusHelpMsg("Shows an aboutbox");
         break;
  }
}


/**  */
void Freecell::won()
{
  CCongratulation c(this);

  c.exec();
		
  pstatistics->addWon();
  pstatistics->show();
}

/**  */
void Freecell::lost()
{
  LostDlg *l = new LostDlg(0, " ", false);
  l->show();
}

/**  */
bool Freecell::newGameWarning()
{
	CLoseWarning l(this);
	return l.exec();
}

/**  */
void Freecell::closeEvent(QCloseEvent *e)
{
	if(view->game_active)
		if(newGameWarning()==QDialog::Accepted)	
		{
			pstatistics->addLost();
			e->accept();
		}
		else e->ignore();
	else e->accept();
}

/**  */
void Freecell::slotFileOptions()
{
}

void Freecell::slotFileRotate()
{
#ifdef QTOPIA
    QtopiaServiceRequest svreq("RotationManager", "setCurrentRotation(int)");
    svreq << rotation;
    svreq.send();
    rotation = (rotation ? 0 : 90);
#endif
}

/**  */
void Freecell::slotProtocolStart(){
//	char buffer[200];
//
//	sprintf(buffer, "%s/protocols", directory);
//	QFileDialog d(buffer, "*.qfc", this, 0, true);
//
//	d.setMode(QFileDialog::AnyFile);
//
//	if(d.exec()==QDialog::Accepted)
//	{
//		protocol_file = new QString(d.selectedFile());
//
//		if(protocol_fd!=NULL) fclose(protocol_fd);
//
//		protocol_fd = fopen((char*)protocol_file->data(), "a");
//
//		if(protocol_fd==NULL) protocol_file = new QString();
//		else
//		{
//   		time_t t = time(NULL);
//   		fprintf(protocol_fd, "Start: %sGame: %i\n", ctime(&t), current_game);
//			protocolMenu->setItemEnabled(ID_PROTOCOL_START, false);
//			protocolMenu->setItemEnabled(ID_PROTOCOL_STOP, true);
//   	}
//
//		view->repaint(5, 580, 150, 20, false);
//	}
}

/**  */
void Freecell::slotProtocolStop(){
	if(protocol_fd!=NULL)
	{
 		time_t t = time(NULL);
 		if(view->moves%10!=0) fprintf(protocol_fd, "\n");
 		fprintf(protocol_fd, "Stop: %s\n\n", ctime(&t));
		fclose(protocol_fd);
		protocol_fd = NULL;
	}
	
//	if(view->game_active)
//		protocolMenu->setItemEnabled(ID_PROTOCOL_START, true);
//	else
//		protocolMenu->setItemEnabled(ID_PROTOCOL_START, false);
	
//	protocolMenu->setItemEnabled(ID_PROTOCOL_STOP, false);

        view->repaint();
}

/**  */
void Freecell::myCopy(char *src, char *dst){
    QFile::copy(src, dst);
}
