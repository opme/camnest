#ifndef QPOINTFWITHPARENT_H
#define QPOINTFWITHPARENT_H
#include <QtGui>
class QPointFWithParent : public QPointF {
	 public:
	 
	 enum type {
         Line = 0x0,
         Arc = 0x1,
         Circle = 0x2,
         Polyline = 0x3
     };
     Q_DECLARE_FLAGS(Types, type)
	 QPointFWithParent::Types parentType;
	 int parentLoop;
	 qreal centerX;
	 qreal centerY;
	 qreal parentRadius;
	 bool cWise;
	 void setLoopNbr(int nbr){ parentLoop=nbr; }
	 /// create by default a point and stores it as a Line
	 QPointFWithParent (qreal x, qreal y, qreal cx=0,qreal cy=0,qreal radius=0,QPointFWithParent::Types type=0x0,bool cw=true);
	 virtual ~QPointFWithParent();
	 QPointFWithParent operator+= (QPointF point );
	 QPointFWithParent operator= (const QPointF point ); /// create an overloaded ont to WithParent
	 //QPointFWithParent operator+ (const QPointFWithParent &point1 );
};
 Q_DECLARE_OPERATORS_FOR_FLAGS(QPointFWithParent::Types)


#endif // QPOINTFWITHPARENT_H
