#include "leads.h"


/// for graphical represezntation of the laser trace on the part
int leadRadius=3;
 QRectF laserRect(-leadRadius/2,-leadRadius/2,leadRadius,leadRadius);
    Lead::Lead (QPointF leadPoint,Part *piece){
	 myBoundingRect=laserRect;
	 setPos(leadPoint.x(),leadPoint.y());
	 leadTouch=leadPoint;
	 myPiece=piece;
	 leadType=LeadTouch;
	 setZValue(2);/// to stayt on top
	}

  Lead::Lead (QPointFWithParent *leadPoint,Part *piece){
	 myBoundingRect=laserRect;
	 setPos(leadPoint->x(),leadPoint->y());
	 newPos=leadPoint;
	 /// Data 3 hold which loop is the lead assigned to
	 data(3)=leadPoint->parentLoop;
	 parentLoop=leadPoint->parentLoop;
	 leadTouch=leadPoint->leadTouch;
	 
	 myPiece=piece;
	 if (leadPoint->parentType==QPointFWithParent::LeadUncertain){
		 leadType=LeadUncertain;
		}
	 else {
		 leadType=LeadCertain;
		}
	 ///myEdge=new Edge(this);
		
	 setZValue(2);/// to stayt on top
	// setCacheMode(ItemCoordinateCache);	
	 setCacheMode(DeviceCoordinateCache);
	 //update();
	 //setFlag(ItemIsMovable);
	 setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	}

	 QRectF Lead::boundingRect()   const {
       return myBoundingRect;
     }
	 
	  QPainterPath Lead::shape() const{
     QPainterPath path;
     path.addEllipse(myBoundingRect);
     return path;
	}

 void Lead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	 //painter->setPen( settings.value("Colors/pen").value<QColor>());
     //painter->setBrush( settings.value("Colors/brush").value<QColor>());
	 painter->setRenderHint(QPainter::Antialiasing);
	  if (leadType==LeadCertain) {
		 painter->setBrush(Qt::green);
		}
		 else if (leadType==LeadTouch) {
		 painter->setBrush(Qt::blue);
		}
		else {
		painter->setBrush(Qt::red);
		}
     painter->setPen(QPen(Qt::black));
     painter->drawEllipse(laserRect);	 
	 //qDebug()<<newPos<<newPos.leadTouch;
	 //painter->drawLine(newPos,newPos.leadTouch);
	 
    }

	
	QVariant Lead::itemChange(GraphicsItemChange change, const QVariant &value){
		
		 switch (change) {
     case ItemPositionHasChanged:
		 ///NOTE:We only need to update the matrix when we release the mouse buton
		 ///newPos.setX(pos().x());
		 ///newPos.setY(pos().y());
		 
//		 qDebug()<<newPos;
		 // if (myEdge!=0) {	 myEdge->adjust();}
		 update();
         break;
	 case ItemSelectedChange	:
		 qDebug()<<"I'm selected";
		  break;
	 default:
	       
         break;
     };
		
	
		return QGraphicsItem::itemChange(change, value);
	}
     void Lead::mousePressEvent(QGraphicsSceneMouseEvent *event){
	  update();  //qDebug()<<"mouse pressed hole";
     QGraphicsItem::mousePressEvent(event);
	 }
     void Lead::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	 update();
	 qDebug()<<"replacing "<<newPos->x()<<newPos->y();
	 newPos->setX(pos().x());
	 newPos->setY(pos().y());
	 /// note: shouldn't call newPos=scenePos(); to avoid loosing loopparent ,...
	 ///qDebug()<<"replacing "<<myPiece->leadsPoints.at(parentLoop)<<"with"<<newPos;
	 ///myPiece->leadsPoints.replace(parentLoop,newPos);
	 qDebug()<<"with"<<newPos->x()<<newPos->y();
	 
     QGraphicsItem::mouseReleaseEvent(event);
	 }
	 
	 
	 void Lead::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	  update();myEdge->adjust();
	  
     QGraphicsItem::mouseMoveEvent(event);
	 }
	  
	/// void Lead::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
	 ///update();  qDebug()<<"mouse 2 click";
	 ///QGraphicsItem::mouseMoveEvent(event);	
	 ///}
	Lead::~Lead(){
}


/* Edges are inspired from Qt exapmle elastic node*/

Edge::Edge(Lead *sourceLead,Lead *destLead)
     : arrowSize(1)
 {
     setAcceptedMouseButtons(0);
     source = sourceLead;
	 dest = destLead;
	 sourcePoint=QPointF(source->newPos->x(),source->newPos->y());
	 destPoint=dest->leadTouch;
	 qDebug()<<"line from"<<sourcePoint<<"to"<<destPoint;
	 /// sourcePoint=sourceLead->newPos;
	 
	 ///Note: Have to keep this although it emit a warnign Item alreayadde to the scene
	 ///set it's parent when adding functionnalty Add manual leads!
	 setParentItem(sourceLead);
     setZValue(3);/// to stayt on top of the TOP :)
	 setCacheMode(DeviceCoordinateCache);
     source->setEdge(this);
     dest->setEdge(this);
     adjust();
 }

 Edge::~Edge()
 {
 }


 void Edge::adjust()
 {
    /// sourcePoint=source->newPos;
	/// NOTE: mapfrom Item is the key;) 
	QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
     //QLineF line(sourcePoint,destPoint);
     qreal length = line.length();
     QPointF edgeOffset((line.dx() * 3) / length, (line.dy() * 3) / length);

     prepareGeometryChange();
     sourcePoint = line.p1() ;//+ edgeOffset;
     destPoint = line.p2() ;//- edgeOffset;
 }

 QRectF Edge::boundingRect() const
 {
     return QRectF(sourcePoint,destPoint);
 }

  static const double Pi = 3.14159265358979323846264338327950288419717;
 static double TwoPi = 2.0 * Pi;
 
 void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
 {
  
     // Draw the line itself
     QLineF line(sourcePoint, destPoint);
     painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
     painter->drawLine(line);
	 
     // Draw the arrows if there's enough room
     double angle = ::acos(line.dx() / line.length());
     if (line.dy() >= 0)
        angle = TwoPi - angle;

	 //QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,cos(angle + Pi / 3) * arrowSize);
     //QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,cos(angle + Pi - Pi / 3) * arrowSize);
     QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,cos(angle - Pi / 3) * arrowSize);
     QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,  cos(angle - Pi + Pi / 3) * arrowSize);

     painter->setBrush(Qt::black);
     //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
     painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
 }