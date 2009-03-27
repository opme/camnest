#ifndef PART_H
#define PART_H
#include "qpointfwithparent.h"
#include <QtGui>
/** A part is a QGraphicsItem IIt is composed by a number of internal loops, its outline and 
the lead-in out points
*/

typedef QList <QPointFWithParent > QPFWPList;
typedef  QList <QPainterPath > QPPList;

class Part: public QGraphicsItem
 /// Qobject is needed for signals 
 {
///Q_OBJECT
public:
	 ///TODO: cleanup this constructor
	 Part(const QPainterPath shape, QRectF rect,QPFWPList pointsList,QPPList partPathsList,QPFWPList circlePointsList,QPPList circlesPathsList);
	 /// used to create a copy on the sheet metal of the current part
	 Part(const Part &parentPart);
	 virtual ~Part();
	 QRectF boundingRect() const;
	 QPainterPath shape() const;
	 QSettings settings;
	 QRectF qtRect ;
	 QPainterPath partShape;
	 /// By default the text ath isn't displayed in the sheet metal (only in the preview scene)
	 QPainterPath partText;
	 bool showText;
	 void clearText();
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *);
	 void applyTransform();
	 ///COPY
	 Part* copy();
	 
	 ///how many closed loops in the part
	 int nbrClosedPath;int nbrCircles;int outlinePos;
	 ///the loops end/start points
	 QPFWPList endPointslist;
	 	/// the same as above but afetr TSp optimizastion
	 QPFWPList bestRoute;
	 /// holds the organised loops paths entity by entity
     QPPList partLoopsListFinal;
	 ///A part is a combinaison of loops (themselves composed of a number of paths ) each path has a start / end point
	 QPFWPList ptsList;
	 QPPList pathsList;
	
	 QPFWPList cirPtsList;
	 QPPList cirPathsList;
	
	 /// stiores the organised entities Start/end points.
	 QList < QPFWPList> gCodePoints;
  
    /// stiores the organised entities Start/end points after TSp optim.
	 QList < QPFWPList> gCodePointsOpt;

	 /// stiores the organised entities Start/end points coordinates in a Sheet metal (afetr trabsformaton being applied)
	 QList < QPFWPList> gCodePointsTrans;
	 
	 QPointFWithParent outlinePoint;
	
	 ///used for matrix transfrom.
	 QPointF position;
	 QPointF deltaPos;
	 QList <QPFWPList>  filterCircles();
	
	 QList <QPFWPList > filterLoops();
	   /// remove a point from the list
	 void shrink(QPFWPList &pointsList,QPFWPList &pointsListNew,int pos,int oldPos);
		 ///find a lonley point if any or repreted one
	 int newPos(QPFWPList pointsList);
	 /// we use the QGraphicsItem default implementation for those events
	 void drawArc(QPointFWithParent point,QPainterPath &pathToModify);
	 QPointFWithParent translateEntity(QPointFWithParent oldPoint, QPointF offset);
	void  findOutline();
	void optimize();
	 void moveMeBy(qreal dx, qreal dy);
	 void setPartPos(){
		 position=pos();
		}
	 
	 /** this matrix holds the transformations applied to the part, transformations can be one of the following:
	 / translation , rotation ,shearing. wWe'll discard shearing and keep both translation and rotation
	 / therefor  x' = m11*x + m21*y + dx
	  /  	 	 y' = m22*y + m12*x + dy    
	  / where The dx and dy elements specify horizontal and vertical translation.
	 / The m11 and m22 elements specify horizontal and vertical scaling. 
	 /And finally, the m21 and m12 elements specify horizontal and vertical shearing.
	 */
	 
	 QMatrix transMatrix;	 
	 enum { Type = UserType + 1 };
     int type() const
     {
        // Enable the use of qgraphicsitem_cast with this item.
        return  Type;
     }
	 
	 
	 ///signals:
	 ///void progressionStep(int currentStep);
	 ///void descStep( QString desc);
	 
	 protected:
     /// called by QGraphicsItem to notify custom items that some part of the item's state changes. 
	 QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	 void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

class LoopThread : public QThread
 {
     Q_OBJECT
	 public:
	 LoopThread(Part *piece);
	 Part *currentPiece;
	 QList <QPFWPList> filterLoop;
 protected:
     void run();
 };
#endif // PART_H
