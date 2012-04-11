#############################################################################
# Makefile for building: qfreecell
# Generated by qmake (2.01a) (Qt 4.6.1) on: Wed Apr 11 16:17:19 2012
# Project:  qfreecell.pro
# Template: app
# Command: /home/radek/qtsdk-2010.01/qt/bin/qmake -spec ../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qfreecell.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -I. -I../qtsdk-2010.01/qt/include/QtCore -I../qtsdk-2010.01/qt/include/QtGui -I../qtsdk-2010.01/qt/include -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-rpath,/home/radek/qtsdk-2010.01/qt/lib
LIBS          = $(SUBLIBS)  -L/home/radek/qtsdk-2010.01/qt/lib -lQtGui -L/home/radek/qtsdk-2010.01/qt/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/radek/qtsdk-2010.01/qt/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		ccongratulationdata.cpp \
		closewarningdata.cpp \
		freecell.cpp \
		lostdlg.cpp \
		freecellview.cpp \
		closewarning.cpp \
		cselectgamedlg.cpp \
		ccongratulation.cpp \
		cstatistics.cpp \
		lostdlgdata.cpp \
		cstatisticsdata.cpp \
		cselectgamedlgdata.cpp \
		coptions.cpp \
		cards.cpp \
		freecelldoc.cpp \
		coptionsdata.cpp moc_lostdlg.cpp \
		moc_freecellview.cpp \
		moc_freecelldoc.cpp \
		moc_freecell.cpp \
		moc_cstatistics.cpp \
		moc_cselectgamedlg.cpp \
		moc_coptions.cpp \
		moc_closewarning.cpp \
		moc_ccongratulation.cpp
OBJECTS       = main.o \
		ccongratulationdata.o \
		closewarningdata.o \
		freecell.o \
		lostdlg.o \
		freecellview.o \
		closewarning.o \
		cselectgamedlg.o \
		ccongratulation.o \
		cstatistics.o \
		lostdlgdata.o \
		cstatisticsdata.o \
		cselectgamedlgdata.o \
		coptions.o \
		cards.o \
		freecelldoc.o \
		coptionsdata.o \
		moc_lostdlg.o \
		moc_freecellview.o \
		moc_freecelldoc.o \
		moc_freecell.o \
		moc_cstatistics.o \
		moc_cselectgamedlg.o \
		moc_coptions.o \
		moc_closewarning.o \
		moc_ccongratulation.o
DIST          = ../qtsdk-2010.01/qt/mkspecs/common/g++.conf \
		../qtsdk-2010.01/qt/mkspecs/common/unix.conf \
		../qtsdk-2010.01/qt/mkspecs/common/linux.conf \
		../qtsdk-2010.01/qt/mkspecs/qconfig.pri \
		../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf \
		../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf \
		../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf \
		../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf \
		../qtsdk-2010.01/qt/mkspecs/features/debug.prf \
		../qtsdk-2010.01/qt/mkspecs/features/default_post.prf \
		../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf \
		../qtsdk-2010.01/qt/mkspecs/features/qt.prf \
		../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf \
		../qtsdk-2010.01/qt/mkspecs/features/moc.prf \
		../qtsdk-2010.01/qt/mkspecs/features/resources.prf \
		../qtsdk-2010.01/qt/mkspecs/features/uic.prf \
		../qtsdk-2010.01/qt/mkspecs/features/yacc.prf \
		../qtsdk-2010.01/qt/mkspecs/features/lex.prf \
		../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf \
		qfreecell.pro
