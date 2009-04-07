#include "gatsp.h"
#include "part.h"
///used to manually set the loopNumber
#include <QInputDialog>
///@note:at() can be faster than operator[](), because it never causes a deep copy to occur.

/// The tolerance defines the disstance within it a loop is estimated to be closed
int tolerance=0.01;
/// Have to be unit dependant 
int leadDist=1;
/// @todo get from settings lead angle for circle loops
int leadAngle=180;
bool plasmaMode=false;

/** have to create an object lead point , a QGraphicsEllipseItem that is magneted to the endPoint parent
and which position will be used by the G code genrator**/
/**   FIXME  handle the case the part outline is a circle!! */
/** For the outline: We first check if the OutlinePoint intersects with the rectBounds, such point can be trivialy
chosen to be a good candidtae for lean in.In that case we draw a line, its lenght being specified by the user,and we
try with different angular positions till the lead-in point is no longer contained in the RectBound*/

/// @fixme: part ansi/6/14-299 is a total mess in leads!



/**
 * 
 * @param path 
 * @param pointsList 
 * @param partPathsList 
 * @param circlePointsList 
 * @param circlesPathsList 
 * @param file 
 */
Part::Part(const QPainterPath path,QPFWPVector pointsList,QPPVector partPathsList,QPFWPVector circlePointsList,QPPVector circlesPathsList):
QGraphicsItem(){
	
	 partShape=path;
	 qtRect=partShape.boundingRect();
	 
	 nbrClosedPath=0;
	 nbrCircles=0;
	 outlinePos=0;
	 
	 partLoops.clear();
	 partLoopsOpt.clear();
	 ptsVector=pointsList;
	 pathsList=partPathsList;
	 cirPtsList=circlePointsList;
	 cirPathsList=circlesPathsList;
	 
	
	 gLoops.clear();
	 gLeadPoints.clear();
	 
	
	 preview=true;
	 ///@note although unused in preview-mode we reset the matrix for proper intialisation
	 transform.reset();
	 
	 ///to keep track of the part Nbr @todo: get this from the scen and use it when deleting parts!!
	 ///setData(0,partNumber);
	 
	 //setFlag(ItemIsMovable);
	 //setFlag(ItemIsSelectable);
	 //LoopThread test(this);
	 setCacheMode(DeviceCoordinateCache);	
	 
	 ///everything is ready we can start processing the part
	 start();
}


