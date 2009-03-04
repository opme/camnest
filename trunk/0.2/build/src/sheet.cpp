
 #include "sheet.h"
 //#define RAND_MAX 255
#define ARROW_LENGHT 10
  DL_Dxf* dxf;
  Test_CreationClass* creationClass;
  Sheet *scene;
  QGraphicsView *view;
  QPainterPath path2;
  
  QGraphicsItem *generatedPath;
  QGraphicsItem  *toolPathItem;
  QGraphicsItem  *contoursPathItem;
  
 //QPainterPathStroker *partOutline2;
   QList<QGraphicsItem *> selectParts;
 int mode=0;
 /// weither thescene is empty or not
 int empty=1;
 /// weitherthere areseneted itmes or not
 int selection_empty=1;
 /// numberof selecteditems
 int selected_nbr=0;
 ///  QGraphicsPathItem *par2t;
 QList <QPointF > linesListNew;
 /// havn't to be pointer reference as they entities are deleted after being read
 QList<Test_CreationClass *> creationClassList;
 
  /// stiores the organised entities Start/end points.
  QList <QList<QPointFWithParent  > > gCodePoints;
  /// stiores the circles centers/radius start & end points bieng the attaque points
   QList<QPointF > gCodeCirclesPoints;
   QList<qreal > gCodeCirclesRadius;
  /// the first closed loop in a piece
 QList<QPointF > closedLoop;
 QPen toolPen(Qt::blue);
 QPen contourPen(Qt::red);