QMAKE_TARGET  = qfreecell
DESTDIR       = 
TARGET        = qfreecell

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: qfreecell.pro  ../qtsdk-2010.01/qt/mkspecs/linux-g++-64/qmake.conf ../qtsdk-2010.01/qt/mkspecs/common/g++.conf \
		../qtsdk-2010.01/qt/mkspecs/common/unix.conf \
		../qtsdk-2010.01/qt/mkspecs/common/linux.conf \
		../qtsdk-2010.01/qt/mkspecs/qconfig.pri \
		../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf \
		../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf \
		../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf \
		../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf \
		../qtsdk-2010.01/qt/mkspecs/features/debug.prf \
		../qtsdk-2010.01/qt/mkspecs/features/default_post.prf \
		../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf \
		../qtsdk-2010.01/qt/mkspecs/features/qt.prf \
		../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf \
		../qtsdk-2010.01/qt/mkspecs/features/moc.prf \
		../qtsdk-2010.01/qt/mkspecs/features/resources.prf \
		../qtsdk-2010.01/qt/mkspecs/features/uic.prf \
		../qtsdk-2010.01/qt/mkspecs/features/yacc.prf \
		../qtsdk-2010.01/qt/mkspecs/features/lex.prf \
		../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf \
		/home/radek/qtsdk-2010.01/qt/lib/libQtGui.prl \
		/home/radek/qtsdk-2010.01/qt/lib/libQtCore.prl
	$(QMAKE) -spec ../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qfreecell.pro
../qtsdk-2010.01/qt/mkspecs/common/g++.conf:
../qtsdk-2010.01/qt/mkspecs/common/unix.conf:
../qtsdk-2010.01/qt/mkspecs/common/linux.conf:
../qtsdk-2010.01/qt/mkspecs/qconfig.pri:
../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf:
../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf:
../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf:
../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf:
../qtsdk-2010.01/qt/mkspecs/features/debug.prf:
../qtsdk-2010.01/qt/mkspecs/features/default_post.prf:
../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf:
../qtsdk-2010.01/qt/mkspecs/features/qt.prf:
../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf:
../qtsdk-2010.01/qt/mkspecs/features/moc.prf:
../qtsdk-2010.01/qt/mkspecs/features/resources.prf:
../qtsdk-2010.01/qt/mkspecs/features/uic.prf:
../qtsdk-2010.01/qt/mkspecs/features/yacc.prf:
../qtsdk-2010.01/qt/mkspecs/features/lex.prf:
../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf:
/home/radek/qtsdk-2010.01/qt/lib/libQtGui.prl:
/home/radek/qtsdk-2010.01/qt/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qfreecell.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qfreecell1.0.0 || $(MKDIR) .tmp/qfreecell1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qfreecell1.0.0/ && $(COPY_FILE) --parents resource.h main.h lostdlg.h freecellview.h freecelldoc.h freecell.h cstatistics.h cselectgamedlg.h coptions.h closewarning.h ccongratulation.h cards.h .tmp/qfreecell1.0.0/ && $(COPY_FILE) --parents main.cpp ccongratulationdata.cpp closewarningdata.cpp freecell.cpp lostdlg.cpp freecellview.cpp closewarning.cpp cselectgamedlg.cpp ccongratulation.cpp cstatistics.cpp lostdlgdata.cpp cstatisticsdata.cpp cselectgamedlgdata.cpp coptions.cpp cards.cpp freecelldoc.cpp coptionsdata.cpp .tmp/qfreecell1.0.0/ && (cd `dirname .tmp/qfreecell1.0.0` && $(TAR) qfreecell1.0.0.tar qfreecell1.0.0 && $(COMPRESS) qfreecell1.0.0.tar) && $(MOVE) `dirname .tmp/qfreecell1.0.0`/qfreecell1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qfreecell1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_lostdlg.cpp moc_freecellview.cpp moc_freecelldoc.cpp moc_freecell.cpp moc_cstatistics.cpp moc_cselectgamedlg.cpp moc_coptions.cpp moc_closewarning.cpp moc_ccongratulation.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_lostdlg.cpp moc_freecellview.cpp moc_freecelldoc.cpp moc_freecell.cpp moc_cstatistics.cpp moc_cselectgamedlg.cpp moc_coptions.cpp moc_closewarning.cpp moc_ccongratulation.cpp
moc_lostdlg.cpp: main.h \
		lostdlg.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) lostdlg.h -o moc_lostdlg.cpp

moc_freecellview.cpp: freecelldoc.h \
		cards.h \
		freecellview.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) freecellview.h -o moc_freecellview.cpp

moc_freecelldoc.cpp: freecelldoc.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) freecelldoc.h -o moc_freecelldoc.cpp