///Constructor used to add multiplie part to a sheet by copying the previewed part items
 Part::Part(const Part &parentPart):QGraphicsItem(){
	 preview=false;
	 setFlag(ItemIsMovable);
	 setFlag(ItemIsSelectable);
	 setFlag(ItemIsFocusable);
	 
	 partShape=parentPart.partShape;
	 qtRect=parentPart.qtRect;
	 
	 
	 ///we start taking transformation into account from here
	 transform.reset();
	 
	 ///NOw that the leads are cleaned we can copy them to gLoops that will be pocede by GCode
	 foreach (Loop* cLoop, parentPart.partLoops){
		 gLoops<<cLoop->getEntities();
		 ///@todo: check for plasma mode to avoid copying unnessacry things
		 gLeadPoints<<cLoop->leadIn;
		}
		
	 
		//qDebug()<<gLeadPoints;
	 /// Any change to preview part will affect the partLoops thus editiing one will edit the others
	 partLoops=parentPart.partLoops;
	 ///@fixme as getting loops entities causes crashes we're going through gcodeEntities which is "static" by part 
	 partName=parentPart.partName;
	 ///to keep track of the part Nbr
	 setData(0,parentPart.data(0));
	 ///NOTE:NO need to take the Trans part 
	 }

 void Part::start(){
	 
	 /// Start by parsing circular loops
	 if(cirPtsList.size()!=0){
		 filterCircles();
	 }
	 
	 ///Search for continous loops in part.
	 if(ptsVector.size()!=0){
		 generateLoops(ptsVector);		
	 }
	
	
	 if (plasmaMode){
		 ///Move the part outline to the List's end it has to be the last to be cut in plasma/laser cutting (if plasmaMode is enabled)

		 //findOutline();

		 //if (partLoops.size()=>1){
		 	
	    	//}
	 ///@fixme outlineLead will be created within generateLead after cheking for is outline
	 /// createOutlineLead();
	    }	
	///Now that all the graphical processing is done we "allow" loops to be drawn
	
	 generateLeads();
	

	 ///@todo: add option : optimize auto
	 qDebug()<<"Starting optimization";
	 ///We try to optimize only if there is more than 1 loop  	
	 if (partLoops.size()>1){
		 optimizeRoute();
		}
	
	  ///now we can start drawing the loops
	 
	   foreach (Loop* cLoop, partLoops){
		 cLoop->setReady(true);
		 qDebug()<<cLoop->loopNumber;
		}
	}

	
 void  Part::filterCircles(){
	 /**As we have to return a QList of Qlist we create a temporary one (for now the temp dimension is one
	 But when introducing circles lead-in lead-out a circle loop will contain 2 points the center and the lead in**/
	 QPFWPVector temp;
	
	 QPointFWithParent currentPoint;
	 ///creating a new circleLoop	 
	 Loop *tempLoop=new Loop(this);

	///@note to avoid crash we append an element to temp and keep changing it 
	 temp.append(cirPtsList[0]);
	  //qDebug()<<"Adding "<<cirPtsList.size()<<" circles";
	  
	  ///create a new lop for each encountered circle and set it's number and shape
	 for (int pos=0; pos <cirPtsList.size();pos++){
		/**We take a point mark its parent loop umber (for later tsp processing) then 
		 appeend it to the endPointslist and add the closedPath counter**/		 
		 currentPoint=cirPtsList.at(pos);
		 /// @fixme We need to save the parent loop in the original point for later use in optimize devise a more elegant way to do that
		 currentPoint.setLoopNbr(nbrClosedPath);
		 
		 //temp[0]=cirPtsList.at(pos);
		 temp[0]=currentPoint;
		 
		  tempLoop->addPath(cirPathsList.at(pos));
		  tempLoop->setStart(currentPoint);
		  tempLoop->setEnd(currentPoint);
		  tempLoop->setTypeCircle(true);
		  tempLoop->setEntities(temp);
		  ///@note: have to call setNumber AFTER setEntitites!!
		  tempLoop->setNumber(nbrClosedPath);
		  partLoops<<tempLoop;
		
		  nbrClosedPath++;
		  tempLoop=new Loop(this);
		  
		}
	 ///at this step we only have circles 
	 nbrCircles=nbrClosedPath;
	 ///@todo We don't need the path list anymore, free it
	 cirPathsList.clear();
	 cirPtsList.clear();
	 
	}



	
	void Part::generateLoops(QPFWPVector ptsVector){
	
	 Loop *tempLoop=new Loop(this);
	 QPointFWithParent currentPoint;
	 
	 QPFWPVector pointsVectorNew;
	 
	 QPainterPath subLoop;
	 bool alreadyChecked=false;
	 int oldPos=0,found=1,pos=0;
	 
	 qDebug() << "Dealing with "<<pathsList.size()<<" Entities represented by "<< ptsVector.size()<<"points";
	 while (ptsVector.size()>=2) {
		 currentPoint=ptsVector.at(pos);
		  //qDebug()<<"Working with"<<currentPoint<< " at "<<pos;	
		 if (ptsVector.count(currentPoint)==1) {
		     oldPos=pos;
			 //qDebug()<<"No corresponding point.AlreadyChecked other coord:"<<alreadyChecked;
			 if ( alreadyChecked==false ) {
				 if (pos%2==0) pos++; else pos--; 
				 alreadyChecked=true;
				}
			 currentPoint=ptsVector.at(pos);
			 if (ptsVector.count(currentPoint)==1) { 		
				 //qDebug()<<"Swaped but still no corresponding point.";
				 if (oldPos==pos) {
					 if (pos%2==0) pos++; else pos--; 
				 }
				 currentPoint=ptsVector.at(pos);
				 shrink (ptsVector,pointsVectorNew,pos,oldPos);
				 /** Will be useful later for TSP optimization*/
				 pointsVectorNew.first().setLoopNbr(nbrClosedPath);
				 pointsVectorNew.last().setLoopNbr(nbrClosedPath);
				 
				 /// if this is closed loop we add just one point elsewhere we add the start/end
				 subLoop.addPath(pathsList.at(pos/2));	
				 
				 tempLoop->addPath(pathsList.at(pos/2));
				 ///have now to close the path @todo redraw th path correctly
				 tempLoop->loopShape.closeSubpath();
				 ///@note:We have to remove the path for the algo to properly work (not just for memory opt)
				 pathsList.remove(pos/2);
				 tempLoop->setStart(pointsVectorNew.first());
				 tempLoop->setEnd(pointsVectorNew.last());
				 ///@todo: have to add a functionthat count and display differently open loops
				 tempLoop->setEntities(pointsVectorNew);
				 ///@note: have to call setNumber after setEntitites!!
				 tempLoop->setNumber(nbrClosedPath);
				/** Now the Loop contains all the necessary parameters to define it:
				 -start point.
				 -end point.
				 -Everypoint between the start and end point.
				 NOte:
				 - lead-in / lead-out points will be added further if needed.
				 */
				 
				 partLoops<<tempLoop;	
				 
				 /// increment only if it's composed of at least one intersection (not neceraly!!!)
				// if (found==1)
				 nbrClosedPath ++; 				
				 pointsVectorNew.clear();
				 ///@todo:differ painting after optimization...
				 /// tempLoop->nowReady();
				 tempLoop=new Loop(this);
				 
				 subLoop=QPainterPath();
				 found=1;
				 alreadyChecked=false;
				 pos=newPos(ptsVector);
				 continue;
				}
			 /// After swapping Points Have found that this point do have a correponding point in another entity
		     else { 
				 found++;
				 if (found==2) {
					 /// to keep the lines order we have to put currentPoint after oldPoint
					 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 
					 shrink (ptsVector,pointsVectorNew,pos,oldPos);
					 //subLoop.addPath(pathsList.takeAt(pos/2));
					 subLoop.addPath(pathsList.at(pos/2));
					 tempLoop->addPath(pathsList.at(pos/2));
					 pathsList.remove(pos/2);					 
					 found=1;
					}				 	
				 /// get the corresponding point location and store the caller one to avoid infinte loop
				 if (ptsVector.indexOf(currentPoint)==pos ) {
					 pos=ptsVector.lastIndexOf(currentPoint);
					}
				 else {
					 pos=ptsVector.indexOf(currentPoint);
					}
				 /// change to the other the point definfig the line
				 if (pos%2==0) pos++; else pos--; 
				 continue;
				}
			}
		 /// Found a corresponding point in another entity
		 else {
			 found++;
			 /// It's time to remove the points and their corresponding entities
			 if (found==2) {
				 if (pos%2==0) {oldPos=pos++;} else {oldPos=pos--;} 
				 shrink (ptsVector,pointsVectorNew,pos,oldPos);
				 //qDebug () << "taking path at"<<pos<<"path size"<<pathsList.size()<<"ptsList size"<<ptsList.size();
				 //subLoop.addPath(pathsList.takeAt(pos/2));
				 subLoop.addPath(pathsList.at(pos/2));
				 tempLoop->addPath(pathsList.at(pos/2));
				 pathsList.remove(pos/2);
				 found=1;/// we still have one point to work with 
				}
			 if (ptsVector.indexOf(currentPoint)==pos ) {	
				  pos=ptsVector.lastIndexOf(currentPoint);
				}
			 else {
				 pos=ptsVector.indexOf(currentPoint);
				}
			 if (pos%2==0) pos++; else pos--;
			 alreadyChecked=true;
			 continue;
			}
		}
	}

