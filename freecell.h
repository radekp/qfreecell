/***************************************************************************
                          freecell.h  -  description
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

#ifndef FREECELL_H
#define FREECELL_H

// include files for QT
#include <qstring.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include <qstatusbar.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>
#include <qprinter.h>
#include <qpainter.h>
#include <QMenu>

// application specific includes
#include "freecellview.h"
#include "freecelldoc.h"
#include "resource.h"

#include "main.h"
#include "cards.h"

/**
  * This Class is the base class for your application. It sets up the main
  * window and providing a menubar, toolbar
  * and statusbar. For the main view, an instance of class FreecellView is
  * created which creates your view.
  */
class Freecell : public QMainWindow
{
  Q_OBJECT
  
  public:
    /** construtor */
    Freecell(char *dir);
    /** destructor */
    ~Freecell();
    /** initMenuBar creates the menu_bar and inserts the menuitems */
    void initMenuBar();
    /** this creates the toolbars. Change the toobar look and add new toolbars in this
     * function */
    void initToolBar();
    /** setup the statusbar */
    void initStatusBar();
    /** setup the document*/
    void initDoc();
    /** setup the mainview*/
    void initView();
  
    /** overloaded for Message box on last window exit */
    bool queryExit();
  /**  */
  void won();
  /**  */
  void lost();
  /**  */
  bool newGameWarning();
  /**  */
  void closeEvent(QCloseEvent *e);
  /**  */
  void myCopy(char *src, char *dst);

  public slots:
  
    /** switch argument for Statusbar help entries on slot selection */
    void statusCallback(int id_);
    /** open a new application window */
  
    /** generate a new document in the actual view */
    void slotFileNew();
    void slotFileSelect();
    /** open a document */

    /** save a document */
    void slotFileStatistic();

    /** exits the application */
    void slotFileQuit();

    /** toggle the toolbar*/
    void slotViewToolBar();
    /** toggle the statusbar*/
    void slotViewStatusBar();
  
    /** shows an about dlg*/
    void slotHelpAbout();
  
    /** change the status message of the whole statusbar temporary */
    void slotStatusHelpMsg(const QString &text);
  /**  */
  void slotFileOptions();

  /** */
  void slotProtocolStart();
  /**  */
  void slotProtocolStop();

  private:

    /** view is the main widget which represents your working area. The View
     * class should handle all events of the view widget.  It is kept empty so
     * you can create your view according to your application's needs by
     * changing the view class.
     */
    FreecellView *view;
    /** doc represents your actual document and is created only once. It keeps
     * information such as filename and does the serialization of your files.
     */
    FreecellDoc *doc;
  
    /** file_menu contains all items of the menubar entry "File" */
    QMenu *fileMenu;
    /** edit_menu contains all items of the menubar entry "Edit" */
    QMenu *protocolMenu;
    /** view_menu contains all items of the menubar entry "View" */
    QMenu *viewMenu;
    /** view_menu contains all items of the menubar entry "Help" */
    QMenu *helpMenu;
  
    QToolBar *fileToolbar;

public: // Public attributes
  /**  */
  class CStatistics *pstatistics;

	struct options{
		char   *empty_file;
		char   *background_file;
		QColor *background_color;
		bool   *background_enabled;
		int    *num_freecells;
		int    *spinbox_freecells_min;
	}opt;

	/** protocol file name */
  QString *protocol_file;
  /**  */
  FILE *protocol_fd;
  /**  */
  int current_game;
  /**  */
  char directory[200];
  /**  */
  char game_directory[200];;
};
#endif 

