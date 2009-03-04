
#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QtGui>

//#define DBL_DIG 4
//#define FLT_DIG 4
//const double Pi = 3.14159265358979323846;
//static const double Pi = 3.14159265358979323846264338327950288419717;




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
	 
	 qreal centerX;
	 qreal centerY;
	 qreal parentRadius;
	 bool cWise;
	 /// create by default a point and stores it as a Line
	 QPointFWithParent (qreal x, qreal y, qreal cx=0,qreal cy=0,qreal radius=0,QPointFWithParent::Types type=0x0,bool cw=true);
	 

};
 Q_DECLARE_OPERATORS_FOR_FLAGS(QPointFWithParent::Types)

class Test_CreationClass : public DL_CreationAdapter {
public:
    Test_CreationClass();

    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);
	  /**
     * Called for every block. Note: all entities added after this
     * command go into this block until endBlock() is called.
	 */
	
	virtual void addBlock(const DL_BlockData& data);
	    /** Called to end the current block */
    virtual void endBlock() ;
	
	virtual void addInsert(const DL_InsertData& data); 
    virtual void addMText(const DL_MTextData& data);
	 virtual void addText(const DL_TextData& data);
	///------------------
	 QPainterPath drawLine( const QPointFWithParent & startPoint, const QPointFWithParent & endPoint);
	 QPainterPath drawArc( const QPointFWithParent & startPoint, const QRectF & rectangle, qreal startAngle, qreal sweepAngle);
	 QPainterPath drawCircle( const QPointF &centerPoint, const qreal radius);


	 ///------------------
	 /** Lines along with arcs and polylines have their end/start points stored within 
		 pointsPathList
		 Circles are classified on their own in a Qlist on points (definig their ceners) and
		 another Qlist holding their respective radis.
		 Arcs are dealt with in another way as we need 
	 */
	 QList <QPainterPath > partPathsList;
	 QList <QPainterPath > circlePathsList;
	 
	 
	 QList <QGraphicsLineItem *> linesList;	

	 QList <QGraphicsPathItem *> polylinesList;
	 QList <QPoint *> vertexesList;
	
	 
	 QList <QPointF > pointsCircleList;
	 QList <QPointFWithParent > pointsPathList;
	 
	 QList <qreal > radiusCircleList;
	 ///------------------
	 
	 /// the resulting part path
	 QPainterPath partPath;
	 /// the part boundries
	 QPainterPath partOutline;
	 /// the list of start end points of entities lines
	 QList <QPointF > pointsList; 
	
	 /// the digit to round to float values (to still be in  the tolerance)
	 int precision;
	 
	 QRectF partBoundingRect;
     void printAttributes();
	 bool polylineNew;
	 bool inBlock;
	 /// indicates weither ot not it's the first encountred polyline 
	 bool polylineFirst;
	 QPainterPath polylineCurrent;
	 QPainterPath blockCurrent;
	 //void drawLine (const DL_LineData& data, QWidget *parent  = 0);
};

#endif