/**  FIXME:something wrong with find outline with parts from folder  
	"/media/donnees/SOLID/PR6-5.1-D12/FABRICATION/DECOUPE/AISI 304/12" */
	
	void Part::findOutline(){
	 ///@note: we should use controlPointRect which is faster to calculate than boundRect but we already have the boundRect 
	 QRectF outerBound=partLoops[0]->loopShape.boundingRect ();
	 QRectF outer=partLoops[0]->loopShape.boundingRect ();	 
	 
	 for (int pos=0;pos<partLoops.size();pos++){
		 outer=partLoops[pos]->loopShape.boundingRect ();
		 if (outerBound.height()* outerBound.width()< outer.height()*outer.width()) {
			 outerBound=outer;
			 outlinePos=pos;
			}
		}
		///Remove the outline from the TSp optimization points list
		outlinePoint=partLoops.at(outlinePos)->startPoint; 
		
		///Move the outline shape to the last position
		outLinePath=partLoops.at(outlinePos)->loopShape;
		partLoops<<partLoops.at(outlinePos);
		partLoops.remove(outlinePos);
		partLoops.last()->setIsOutline(true);			
		qDebug()<<"The outline is the " <<outlinePos+1 <<"th element:"<<outlinePoint;
  }
  
  // FIXME: Openloops have to be taken into consdideration! 
	/// When encountering an endPointwhose parentLoop hadalready been assigned a leadwe simplyskip it.(It becomes a leadout).
	 
 void Part::generateLeads(){
	 QPointFWithParent leadPoint;
	 int myleadDist=leadDist;
	 QPointFWithParent touchPoint;	
	 QPointFWithParent temp;
	 bool sucess=false;
	 Loop *currentLoop;
	 Lead *templead;	 
	 
	 for (int i=0; i<partLoops.size(); i++) {
		 
		 currentLoop=partLoops.at(i);
		 temp=currentLoop->startPoint;
		 ///@Fixme: first try to find the outline!!
		    if (currentLoop->isCircle) {
			     myleadDist=leadDist;				 
			     if (temp.parentRadius< leadDist) {
				     myleadDist=temp.parentRadius/2;
				     ///Have to mit an alert and check that supplied minimal radius constarint is met
				     qDebug() << "the raius is too small!!";
					}
			     ///@fixme: replace the startsPoint by leadPoint and see if it influences Optimization				 
				 /// FOR circle touchPoint become the loop startPoint
				 touchPoint=temp;
				 touchPoint.setX(temp.x()+temp.parentRadius*cos(leadAngle));
				 touchPoint.setY(temp.y()+temp.parentRadius*sin(leadAngle));
				 /// The lead point is user specified
			     leadPoint.setX(temp.x()+myleadDist*cos(leadAngle));
			     leadPoint.setY(temp.y()+myleadDist*sin(leadAngle));
			     leadPoint.setParentType(QPointFWithParent::LeadCertain);
				 
			     currentLoop->setLeadIn(leadPoint);
				 currentLoop->setTouchPoint(touchPoint);				 
				 templead=new Lead(currentLoop);
			     qDebug()<<"Placing a circle lead point N°"<<i;
			    }
			    /**maybe an arc or a ruglar line: this is how it works . first we draw a line from rectBound center to 
				start point. If the line intersect with part shape we reduce the line length (cheking that it's endpoint
				is contained in the rectbound.
				*/
		     else{
			     for (int j=1; j<=10; j++){
				     /// try to find a valid lead-in point within constrains
					 leadPoint.setX(temp.x()+leadDist*cos(36*j*M_PI/180));
					 leadPoint.setY(temp.y()+leadDist*sin(36*j*M_PI/180));
					 
					 if (currentLoop->loopShape.contains(leadPoint) ){ /// Put intersect here&& !outLinePath.contains(leadPoint)){
					     qDebug()<<leadPoint<<j<<"try is a valid lead-in point";
					     
					     if(temp.parentType==QPointFWithParent::Arc){ qDebug()<< "The lead is on an arc";}					     
						 leadPoint.setParentType(QPointFWithParent::LeadCertain);
					     sucess=true;
					     break;
						}
					 else {
					     qDebug()<<j<<"try:"<<leadPoint<<"not a valid point";
					    }
					}
			     ///If we havn't found a valid lead we place a random one with a revelant COLOR
			     if (!sucess) {
				     qDebug()<<"placing an uncertain lead point"<<i;
				     ///HAVe to use the parentloop reference to avoid crach when having open loops
				     ///QPointF center= partLoopsListFinal.at(temp.parentLoop).controlPointRect().center();
					 QPointF center= currentLoop->qtRect.center();
				     leadPoint.setX(center.x());
				     leadPoint.setY(center.y());
				     leadPoint.setParentType(QPointFWithParent::LeadUncertain);
				    }	
			     currentLoop->setLeadIn(leadPoint);
				 ///@todo put this from loop filtering by default
				 currentLoop->setTouchPoint(temp);
				 templead=new Lead(currentLoop);
			    }
		}	
	}

	void Part::optimizeRoute(){	
	 QPFWPVector bestRoute;	
	 
	 /// replaces the points list with the previously created one (inspired from genetic algo)
	 partLoopsOpt.clear();
	 QList<int> procededLoops;
	 ///endPointslist=test->createNew(endPointslist);
	 /// Have to use leads later after the user made changes to leads. For now use Strat/end points
	 for (int i=0;i<partLoops.size();i++){
		  ///If we encounter the outline we skip it although we already know it's the last part
		  if (partLoops[i]->isOutline) {continue;}
		  bestRoute<<partLoops[i]->startPoint;
		 if (partLoops[i]->startPoint!=partLoops[i]->endPoint){
			  bestRoute<<partLoops[i]->endPoint;
			}		 
		}	 
	 
	 if (bestRoute.size()>1) {
		 Popu *popu=new Popu();
		 /// Fixme work with refenrece to bestRoute 
		 bestRoute=popu->init(bestRoute);
	 }
	 	int i=0; 
		 procededLoops.clear();
		 ///TIEME to reorder the Paths the same order as the returned list fromo ptimization
		 while (i<bestRoute.size()) {
				///FIXME: merge before Circles and Points into gcode
			 if (!procededLoops.contains(bestRoute.at(i).parentLoop)) {
				 qDebug()<<bestRoute.at(i)<<"was  "<<bestRoute.at(i).parentLoop<<"th position became"<<i;
				 partLoops.at(bestRoute.at(i).parentLoop)->setNumber(i);
				 partLoopsOpt.append(partLoops.at(bestRoute.at(i).parentLoop));		 
				 procededLoops.append(bestRoute.at(i).parentLoop);
				 
				}
				else {
				qDebug()<<"loop"<<i<<" already proceded";
				}
			 i++;
			}
		 ///Now we add the part's outline
		 qDebug()<<"Procedded loops"<<procededLoops;
		 if (plasmaMode){
			 /// HOW could this be possible as we havn't included it ?
			 if (!procededLoops.contains(outlinePoint.parentLoop)) {				 
				 qDebug()<<"Finally the outline "<<outlinePos;
				 partLoopsOpt.append(partLoops.last());
				 ///HAve to stay the same
				 partLoopsOpt.last()->setNumber(partLoopsOpt.size()-1);
				 //partLoops.last()->setNumber(partLoopsOpt.size()-1);
				 bestRoute.append(outlinePoint);
				}
			}
		 else {
			 qDebug()<<"I'm  impossible !!";
			 //we must reappend the outlinepoint anyway!
			 ///useful for animation for now
			 bestRoute.append(outlinePoint);
			}
	 partLoops=partLoopsOpt;
	 	
	}
	
	
	Part::~Part(){
}

	Part* Part::copy(){
	 Part* newPart=new Part(*this);
     	return newPart;
	}


