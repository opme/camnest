
#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H
#include <float.h>
   /* Number of decimal digits of precision in a double */


#undef DBL_DIG
#define DBL_DIG 9


///#define DBL_DIG 10
#include "dl_creationadapter.h"
#include <QtGui>
#include "qpointfwithparent.h"
class QPointFWithParent;


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
	 QPainterPath drawArc( const QPointFWithParent & startPoint, const QRectF & rectangle, qreal startAngle, qreal sweepAngle);
	 QPainterPath drawCircle( const QPointFWithParent  &centerPoint);


	 ///------------------
	 /** Lines along with arcs and polylines have their end/start points stored within 
		 pointsPathList
		 Circles are classified on their own in a Qlist of paths (definig their ceners, radis).
		 Arcs are dealt with in another way as we need 
	 */
	 QList <QPainterPath > partPathsList;
	 QList <QPainterPath > circlePathsList;
	 
	  QList <QPointFWithParent > pointsCircleList;
	 QList <QPointFWithParent > pointsPathList;
	 
	 QList <QGraphicsPathItem *> polylinesList;
	 QList <QPoint *> vertexesList;
	
	 /// the resulting part path
	 QPainterPath partPath;
		
	 /// the digit to round to float values (to still be in  the tolerance)
	 int precision;
	 
	 void printAttributes();
	 bool polylineNew;
	 bool inBlock;
	 /// indicates weither ot not it's the first encountred polyline 
	 bool polylineFirst;
	 QPainterPath polylineCurrent;
	 
	 double getPoint(double pos,double teta1,double radius,bool cos);
	double roundMe(double val);
};

#endif
