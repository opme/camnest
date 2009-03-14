#include "qpointfwithparent.h"

/// mabe have to create a subclass of withpareznt for lines to be lighter than others as it just 

QPointFWithParent::QPointFWithParent(qreal x, qreal y, qreal cx,qreal cy,qreal radius,QPointFWithParent::Types type,bool cw):QPointF(){
	 setX(x);
	 setY(y); 
	 parentType=type;
	 centerX=cx;
	 centerY=cy;
	 cWise=cw;
	 parentRadius=radius;
	 parentLoop=0;
	}
QPointFWithParent::~QPointFWithParent()
{
}


QPointFWithParent QPointFWithParent::operator+= ( QPointF point ){
	 this->setX(point.x()+this->x());
	 this->setY(point.y()+this->y());
	 if (this->parentType==QPointFWithParent::Arc) {
	     this->centerX+=point.x();
		 this->centerY+=point.y();
		}
	 //qDebug()<< point.x();
	 return *this; 
}
QPointFWithParent QPointFWithParent::operator=( const QPointF point){
	 this->setX(point.x());
	 this->setY(point.y());
	 return *this; 
}
//QPointFWithParent QPointFWithParent::operator+ ( const QPointFWithParent &point1,const QPointFWithParent &point2 ){
	 //this->setX(point.x()+this->x());
	 //this->setY(point.y()+this->y());
	// return QPointFWithParent(point1.x()+point2.x(),point1.y()+point2.y());
	 //qDebug()<< point.x();
	 //return *this; 
//}
