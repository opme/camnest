#ifndef SHEET_H
#define SHEET_H
#include <QtGui>
#include <QWidget>
  
///LibDxf headers  
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
  //
  
  /**
	 the class GCode implement some essential functions along with some optional one:
	 -Add Header
	 -Add line
	 -Add arc
	 -Add circle
	 -Add line number
	 -Add comment
	 -Add EOF
	 -Write to file
	 
  */
  
  class GCode : public QTextStream{
  
	 public:
	 GCode( QFile *file);
	 void writeHeader();
	 void writeClosedLoop(QList<QPointFWithParent > closedLoop);
	 void writeCircleLoop(QList<QPointF> circleLoop, QList<qreal>  circlesRadius);
	 void writeEnd();
	 void comment(QString comment);
	 void addLineNumber ();
	 
	 void home();
	 void rapidMove (qreal X, qreal Y,qreal Z);
	 void feedRateMove (qreal X,qreal Y,qreal Z);
	 
	 void ArcCut (qreal X,qreal Y,qreal Z,qreal I,qreal J,qreal radius,bool cw=true);
	 
	 void appendCode (QString code, QString value="");
	 void appendNumCode ( QString code, qreal value);
	 
	 
	 void  cartidgeReturn() { *this<< endl;}
	   //private:
	 QString fileName;
	 int lineNumber;
	 qreal lastX, lastY,lastZ ,homeX, homeY, homeZ;
	 QString lastgcode;
	 int lastfeed;	 
    };
  
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
	 
	 QList <QList<QPointFWithParent  > > organiseEntities(QList <QPointFWithParent > pointsList,QList <QPainterPath > partPathsList);
	 QList <QPointF >  addCircles(QList <QPointF > circlePointsList,QList <QPainterPath > circlesPathsList);
	 
	/// de"precated version of the algo to organsie the points 
	 QList <QList<QPointF > > commonPoints(QList <QPointF > pointsList,QList <QPointF > arcsList,QList <QPainterPath > arcsPathsList);
	 SheetMetal *sheet;
	 
 
   private:
     QAction *aboutAction;
     QAction *openAction;
     QAction *clearAction;   
	 QAction *clearPathAction; 
     QAction *mirrorAction;
	 QAction *yMirror;
	 QAction *rotateAction; 
     QAction *generateAction;
	 QAction *saveAction;
	 
     QMenu *fileMenu;
	 
     QToolBar *fileToolBar;
     QToolBar *editToolBar;
	 
   private slots:
     void about();
	 void readDxfFile();
	 void openFile();
	 bool saveFile();
	 void clearScene();
	 void rotateParts();
	 void generatePath();
	 void clearGeneratedPath();
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
  
     double getAngle(QPointF start_point,QPointF end_point);
	 QPointF ArrowWing1(double line_angle,QPointF end_point);
	 QPointF ArrowWing2(double line_angle,QPointF end_point);
	

  
  #endif 
