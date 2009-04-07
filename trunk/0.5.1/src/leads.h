#ifndef LEADS_H
#define LEADS_H
#include "qpointfwithparent.h"
#include "part.h"
#include <QtGui>

class Lead;
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