/// See http://www.linuxcnc.org/handbook/gcode/g-code.html for more infos about G-code

	void GCode::writeHeader() {
	 //setFieldWidth(2);
	 setRealNumberPrecision(6);
	 //QDateTime date;
	 //QString dateString (date.toString
	 //("dd.MM.yyyy"));
	 //qDebug()<<dateString;
	 
	 //*this << dateString <<endl;
	 //*this <<"(program start)"<<endl;
	 comment ("Program generated from :" + this->fileName) ; //FIXME the operator << can't deal with pointers !!s
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
	void GCode::writeClosedLoop(QList<QPointFWithParent > closedLoop){
	 int pos=0;
	 ///the end point of an arc
	 QPointFWithParent  endPoint(0,0);
	 /// a point in a line entinty weiither the start or end (becomle the start in a arc one)
	 QPointFWithParent point(0,0);
	 ///FIXME: a problem with qlist dimension size pos+2 to solve
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
	
	 QPointF circleCenter, attackPoint;
	 qreal radius;

	void GCode::writeCircleLoop(QList<QPointF> circleLoop,QList<qreal> circlesRadius){
	 int pos=0;
	 while (pos <= circleLoop.size()-2){
	 /// Todo maybe should replace regular QPOINTF with QPointFWithParent and get rid of Qlist circles attackpoint
		 circleCenter=circleLoop.at(pos);
		 attackPoint=circleLoop.at(pos+1);
		 radius=circlesRadius.at(pos/2);
		 /// go to the center with G0
		 rapidMove( circleCenter.x(),circleCenter.y(),0);
		 ///start cutting till being onthe circle
		 feedRateMove( attackPoint.x(),attackPoint.y(),0);	
		 /// now that we are on the circle cut it
		 ArcCut(attackPoint.x(),attackPoint.y(),0,circleCenter.x()-attackPoint.x(),circleCenter.y()-attackPoint.y(),0);
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
	
	
	bool MainWindow::saveFile() {

	 QString fileName (QFileDialog::getSaveFileName(this, tr("Save File"),"/media/donnees/SL+TN",tr("Gcode Files (*.nc)")));
	 QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("CamNest"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
         return false;
		}
	 /// Create the Gcode File
	 GCode partGCode (& file);
	 partGCode.fileName=fileName;
	 partGCode.writeHeader();
	 int i=0;
	 while (i < gCodePoints.size()){
		 partGCode.comment("Adding a Loop");
		 partGCode.comment("Turnin off torch");
		 partGCode.comment("going to Z home");
	 	 partGCode.writeClosedLoop( gCodePoints.at(i));
		 i++;
	 }
	 partGCode.writeCircleLoop( gCodeCirclesPoints,gCodeCirclesRadius);
	 
	 partGCode.writeEnd();
	 statusBar()->showMessage(tr("File saved"),4000);
	 return true;
	}
 
 

  GCode::GCode( QFile *file):QTextStream (file) {
	 lineNumber=0;
	 lastX=lastY=lastZ=homeX=homeY=homeZ=0; /// change to Home pos from settings
	 lastgcode="G90";
	 ///some stupid cam soft do need the trailing zeros to work like ncplot!!!
	 setRealNumberNotation(QTextStream::FixedNotation);
	 ///setRealNumberPrecision (4);
    }
	
    void MainWindow::openFile() {
     QString file = QFileDialog::getOpenFileName(0,"Find Files", "/media/donnees/SL+TN","DXF Files (*.dxf)");
     if (!file.isEmpty()) {
		 Test_CreationClass* creationClass = new Test_CreationClass();
		 DL_Dxf* dxf = new DL_Dxf();
		 if (!dxf->in(file.toStdString(), creationClass)) { // if file open failed
			 qDebug() << "Could not open " << file;
			 return;
			}
		 else {
			 qDebug() << "Reading file Done";
			}
			 creationClassList.append(creationClass);
			 statusBar()->showMessage(tr("File: ")+file);
			 /// Display the parsed part path as is. 
			 path2 =creationClass->partPath;
			 QGraphicsPathItem *part= new QGraphicsPathItem(path2);
			 empty=0;
			 part->setFlag(QGraphicsItem::ItemIsMovable, true);
			 part->setFlag(QGraphicsItem::ItemIsSelectable, true);
			 part->setPos(300,300);
			 scene->addItem(part);
			 QGraphicsRectItem *rectBound = new QGraphicsRectItem(creationClass->partBoundingRect);
		}
	 else {
		 statusBar()->showMessage(tr("Please select a file"));
		}
	}

	void MainWindow::generatePath() {	 
	 if (creationClassList.at(0)!=0){
		 //qDebug()<<"Generating the path"<<creationClassList.at(0)->pointsPathList;
		 gCodePoints=organiseEntities(creationClassList.at(0)->pointsPathList,creationClassList.at(0)->partPathsList);
		 //qDebug()<<"the linked lines list:"<<gCodePoints;
		 gCodeCirclesPoints=addCircles(creationClassList.at(0)->pointsCircleList,creationClassList.at(0)->circlePathsList);
		 //qDebug()<<"the circles cut list:"<<addCircles(creationClassList.at(0)->pointsCircleList,creationClassList.at(0)->circlePathsList);
		 gCodeCirclesRadius=creationClassList.at(0)->radiusCircleList;
		}
     statusBar()->showMessage(tr("Path generated"));
	}	

	
    void MainWindow::clearGeneratedPath (){
		scene->removeItem(toolPathItem);
		scene->removeItem(contoursPathItem);
	}
	
    void MainWindow::rotateParts() {
	 if (!selectParts.isEmpty ()) { 
	 	 foreach(QGraphicsItem *part,selectParts){
	 		 part->rotate(90);
			 statusBar()->showMessage(tr("Rotation done"));
	 		}
	 	}
		else{
		  statusBar()->showMessage(tr("Please make a selection"));
		}
	}
	
    void MainWindow::clearScene() {
	 creationClassList.removeAt(0);
     statusBar()->showMessage(tr("Emptied Scene"));
	 scene->clear();
	}	
	
	
	QList <QPointF >  MainWindow::addCircles(QList <QPointF > circlePointsList,QList <QPainterPath > circlesPathsList){

	 QPainterPath subLoop;
	 QPainterPath toolLoop;
	 QPainterPath arrowPath;
	 
	 //arrowPath.lineTo(5,5);
	 //arrowPath.lineTo(100,0);
	 //QGraphicsPathItem arrow(arrowPath);
	 //arrow.setFlag(QGraphicsItem::ItemIsMovable, false);
	
	 int pos=0;double angle;
	 qDebug()<<"Adding "<<circlePointsList.size()<<" circles";
	 while (pos<=circlePointsList.size()-2) {	 
		 /// add the arrrow to indicate the toolpath sens
		 ///go to the circle center
		 angle=getAngle(circlePointsList.at(pos),circlePointsList.at(pos+1));// shoukld be +2 but then go oaftre size
		 toolLoop.lineTo(circlePointsList.at(pos));		
		 arrowPath.moveTo(circlePointsList.at(pos));
		 arrowPath.lineTo(ArrowWing1(angle,circlePointsList.at(pos)));
		 arrowPath.moveTo(circlePointsList.at(pos));
		 arrowPath.lineTo(ArrowWing2(angle,circlePointsList.at(pos)));
		  ///touch the circle 
		// toolLoop.lineTo(circlePointsList.at(pos+1));
		  ///add the circle to the scene
		 scene->addPath(circlesPathsList.at(pos/2));
		 pos=pos+2;	
		 //qDebug()<<pos;
		}
		// arrow.setPos(toolLoop.currentPosition());
		// scene->addItem(&arrow);
	 scene->addPath(arrowPath,QPen(Qt::blue,1));
	 scene->addPath(toolLoop,toolPen);
	 return circlePointsList;
	}
	 
	double getAngle(QPointF start_point,QPointF end_point){
	 
	 double d_x = end_point.x() - start_point.x();
	 double d_y = end_point.y() - start_point.y();
	 double angle = atan2 (d_y, d_x)  * 180.0 / M_PI;
	 //qDebug()<< "angle of the line " <<angle;
	 return angle;
	 }
	
	QPointF ArrowWing1(double line_angle,QPointF end_point){
	 QPointF wing1;
	 double angle_wing1=(line_angle -12 +180) * M_PI /180;	
	 //qDebug()<< "angle wing 1 " <<angle_wing1;
	 wing1.setX(end_point.x()+cos(angle_wing1)*ARROW_LENGHT);
	 wing1.setY(end_point.y()-sin(angle_wing1)*ARROW_LENGHT);
	 return wing1;
	}

	
	QPointF ArrowWing2(double line_angle,QPointF end_point){
	  QPointF wing2;
	 double angle_wing2=(line_angle +12+180)/180*M_PI;
	 wing2.setX(end_point.x()+cos(angle_wing2)*ARROW_LENGHT);
	 wing2.setY(end_point.y()-sin(angle_wing2)*ARROW_LENGHT);
	 return wing2;
	}
	 
	 
 /// NOTE: some parts may contains repeated lines (drawn above others) How to deal with such entities ?
    QList <QList<QPointFWithParent  > > MainWindow::organiseEntities(QList <QPointFWithParent > pointsList,QList <QPainterPath > partPathsList){
	
	 /// those two have to be returned to be used by the gcode generator
	 QList <QList<QPointFWithParent > > entitiesListFinal;
	 /// holds the organised entities paths between tow end points 
	 QList <QPainterPath > partPathsListFinal;
	 
	 /// stores the end points list that is used to optimize toolpath TSP optimization
	 QList <QPointFWithParent > pointsEndList;
	 
	 QPainterPath subLoop;
	 QPainterPath toolLoop;
	 //generatedPath=new QGraphicsItem();
	 //toolPathItemGroup=new QGraphicsItemGroup();
	 bool alreadyChecked=false;
	 int oldPos=0,found=1;
	 
	 QPointFWithParent currentPoint(0,0);
	 QPointFWithParent oldPoint(0,0);
	 QList <QPointFWithParent > pointsListNew;
	 
	 int numberClosedPath=0;
	 	 //entitiesListFinal.clear();
	 qDebug() << "Have to deal with "<<partPathsList.size()<<" Entities represented by "<< pointsList.size();
	 int k=0,occurence=0, pos=0;
	  /**
	  *for the algorithm to be efficient on open loops we have to start by an unique end point!
	  *loop until we find a unique point in the list to start with elsewhere go with the first
	  */
	 while ((k<pointsList.size()) &&(occurence!=1)){
	     pos=k;
	     occurence=pointsList.count(pointsList.at(pos));
	 	 k++;		 
		 }
	 /**
	  *Some shapes can contains an odd number of points (intersection) the user may be interted by
	  *being notified of their presence FIXME: TO be removed ?
	  */ 
	 ///int occurences=0;
	  /**
	  *Start the entities reorganisation process until the last 2 points in the list
	  */ 
	 
	 while (pointsList.size()>=2) {
		 currentPoint=pointsList.at(pos);
		 /// occurences=linesList.count(currentPoint);
		 /// if (occurences>2) {
		/// 	 QMessageBox msg(QMessageBox::Critical,"Warning" , "Point apperas on list "+QString::number(occurences, 10)+" times",QMessageBox::Ok,this);
		 ///     msg.exec(); 
		///  }
		 // qDebug()<<"Working with"<<currentPoint<< " at "<<pos;		  
		  /** 
		  * If the list contains the point only one time we can't link between it and other shapes
		  * unless we stwitch to the other point definfing the shape, if it hadn't already been checked
		  *(avoiding infinte loops )
		  */
		 if (pointsList.count(currentPoint)==1) {
		     oldPos=pos;
			 //qDebug()<<"No corresponding point.AlreadyChecked other coord:"<<alreadyChecked;
			/// change to the other the point definfig the entity if it havn't already been checked
		     if ( alreadyChecked==false ) {
				 if (pos%2==0) pos++; else pos--; 
				 alreadyChecked=true;
				}
			 currentPoint=pointsList.at(pos);
			 /// still havn't found a corresponding point have to close the current path and start another
			 if (pointsList.count(currentPoint)==1) { 		
				// qDebug()<<"Swaped but still no corresponding point.";
				 /// to garantee that we have swaped values before entering here even when we have alreadyChecked
				 if (oldPos==pos) {
				 if (pos%2==0) pos++; else pos--; 
				 }
				 currentPoint=pointsList.at(pos);
				 /// push the Two current points into the Qlist of the current path
				 pointsListNew <<pointsList.at(pos);
				 pointsListNew <<pointsList.at(oldPos);
				 if (oldPos<pos)  {
					 pointsList.removeAt(oldPos);
				     pointsList.removeAt(oldPos);
					}
			     else {
					 pointsList.removeAt(pos);
				     pointsList.removeAt(pos);
					}	
				 /** Will be useful later for TSP optimization*/
				 pointsEndList.append(pointsListNew.first());
				 pointsEndList.append(pointsListNew.last());
				 
				 toolLoop.lineTo(pointsListNew.first());
				 
				 ///It's time to draw the corresponding entity
				 subLoop.addPath(partPathsList.at(pos/2));
				 partPathsList.removeAt(pos/2);
				 
				 ///subLoop.moveTo(linesListNew.first());				 
				 
				 if (found==1) numberClosedPath ++; /// increment only if it's composed of at least one intersection
				 /// Add the current path to entities list
				 entitiesListFinal<< pointsListNew;
				// qDebug()<<"The drawn Contour:"<< pointsListNew;
				 pointsListNew.clear();
				 contoursPathItem=scene->addPath(subLoop,contourPen);				 
				 toolPathItem=scene->addPath(toolLoop,toolPen);
				 //toolPathItem->setParentItem(generatedPath);
				 //contoursPathItem->setParentItem(generatedPath);
				
				 ///toolPathItem.addToGroup(scene->addPath(subLoop,QPen(color,1)));
				 ///contoursPathItem.addToGroup(scene->addPath(toolLoop,QPen(Qt::red,1)));	
				 
				 partPathsListFinal<<subLoop;
				 //qDebug()<<subLoop;
				 subLoop=QPainterPath();
				 //toolLoop=QPainterPath();
				 found=1;k=0;occurence=0;alreadyChecked=false;
				 /// Refind a better starting point than 0
				   while ((k<pointsList.size()) &&(occurence!=1)){
	                  pos=k;
	                  occurence=pointsList.count(pointsList.at(pos));
	 	              k++;		 
					}	
				 continue;
				}
				/// After swapping Points Have found that this point do have a correponding point in another entity
		     else { 
		        // qDebug()<<"The other point at pos "<<pos<<" has a correponding";
			     found++;
				 /// It's time to remove the points and their corresponding entities
			     if (found==2) {
						/// to keep the lines order we have to put currentPoint after oldPoint
			  
					 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 			  
		 			 /// push the Two current points into the Qlist of the current path
					 pointsListNew <<pointsList.at(pos);
					 pointsListNew <<pointsList.at(oldPos);
					 /// since oldPose become pos hen we remove the first time we have to remove the minor position between the two
					 if (oldPos<pos)  {
						 pointsList.removeAt(oldPos);
						 pointsList.removeAt(oldPos);
						}
					 else {
						 pointsList.removeAt(pos);
						 pointsList.removeAt(pos);
						}	
					 ///It's time to draw the corresponding entity
					 subLoop.addPath(partPathsList.at(pos/2));
					 partPathsList.removeAt(pos/2);
					 found=1;/// we still have one point to work with 
				}
				 /// get the corresponding point location and store the caller one to avoid infinte loop
				 if (pointsList.indexOf(currentPoint)==pos ) {
					 pos=pointsList.lastIndexOf(currentPoint);
					}
				 else {
					 pos=pointsList.indexOf(currentPoint);
					}
				 /// change to the other the point definfig the line
				 if (pos%2==0) pos++; else pos--; 
				 continue;
			}
		 	 /** Found a corresponding point in another netity*/
		}
		else {
		 found++;		 
		 /// It's time to remove the points and their corresponding entities
		 if (found==2) {
			 /// to keep the lines order we have to put currentPoint after oldPoint			  
			 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 			  
		 	 /// push the Two current points into the Qlist of the current path
			 pointsListNew <<pointsList.at(pos);
			 pointsListNew <<pointsList.at(oldPos);
			 /// since oldPose become pos hen we remove the first time we have to remove the minor position between the two
			 if (oldPos<pos)  {
				 pointsList.removeAt(oldPos);
				 pointsList.removeAt(oldPos);
				}
			 else {
				 pointsList.removeAt(pos);
				 pointsList.removeAt(pos);
				}		
		     ///It's time to draw the corresponding entity
			 subLoop.addPath(partPathsList.at(pos/2));
			 partPathsList.removeAt(pos/2);
			 found=1;/// we still have one point to work with 
			}
			 /// get the corresponding point location and store the caller one to avoid infinte loop
		 if (pointsList.indexOf(currentPoint)==pos ) {
			 pos=pointsList.lastIndexOf(currentPoint);
			}
		 else {
			 pos=pointsList.indexOf(currentPoint);
			}
				 /// change to the other the point definfig the line
		 if (pos%2==0) pos++; else pos--; 
		 /// alreadyChecked the other coordinate as we're coming from
		 alreadyChecked=true;
		 continue; /// TODO:remove this as it will continue naturally
		}		 
	}
	 qDebug () << "Found" << numberClosedPath << "closed Paths";//linesListNew;
	 ///qDebug()<<"The end points lines list: "<<pointsEndList;
	 // qDebug()<<"The parts paths list: "<<partPathsListFinal;
	 /// mAybe should do further processing to simplify the path 
	 // qDebug()<<"The simplified parts paths list: "<<partPathsListFinal.at(0).simplified();
	 return entitiesListFinal;
    }
	
  /*
   the seetMetal declarations
  */
  
 SheetMetal::SheetMetal(QWidget *parent): QWidget(parent)   {     
	 /// put the scen in the view
	 scene = new  Sheet (this);
	 QRect sceneRect(0,0,1100,900);
     scene->setSceneRect(sceneRect);
	 view = new QGraphicsView (scene,this);   
	 //QPushButton *quit = new QPushButton("Quit",this);
	}  
	
 
	
	void Sheet::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 QPointF p1=mouseEvent->scenePos();QPointF p2=mouseEvent->lastScenePos();
	 
	 if (mouseEvent->button() == Qt::RightButton)
	  {
	      view->fitInView(QRectF(p1,p2),Qt::KeepAspectRatio);
		  view->setDragMode(QGraphicsView::NoDrag);
	  } 
	  
	  if (mouseEvent->button() == Qt::LeftButton) { 
	     //mode=0;
		 /// or couldbe simply retrived from scene->selectedItems()
	     selectParts=scene->selectedItems();
		///selectedItems= scene->items ( QRectF(p1,p2), Qt::IntersectsItemShape  );
		 
	     if (!selectParts.isEmpty ()) { 	      
		     ///   qDebug()  << "creating thegroup";		 
			 ///  selection = new QGraphicsItemGroup();
			 ///  selection = scene->createItemGroup(selectedItems);
			 ///  qDebug()  << "groupcreated";
		      selection_empty=0;
		      /// createa groupcontaingin  theselected  items
		      selected_nbr=selectParts.size();
			 //if (selected_nbr==1) {
		     /// NOTE: first returns a referencenot theobject!!!!
			 qDebug()  << selected_nbr<< "items selected";
		      selectedItem=selectParts.first();		 
		     // }
	          //QGraphicsItem *selectedItem =(selectedItems().first());
	         
		    ///  int i=0;
		       //////foreach(QGraphicsItem *item,selectedItems){
      			 /// qDebug() << i << " item is of type :" << item->type()<<" and is selected= "<< item->isSelected();
				 //selection->addToGroup(item);
				 // if (item->isSelected()==true){				    
				   //   item->setSelected (false);				     
				 // }
				 //  else {
				  //    item->setSelected (true);				     
				 // }
				 /// i++;
				 ///  if (item->type()==6) {
				     //QGraphicsLineItem test = QGraphicsLineItem(item);
				     //QGraphicsLineItem test;
				     /// QGraphicsLineItem *test=qgraphicsitem_cast<QGraphicsLineItem*> ( item );
				     //QPainterPath testPath= item->shape();
				     /// qDebug() << test->scenePos ();
				    ///  if (item->isSelected()){
				          //  qDebug() << "selected";
				         //    item->setSelected (false);
				         /// test->setPen (QPen(Qt::black, 1));// Qt::RoundCap, Qt::RoundJoin ));
				      ///   }
				     /// else {
				         //   item->setSelected (true);
				       ///   test->setPen (QPen(Qt::red, 1));
				        /// }
				    /// }
				 ///}	
        	}
			/// else {
			 /// no selection and the group already exists
			 //if (selection!=0) {
			 /// haveto createthe groupand then destroyit to prevent destroying soething that dosen't exist:)
				///  selection = new QGraphicsItemGroup();
			    ///  scene->destroyItemGroup(selection);
			    ///  qDebug()  << "destroyed old group";	
			   //  }
			///  }
	    }
	 if (mouseEvent->button() == Qt::MidButton) { 
	     qDebug()  << "Mid released";
	     view->fitInView(QRectF(0,0,800,800),Qt::KeepAspectRatio);
		  view->setDragMode(QGraphicsView::NoDrag);
		}
	   
	
	}
	
	void Sheet::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 //qDebug()  << 
	 //QPoint P= mouseEvent->screenPos();
		 //if( mode==1 ) {
		 //qDebug ()<<mouseEvent->screenPos();
		 //mouseEvent->scenePos()
		 //}
		if (empty==0 && selection_empty==0) {		 
	      if	(selected_nbr==1  && mode==1 ) {
	      //qDebug ()<<"Moving" <<mouseEvent->screenPos();
		 // qDebug ()<<selection->pos();
		  selectedItem->setPos(mouseEvent->scenePos());
	     // selection->setPos(mouseEvent->scenePos());
	     }
		}
		
		//qDebug () << P;
	}

	void Sheet::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
		if (mouseEvent->button() == Qt::RightButton){ qDebug()  << "right"; 
	
	     view->setDragMode(QGraphicsView::RubberBandDrag); 
	        mode=0;
	    }
		if (mouseEvent->button() == Qt::LeftButton) { 
		  qDebug()  << "left";
		  mode=1 ; /// moveitem
		 view->setDragMode(QGraphicsView::RubberBandDrag);
		  //QGraphicsItem *selectedItem=itemAt(mouseEvent->scenePos());
		
		}
		
		 if (mouseEvent->button() == Qt::MidButton) { qDebug()  << "Mid";}
		 ///selectedItem  :Returns a list of all currently selected items. The items are returned in no particular order.
		
		 //view.rotate(90);
		 //if(!selectedItem().isEmpty()){
		 if(selectedItem!=0){
		
	     //QList<QGraphicsItem *> collideWithMe= collidingItems (selectedItem);
		 
		 //qDebug() << itemAt(mouseEvent->scenePos());
		 
		 //QGraphicsItem *selectedItem =(selectedItems().first());
		 //selectedItem->setPos(selectedItem->pos().x()+1,selectedItem->pos().y()+3);// hide();
		 // selectedItem->moveBy(-dx,-dy)
		 //myline
		 //if (!collideWithMe.isEmpty()) {
			// qDebug() << "colliding";
		 //}
		 //else 
		 //{
		 //qDebug() << "Not colliding";
		 //}
		}
		
    }
	
	
	void Sheet::wheelEvent(QGraphicsSceneWheelEvent *mouseEvent)    {
	 //if(mouseEvent->modifiers()==Qt::ControlModifier){
		int i =  mouseEvent->delta();
		qreal factor;
		if(i>=0){
			factor = i/100.0;
		}
		else {
			factor = -100.0/i; // negative Richtung ...
		}
		//emit zoom(factor);
		
	 QPointF topLeft     = view->mapToScene( 0, 0 );
	 QPointF bottomRight = view->mapToScene( view->viewport()->width() - 1, view->viewport()->height() - 1 );
	 qreal width=bottomRight.x()-topLeft.x();
	 qreal height=bottomRight.y()-topLeft.y();
	 //std::cout << width << "/" << height << " : " << factor << std::endl;
	 if((width/factor<=5000)&&(height/factor<=5000)){
		QMatrix oldMatrix = view->matrix();
		qreal newScale=oldMatrix.m11()*factor;
		view->resetMatrix();
		view->translate(oldMatrix.dx(), oldMatrix.dy());
		view->scale(newScale, newScale);		
	}
		view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		// / mWhy do we need theset Accepted???ouseEvent->setAccepted(true);
		return;
}
 
 
 void MainWindow::createStatusBar() {
     statusBar()->showMessage(tr("Ready"));
    }

 
 void MainWindow::createToolBars(){
	 fileToolBar = addToolBar(tr("File"));
     fileToolBar->addAction(openAction);
	 
     editToolBar = addToolBar(tr("Edit"));
     editToolBar->addAction(clearAction);
	 editToolBar->addAction(generateAction);
	 editToolBar->addAction(rotateAction);
	 editToolBar->addAction(saveAction);
	 editToolBar->addAction(clearPathAction);	 
	}
	

  MainWindow::MainWindow(){
  
     /// Actions have to be first declared before setting the menus
	 aboutAction = new QAction(tr("&About"), this);
	 aboutAction->setShortcut(tr("Ctrl+B"));
     openAction = new QAction(tr("&Open"), this);
	 openAction->setShortcut(tr("Ctrl+O"));
	 saveAction = new QAction(tr("&Save"), this);
	 saveAction->setShortcut(tr("Ctrl+S"));
	 clearAction = new QAction(tr("&Clear"), this);
	 clearAction->setShortcut(tr("Ctrl+C"));	
	 clearPathAction = new QAction(tr("&Erease Path"), this);
	 clearPathAction->setShortcut(tr("Ctrl+E"));
	 rotateAction = new QAction(tr("&Rotate"), this);
	 rotateAction->setShortcut(tr("Ctrl+R"));	 
	 generateAction = new QAction(tr("&Generate path"), this);
	 generateAction->setShortcut(tr("Ctrl+G"));
	 
	 /// connecting the signals
	 connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));  
	 connect(openAction, SIGNAL(triggered()),this, SLOT(openFile())); 
	 connect(clearAction, SIGNAL(triggered()),this, SLOT(clearScene())); 
	 connect(clearPathAction, SIGNAL(triggered()),this, SLOT( clearGeneratedPath())); 
	 connect(rotateAction, SIGNAL(triggered()),this, SLOT(rotateParts())); 
	 connect(generateAction, SIGNAL(triggered()),this, SLOT(generatePath())); 
	 connect(saveAction, SIGNAL(triggered()),this, SLOT( saveFile())); 
     

	
	  /// setup theGUI
	 createMenus() ;
	 createStatusBar(); 
	 createToolBars();
	 qDebug()<< "Interface ready";
    /// create the view  in the mainWindow
     sheet= new  SheetMetal (this);
	 sheet->setGeometry(20, 60, 1000, 1000);
	 // QPushButton *quit = new QPushButton("Quit",this);
     //QHBoxLayout *layout = new QHBoxLayout;
     //layout->addWidget(sheet);   
  }
    
 void MainWindow::createMenus() 
 {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(clearAction);
    fileMenu = menuBar()->addMenu(tr("&Help"));
  fileMenu->addAction(aboutAction);
  
 }
 
    Sheet::Sheet (QWidget *parent):QGraphicsScene () {
	
	}
 
  void MainWindow::about()
{
  
     QMessageBox::about(this, tr("About CamNest"),
                       tr("<b>CamNest</b> Dxf Viewer and Parts neting software "));
}
 
 
  Part::Part(QWidget *parent) 
  {
      /// construct an empty QGraphicsItem for now
  
  }
  
  void  Part::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
     //
      //foreach(QGraphicsLineItem* item,creationClass->linesList){
        //  			scene->addItem(item);
        //		}
		//painter->setBrush(Qt::black);
	 //QPainterPath path;
     
      //path.lineTo(20, 30);
        //path.cubicTo(80, 0, 50, 50, 80, 80);
        //painter->drawPath(path);		
		path2 =creationClass->partPath;
		path2.moveTo(20, 80);
		path2.lineTo(20, 30);
		qDebug() << "path fetched";
		if (!path2.isEmpty()) {
		qDebug() << "path not empty";
		painter->drawPath(path2);
		}
    }	
	  QSize SheetMetal::sizeHint() 
	  {
     return QSize(300, 300);
     }
	 
	 QSize SheetMetal::minimumSizeHint() 
 {
     return QSize(200, 150);
 }
 
	


 /// NOTE: some parts may contains repeated lines (drawn above others) How to deal with such entities ?
   QList <QList<QPointF > > MainWindow::commonPoints(QList <QPointF > linesList, QList <QPointF > arcsList,QList <QPainterPath > arcsPathsList){
     //QList <QPointF > linesList;
	 QList <QList<QPointF > > linesListFinal;
	 /// stores the lines ends to be used later to link between them
	 QList <QPointF > linesListEnds;
	 int pos=0,found=1;//i=0,
	 bool alreadyChecked=false;
	 int oldPos=0, arcPos=0,oldArcPos=0;
	 QPointF currentPoint;
	 QPointF oldPoint;
	 QPainterPath subLoop;//=new QPainterPath();;
	 QPainterPath toolLoop;
	 int numberClosedPath=0;
	 //int callerPos=0;
	 QColor color =Qt::green;
	 linesListFinal.clear();
	 ///for the algorithm to be efficient on open loops have to start by an unique end point!
	 int k=0,occurence=0;
	 while ((k<linesList.size()) &&(occurence!=1)){
	     pos=k;
	     occurence=linesList.count(linesList.at(pos));
	 	 k++;		 
		 }
	
	 ///QList <QPList > linesListList;
	 ///linesList.clear();
     ///linesList<<QPoint(0,20)<<QPoint(10,10)<<QPoint(20,30)<<QPoint(40,90)<<QPoint(10,10)<<QPoint(20,30)<<QPoint(10,40)<<QPoint(0,0)<<QPoint(40,90)<<QPoint(10,40);
	 // linesList=pointsList;
	 //qSort (linesList.begin.x(), linesList.end.x());
	 qDebug()<<"lines:"<< linesList;
	  qDebug()<< "arcs:"<<arcsList;
	 // qDebug()<< arcsList.at(3)-linesList.at(0);
	 /// the first point removed from the list has to be checked and use prepend instead of append then
	 int occurences=0;
	 while (linesList.size()>=2) {//i<linesList.size()){//
		 currentPoint=linesList.at(pos);
		 occurences=linesList.count(currentPoint);
		// qDebug()<<occurences;
		 if (occurences>2) {
			 QMessageBox msg(QMessageBox::Critical,"Warning" , "Point apperas on list "+QString::number(occurences, 10)+" times",QMessageBox::Ok,this);
		     msg.exec(); 
		 }
		  qDebug()<<"Working with"<<currentPoint<< " at "<<pos;
		 if (linesList.count(currentPoint)==1) {
		     oldPos=pos;
			 qDebug()<<"No corresponding point.AlreadyChecked other coord:"<<alreadyChecked;
			
		     if ( alreadyChecked==false ) {
				 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line if havn't been already ch=edcked
				 alreadyChecked=true;
				}
			 currentPoint=linesList.at(pos);
			 if (linesList.count(currentPoint)==1) { /// still havn't found a corresponding point			
				 /// before stopping have to check if they arn"t other entities that can continue teh chain
				 /// remove items in othe same orders for arcs to be well handled
				 if (oldPos==pos) {
				 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line if havn't been already ch=edcked
				 }
				 currentPoint=linesList.at(pos);
				 qDebug()<<"Swaped but still no corresponding point.trying with arcs: ";
				 linesListNew <<linesList.at(pos);
				 linesListNew <<linesList.at(oldPos);
				 if (oldPos<pos)  {
					 linesList.removeAt(oldPos);
				     linesList.removeAt(oldPos);
					}
			     else {
					 linesList.removeAt(pos);
				     linesList.removeAt(pos);
					}	
				 // qDebug()<<numberClosedPath <<"Stopping the Chain. Result :"<< linesListNew;
				 // qDebug()<<qFuzzyCompare(linesListNew.last().x(),arcsList.at(3).x());
				 // qDebug()<<(linesListNew.last().x()-arcsList.at(3).x());
				  // qDebug()<<(linesListNew.last().y()-arcsList.at(3).y());
				 int j=0;//Qt::green;
				 //Q_ASSERT(!creationClass->pointsArcsList.isEmpty());
				 // qDebug()<<arcsList<<linesListNew.last()<<linesListNew.first();
				 //  qDebug()<<linesListNew;
				 linesListEnds.append(linesListNew.first());
				 linesListEnds.append(linesListNew.last());
				 //qDebug()<<"Working with"<<linesListNew.last();
				 /// IMPORTANT have to check for the last entered point first !!
				 if  (arcsList.contains(linesListNew.last()) ) {
				     arcPos=arcsList.indexOf(linesListNew.last());
					   qDebug()<<"********Found a complementary arc at : "<<arcPos;
					   subLoop.addPath(arcsPathsList.at(arcPos/2));
					 //scene->addPath(arcsPathsList.at(arcPos/2),QPen(color,1));/// NOTE: the odd position /2 are handled by Qt correctly
					 /// remove the arcs entities and add extrmities points
					  // subLoop.moveTo(arcsList.at(arcPos));
					 if (arcPos%2==0) {						
						 oldArcPos=arcPos;
						 arcPos++;
						 currentPoint=arcsList.at(arcPos);
						 //arcsList.removeAt(arcPos);
					 	 // arcsList.removeAt(arcPos);
						} 
					 else {
						 oldArcPos=arcPos;
						 arcPos--;
						 currentPoint=arcsList.at(arcPos);
						 //arcsList.removeAt(arcPos);
				         //arcsList.removeAt(arcPos);
						} 
					 // qDebug()<<"Searching for: "<<currentPoint<<"in "<< linesList;
					 //qDebug()<<"arcs Lists became: "<<arcsList;
					 //subLoop.moveTo(arcsList.at(arcPos));					 
					 /// if the other point or the arc can be used to continue the algo stores the new pos
					 if ( linesList.contains(currentPoint)) {
					     pos=linesList.indexOf(currentPoint);
						 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line
						 qDebug()<<"continueing from positin :" <<pos;
						 continue;
						}
						 //qDebug()<<"HOP" ;
					}
				  if  (arcsList.contains(linesListNew.first()) ) {
					 arcPos=arcsList.indexOf(linesListNew.first());
					 qDebug()<<"***********adding an Arc from first point at pos "<< arcPos;
					 subLoop.addPath(arcsPathsList.at(arcPos/2));
					 ///scene->addPath(arcsPathsList.at(arcPos/2),QPen(color,1));
					 /// remove the arcs entities and add extrmities points
					 //subLoop.moveTo(arcsList.at(arcPos));
					 if (arcPos%2==0) {						
						 oldArcPos=arcPos;
						 arcPos++;
						 currentPoint=arcsList.at(arcPos);
						 //arcsList.removeAt(arcPos);
						 //arcsList.removeAt(arcPos);
						} 
					 else {
						 oldArcPos=arcPos;
						 arcPos--;
						 currentPoint=arcsList.at(arcPos);
						 //arcsList.removeAt(arcPos);
				         //arcsList.removeAt(arcPos);
						} 
					 //qDebug()<<"Searching for: "<<currentPoint<<"in "<< linesList;
					 //qDebug()<<"arcs Lists became: "<<arcsList;					  
					 /// if the other point or the arc can be used to continue the algo stores the new pos
					 if ( linesList.contains(currentPoint)) {
					     pos=linesList.indexOf(currentPoint);
						 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line
						 qDebug()<<"continueing from positin :" <<pos;
						 ///continue;
						}
					}
				 /// drawing the lines 
				 // color= QColorDialog::getColor(Qt::green, this);
				 // color.setRgb(qrand()%255,qrand()%255,qrand()%255);
			 	 // subLoop.moveTo(arcsList.at(arcPos));
				 //colorTool=Qt::red;
				 toolLoop.lineTo(linesListNew.first());
				 subLoop.moveTo(linesListNew.first());				 
				 color=Qt::green;
				 foreach(QPointF point,linesListNew){				     
				     if (j%2==1) {
					     //QGraphicsLineItem line (&linesListNew.at(j-1),& point);
					     // test->setPen (QPen(Qt::red,numberClosedPath))    				 
                         if (color.isValid()) {					 
					         ///scene->addLine(QLineF(linesListNew.at(j-1),point),QPen(color,1));//QPen(QColor(255, 0, (numberClosedPath+j)*2, 127),1));
							 subLoop.lineTo(point);
							}///Fixme : have to link entities by hand 
					    }
				     j++;
				    }					
				 if (found==1) numberClosedPath ++; /// increment only if it's composed of at least one intersection
				  //AppendArc;
				 qDebug()<<"The drawn Contour:"<< linesListNew;
				 linesListNew.clear();
				 scene->addPath(subLoop,QPen(color,1));
				 scene->addPath(toolLoop,QPen(Qt::red,1));
				 subLoop=QPainterPath();
				 toolLoop=QPainterPath();
				 found=1;k=0;occurence=0;alreadyChecked=false;
				 /// find a better starting point than 0
				   while ((k<linesList.size()) &&(occurence!=1)){
	                  pos=k;
	                  occurence=linesList.count(linesList.at(pos));
	 	              k++;		 
					}	
				 //pos=0 ; /// FIXME 
				 continue;
				}
		 else { /// the other coordinate has a correponding point in another line
		         qDebug()<<"The other point at pos "<<pos<<" has a correponding";//Checking if it's the caller "<<callerPos;
			     found++;
			     if (found==2) {
						/// to keep the lines order we have to put currentPoint after oldPoint
			  
					 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 
			
						 //qDebug()<< "Removing item at"<<pos << "and at"<<oldPos;			 
			  
					 linesListNew<<linesList.at(pos);
					 linesListNew <<linesList.at(oldPos);
			
					 /// since oldPose become pos hen we remove the first time we have to remove the minor position between the two
					 if (oldPos<pos)  {
						 linesList.removeAt(oldPos);
						 linesList.removeAt(oldPos);
						}   
					 else {
						 linesList.removeAt(pos);
						 linesList.removeAt(pos);
						}				 
						//qDebug()<< linesListNew ;
					 found=1;/// we still have one point to work with 
				}
			 /// get the corresponding point location and store the caller one to avoid infinte loop
		     if (linesList.indexOf(currentPoint)==pos ) {
			     pos=linesList.lastIndexOf(currentPoint);
				}
			 else {
			     pos=linesList.indexOf(currentPoint);
				}
			 //i++;
			 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line
			 continue;
			}
		 	
		}
		else { /// founding a corresponding point
		 found++;
		 
		 if (found==2) {
		     /// to keep the lines order we have to put currentPoint after oldPoint
			  
			 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 
			
			 //qDebug()<< "Removing item at"<<pos << "and at"<<oldPos;			 
			  
			 linesListNew<<linesList.at(pos);
			 linesListNew <<linesList.at(oldPos);
			
			 //qDebug()<<linesList;
	/// since oldPose become pos hen we remove the first time we have to remove the minor position between the two
			 if (oldPos<pos)  {
			     linesList.removeAt(oldPos);
				 linesList.removeAt(oldPos);
			    }
			else {
				 linesList.removeAt(pos);
				 linesList.removeAt(pos);
            }				 
			 //qDebug()<<"the new lines list:"<<linesList;
			// qDebug()<< linesListNew ;
			 found=1;/// we still have one point to work with 
		    }
			///moving to the correponding point
		 if (linesList.indexOf(currentPoint)==pos ) {
			 pos=linesList.lastIndexOf(currentPoint);
			}
		 else {
		     pos=linesList.indexOf(currentPoint);
			}
		 //qDebug()<< "found another" <<currentPoint<< "at" <<pos;
		 if (pos%2==0) pos++; else pos--; /// change to the other the point definfig the line
		 alreadyChecked=true;/// alreadyChecked the other coordinate as we're coming from
			//i++;
		 continue;
		}		 
	 }
	 qDebug () << "found" << numberClosedPath << "closed Paths";//linesListNew;
	 qDebug()<<"the end points lines list:"<<linesListEnds;
	 
	 return linesListFinal;
    }
	

 	