void Part::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *) {
	 ///part in preview scen are drawn loop by loop so we d'ont do any painting for them
	 if (preview) return;
	 ///@note isSelected is provided by Qt
	 if (isSelected()) {
		 ///@todo add an option to the config Dialogdesig
		 ///@todo add pen width to the rectBound
		 painter->setPen(QPen(Qt::blue,1,Qt::DashLine));
		 painter->drawRect(qtRect);		 
		}
	 painter->setPen( settings.value("Colors/pen").value<QColor>());
	 painter->setBrush( settings.value("Colors/brush").value<QColor>());
	 painter->drawPath(partShape); 
	 ///draw the part bounding rect 
	 
 }
 

QVariant Part::itemChange(GraphicsItemChange change, const QVariant &value) {
	 //qDebug()<<change;
     switch (change) {
     case ItemPositionHasChanged:
		 ///@todo:We only need to update the matrix when we release the mouse buton check for this before!
		 //transform=sceneTransform();
		 // qDebug()<<transform.type();
		 //applyTransform();
		 update();
         break;
	 case ItemSelectedChange	:
		 qDebug()<<"Part selected";
		  break;
	 case ItemTransformHasChanged:
		 ///transMatrix=transform().toAffine();
		 ///transMatrix=transform().rotate(90).toAffine();//.setMatrix(
		 transform=sceneTransform();
		 ///transform.rotate(90);
		 ///transMatrix.setMatrix(transform().m11(),transform().m12(),transform().m21(),transform().m22(),0,0);
		 qDebug()<<transform<<transform.type();
		 //applyTransform();
		 qDebug()<<"Transformation";
		 ///We chnage our matrix
		 break;
     default:
	       
         break;
     };

     return QGraphicsItem::itemChange(change, value);
 }
	
	
 void Part::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {    
	 /// When mouse button is released we get the transform matrix
	 qDebug()<<pos();
	 transform=sceneTransform();
	 qDebug()<<"transfor matrix updated"<<transform;
	 ///@todo: see if update() isn't called automatically??
     QGraphicsItem::mouseReleaseEvent(event);
 }
 
	 void Part::moveMeBy(qreal dx, qreal dy){
		/// leave the actual move to Qt
		 qDebug()<<dx<<dy;
		 moveBy(dx-pos().x(),dy-pos().y());
		 //setPartPos();
 }
 
 void Part::mousePressEvent(QGraphicsSceneMouseEvent *event) {
 /// each time update is called the paint function is called
     //event->ignore();
     //qDebug()<<"mouse pressed piece";
     	 ///@todo: see if update() isn't called automatically??
	 update();//setSelected (true);
	 QGraphicsItem::mousePressEvent(event);
	 
 }
 
 void Part::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	 update(); // qDebug()<<"mouse moving";
	 	 ///@todo: see if update() isn't called automatically??
	 QGraphicsItem::mouseMoveEvent(event);	 
	}	
	
	///@todo show possible start poits (the user may want to change the lead point for route/space optimization)	
	Loop::Loop(QGraphicsItem * parent):QGraphicsItem(parent){
	 loopShape=QPainterPath();
	 originalShape=QPainterPath();
	 //addPath(loopText);
	 selectedPen=QPen(Qt::blue);
	 unSelectedPen=QPen(settings.value("Colors/pen").value<QColor>());
	 outlinePen=QPen(Qt::red,Qt::DashLine);
	 isCircle=false;
	 loopNumber=0;
	 setFlag(ItemIsSelectable);	 
	 //setCacheMode(DeviceCoordinateCache);	 
	 isOutline=false;
	 entities.clear();
	 ready=false;
	 ///@todo proper intialisationof all valuesstartPoint=
	}
	
 void Loop::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *){
	 ///start drawing only when the painterPath is defined and all parametres set
	  if (!ready) {return;}
	
	 if (isSelected()) {
		 myPen=selectedPen;
		}
	 else {
		 myPen=unSelectedPen;
		}
	  if (isOutline) { myPen.setStyle(Qt::DashLine);}
	  painter->setPen(myPen);
	  painter->setBrush(settings.value("Colors/brush").value<QColor>());
	  painter->drawPath(loopShape);	  
	  painter->setFont(QFont("Times", 6));	 
	}
	
 void Loop::addPath(QPainterPath pathToAdd){ 
	 loopShape.addPath(pathToAdd);
	 prepareGeometryChange();
	 qtRect=loopShape.boundingRect();
	}
	
 void Loop::setEntities(QPFWPVector ts){
	 entities=ts;
	 ///we save the original shape to avoid alteration when adding text path
	 originalShape=loopShape;
	}
	
	
	///To avoid adding again and again textpath
	void Loop::addTextPath(QPainterPath pathToAdd){
	 ///restore thge original shape
	 loopShape=originalShape;
	  prepareGeometryChange();///don't need to updtae rectBound
	 loopShape.addPath(pathToAdd);
	}
	
	///@note;as we're using windFilling method the text is granted to be visible over the loop's shape
	void Loop::setNumber(int nbr){
	 loopNumber=nbr;	 
	 ///shows the loop number @todo:add optioon from gui config
	 QPainterPath loopText;
	 ///first we erease the previous nuber if any @todo: check for it 
	  ///@todo have to devise a way to updta loo number after deleting the old one
	 //loopText=QPainterPath();
	 if (isOutline){
	     loopText.addText(startPoint,QFont("Times", 6),(QString("%1").arg(loopNumber)));
	  }
	  else{
		  ///to ensure that selection highlight the loop number we put the number in rect Center
		 loopText.addText(qtRect.center(),QFont("Times", 6),(QString("%1").arg(loopNumber)));
	  }
	  ///now we add the loopNumber to the shape to be able to sleect the loop from its number 
	  addTextPath(loopText);
	 }
	