moc_freecell.cpp: freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h \
		main.h \
		freecell.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) freecell.h -o moc_freecell.cpp

moc_cstatistics.cpp: main.h \
		cstatistics.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) cstatistics.h -o moc_cstatistics.cpp

moc_cselectgamedlg.cpp: main.h \
		cselectgamedlg.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) cselectgamedlg.h -o moc_cselectgamedlg.cpp

moc_coptions.cpp: main.h \
		freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h \
		coptions.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) coptions.h -o moc_coptions.cpp

moc_closewarning.cpp: main.h \
		closewarning.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) closewarning.h -o moc_closewarning.cpp

moc_ccongratulation.cpp: main.h \
		ccongratulation.h
	/home/radek/qtsdk-2010.01/qt/bin/moc $(DEFINES) $(INCPATH) ccongratulation.h -o moc_ccongratulation.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

ccongratulationdata.o: ccongratulationdata.cpp ccongratulation.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ccongratulationdata.o ccongratulationdata.cpp

closewarningdata.o: closewarningdata.cpp closewarning.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o closewarningdata.o closewarningdata.cpp

freecell.o: freecell.cpp freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h \
		main.h \
		filenew.xpm \
		cselectgamedlg.h \
		cstatistics.h \
		ccongratulation.h \
		lostdlg.h \
		closewarning.h \
		coptions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o freecell.o freecell.cpp

lostdlg.o: lostdlg.cpp lostdlg.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lostdlg.o lostdlg.cpp

freecellview.o: freecellview.cpp freecellview.h \
		freecelldoc.h \
		cards.h \
		main.h \
		freecell.h \
		resource.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o freecellview.o freecellview.cpp

closewarning.o: closewarning.cpp closewarning.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o closewarning.o closewarning.cpp

cselectgamedlg.o: cselectgamedlg.cpp cselectgamedlg.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cselectgamedlg.o cselectgamedlg.cpp

ccongratulation.o: ccongratulation.cpp ccongratulation.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ccongratulation.o ccongratulation.cpp

cstatistics.o: cstatistics.cpp cstatistics.h \
		main.h \
		freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cstatistics.o cstatistics.cpp

lostdlgdata.o: lostdlgdata.cpp lostdlg.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lostdlgdata.o lostdlgdata.cpp

cstatisticsdata.o: cstatisticsdata.cpp cstatistics.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cstatisticsdata.o cstatisticsdata.cpp

cselectgamedlgdata.o: cselectgamedlgdata.cpp cselectgamedlg.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cselectgamedlgdata.o cselectgamedlgdata.cpp

coptions.o: coptions.cpp coptions.h \
		main.h \
		freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o coptions.o coptions.cpp

cards.o: cards.cpp cards.h \
		main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cards.o cards.cpp

freecelldoc.o: freecelldoc.cpp freecelldoc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o freecelldoc.o freecelldoc.cpp

coptionsdata.o: coptionsdata.cpp coptions.h \
		main.h \
		freecell.h \
		freecellview.h \
		freecelldoc.h \
		cards.h \
		resource.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o coptionsdata.o coptionsdata.cpp

moc_lostdlg.o: moc_lostdlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_lostdlg.o moc_lostdlg.cpp

moc_freecellview.o: moc_freecellview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_freecellview.o moc_freecellview.cpp

moc_freecelldoc.o: moc_freecelldoc.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_freecelldoc.o moc_freecelldoc.cpp

moc_freecell.o: moc_freecell.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_freecell.o moc_freecell.cpp

moc_cstatistics.o: moc_cstatistics.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_cstatistics.o moc_cstatistics.cpp

moc_cselectgamedlg.o: moc_cselectgamedlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_cselectgamedlg.o moc_cselectgamedlg.cpp

moc_coptions.o: moc_coptions.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_coptions.o moc_coptions.cpp

moc_closewarning.o: moc_closewarning.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_closewarning.o moc_closewarning.cpp

moc_ccongratulation.o: moc_ccongratulation.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ccongratulation.o moc_ccongratulation.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

