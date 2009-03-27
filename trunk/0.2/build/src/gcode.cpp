#include "gcode.h"

 GCode::GCode( QFile *file):QTextStream (file) {
	 lineNumber=0;cncMode=0;
	 lastX=lastY=lastZ=homeX=homeY=homeZ=0; /// change to Home pos from settings
	 lastgcode="G90";
	 ///some stupid cam soft do need the trailing zeros to work like ncplot!!!
	 setRealNumberNotation(QTextStream::FixedNotation);
	 ///setRealNumberPrecision (4);
	 setOffset(QPointF(0,0));
	 fileName=file->fileName ();
    }
	
	
	
	void GCode::writeHeader(QString filename) {
	 setRealNumberPrecision(6);
	 comment ("Program generated from :" + fileName) ; //FIXME the operator << can't deal with pointers !!s
	 comment("program start");
	 comment("Units = millimeters");
	 appendCode ("G21");
	 comment("Absolute coordinates");
	 appendCode (" G90");	 
	 comment(" feed per minute mode ");
	 appendCode ("G94");
	 comment("Homing");
	 home();
	}
	
	
	
	/**
G1 X0.0 Y1.0 F20.0 ----go to X1.0, Y0.0 at a feed rate of 20 inches/minute 
G2 X1.0 Y0.0 I0.0 J-1.0 ----go in an arc from X0.0, Y1.0 to X1.0 Y0.0, with the center of the arc at X0.0, Y0.0 
G2 for a clockwise Arc , G3 for an anticlockWise one
*/

