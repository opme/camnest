#ifndef SHEET_H
#define SHEET_H
#include <QtGui>
#include <QWidget>
  
///LibDxf headers  
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
  //
  
   class SheetMetal: public QWidget  /// could be a Qview directly ???
 {
     Q_OBJECT

 public:
     SheetMetal(QWidget *parent = 0);
     QSize sizeHint()  ;
	 QSize minimumSizeHint(); 
	 
	 //QGraphicsItem *selectedItem;
  private:     
	  
     // QList<QGraphicsItem *> selectedItems;
  
  };
  
    
 class Sheet: public QGraphicsScene {
  Q_OBJECT
  
  public:
     Sheet(QWidget *parent = 0);
	 QGraphicsItem *selectedItem;
	 QGraphicsLineItem *test;
	 QGraphicsItemGroup *selection;
	
  protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	 void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void wheelEvent(QGraphicsSceneWheelEvent *mouseEvent);
 
 
 };
 
 class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	 MainWindow();
	 void createStatusBar();
	 void createToolBars();
	 void createMenus();
	 void addArc(double cx,double cy,double radius,double teta1,double teta2);
	 QList <QList<QPointF > > commonPoints(QList <QPointF > pointsList,QList <QPointF > arcsList,QList <QPainterPath > arcsPathsList);
	 QList <QList<QPointF > > organiseEntities(QList <QPointF > pointsList,QList <QPainterPath > partPathsList);
	 QList <QPointF >  addCircles(QList <QPointF > circlePointsList,QList <QPainterPath > circlesPathsList);
	 
	 QList <QList<QPointF > > linkLines (QList <QList<QPointF > >  linesFinal);
	 
	 SheetMetal *sheet;
	 
   private:
     QAction *aboutAction;
     QAction *openAction;
     QAction *clearAction;   
     QAction *mirrorAction;
	 QAction *yMirror;
	 QAction *rotateAction; 
     QAction *generateAction;
     QMenu *fileMenu;
     QToolBar *fileToolBar;
     QToolBar *editToolBar;
	 
   private slots:
     void about();
	 void readDxfFile();
	 void openFile();
	 void clearScene();
	 void rotateParts();
	 void generatePath();
  };
  
  
  
  /// Note: if public QObject isn't declared the macro will fail when compiling   
class Part: public QObject,public QGraphicsItem { 
  Q_OBJECT
 
  public:
     Part(QWidget *parent = 0);	
	  /// implemant the virtual public functions to make them our class specifec
	   QRectF boundingRect() const
     {
         qreal penWidth = 1;
         return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                       20 + penWidth / 2, 20 + penWidth / 2);
     }
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	 
 };
  
  

  
  #endif 
