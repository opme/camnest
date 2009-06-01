# include "settingsdlg.h"
//
// C++ Implementation: settingsdlg
//
// Description: 
//
//
// Author: invite <invite@invite-laptop>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
 ///@todo should set up thing only when interface is called the first time

SettingsDialog::SettingsDialog(QWidget *parent)   : QDialog(parent)
 {
	 setupUi(this);
	 qDebug()<< settings.fileName();
	 loadSettings();
	
	 connect (penPB,SIGNAL(clicked()),this, SLOT( setPenColor())); 
	 connect (brushPB,SIGNAL(clicked()),this, SLOT( setBrushColor())); 
	  ///@todo create own button to change color
	 //connect (sheetPenPB,SIGNAL(clicked()),this, SLOT( setMyColor())); 
	 //connect (sheetBrushPB,SIGNAL(clicked()),this, SLOT( setMyColor()));
	 connect (sheetPenPB,SIGNAL(clicked()),this, SLOT( setSheetPenColor())); 
	 connect (sheetBrushPB,SIGNAL(clicked()),this, SLOT( setSheetBrushColor()));
	 connect (setTextPB,SIGNAL(clicked()),this, SLOT( setTextFont()));
	 connect (texturePB,SIGNAL(clicked()),this, SLOT( setInner()));
	 connect (okButton,SIGNAL(clicked()),this, SLOT( save()));
 }
 
  void SettingsDialog:: setInner(){
	 
	}
	
 void SettingsDialog:: save(){
         //qDebug()<<"saving seetings";
     settings.beginGroup("Colors");
	 
     settings.setValue("pen", penPB->palette().background().color());
	 if (InnerColorCHK->checkState()==Qt::Checked){
     settings.setValue("brush",brushPB->palette().background().color());	
	 }
	 else 
	 {
	  settings.setValue("brush",Qt::NoBrush);	 
	 }
	 //settings.setValue("text",textPB->palette().background().color());
	 //settings.setValue("brush Color",texturePB->palette().background().color());
	settings.setValue("sheetPen",sheetPenPB->palette().background().color());  
	settings.setValue("sheetBrush",sheetBrushPB->palette().background().color()); 
	
	settings.endGroup();
	 
	 settings.beginGroup("Fonts");
	 settings.setValue("font", fontCB->currentFont());
	 settings.setValue("index", fontCB-> currentIndex () );
	settings.endGroup();
		 	 
	settings.beginGroup("Leads");
	settings.setValue("radius", leadRadiusSB->value ());
	settings.setValue("angle", leadAngleSB->value ());
        settings.setValue("radiusMotion", leadRadiusMotionSB->value ());
	settings.setValue("leadDist", leadDistSB->value ());
	settings.setValue("minLeadDist",minLeadDistSB->value ());
	settings.endGroup();	 
	 
	 settings.beginGroup("Options");
	 settings.setValue("sheetH", sheetH->value ());
	 settings.setValue("sheetW", sheetW->value ());
         settings.setValue("colorizeInner", InnerColorSheetCHK->checkState());
         settings.setValue("optPath", optPathCB->checkState());
         settings.setValue("plasmaMode", plasmaCB->checkState());
	 settings.endGroup();
	 ///@todo emit signal to update scenes

         emit accepted();
         close ();
	}
	
	
	void SettingsDialog:: loadSettings(){	 
	 //qDebug()<<"loading seetings";
	 penPB->setPalette(QPalette( settings.value("Colors/pen").value<QColor>()));
	 sheetPenPB->setPalette(QPalette( settings.value("Colors/sheetPen").value<QColor>()));
	 sheetBrushPB->setPalette(QPalette( settings.value("Colors/sheetBrush").value<QColor>())); 
	 //textPB->setPalette(QPalette( settings.value("Colors/text").value<QColor>()));	 
	 fontCB->setCurrentIndex(settings.value("Fonts/index").toInt());
	 QFont font = settings.value("Fonts/font").value<QFont>();
	 if (settings.value("Options/colorizeInner").toInt()==2) {
	 InnerColorCHK->setCheckState(Qt::Checked);
	 brushPB->setPalette(QPalette( settings.value("Colors/brush").value<QColor>()));
	 }
	 else {
	 ///@fixem: check for previously used color
	 InnerColorCHK->setCheckState(Qt::Unchecked);
	 }
	 //*****************leads proerties ***************
	 leadRadiusSB->setValue(settings.value("Leads/radius").toDouble());
         leadRadiusMotionSB->setValue(settings.value("Leads/radiusMotion").toDouble());
	 leadAngleSB->setValue(settings.value("Leads/angle").toInt());
	 minLeadDistSB->setValue(settings.value("Leads/minLeadDist").toDouble());
	 leadDistSB->setValue(settings.value("Leads/leadDist").toDouble());
         //**********************Sheet metal props*********************
         sheetW->setValue(settings.value("Options/sheetW").toInt());
         sheetH->setValue(settings.value("Options/sheetH").toInt());

         //**************Various options****************
         if (settings.value("Options/optPath").toInt()==2) {
         optPathCB->setCheckState(Qt::Checked);
         }
           if (settings.value("Options/plasmaMode").toInt()==2) {
         plasmaCB->setCheckState(Qt::Checked);
         }
	 
	 }
	 
	  
	  void SettingsDialog::setTextFont(){
	  bool ok;
	 QFont font=QFontDialog::getFont(&ok,fontCB->currentFont(), this);
	 if (ok) {
		  fontCB->setCurrentFont(font);
		}
	 else {
		 fontCB->currentFont();
		}
	}
   
 void SettingsDialog::setPenColor(){
	 QColor color = QColorDialog::getColor(penPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
	 penPB->setPalette(QPalette(color)); 
     }
	}
   
   void SettingsDialog::setBrushColor(){
	 QColor color = QColorDialog::getColor(brushPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
	 brushPB->setPalette(QPalette(color)); 
     }
	}
	
	  void SettingsDialog::setSheetBrushColor(){
	 QColor color = QColorDialog::getColor(sheetBrushPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
	 sheetBrushPB->setPalette(QPalette(color)); 
     }
	}
	
	  void SettingsDialog::setSheetPenColor(){
	 QColor color = QColorDialog::getColor(sheetPenPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
	 sheetPenPB->setPalette(QPalette(color)); 
     }
	}
	
	
      //void SettingsDialog::setMyColor(){
	// QColor color = QColorDialog::getColor(sender()->palette().color(QPalette::Active,QPalette::Window), this);
     //if (color.isValid()) {
		 ///How to make it workÂ§
	 ///sender ()->setPalette(QPalette(color)); 
	 //sender()->setPalette(QPalette(color)); 
     //}
	//}
   
   
     // void SettingsDialog::setTextColor(){
	// QColor color = QColorDialog::getColor(textPB->palette().color(QPalette::Active,QPalette::Window), this);
    // if (color.isValid()) {
		 ///How to make it workÃÂ§
	 ///sender ()->setPalette(QPalette(color)); 
	// textPB->setPalette(QPalette(color)); 
    // }
	//}
