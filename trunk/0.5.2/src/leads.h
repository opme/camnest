#ifndef LEADS_H
#define LEADS_H
#include "qpointfwithparent.h"
#include "part.h"
#include <QtGui>

 ///Forward declaration 

class Lead;
class Loop;

 class Edge : public QGraphicsItem
 {
 public:
     Edge(Lead *sourceLead,Lead *destLead);
     ~Edge();

	
     void adjust();

     enum { Type = UserType + 3 };
     int type() const { return Type; }

 protected:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 private:
    QSettings settings;
     Lead *source, *dest;
     QPointF sourcePoint;
      /// for graphical represezntation of the laser path between lead-in/out
        //double leadRadiusMotion;
     QPointF destPoint;
     qreal arrowSize;
 };
 
/// As we have to track the lead In/out position we create a special QGraphicsEllipseItem
class Lead: public QGraphicsItem {

	 public :
         ///constructor for leads certain/uncertain
	 Lead (Loop *loop);
         /// @todo create a more meaningfull constructor
         /// create the Lead out= lead touch
	 Lead(Loop *loop,int j );
	 virtual ~Lead();
	 
	
	
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *);
	 QRectF boundingRect() const {return myBoundingRect;  }
	 QPainterPath shape() const{QPainterPath path; path.addEllipse(myBoundingRect);return path;}
	
	 int type() const { return  Type; }
	 
	 QRectF myBoundingRect;
	 enum { Type = UserType + 2 };
     
	 enum Leadtype {LeadCertain=0x1,LeadUncertain=0x2,LeadTouch=0x3};
     Q_DECLARE_FLAGS(leadTypes, Leadtype)
	 Lead::leadTypes leadType;
	
	
	 Loop *myLoop;
	 
         QPointFWithParent *myPos;
	 QPointFWithParent leadTouch;
	 
	 Edge *myEdge;
	 QGraphicsLineItem linkLine;
	 void setEdge(Edge *edge){myEdge=edge;}
	 
	 ///@todo cleanup private public
	   QRectF laserRect;
       /// for graphical represezntation of the laser lead-in/out
	double leadRadius;

	QSettings settings;
	 protected:
     /// called by QGraphicsItem to notify custom items that some part of the item's state changes. 
	 QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	 void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	 ///void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};
 Q_DECLARE_OPERATORS_FOR_FLAGS(Lead::leadTypes)





#endif // LEADS_H
