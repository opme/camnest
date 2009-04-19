#include "window.h"
// C++ Implementation: window
//
// Description: 
//
//
// Author: invite <invite@invite-laptop>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
    
   	///Todo move to class window and get value from settings dialog
	/// used when drawing toolpath and for homing on G-code
	 QPointF absoluteHome(0,0);
	 QPointF homePoint(0,0);
	 int currentLoop=0;
	 QGraphicsPixmapItem *toolPix;
	 QGraphicsLineItem toolLine;
	
	
	
      Sheet::Sheet (bool prev,QWidget *parent):QGraphicsScene (parent) {
	 selectedSome=false;
         preview=prev;
	 ///draw the sheet rectangle if we're not previewing the part
	 if (!preview) {
         ///start with a default sheet rect dimension
             sheetRect=new QGraphicsRectItem();
             setSheetRect();
	 }
	 toolPen = QPen  (Qt::blue,1, Qt::DotLine);
	}
	
      
      void Sheet::setSheetRect(QRect rect){

          QPen rectPen( settings.value("Colors/sheetPen").value<QColor>());
          QBrush rectBrush(Qt::NoBrush);
	  if (settings.value("Options/colorizeInner").toInt()==2){
		 rectBrush=QBrush(settings.value("Colors/sheetBrush").value<QColor>());
		}

         ///if a sheet rect had been already created cause there is no simple way to update it's color
          if (sheetRect!=0)    delete sheetRect;

          sheetRect=addRect(rect,rectPen,rectBrush);
      } 
	

void Sheet::zoomFit(){
///@fixme: change to an approch not depending on the graphicxsView
	 views().at(0)->fitInView(itemsBoundingRect(),Qt::KeepAspectRatio);
 }
	
	///The default mouse move event on diagScene handle a one by one item move. To move mutiple items
	/// we implment outr own one.
	
	
	///@fixme have to get a bool from mouseClickEvent to avoid unessary calls to selectedItems with no selection
	void Sheet::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

            ///if we're in preview sheet we do nothing on mouse move
            if (preview) {
                ///must propagate the signal (for leads  moving e.g)
                mouseEvent->ignore();

            }
            else{
            if (selectedSome){
	 	 qDebug()<<"Moving the part";
		 QGraphicsScene::mouseMoveEvent(mouseEvent);
		
		 if((selectedItems()).size()>1){
		 qDebug()<<"moving multi items";
		/// foreach ( QGraphicsItem *item ,selectedItems()){			  
			/// qgraphicsitem_cast<Part *>(item)->moveMeBy(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
			///}
		 
		}
             }
	   }
           QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	
	void Sheet::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 QGraphicsScene::mouseReleaseEvent(mouseEvent);	
	}
 
        void Sheet::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
	if ((selectedItems()).size()>=1){
	selectedSome=true;
	qDebug()<<"made selection";
	QGraphicsScene::mousePressEvent(mouseEvent);
	}
        else {
         selectedSome=false;
         mouseEvent->ignore();
        }
	}
 
	void Sheet::wheelEvent(QGraphicsSceneWheelEvent *mouseEvent)    {
	 /// @todo: add option to change modifier key to activate zoom
	 if(mouseEvent->modifiers()==Qt::ControlModifier){

	 qreal scaleFactor=pow((double)2, -mouseEvent->delta() / 240.0);
		  qreal factor =views().at(0)->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
     if (factor < 0.07 || factor > 10)
         return;

     	 views().at(0)->scale(scaleFactor, scaleFactor);
	 views().at(0)->centerOn(mouseEvent->scenePos());
	 ///necerrary to avoid  propagating event to child items although no mouse whell is implmenton parts for now...
	 mouseEvent->setAccepted(true);
		//return;
	 }
	}
		 
	void Sheet::zoom(bool in){
	qreal scaleFactor;
	if (in){
	scaleFactor=pow((double)2, -24 / 240.0);
	}
	else{
	scaleFactor=pow((double)2, 24 / 240.0);
	}
	qreal factor =views().at(0)->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	
     	if (factor < 0.07 || factor > 10)
         return;

     	 views().at(0)->scale(scaleFactor, scaleFactor);	  
	}
void Sheet::cleanUpAnim(bool end){

                removeItem(&toolLine);
                removeItem(toolPix);
                currentLoop=0;

                ///@todo use Qt rc files
                if (!end){
                 toolPix=addPixmap(QPixmap("/home/invite/Desktop/bazar/PFE/camnest/tool.png"));
                 ///to guarantee that the tool is on top
                 /// @note: first we find part loops at z=0 then  comes Leads and loops numbers and finally the tool pix when in animation mode
                 toolPix->setZValue(3);
                  toolPix->setPos(absoluteHome);
                 }
                 toolLine.setZValue(3);

                 homePoint=absoluteHome;
        }

   void Sheet::timerEvent(QTimerEvent *event) {

     if (event->timerId() == timer.timerId()) {

                         qDebug()<<"timer trigger";
                         emit progressionDone(currentLoop);
                         ++currentLoop;

     } else {
         /// deal with other event...this way it will make it's way and propagate
                 qDebug()<<"other timer";
                 event->ignore();
     }

        }

   void Sheet::moveTool(QPointF endP){

         qDebug()<<"Moving to point "<<endP;
         ///Fixme there's a crash in setPos when animating clearing then reanomating
         toolLine.setLine( QLineF(homePoint,endP));
         toolLine.setPen(toolPen);
         ///@note as tooline is already inserted Qt gives us an info message
         ///@fixme use set pos or something like that
         addItem(&toolLine);
         toolPix->setPos(endP);
         ///To ensure that we start at the core'ct position when going to the next part
         homePoint=endP;
        }


