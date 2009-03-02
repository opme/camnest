/*
 * @file test_creationclass.cpp
 */

/*****************************************************************************
**  $Id: test_creationclass.cpp 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include "test_creationclass.h"

#include <iostream>
#include <stdio.h>
QPointF p1, p2;

/**
 * Default constructor.
 */
Test_CreationClass::Test_CreationClass() {
      polylineNew= true;
      polylineFirst= true;
      inBlock=false;
	  partPath.moveTo( 0,0);
	  partPath.setFillRule(Qt::WindingFill);
}

/**
 * Sample implementation of the method which handles line entities.
 */
 
  QPainterPath Test_CreationClass::drawLine( const QPointF & startPoint, const QPointF & endPoint) {
     QPainterPath lineEntity=QPainterPath ();
	 lineEntity.moveTo(startPoint);
	 lineEntity.lineTo(endPoint);
	 return lineEntity;	 
    }
 
void Test_CreationClass::addLine(const DL_LineData& data) {

	 if (inBlock) return;
	 QGraphicsLineItem *line = new QGraphicsLineItem (data.x1, data.y1, data.x2, data.y2);
	 p1= QPointF ( data.x1, data.y1);
	 p2= QPointF ( data.x2, data.y2);
	 /// if a line ending= it's begining have to skip it (may occur in some poorly coded cad)
	 if ( p1==p2 ) return;
	 /// store the line in the paths list
	 partPathsList.append(drawLine(p1,p2));
	 pointsPathList.append( p1);
	 pointsPathList.append( p2);
	 
	// qDebug() << pointsList.count(p1);
	// qDebug() << pointsList.count(p2);
	// if (pointsList.contains(p1) ){
	    // qDebug() << "the point "<< p1<< "exists at " << pointsList.indexOf(p1);
		 /// stroe the preivous point entitiy index and the current one
		// commonList<< (pointsList.indexOf(p1))/2;
		// commonList<< (pointsList.size())/2;
		 //partOutline.moveTo(p1);
		// }	
	//if (pointsList.contains(p2)) {
	 //    qDebug() << "the point"<< p2 <<"exists at "<< pointsList.indexOf(p2);
		 /// stroe the preivous point entitiy index and the current one
		// commonList<< (pointsList.indexOf(p2))%2;
		// commonList<< (pointsList.size())%2;
		 //partOutline.moveTo(p2);
		//} 
	 pointsList.append( p1);
	 pointsList.append( p2);
	 partPath.moveTo( p1);
	 partPath.lineTo( p2);
	 //QList<QGraphicsItem *> colidesWith= line->collidingItems ( Qt::IntersectsItemShape );
	// qDebug()<< line->collidesWithPath(partPath);
	 partBoundingRect=partPath.controlPointRect();
	 //qDebug() << "intersect with " << colidesWith.size();
	 linesList.append(line);
	 //partPathsList.append(&partPath);/// maybe add a type column to the list holding the path nature ; line; vertex; circle...
	 //  qDebug() << "line "<<data.x1<< data.y1<< data.x2<< data.y2;
    }
	
	QPainterPath Test_CreationClass::drawArc( const QPointF & startPoint, const QRectF & rectangle, qreal startAngle, qreal sweepAngle) {
     QPainterPath arcEntity=QPainterPath ();
	 arcEntity.moveTo(startPoint);
	 arcEntity.arcTo(rectangle,-(startAngle),-qAbs(sweepAngle));
	 return arcEntity;	 
    }

void Test_CreationClass::addArc(const DL_ArcData& data) {

	 if (inBlock) return;	
	 double teta1=data.angle1,teta2=data.angle2;
	
	 if (teta1>teta2) { /// have to go clockwise or swap values
	     //if (teta2==0) teta2=360; // teta2=data.angle1;// teta1=data.angle2;  //if (teta2==0) teta2=360;
	     teta2=360+teta2;
	  }
	  
	 QPointF p1(data.cx + cos((teta1)*M_PI/180) * data.radius,data.cy + sin((teta1)*M_PI/180) * data.radius);
	 QPointF p2(data.cx + cos((teta2)*M_PI/180) * data.radius,data.cy + sin((teta2)*M_PI/180) * data.radius);
	 QRectF boundingRect (data.cx-data.radius, data.cy-data.radius,2*data.radius,2*data.radius);

	 partPathsList.append(drawArc(p1,boundingRect,teta1,teta1-teta2));
	 pointsPathList.append(p1);
	 pointsPathList.append(p2);
	 QPainterPath arcTemp;
	
	 /// move to the extrimity point first without drawing 
	 partPath.moveTo(p1);
	 arcTemp.moveTo(p1);
	 //qDebug() << "Arc of R= "<< data.radius<<" starts at:" <<p1<<"ends at: "<<p2<< "and angles"<<data.angle1<<" , "<< data.angle2<< teta1<<teta2;;//artPath.currentPosition();	
	 pointsArcsList.append(p1);//.append(&p1);
	  //boundingRect.moveCenter(QPointF(data.cx,data.cy));
	  /// Clockwise arcs can be specified using negative angles(selon doc Qt) fabs or qAbs ?
	   partPath.arcTo(boundingRect,-(teta1),-qAbs(teta1-teta2));
	   arcTemp.arcTo(boundingRect,-(teta1),-qAbs(teta1-teta2));
	   arcsPathsList.append(arcTemp);
	 // qDebug() <<"differnece in the drawn  arc"<< p2-partPath.currentPosition();
	 // qDebug() << "Arc ends at:" <<partPath.currentPosition();
	 pointsArcsList.append(p2);//partPath.currentPosition());
	  //radiusArcsList.append( data.radius );
	 //partPath.closeSubpath();
	 //	 qDebug() << "Arc "<<data.cx<< data.cy<< teta1<< teta2<< data.radius ;
	// QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem (data.cx, data.cy, data.radius,data.radius);
	 //ellipse->setStartAngle(data.angle1*16);
	// ellipse->setSpanAngle(data.angle2*16);
	// ellipsesList.append(ellipse);
	 //qDebug() << "last position is :" <<partPath.currentPosition();

}

