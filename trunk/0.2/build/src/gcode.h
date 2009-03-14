#ifndef GCODE_H
#define GCODE_H

/// use ifndef ...
#include <QtGui>
#include <QWidget>

#include "qpointfwithparent.h"
class QPointFWithParent;
  /**
	 the class GCode implement some essential functions along with some optional one:
	 -Add Header
	 -Add line
	 -Add arc
	 -Add circle
	 -Add line number
	 -Add comment
	 -Add EOF
	 -Write to file
	 
  */
  
  class GCode : public QTextStream{
  
	 public:
	 GCode( QFile *file);
	 void writeHeader(QString filename);
	 void writeClosedLoop(QList<QPointFWithParent > closedLoop);
	 void writeCircleLoop(QList<QPointFWithParent> circleLoop, QList<qreal>  circlesRadius,int cncMode);
	 void writeEnd();
	 void comment(QString comment);
	 void addLineNumber ();
	 
	 void home();
	 void rapidMove (qreal X, qreal Y,qreal Z);
	 void feedRateMove (qreal X,qreal Y,qreal Z);
	 
	 void ArcCut (qreal X,qreal Y,qreal Z,qreal I,qreal J,qreal radius,bool cw=true);
	 
	 void appendCode (QString code, QString value="");
	 void appendNumCode ( QString code, qreal value);
	 void  cartidgeReturn() { *this<< endl;}
	 void setOffset(QPointF val) {offset=val;}
	/// virtual ~GCode();
	 
	   //private:
	   int cncMode;
	 QString fileName;
	 int lineNumber;
	 qreal lastX, lastY,lastZ ,homeX, homeY, homeZ;
	 QString lastgcode;
	 int lastfeed;	 
	 QPointF offset;
	 
    };


#endif // GCODE_H