void MainWindow::readDxfFile() {
	  // get the dxf entities
	 QString file = QFileDialog::getOpenFileName(0,"Find Files", "/media/donnees/SL+TN","DXF Files (*.dxf)");
     if (!file.isEmpty()) {
	 // qDebug() << "File chosen " << file ;
	 }	
     // Load DXF file into memory:

     Test_CreationClass* creationClass = new Test_CreationClass();
     DL_Dxf* dxf = new DL_Dxf();
     if (!dxf->in(file.toStdString(), creationClass)) { // if file open failed
	   qDebug() << "Could not open " << file;
        return;
     }
	 else {
		qDebug() << "Reading file Done";
	 }
	 statusBar()->showMessage(tr("File open"));
	 
	 // Part *partTest = new Part(this);

	 /// createc the part
	 path2 =creationClass->partPath;

	 QGraphicsPathItem *par2t= new QGraphicsPathItem(path2);
	 empty=0;
	 /// add part as sub items
	 //foreach(QGraphicsLineItem* item,creationClass->linesList){
      			//scene->addItem(item);
				//item->setFlag(QGraphicsItem::ItemIsSelectable, true);
				//item->setFlag(QGraphicsItem::ItemIsMovable, true);
				//item->setParentItem(par2t);
        	//}
			//int i=0;
			//foreach(qint32 item,creationClass->commonList){
			// qDebug()<<"indexes"<< item;
			 
			// scene->addItem(creationClass->linesList.at(item));
			 //qDebug()<<"flags"<<creationClass->linesList.at(item)->flags ();
			// creationClass->linesList.at(item)->setFlag(QGraphicsLineItem::ItemIsMovable, false);
			 //}
      			//scene->addItem(item);
				//item->setFlag(QGraphicsItem::ItemIsSelectable, true);
				//item->setFlag(QGraphicsItem::ItemIsMovable, true);
				//item->setParentItem(par2t);
        	//}
			// QList<qint32>::iterator i;
           //  for (i = creationClass->commonList.begin(); i != creationClass->commonList.end(); ++i) {
			//    // scene->addItem(creationClass->linesList.at(i));
			//	 qDebug()<<"indexes"<< *i;
        	// }
	 //foreach(QGraphicsEllipseItem* item,creationClass->ellipsesList){
       	//	scene->addItem(item);
		//	item->setFlag(QGraphicsItem::ItemIsSelectable, true);
			//item->setFlag(QGraphicsItem::ItemIsMovable, true);
			//item->setParentItem(par2t);
      // 	}
	 QPen pen(Qt::red, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);		
	 par2t->setFlag(QGraphicsItem::ItemIsMovable, true);
	 par2t->setFlag(QGraphicsItem::ItemIsSelectable, true);
	 par2t->setPos(300,300);
	 scene->addItem(par2t);
	 QGraphicsRectItem *rectBound = new QGraphicsRectItem(creationClass->partBoundingRect);
		// rectBound->setPos(100,100);
		// scene->setForegroundBrush(Qt::red);
	 //scene->addItem(rectBound);
	 //qDebug()<<"the linked lines list:"<<linkLines(organiseEntities(creationClass->pointsPathList,creationClass->partPathsList));
	
	 //qDebug()<<"the linked lines list:"<<linkLines(commonPoints(creationClass->pointsList,creationClass->pointsArcsList,creationClass->arcsPathsList));
	 /// then we search for possible arcs joint , arcs extrimities should find two corresponding points on 
	 /// previously created lines to join between them.
	 //qDebug()<< "Arcs extrimity points"<< creationClass->pointsArcsList;
	 	 //qDebug()<< "Radius list"<<creationClass->radiusArcsList;
	 //qDebug()<< creationClass->commonList.size() << "common points definig the outbounds";
	 //	partOutline2 = new QPainterPathStroker();
	// foreach(QGraphicsLineItem* item,creationClass->linesList){
      			//scene->addItem(item);
				//item->setFlag(QGraphicsItem::ItemIsSelectable, false);
				//item->setFlag(QGraphicsItem::ItemIsMovable, false);
				//item->setParentItem(rectBound);
				//item->setParentItem(par2t);
        	//}
	    //QList<QGraphicsItem *> colidesWith= rectBound->collidingItems ( Qt::ContainsItemShape );
		//partOutline2->setCapStyle(Qt::FlatCap);
		//QGraphicsPathItem *itemOutline= scene->addPath ( partOutline2->createStroke(path2), pen) ;
		//qDebug() << "intersect with " << colidesWith.size();
			 
	 // delete dxf;
     //delete creationClass;
	 //addArc(20,20,130,285.1,318);
}
 	
 void MainWindow::addArc(double cx,double cy,double radius,double teta1,double teta2) {
	 QPainterPath partPath;
	 QRectF boundingRect (cx-radius,cy-radius,2*radius,2*radius);
	 if (teta1>teta2) {
	   teta2=360+teta2;
	  }
	  QPointF p1(cx + cos((teta1)*M_PI/180) * radius,cy + sin((teta1)*M_PI/180) * radius);
	  QPointF p2(cx + cos((teta2)*M_PI/180) * radius,cy + sin((teta2)*M_PI/180) * radius);
	 /// move to the arc start point	
	 partPath.moveTo(p1);
	 partPath.arcTo(boundingRect,-(teta1),-fabs(teta1-teta2));	 
	 qDebug() << "Drawn arc ends at:" <<partPath.currentPosition();
	 qDebug() << "Expected arc ends at:" <<p2;
}
 