QVariant Loop::itemChange(GraphicsItemChange change, const QVariant &value){
     switch (change) {
	 case ItemSelectedHasChanged:
		 //if (value.toInt()==1)
		 
		 qDebug()<<"selecting loop n°"<<loopNumber;
		 update();
		 
		  break;
     default:
         break;
		}
	 return QGraphicsItem::itemChange(change, value);
	}
	
	/// Setting loop number is achived through swapping values
	
	
	void Loop::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){
	 bool ok;
	 /// @fixme use QObject::tr
	 int i=QInputDialog::getInteger(0,QString( "set loop Number"),QString("Loop Number :"), loopNumber, 0, 100, 1, &ok);
	 if (ok) setNumber(i);
	}



	

	
  QPointFWithParent Part::translateEntity(QPointFWithParent oldPoint, QPointF offset){
	 QPointFWithParent temp(oldPoint);
	 temp+=offset;
	 return temp;
	}
	
	 void Part::shrink(QPFWPVector &pointsList,QPFWPVector &pointsListNew,int pos,int oldPos){
	/// push the Two current points into the Qlist of the current path
	/// The translation has to be relative not absolute therfor it had to be done
	///when the part is inserted in the sheetMetal not before
				 ///pointsListNew <<translateEntity(pointsList.at(pos),offsets.at(currentPart));
				 ///pointsListNew <<translateEntity(pointsList.at(oldPos),offsets.at(currentPart));
				 pointsListNew<<pointsList.at(pos);
				 pointsListNew<<pointsList.at(oldPos);
				 if (oldPos<pos)  {
					 pointsList.remove(oldPos);
				     pointsList.remove(oldPos);
					}
			     else {
					 pointsList.remove(pos);
				     pointsList.remove(pos);
					}		
	return;
    }
	
	void Part::drawArc(QPointFWithParent point,QPainterPath &pathToModify) {	 
	 QRectF rect(point.centerX-point.parentRadius,point.centerY-point.parentRadius,2*point.parentRadius,2*point.parentRadius);
	 pathToModify.arcTo(rect,-( point.angle1),-fabs( point.angle1- point.angle2));	 
	 //pathToModify.arcMoveTo(rect,-fabs( point.angle1- point.angle2));
	 
	}
	
	
	int Part::newPos(QPFWPVector pointsList){
 	 int k=0,occurence=0;
	 while ((k<pointsList.size()) &&(occurence!=1)){
	     occurence=pointsList.count(pointsList.at(k));
	 	 k++;		 
		}
	 return k-1;
	}

	
	
 
	
