#ifndef PART_H
#define PART_H
#include "qpointfwithparent.h"
#include "leads.h"
#include <QtGui>
/** A part is a QGraphicsItem composed by a number of internal loops, its outline and 
the lead-in out points
*/
///@todo show possible start poits (the user may want to change the lead point for route/space
class Loop : public QGraphicsItem{
	 ///@fixme use qobject to allow passing parent and using Tr inside getLoopNumber manullay
	 ///Q_OBJECT
	 public:
	 Loop(QGraphicsItem * parent = 0);
	 
	 
	 QRectF boundingRect() const {
		 return qtRect;
		}
	 QPainterPath shape() const {
		 return loopShape;
		}
	 
	 
	 QRectF qtRect ;
		
	 ///curretn loop shape
	 QPainterPath loopShape;

	 ///loop shape without any modif (text for now...)
	 QPainterPath originalShape;
	 
	 
	 QSettings settings;
	 QPen myPen;
	 QPen selectedPen;
	 QPen unSelectedPen;
	 QPen  outlinePen;
	 
	 ///weither or not to display loop number @todo have to get it from settings
	 bool showText;
	 void setSelected(){myPen=selectedPen;}
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *);
	 /// set the original loop path entity by entity
	 void addPath(QPainterPath pathToAdd);
	 ///add a text path to the originalShape path
	 void addTextPath(QPainterPath pathToAdd);
	 QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	 ///Loop number in the current part
	 int loopNumber;
	 ///Weither or not the loop is a circle
	 bool isCircle;
	 ///Weither or not the loop is the part outline
	 bool isOutline;
	 ///used to stat painting the path when appropriate
	 bool ready;
	 /// Lead-In/out position for this loop
	 QPointFWithParent leadIn;
	 QPointFWithParent leadOut;
	 /// the loop start/end point. If it's a closed one, then startPoint=endPoint
	 QPointFWithParent startPoint;
	 QPointFWithParent endPoint; 
	 /// @note Mayeb should remove touchPoin and replace startPoint with this value for both g-code and Optimi
	 QPointFWithParent touchPoint;
	 
	 void setReady(bool b){ready=b;if (b) update();}
	 void setStart(QPointFWithParent sP){startPoint=sP;}
	 void setEnd(QPointFWithParent eP){endPoint=eP;}
	 void setIsOutline(bool s){ update(); isOutline=s; }
	 void setNumber(int nbr);//{loopNumber=nbr;}
	 void setTypeCircle(bool type){isCircle=type;}
	 void setLeadIn(QPointFWithParent p){leadIn=p;}
	 void setTouchPoint(QPointFWithParent p){touchPoint=p;}
	 
	 
	 QPFWPVector entities;
	 void setEntities(QPFWPVector ts);
	 QPFWPVector getEntities(){return entities;}
	 
	 protected:
	 virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
	 };


	/// A part is a set of loops.
class Part: public QGraphicsItem
 // Qobject is needed for signals 
 {
 
	 
	//Q_OBJECT
public:
	 ///@todo: cleanup this constructor
	 ///@todo use set/get 
	 static double movePartVal;
	 static void setMovePartVal(double val);
	 Part(const QPainterPath shape,QPFWPVector pointsList,QPPVector partPathsList,QPFWPVector circlePointsList,QPPVector circlesPathsList);
	
	 /// used to create a copy on the sheet metal of the current part
	 Part(const Part &parentPart);
	 virtual ~Part();
	 
	 QRectF boundingRect() const {
		 return qtRect;
		}
	 QPainterPath shape() const {
		 return partShape;
	    }
	 
	 
	 ///define the part shape for geometry collision and painting
	 QPainterPath partShape;
	 ///used for selection along with partshape
	 QRectF qtRect ;
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *);
	 
	  ///declare as static in main app and use everywhere needed 
	 QSettings settings;
	 
	 int leadAngle;
	 double leadDist;
	  
	   
	 
	 ///@see COPY constuctor
	 Part* copy();
	 ///If the part is for preview or to be inserted in sheetmetal
	 bool preview;
	 ///number of closedloops
	 int nbrClosedPath;
	 ///number of circles
	 int nbrCircles;
	 ///the outline position in partLoops list
	 int outlinePos;	

	 /// @note:As we are using pointers to loops any change in a previewed part will affect all the others.
	 ///This is a desirbvale behavior!
	 QVector <Loop* > partLoops;
	 QVector <Loop* > partLoopsOpt;
	 ///A part is a combinaison of loops (themselves composed of a number of paths ) each path has a start / end point
	 ///the points definig the part
	 QPFWPVector ptsVector;
	 ///the painterPath used to draw the part
	 QPPVector pathsList;
	 ///the circles points coordinates
	 QPFWPVector cirPtsList;
	 ///the painterPath used to draw part circles
	 QPPVector cirPathsList;
	 
	/// a list of points that we pass to the optimization algorithm
	 /// @todo:remove this and use another trik to animate stepoop
	 

	 QString partName;
	 
	 ///@todo:Maybe to be removed
	 QPointFWithParent outlinePoint;
	 QPainterPath outLinePath;
	 
	 	 
	 /// stiores the lead/in out points 
	 QPFWPVector gLeadPoints;
	  /// stiores the loops for gcode generation
	 QList<QPFWPVector> gLoops;
	 
	 void start();

	 
	 void createOutlineLead();
	 void generateLeads();
	 void findOutline();
	 
	 void  filterCircles();
	 void generateLoops(QPFWPVector ptsVector);
	 
	 
	   /// remove a point from the list
	 
	 void shrink(QPFWPVector &pointsList,QPFWPVector &pointsListNew,int &pos,int &oldPos);
	 ///find a lonley point if any or repreted one
	 
	 int newPos(QPFWPVector &pointsList);
	 /// we use the QGraphicsItem default implementation for those events
	 void drawArc(QPointFWithParent point,QPainterPath &pathToModify);
	 QPointFWithParent translateEntity(QPointFWithParent oldPoint, QPointF offset);
	

	 void optimizeRoute();
	 void moveMeBy(qreal dx, qreal dy);
	  
	 void setPartName(QString f){partName=f;};
	
	 /** this matrix holds the transformations applied to the part, transformations can be one of the following:
	 / translation , rotation ,shearing. wWe'll discard shearing and keep both translation and rotation
	 / therefor  x' = m11*x + m21*y + dx
	  /  	 	 y' = m22*y + m12*x + dy    
	  / where The dx and dy elements specify horizontal and vertical translation.
	 / The m11 and m22 elements specify horizontal and vertical scaling. 
	 /And finally, the m21 and m12 elements specify horizontal and vertical shearing.
	 */

	 QTransform transform;
	 enum { Type = UserType + 1 };
     int type() const
     {
        // Enable the use of qgraphicsitem_cast with this item.
        return  Type;
     }
	
	 //public slots:
	 //void setMoveVal(int);
	 //{qDebug()<<"test";movePartVal=val;}
	 ///signals:
	 ///void progressionStep();
	 ///void descStep( QString desc);
	 
	 protected:
     /// called by QGraphicsItem to notify custom items that some part of the item's state changes. 
	 QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	 void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	 void keyPressEvent ( QKeyEvent * keyEvent );
};





class LoopThread : public QThread
 {
     Q_OBJECT
	 public:
	 LoopThread(Part *piece);
	 Part *currentPiece;
	 //QList <QPFWPList> filterLoop;
 protected:
     void run();
 };
#endif // PART_H
