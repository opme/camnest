#include "gcode.h"

 GCode::GCode( QFile *file):QTextStream (file) {
	 lineNumber=0;plasmaMode=true;
	 lastX=lastY=0;
	 /// @todo get Home from settings 
	 homeX=homeY=homeZ=0; 
	 lastgcode="G90";
	 ///@note:some cam soft need the trailing zeros to work like ncplot!!!
	 setRealNumberNotation(QTextStream::FixedNotation);
	 ///@todo: get output g-code precision from settings
	 setRealNumberPrecision(6);
	 homePoint= QPointF(homeX,homeY);
	 ///@todo: get the part name!
	 fileName=file->fileName ();
	 partTrans=QTransform();
    }
	
	
	
	void GCode::writeHeader(QString filename) {
	 
	 comment ("Program generated from :" + fileName) ;
	 ///@todo have to get the header code from settings dialog
	 comment("program start");
	 comment("Units = millimeters");
	 appendCode ("G21");
	 comment("Absolute coordinates");
	 appendCode (" G90");	 
	 comment(" feed per minute mode ");
	 appendCode ("G94");
	 /// @todo get Home at start option from settings 
	 comment("Homing");
	 home();
	}
	
	
	


QPointF circleCenter, attackPoint;
qreal radius;
	 
	void GCode::writeClosedLoop(QPFWPVector closedLoop){
	 int pos=0;
	 ///the end point of an arc
	 QPointFWithParent  endPoint(0,0);
	 /// a point in a line entinty weiither the start or end (becomle the start in a arc one)
	 QPointFWithParent point(0,0);
	 ///the center of a circle
	 QPointFWithParent  circle(0,0);
	 ///FIXME: a problem with qlist dimension size pos+2 to solve
	 
	 qDebug()<<"Writing the G-code of a loop composed of "<<closedLoop.size()<<"entities";
	 /// we first go to the lead point if any

	 while (pos < closedLoop.size()) {
		 //qDebug()<<pos;
		 point=closedLoop.at(pos);
		 
			 if (point.parentType==QPointFWithParent::Arc) {

				 endPoint=closedLoop.at(pos+1);
				 /// go to the first point at rapid move
				 if (pos==0) {
					 rapidMove(point,0);
					}
				 else{
					 feedRateMove(point,0);
					}
				 ArcCut(endPoint,0, (endPoint.center-point),0,endPoint.cWise);
				
				///@note Have to skip the other point definig the arc
				 pos=pos+2;
				 //qDebug()<<"dealing with an arc rad="<<endPoint.parentRadius<<"center="<<endPoint.centerX<<endPoint.centerY;
				 /// @todo Implment operator = in QPointFWIthParent  & QPointF::operator= ( const QPointF & point )
				 point.setX(endPoint.x());
				 point.setY(endPoint.y());
				}
			 else if (point.parentType==QPointFWithParent::Circle) {
				  qDebug()<<"Writing g code of circle at"<<pos;
				 circleCenter=point;
				 radius=point.parentRadius;

				 ///We touch the circle
				/** @note:
G1 X0.0 Y1.0 F20.0 ----go to X1.0, Y0.0 at a feed rate of 20 
G2 X1.0 Y0.0 I0.0 J-1.0 ----go in an arc from X0.0, Y1.0 to X1.0 Y0.0, with the center of the arc at X0.0, Y0.0 
G2 for a clockwise Arc , G3 for an anticlockWise one
*/
				
				 /// go to the center with G0
				 ///rapidMove( circleCenter.x(),circleCenter.y(),0);
				 ///start cutting till being onthe circle
				 if (plasmaMode) { /// cncMode=1 if we are cutting plamsa (should be the default mode)
					 ///feedRateMove( attackPoint.x(),attackPoint.y(),0);	
					

					 ///@todo make this homogene with genrated lead @fixme should get the point from lead
					 attackPoint=point+QPointF(radius,0);
					 feedRateMove(attackPoint);
					  // now that we are on the circle cut it
					 ArcCut(attackPoint,0,circleCenter-attackPoint,0);
					}
				else {
					 attackPoint=point+QPointF(radius,0);
					 //feedRateMove(point.x()+radius,point.y()+radius);
					 rapidMove( circleCenter,0);
					 //ArcCut(attackPoint.x(),attackPoint.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
					 ArcCut(circleCenter,0,circleCenter-attackPoint,0);
					}		
				 pos++;	
				}
			else {	
				 //qDebug()<<"line at"<<pos;
			     /// go to the first point at rapid move
				 if (pos==0) {
					 rapidMove( point,0);
					}
				 else{
					 feedRateMove(point,0);
					}
				 pos++;
			    }
		 /// @fixme isn't this granted by feedRate and arccut?
		 setLastPos(point);
		 //qDebug()<<"last point: ("<<lastX<<" , " << lastY<<")" ;
		}	
		//qDebug()<<"loop written";
	}	
	
	 void GCode::ArcCut (QPointF p,qreal Z,QPointF p2,qreal radius,bool cw){
	 
	 p=partTrans.map(p);
	/// p2=partTrans.map(p2);
	 if (!cw){
		 appendCode("G03");
		} 
	 else{
		 appendCode("G02");
		}
	 appendNumCode ("X",p.x());
	 appendNumCode ("Y",p.y());
	 if (radius==0) {
		 appendNumCode ("I",p2.x());
		 appendNumCode ("J",p2.y());
	    }
		else{
		 appendNumCode ("R",radius);
		}
	 cartidgeReturn();
	 setLastPos(p);
	}
	
	
	void GCode::feedRateMove (QPointF p,qreal Z){
	
	 p=partTrans.map(p);
	 ///@todo: change qfuzzycompare to precision related check
	 ///@note Qfuzzycompare is used to limit unnessary(cause not within precision) moves of the tool
	 if (!qFuzzyCompare(p.x(),lastX) || !qFuzzyCompare(p.y(),lastY) ) {
		 appendCode("G01");
		 if (p.x()!=lastX) 	 appendNumCode ("X",p.x());
		 if (p.y()!=lastY) 	 appendNumCode ("Y",p.y());	 
         ///appendNumCode ("Z",Z);	 
		 cartidgeReturn();
		 setLastPos(p);
		}
		
	}
	
	///@todo: when implmenting post-processor replace G00, G01, with user specified codes
	void GCode::rapidMove(QPointF p,qreal Z){
	 
	 p=partTrans.map(p);
	  if (!qFuzzyCompare(p.x(),lastX) || !qFuzzyCompare(p.y(),lastY) ) {
		 appendCode("G00");
		 if (p.x()!=lastX) 	 appendNumCode ("X",p.x());
		 if (p.y()!=lastY) 	 appendNumCode ("Y",p.y());	 
         ///appendNumCode ("Z",Z);	 
		 cartidgeReturn();
		 setLastPos(p);
		}
	}	
	
	void GCode::comment(QString comment){
	 *this <<"( "+comment+" )"<<endl;
	}

	void GCode::home(){
	 /// Move the tool to its home position
	 rapidMove(homePoint,homeZ);
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
	
	