/** As the same scheme is possible for all leads we'll use it:
We get the endPoints list, we create a lead for the ezndpoint and then we append the calculated point to another
Qlist leadsPoints. once leadsPoints is filled we use it in G-code generation as follow.
We read a lead-in point from the list Move at feed rate to the EndPoint at the same position.If the item to cut is a 
circle, we simply move to cutting the circle.
  */

void Part::createOutlineLead(){
	 QPointFWithParent leadPoint;
	 /// A void to start with ZERo 
	 /// If the outlineLead Havn't alreadybeen created
	 //even if an outline lead has been created we have to overwrite it as it will 100% be an uncertain one
	 /// if (!procededLeads.contains(outlinePos)){
	 for (int i=1; i<=5; i++){
		 leadPoint=QPointF(outlinePoint.x()+leadDist*cos(90*i),outlinePoint.y()+leadDist*sin(90*i));
		 
		 /// could use intersects with QPainterPaths making the outershape
		 
		 if (!outLinePath.contains(leadPoint) ){ /// Put intersect here&& !outLinePath.contains(leadPoint)){
			 qDebug()<<leadPoint<<"is a valid Outline lead-in point";
			 leadPoint.setParentType(QPointFWithParent::LeadCertain);
			 leadPoint.setLoopNbr(outlinePos);
			 leadPoint.setLeadTouch(outlinePoint);
			 //leadsPoints.append(leadPoint);
			 //update();
			 return;
			}
		 //else {
			 //qDebug()<<"rejecting"<<leadPoint.x()<<leadPoint.y();
			//}
		} 	 
	 leadPoint.setParentType(QPointFWithParent::LeadUncertain);
	 leadPoint.setLoopNbr(outlinePos);
	 leadPoint.setLeadTouch(outlinePoint);
	 //leadsPoints.append(leadPoint);
	 
	 qDebug()<<"Warning:No possible lead point found!";
	 /// }
	}
	
	

 LoopThread::LoopThread(Part *piece){
	 //qDebug()<<"parsing"<<piece->ptsList.size()<<"elements";
	 currentPiece=piece;
	}

