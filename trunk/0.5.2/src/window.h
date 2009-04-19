#ifndef WINDOW_H
#define WINDOW_H
// C++ Interface: window
//
// Description: 
//
//
// Author: invite <invite@invite-laptop>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <QtGui>
#include <QWidget>

 class Sheet: public QGraphicsScene {
  Q_OBJECT
  
  public:
     Sheet(bool preview=true,QWidget *parent = 0);
	 
	 QBasicTimer timer;
	 
	 QPen toolPen;
//	 QSettings settings;
	 
	 ///Rectangle representing the sheet metal bounds.@todo: use shape to detect if some parts are otu of the sheet within a margin.
//	  QRect outlineRect;
	  QGraphicsRectItem *sheetRect;
	  
          void setSheetRect(QRect rect=QRect(0,0,1,1));
	  void moveTool(QPointF endPoint);
	  
	public slots:
	 ///Clean up or start the animation
	 void cleanUpAnim(bool end=false);
	
	 void zoomFit();
	 void zoom(bool in=true);
	 
	 protected:
     	 void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
     	 void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
         void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
     	 void wheelEvent(QGraphicsSceneWheelEvent *mouseEvent);
	 void timerEvent(QTimerEvent *event);
	
	 signals:
	 void progressionDone(const int currentLoop);
	 //void animatonEnded();
	 private:
	 QSettings settings;
	 bool selectedSome;
         /// @note: a sheet can be for part previews or for parts placing( sheet metal)
         bool preview;
 
 };
 
   #endif 
