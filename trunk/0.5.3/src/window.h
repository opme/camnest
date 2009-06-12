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

/// A special QGraphicsScene used for previewing a part or placing parts
 class Sheet: public QGraphicsScene {
  Q_OBJECT
  
  public:
     /// we use modes to track the approriate thing to do ZOOm selcetc lezad, select loops ,... inspired from qdiagramme example
          enum Mode { MoveItem, Zoom ,selectLoops,selectLeads};
     /**
      * 
      * @param preview if true the scene is used to preview the part, else it's for parts placement
      * @param parent the QGraphicsView parent
      */
     Sheet(bool preview=true,QWidget *parent = 0);
	 ///used for animating the cutter tool
	 QBasicTimer timer;
	 ///Penr of the line drawn when moving the tool
	 QPen toolPen;
	 ///@todo: use shape to detect if some parts are otu of the sheet within a margin.
	 
	 /// Rectangle representing the sheet metal bounds if preview isn't set
	 ///@see preview
	 QGraphicsRectItem *sheetRect;
          void setMode(Mode mode){myMode=mode;}
          /**
           * Set the sheetRect rectangle
           * @param rect new Sheetrect value
           */
          void setSheetRect();
	  /**
	   *        Moves the Pixmap of the cutter tool to the specfied point
	   * @param endPoint Point coordinates to move the tool to
	   */
	  void moveTool(QPointF endPoint);
	  
	public slots:
	 //
	 /**
	  * Start the animation of the cutter OR Clean the scene
	  * @param end if set Clean the scen else start the animation
	  */
	 void cleanUpAnim(bool end=false);
	
	
	 /**
	  * Zoom to show all the parts in the scene
	  */
	 void zoomFit();
	 
	 /**
	  * Zoom in / out by a factor
	  * @param in if set to true Zoom in else zoom Out
	  */
	 void zoom(bool in=true);
	 
	 protected:
     	 void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
         //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
         void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
     	 void wheelEvent(QGraphicsSceneWheelEvent *mouseEvent);
	 void timerEvent(QTimerEvent *event);
	
	 signals:
	 
	 /**
	  *        Used to track the loop being drawn in animation mode
	  * @param currentLoop The loop pos to draw
	  */
	 void progressionDone(const int currentLoop);
         /// inform the mainUi that the retc zoom had been drawn
         void zoomRect(QPointF p1,QPointF p2);



	 private:
         Mode myMode;
	 ///access The application config settings for colors/preferences
	 QSettings settings;
	 /// to track the selection (not in preview mode)
	 bool selectedSome;
         /// @note: a sheet can be for part previews or for parts placing( sheet metal)
	 /**If set the sheet is for part preview else its for parts placement
	 */
         bool preview;
 
 };
 
   #endif 
