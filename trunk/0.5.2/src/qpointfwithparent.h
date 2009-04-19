#ifndef QPOINTFWITHPARENT_H
#define QPOINTFWITHPARENT_H
#include <QtGui>

class QPointFWithParent;
typedef QList <QPointFWithParent > QPFWPList;
typedef QVector <QPointFWithParent > QPFWPVector;

typedef  QList <QPainterPath > QPPList;
typedef  QVector <QPainterPath > QPPVector;

class QPointFWithParent : public QPointF {
	 public:
		
	 enum type {
         Line = 0x0,
         Arc = 0x1,
         Circle = 0x2,
         Polyline = 0x3,
		 LeadCertain=0x4,
		 LeadUncertain=0x5
     };
     Q_DECLARE_FLAGS(Types, type)
	 QPointFWithParent::Types parentType;
	 int parentLoop;
	 double centerX;
	 double centerY;
	 QPointF center;
	 ///@fixme remove leadTouch at it's now loop dependant
	 QPointF leadTouch;
	 double parentRadius;
	 double angle1;
	 double angle2;
	 bool cWise;
	 ///TODO : use inline functions here 
	 void setLeadTouch(QPointF myLeadTouch){ leadTouch=myLeadTouch;}
	 
	 /// TODO: rename to setParentLoop for homongenity
	 void setLoopNbr(int nbr){ parentLoop=nbr; }
	 void setParentType(QPointFWithParent::Types type ){  parentType=type; }
	 void setCenter(QPointF newCenter){ center=newCenter; centerX=newCenter.x();centerY=newCenter.y();}
	 /// create by default a point and stores it as a Line
	 QPointFWithParent (double x=0, double y=0, double cx=0,double cy=0,double radius=0,QPointFWithParent::Types type=0x0,bool cw=true, double teta1=0, double teta2=0);
	 virtual ~QPointFWithParent();
	 QPointFWithParent operator+= (QPointF point );
	 QPointFWithParent operator= (const QPointF point ); /// create an overloaded ont to WithParent
	 //QPointFWithParent operator+ (const QPointFWithParent &point1 );
};
 Q_DECLARE_OPERATORS_FOR_FLAGS(QPointFWithParent::Types)


#endif // QPOINTFWITHPARENT_H
