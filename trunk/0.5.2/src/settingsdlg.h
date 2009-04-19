#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

 //CONFIG DIALOG INTERFACE
#include "ui_settingsdialog.h"
#include <QtGui>
//
// C++ Interface: settingsdlg
//
// Description: 
//
//
// Author: invite <invite@invite-laptop>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
  
  class SettingsDialog : public QDialog, private Ui::SettingsDialog {
     Q_OBJECT

	 public:
     	 SettingsDialog(QWidget *parent = 0);
	 QSettings settings;
	 
	 public slots:
	 void setPenColor();
	 
	 void setBrushColor();
	 // void setMyColor();
	 void setSheetPenColor();
	 void setSheetBrushColor();
	 //void setTextColor();
	 void setTextFont();
	 void setInner();
	 void save();
	 void loadSettings();
	
	// private:
     	//Ui::SettingsDialog ui;
 };


   #endif 
