
#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QtGui>

//#define DBL_DIG 4
//#define FLT_DIG 4
//const double Pi = 3.14159265358979323846;
//static const double Pi = 3.14159265358979323846264338327950288419717;

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
	 QPainterPath drawLine( const QPointF & startPoint, const QPointF & endPoint);
	 QPainterPath drawArc( const QPointF & startPoint, const QRectF & rectangle, qreal startAngle, qreal sweepAngle);
	 QPainterPath drawCircle( const QPointF &centerPoint, const qreal radius);


	 ///------------------
	 QList <QPainterPath > partPathsList;
	 QList <QPainterPath > circlePathsList;
	 
	 QList <QGraphicsLineItem *> linesList;	
	 //QList <QGraphicsEllipseItem *> ellipsesList;
	 QList <QGraphicsPathItem *> polylinesList;
	 QList <QPoint *> vertexesList;
	 QList <QPointF > pointsPathList;
	 
	 QList <QPointF > pointsCircleList;
	 ///------------------
	 
	 /// the resulting part path
	 QPainterPath partPath;
	 /// the part boundries
	 QPainterPath partOutline;
	 /// the list of start end points of entities lines
	 QList <QPointF > pointsList;
	  /// the list of start end points of entities arcs
	 QList <QPointF > pointsArcsList;
	 QList <float > radiusArcsList;
	 QList <QPainterPath > arcsPathsList;
	 /// list of entities having common points 
	 QList <qint32 > commonList;	
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
