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
     SheetMetal(QGraphicsScene *scene,QWidget *parent = 0);
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
	 
	 QList <QList<QPointFWithParent  > > organiseEntities(QList <QPointFWithParent > pointsList,QList <QPainterPath > partPathsList);
	 QList <QPointF >  addCircles(QList <QPointF > circlePointsList,QList <QPainterPath > circlesPathsList);
	 /// remove a point from the list
	 void shrink(QList <QPointFWithParent > &pointsList,QList <QPointFWithParent > &pointsListNew,int pos,int oldPos);
	 ///find a lonley point if any or repreted one
	 int newPos(QList <QPointFWithParent > pointsList);
	 SheetMetal *sheet;
	 SheetMetal *pathSheet;
 
   private:
     QAction *aboutAction;
     QAction *openAction;
     QAction *clearAction;  
	 QAction *deleteAction;  
	 //QAction *stepAction; 
     QAction *mirrorAction;
	 QAction *yMirror;
	 QAction *rotateAction; 
     QAction *generateAction;
	 QAction *saveAction;
	 QAction *stepAction;
	 QAction *simulateAction;
	 QAction *zoomFitAction;
	 
     QMenu *fileMenu;
	 
     QToolBar *fileToolBar;
     QToolBar *editToolBar;
	 
	 QListView *piecesList;
	 
   private slots:
     void about();
	 void openFile();
	 bool saveFile();
	 void clearScene();
	 void rotateParts();
	 void generatePath();
	 void stepByStep();
	 void zoomFit();
	void deleteItems();
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
	 QPointFWithParent translateEntity(QPointFWithParent oldPoint, QPointF offset);
     double getAngle(QPointF start_point,QPointF end_point);
	 QPointF ArrowWing1(double line_angle,QPointF end_point);
	 QPointF ArrowWing2(double line_angle,QPointF end_point);

	
  
  #endif 