QPointF circleCenter, attackPoint;
qreal radius;
	 
	void GCode::writeClosedLoop(QList<QPointFWithParent > closedLoop){
	 int pos=0;
	 ///the end point of an arc
	 QPointFWithParent  endPoint(0,0);
	 /// a point in a line entinty weiither the start or end (becomle the start in a arc one)
	 QPointFWithParent point(0,0);
	 ///the center of a circle
	 QPointFWithParent  circle(0,0);
	 ///FIXME: a problem with qlist dimension size pos+2 to solve
	 qDebug()<<"Writing the G-code of a loop composed of "<<closedLoop.size()<<"entities";
	 while (pos < closedLoop.size()) {
		 point=closedLoop.at(pos);

			 if (point.parentType==QPointFWithParent::Arc) {
				 endPoint=closedLoop.at(pos+1);
				 /// go to the first point at rapid move
				 if (pos==0) {
					 rapidMove( point.x(),point.y(),0);
					}
				 else{
					 feedRateMove(point.x(),point.y(),0);
					}
				 ArcCut(endPoint.x(),endPoint.y(),0, (endPoint.centerX-point.x()), (endPoint.centerY-point.y()),0,endPoint.cWise);
				 ///ArcCut(endPoint.x(),endPoint.y(),0, (endPoint.centerX-point.x()), (endPoint.centerY-point.y()),endPoint.parentRadius);
				 pos=pos+2;
				 //qDebug()<<"dealing with an arc rad="<<endPoint.parentRadius<<"center="<<endPoint.centerX<<endPoint.centerY;
				 /// Implment opertao = in WIthParent QPointF & QPointF::operator= ( const QPointF & point )
				 point.setX(endPoint.x());
				 point.setY(endPoint.y());
				}
			 else if (point.parentType==QPointFWithParent::Circle) {
				 circleCenter=point;
				 radius=point.parentRadius;
				 attackPoint=QPointF(point.x()+radius,point.y());
				 ///attackPoint=circleLoop.at(pos+1);
				 
				 /// go to the center with G0
				 rapidMove( circleCenter.x(),circleCenter.y(),0);
				 ///start cutting till being onthe circle
				 if (cncMode==1) { /// cncMode=1 if we are cutting plamsa (should be the default mode)
					 feedRateMove( attackPoint.x(),attackPoint.y(),0);	
					 /// now that we are on the circle cut it
					 ArcCut(attackPoint.x(),attackPoint.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
					}
				else {
					ArcCut(circleCenter.x(),circleCenter.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
					}		
				 pos++;	
				}
			else {	
			     /// go to the first point at rapid move
				 if (pos==0) {
					 rapidMove( point.x(),point.y(),0);
					}
				 else{
					 feedRateMove(point.x(),point.y(),0);
					}
				 pos++;
			    }
		 lastX=point.x();
		 lastY=point.y();
		 //qDebug()<<"last point: ("<<lastX<<" , " << lastY<<")" ;
		}	
	}	
	
	 

	void GCode::writeCircleLoop(QList<QPointFWithParent> circleLoop,QList<qreal> circlesRadius,int cncMode ){
	 int pos=0;
	 while (pos <= circleLoop.size()-2){
	 /// Todo maybe should replace regular QPOINTF with QPointFWithParent and get rid of Qlist circles attackpoint
		 circleCenter=circleLoop.at(pos);
		 attackPoint=circleLoop.at(pos+1);
		 radius=circlesRadius.at(pos/2);
		 /// go to the center with G0
		 rapidMove( circleCenter.x(),circleCenter.y(),0);
		 ///start cutting till being onthe circle
		 if (cncMode==1) { /// cncMode=1 if we are cutting plamsa (the default mode)
		 feedRateMove( attackPoint.x(),attackPoint.y(),0);	
		 /// now that we are on the circle cut it
		 ArcCut(attackPoint.x(),attackPoint.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
		}
		else {
		 ArcCut(circleCenter.x(),circleCenter.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
		}
		 
		  pos=pos+2;
		}
	
	}
	 void GCode::ArcCut (qreal X,qreal Y,qreal Z,qreal I,qreal J,qreal radius,bool cw){
	 ///add counterClockwise case handle
	 if (!cw){
		 appendCode("G03");
		} 
	 else{
		 appendCode("G02");
		}
	 appendNumCode ("X",X);
	 appendNumCode ("Y",Y);
	 if (radius==0) {
		 appendNumCode ("I",I);
		 appendNumCode ("J",J);
	    }
		else{
		 appendNumCode ("R",radius);
		}
	 cartidgeReturn();
	}
	
	
	void GCode::feedRateMove (qreal X,qreal Y,qreal Z){
	 if (!qFuzzyCompare(X,lastX) || !qFuzzyCompare(Y,lastY) ) {
		 appendCode("G01");
		 if (X!=lastX) 	 appendNumCode ("X",X);
		 if (Y!=lastY) 	 appendNumCode ("Y",Y);	 
         ///appendNumCode ("Z",Z);	 
		 cartidgeReturn();
		}
	}
	
	
	void GCode::rapidMove(qreal X,qreal Y,qreal Z){
	 /// TIODO: Replace qFuzzyColpare with a tolerance to be set by the user
	if (!qFuzzyCompare(X,lastX)  || !qFuzzyCompare(Y,lastY)) {
		 appendCode("G00");
		 ///TODO: replace with line code and group X & Y
		 if (X!=lastX) 	 appendNumCode ("X",X);
		 if (Y!=lastY) 	 appendNumCode ("Y",Y);	 	
		 ///appendNumCode ("Z",Z); 
		 cartidgeReturn();
		}
	}	
	
	void GCode::comment(QString comment){
	 *this <<"( "+comment+" )"<<endl;
	}

	void GCode::home(){
	 /// Move the tool to its home position
	 rapidMove(homeX,homeY,homeZ);
	}
	
	void GCode::addLineNumber (){
	 *this << "N"<<lineNumber<< " ";
	 lineNumber=lineNumber+10;
	}
	
	void GCode::appendCode ( QString code, QString value){
	 addLineNumber();
	 *this << code+ " "<< value<< " ";
	}
	
	void GCode::appendNumCode ( QString code, double value){	  
	 *this << code + " "<< value<< " ";	 
	}
	
	void GCode::writeEnd(){
	 comment("program End");
	 appendCode ("M2");	
	}
	