void LoopThread::run(){
	 //currentPiece->optimize();
	 ///isn't there any more elegant way to do this
	// filterLoop<<currentPiece->filterLoops();
	 
	}

///startJob()


/** @note: SEE BUG.SDXF TWO same points  Point 82.50771287080000604419,-133.07855302429999255764)
and Point 82.50771287070070059144,-133.07855302426852972530) became different at the 9th digit=> have to take into account 
only to the 9th digit  (inform the user about that!)

*/

/** @note: Someparts with redendant entities cause the filter loops algo to crash! see 2-0.dxf and 12-0.dxf
Have to wrap that issue*/



/// for graphical represezntation of the laser trace on the part
int leadRadius=3;
 QRectF laserRect(-leadRadius/2,-leadRadius/2,leadRadius,leadRadius);
 
	
	Lead::Lead(Loop *loop):QGraphicsItem(loop){
	 myBoundingRect=laserRect;
	 myLoop=loop;
	 myPos=&myLoop->leadIn;
	 setPos(myLoop->leadIn);
	 data(3)=myLoop->loopNumber;
	 leadTouch=myLoop->touchPoint;
	 if (myPos->parentType==QPointFWithParent::LeadUncertain){
		 leadType=LeadUncertain;
		}
	 else {
		 leadType=LeadCertain;
		}		
	 setZValue(2);/// to stayt on top
	 setCacheMode(DeviceCoordinateCache);
	 setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	 Lead *touchLead=new Lead(myLoop,0);
	 myEdge=new Edge(this,touchLead);
	}	

	Lead::Lead(Loop *loop,int j):QGraphicsItem(loop){
	 myBoundingRect=laserRect;
	 myLoop=loop;
	 //myPos=myLoop->touchPoint;
	 setPos(myLoop->touchPoint);
	 data(3)=myLoop->loopNumber;
	 leadTouch=myLoop->touchPoint;
	 leadType=LeadTouch;
	 setZValue(2);/// to stayt on top
	 //setCacheMode(DeviceCoordinateCache);
	 //setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	}
	
	
 void Lead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	 //painter->setPen( settings.value("Colors/pen").value<QColor>());
     //painter->setBrush( settings.value("Colors/brush").value<QColor>());
	// painter->setRenderHint(QPainter::Antialiasing);
	  if (leadType==LeadCertain) {
		 painter->setBrush(Qt::green);
		}
		 else if (leadType==LeadTouch) {
		 painter->setBrush(Qt::blue);
		}
		else {
		painter->setBrush(Qt::red);
		}
     painter->setPen(QPen(Qt::black));
     painter->drawEllipse(laserRect);	 
	 //qDebug()<<myPos<<myPos.leadTouch;
	 //painter->drawLine(myPos,myPos.leadTouch);
	 
    }

	
	QVariant Lead::itemChange(GraphicsItemChange change, const QVariant &value){
		
		 switch (change) {
     case ItemPositionHasChanged:
		 ///NOTE:We only need to update the matrix when we release the mouse buton
		 update();
         break;
	 case ItemSelectedChange	:
		 qDebug()<<"Lead selected";
		  break;
	 default:
	       
         break;
     };
		
	
		return QGraphicsItem::itemChange(change, value);
	}
     void Lead::mousePressEvent(QGraphicsSceneMouseEvent *event){
	  update();  //qDebug()<<"mouse pressed hole";
     QGraphicsItem::mousePressEvent(event);
	 }
	 
     void Lead::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	 
	 qDebug()<<"replacing "<<myPos->x()<<myPos->y();
	 myPos->setX(pos().x());
	 myPos->setY(pos().y());
	 qDebug()<<"from Parent lead with"<<myLoop->leadIn;
	 update();
     QGraphicsItem::mouseReleaseEvent(event);	 
	 //myLoop->leadIn=myPos;
	 /// note: shouldn't call myPos=scenePos(); to avoid loosing loopparent ,...
	 ///qDebug()<<"replacing "<<myPiece->leadsPoints.at(parentLoop)<<"with"<<myPos;
	 ///myPiece->leadsPoints.replace(parentLoop,myPos);

	 }
	 
	 
	 void Lead::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	  update();
	  myEdge->adjust();
     QGraphicsItem::mouseMoveEvent(event);
	 }
	  
	/// void Lead::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
	 ///update();  qDebug()<<"mouse 2 click";
	 ///QGraphicsItem::mouseMoveEvent(event);	
	 ///}
	Lead::~Lead(){
}
