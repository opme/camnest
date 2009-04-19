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
	 ///construct a QTEXtStream that will be saved as the .ng .ngc file
	 GCode( QFile *file);
	 ///write header (user defined for homing turning coolant ,...)
	 void writeHeader(QString filename);
	 ///write the corresponding G code to loops entities
	 void writeClosedLoop(QPFWPVector closedLoop);
	 ///write program end instruc
	 void writeEnd();
	 ///Add a comment
	 void comment(QString comment);
	 ///Add line number to the line (format= N XXX)
	 void addLineNumber ();
	 ///Move the tool to its home position in rapid mouvement
	 void home();
	 /// Rapid move to point @param p the coordinates of the point to move to
	 void rapidMove (QPointF p,qreal Z=0);
	 /// Feedrate move to point @param p the coordinates of the point to move to
	 void feedRateMove (QPointF p,qreal Z=0);

	 
	 /**
	  *  G code Arc cut 
	  * @param p starting arc point 
	  * @param Z =0
	  * @param p2 arc end point- start point @see example
	  * @param radius if no circle radius is given we use G2 X1.0 Y0.0 I0.0 J-1.0 
	  * @param cw if true go in ClockWise mouvment
	  * @example
	  
	  	G1 X0.0 Y1.0 F20.0 ----go to X1.0, Y0.0 at a feed rate of 20 
		G2 X1.0 Y0.0 I0.0 J-1.0 ----go in an arc from X0.0, Y1.0 to X1.0 Y0.0, with the center of the arc at X0.0, Y0.0 
		G2 for a clockwise Arc , G3 for an anticlockWise one
	  */
	 void ArcCut (QPointF p,qreal Z,QPointF p2,qreal radius,bool cw=true);
	 
	 /**
	  * Add a new line number then Write  G code
	  * @param code Code Lettre 
	  ///@fixme should be the value but appendNumcode is used now instead
	  * @param value value following the code 
	  */
	 void appendCode (QString code, QString value="");
	 void appendNumCode ( QString code, qreal value);
	 /// add a cartidge return to the stream
	 void  cartidgeReturn() { *this<< endl;}
	 ///Save the last position to avoid rewriting (as G code interpreters save last coordinate until changed)
	 void setLastPos(QPointF val){lastX=val.x(), lastY=val.y();}
	/// virtual ~GCode();
	 
	 /// The transform matrix is a copy from the part's one
	 QTransform partTrans;
	 ///Set the trans matrix for the part/loop
	 void setTrans(QTransform tr){partTrans=tr;}
	 
	  private:
	 ///if plasma mode is chosen leads are generated in G code and torch is set On/off on loop end
	 bool plasmaMode;
	 QString fileName;
	 int lineNumber;
	 qreal lastX, lastY,homeX, homeY, homeZ;
	 QPointF homePoint;
	 QString lastgcode;
	 //int lastfeed;
	 
	 
    };


#endif // GCODE_H