QPainterPath Test_CreationClass::drawCircle( const QPointF &centerPoint, const qreal radius) {
     QPainterPath circleEntity=QPainterPath ();
	 QPointF touchCircle(centerPoint.x()+radius,centerPoint.y());
	// circleEntity.moveTo(centerPoint);
	 pointsCircleList.append(centerPoint);
	 /// move by radius to touch the circle
	 //circleEntity.moveTo(touchCircle);
	 pointsCircleList.append(touchCircle);
	 circleEntity.addEllipse(centerPoint,radius,radius);
	 return circleEntity; 
    }

/**
 * Circles are special entities as they 're defined only be a unique point, their center (and the radius)
 */
void Test_CreationClass::addCircle(const DL_CircleData& data) {
     if (inBlock) return;
	 
	 circlePathsList.append((drawCircle(QPointF(data.cx,data.cy),data.radius)));
	 
	 //QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem (data.cx, data.cy, data.radius,data.radius);
	 //ellipsesList.append(ellipse);
	 partPath.addEllipse(QPointF(data.cx, data.cy), data.radius,data.radius);
	 
    }
	
void Test_CreationClass::addBlock(const DL_BlockData& data) {
	 
	 //printAttributes();
	// qDebug() <<  data.name.c_str();
	   //printf(" Type: %s\n", data.name.c_str());
	   ///blocks have to be stored as paths and called afterwhile with insert
	 inBlock=true;
    }

	void Test_CreationClass::endBlock(){	
	
	 inBlock=false;
	// qDebug() << "end block";
	}
	
	void Test_CreationClass:: addMText(const DL_MTextData& data){	
	
	//qDebug() << " Adding Mtext";
	}
	
	
	void Test_CreationClass:: addText(const DL_TextData& data){	
	
	qDebug() << " Adding text";
	
	}
	 void Test_CreationClass:: addInsert(const DL_InsertData& data)
{	
	
	//qDebug() << " Adding block "<<data.name.c_str();
	
	}
/**
 * Sample implementation of the method which handles polyline entities.
 */
 
 ///FIXME : use the built in DXF SEQEND to draw polylines
void Test_CreationClass::addPolyline(const DL_PolylineData& data) {
       if (inBlock) return;
     printf("Adding a POLYLINE \n");
     //printf("flags: %d\n", (int)data.flags);
     //printAttributes();
	 /// inform the vertex joiner that's a new path
	 polylineNew=true;
	
	 /// we have to wait for the polyline to end before ending it to polylinesList
	 if (!polylineFirst) {
	 /// store the polyline as a PathItem for later use
	 QGraphicsPathItem *polyline = new QGraphicsPathItem ();
	 polyline->setPath (polylineCurrent);
	 ///add the polyline to the polylinesList
	 polylinesList.append(polyline);
	 partPath.addPath(polylineCurrent);
	 }
	 /// Prepare the new polyline path
	 QPainterPath polylineCurrent;//= new ();
	 
}


/**
 * Sample implementation of the method which handles vertices.
 */
 
 //NOTE IF a vertex comes between two other entities it's lost !!!
void Test_CreationClass::addVertex(const DL_VertexData& data) {
    // printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f\n",data.x, data.y, data.z,data.bulge);
     // printAttributes();
	 if (inBlock) return;
     QPoint vertex ( data.x, data.y );
	 vertexesList.append(&vertex);
	 /// FIXME handle the case: a vertex is encountered which isn't a part of polyline !!
	 
	/// The vertexes are members of the same polyline as long as polylineNew=false
	if (polylineNew) {
	 polylineCurrent.moveTo(vertex);
	 partPath.moveTo(vertex);
	
	  qDebug() << "startuing a new polyLine ";
	}
	else 	{
	 /// add the vertex to the current path
	 polylineCurrent.lineTo(vertex);
	 partPath.lineTo(vertex);
	 qDebug() << "joining vertexes";
	}
	 polylineNew=false;
	 polylineFirst=false;
}


/**
 * Sample implementation of the method which handles layers.
 */
   void Test_CreationClass::addLayer(const DL_LayerData& data) {
     printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
     // printAttributes();
  }

/**
 * Sample implementation of the method which handles point entities.
 */
void Test_CreationClass::addPoint(const DL_PointData& data) {
     //  printf("POINT    (%6.3f, %6.3f, %6.3f)\n",
      //     data.x, data.y, data.z);
      // printAttributes();
	 // if (inBlock) return;
}

void Test_CreationClass::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n", 
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}


void Test_CreationClass::printAttributes() {
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLineType().c_str());
}
    
    

// EOF
