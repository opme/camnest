#ifndef GCODE_H
#define GCODE_H

/// use ifndef ...


#include "qpointfwithparent.h"

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
	 void writeClosedLoop(QPFWPVector closedLoop);
	 
	 void writeEnd();
	 void comment(QString comment);
	 void addLineNumber ();
	 
	 void home();
	 void rapidMove (QPointF p,qreal Z=0);
	 void feedRateMove (QPointF p,qreal Z=0);
	 
	 void ArcCut (QPointF p,qreal Z,QPointF p2,qreal radius,bool cw=true);
	 
	 void appendCode (QString code, QString value="");
	 void appendNumCode ( QString code, qreal value);
	 void  cartidgeReturn() { *this<< endl;}
	 
	 void setLastPos(QPointF val){lastX=val.x(), lastY=val.y();}
	/// virtual ~GCode();
	 
	   ///private:
	 bool plasmaMode;
	 QString fileName;
	 int lineNumber;
	 qreal lastX, lastY,homeX, homeY, homeZ;
	 QPointF homePoint;
	 QString lastgcode;
	 int lastfeed;
	 QTransform partTrans;
	 void setTrans(QTransform tr){partTrans=tr;}
	 
    };


#endif // GCODE_H
