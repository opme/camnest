#ifndef LEADS_H
#define LEADS_H
#include "qpointfwithparent.h"
#include "part.h"
#include <QtGui>

class Edge;
/// As we have to track the lead In/out position we create a special QGraphicsEllipseItem
class Lead: public QGraphicsItem {
	 public :
	 Lead (QPointFWithParent *leadPoint,Part *piece);
	 Lead (QPointF leadTouch,Part *piece);
	 virtual ~Lead();
	
	
	 void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *);
	 QRectF boundingRect() const;
	 QPainterPath shape() const;
	 int type() const { return  Type; }
	 
	 QRectF myBoundingRect;
	 enum { Type = UserType + 2 };
     
	 enum Leadtype {LeadCertain=0x1,LeadUncertain=0x2,LeadTouch=0x3};
     Q_DECLARE_FLAGS(leadTypes, Leadtype)
	 Lead::leadTypes leadType;
	 
	 
	 int parentLoop;
	 Part *myPiece;
     QPointFWithParent *newPos;  
	 QPointF leadTouch;
	 
	 Edge *myEdge;
	 QGraphicsLineItem linkLine;
	 void setEdge(Edge *edge){myEdge=edge;}
	 
	 protected:
     /// called by QGraphicsItem to notify custom items that some part of the item's state changes. 
	 QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	 void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	 ///void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};
 Q_DECLARE_OPERATORS_FOR_FLAGS(Lead::leadTypes)


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
    
	 Lead *source, *dest;;
     QPointF sourcePoint;
     QPointF destPoint;
     qreal arrowSize;
 };



#endif // LEADS_H
