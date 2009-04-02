#include "gatsp.h"
#include "part.h"

/** NOTE: SEE BUG.SDXF TWO same points  Point 82.50771287080000604419,-133.07855302429999255764)
and Point 82.50771287070070059144,-133.07855302426852972530) became different at the 9th digit=> have to take into account 
only to the 9th digit  (inform the user about that!)

*/

/** NOTE : Someparts with redendant entities cause the filter loops algo to crash! see 2-0.dxf and 12-0.dxf
Have to wrap that issue*/

/// The tolerance defines the disstance within it a loop is estimated to be closed
int tolerance=0.01;
int leadDist=10;/// Have to be unit dependant 
/// lead angle for circle loops
int leadAngle=180;
bool plasmaMode=true;

  Popu *popu;
bool fillInBrush=false;
/** have to create an object lead point , a QGraphicsEllipseItem that is magneted to the endPoint parent
and which position will be used by the G code genrator**/
/**   FIXME  handle the case the part outline is a circle!! */
/** For the outline: We first check if the OutlinePoint intersects with the rectBounds, such point can be trivialy
chosen to be a good candidtae for lean in.In that case we draw a line, its lenght being specified by the user,and we
try with different angular positions till the lead-in point is no longer contained in the RectBound*/



/** As the same scheme is possible for all leads we'll use it:
We get the endPoints list, we create a lead for the ezndpoint and then we append the calculated point to another
Qlist leadsPoints. once leadsPoints is filled we use it in G-code generation as follow.
We read a lead-in point from the list Move at feed rate to the EndPoint at the same position.If the item to cut is a 
circle, we simply move to cutting the circle.
  */
void Part::generateLeads() {
	 
 	 qDebug()<<"Creating Circular leads";
	 /// the only thing to deal with  is the outline
	 if (partLoopsListFinal.size()>1){
		 createLead();
	    }
	 qDebug()<<"Creating Outline lead";
	 createOutlineLead();
		 // qDebug()<<bestRoute.size()<<leadsPoints.size();
	 /// We now reorder the leade to get synchro with the Optimized path 
	 QPFWPList temp;
	 qDebug()<<"old leadPoints:"<<leadsPoints;
	 qDebug()<<"end points"<<bestRoute;
	 ///Fixme:here and for reorganisaingshapes when dealing with openLoops we end up with duplicate paths!!
	 /// Would crash if we don't putthis casehandle
	 if (leadsPoints.size()>1){
		 for (int i=0;i<leadsPoints.size();i++){				
			 if (bestRoute.at(i).parentLoop<leadsPoints.size()){
				 temp.append(leadsPoints.at(bestRoute.at(i).parentLoop));
				}
			 else {
				 temp.append(bestRoute.at(i));
			    }
			}
		 leadsPoints=temp;
		 qDebug()<<"new Leads"<<leadsPoints;
		}
	}
  
void Part::createOutlineLead(){
	 QPointFWithParent leadPoint;
	 /// A void to start with ZERo 
	 /// If the outlineLead Havn't alreadybeen created
	 if (!procededLeads.contains(outlinePos)){
	 for (int i=1; i<=5; i++){
		 leadPoint=QPointF(outlinePoint.x()+leadDist*cos(90*i),outlinePoint.y()+leadDist*sin(90*i));
		 
		 /// could use intersects with QPainterPaths making the outershape
		 
		 if (!outLinePath.contains(leadPoint) ){ /// Put intersect here&& !outLinePath.contains(leadPoint)){
			 qDebug()<<leadPoint<<"is a valid Outline lead-in point";
			 leadPoint.setParentType(QPointFWithParent::LeadCertain);
			 leadPoint.setLoopNbr(outlinePos);
			 leadPoint.setLeadTouch(outlinePoint);
			 leadsPoints.append(leadPoint);
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
	 leadsPoints.append(leadPoint);
	 
	 qDebug()<<"Warning:No possible lead point found!";
	 }
	}
	
	/// All leads have to be created justa after circle loops filtering, have to find a way to update lead if the 
	///outer one is a cirlar
	
	
	
	
	/// FIXME: Openloops have to be taken into consdideration! 
	/// When encountering an endPointwhose parentLoop hadalready been assigned a leadwe simplyskip it.(It becomes a leadout).
	 
 void Part::createLead(){
	 QPointFWithParent leadPoint;
	 int myleadDist=leadDist;
	 QPointF touchPoint;	
	 QPointFWithParent temp;
	 
	 bool sucess=false;
	 qDebug()<<"End points"<<endPointslist.size();
	 qDebug()<<"part loops"<<partLoopsListFinal.size();
	 
	 for (int i=0; i<endPointslist.size(); i++) {
		 temp=endPointslist.at(i);
		 if (procededLeads.contains(temp.parentLoop)) {
			 qDebug()<< "ParentLoop already proceded";			 
			 //break;
			}
	 /// Haveto proced this Leadpoint
	 else{		  
		 if (temp.parentType==QPointFWithParent::Circle) {
			 myleadDist=leadDist;
			
			 if (temp.parentRadius< leadDist) {
				 myleadDist=temp.parentRadius/2;
				 ///Have to mit an alert and check that supplied minimal radius constarint is met
				 ///qDebug() << "the raius is too small!!";
				}
			 /// we simply draw a line at the angle specified by the user inside the circle
			 touchPoint=QPointF(temp.x()+temp.parentRadius*cos(leadAngle),temp.y()+temp.parentRadius*sin(leadAngle));
			 leadPoint.setX(temp.x()+myleadDist*cos(leadAngle));
			 leadPoint.setY(temp.y()+myleadDist*sin(leadAngle));
			 leadPoint.setLeadTouch(touchPoint);
			 leadPoint.setParentType(QPointFWithParent::LeadCertain);
			 leadPoint.setLoopNbr(temp.parentLoop);
			 qDebug()<<"Placing a circle lead "<<i;
			 /**Items can contain other items, and also be contained by other items.
			 All items can have a parent item and a list of children. Unless the item has no parent, 
			 its position is in parent coordinates (i.e., the parent's local coordinates). 
			 Parent items propagate both their position and their transformation to all children. */
	
			 /// we finally store the created leadPoint and it's parent touchpoint
			 leadsPoints.append(leadPoint);
			}
			///maybe an arc or a ruglar line
		 else{
			 for (int j=1; j<=5; j++){
				 leadPoint=QPointF(temp.x()+leadDist*cos(90*j),temp.y()+leadDist*sin(90*j));
				 if (partLoopsListFinal.at(temp.parentLoop).contains(leadPoint) ){ /// Put intersect here&& !outLinePath.contains(leadPoint)){
					 qDebug()<<leadPoint<<j<<"try is a valid lead-in point";
					 leadPoint.setParentType(QPointFWithParent::LeadCertain);
					
					 leadPoint.setLeadTouch(temp);
					 leadPoint.setLoopNbr(temp.parentLoop);
					 leadsPoints.append(leadPoint);
					 sucess=true;
					 break;
					}
				 else {
					 //qDebug()<<j<<"try:"<<leadPoint<<"not a valid point";
					}
				}
			 ///If we havn't found a valid lead we place a random one with a revelant COLOR
			 if (!sucess) {
				 qDebug()<<"placing an uncertain lead point"<<i;
				 ///HAVe to use the parentloop reference to avoid crach when having open loops
				 QPointF center= partLoopsListFinal.at(temp.parentLoop).controlPointRect().center();
				 leadPoint.setX(center.x());
				 leadPoint.setY(center.y());
				 leadPoint.setLeadTouch(temp);
				 leadPoint.setParentType(QPointFWithParent::LeadUncertain);				 
				 leadPoint.setLoopNbr(temp.parentLoop);
				 leadsPoints.append(leadPoint);
				}
	
			}
		 procededLeads.append(temp.parentLoop);
		}/// endcase notprocedde	
		}	
	}

	



Part::Part(const QPainterPath path, QRectF rect,QPFWPList pointsList,QPPList partPathsList,QPFWPList circlePointsList,QPPList circlesPathsList):QGraphicsItem()//:partShape(path),qtRect(rect)
{
	 //setFlag(ItemIsMovable);
	 //setFlag(ItemIsSelectable);
	 partShape=path;
	 /// We add some space to guarantee good rendering of text/number loop
	 qtRect=rect;
	 qtRect.setHeight(qtRect.height()+4);qtRect.setWidth(qtRect.width()+4);
	 showText=true;
	 position=QPointF(0,0);
	 deltaPos=QPointF(0,0);
	 pathsList=partPathsList;
	 //partLoopsListFinal=partPathsList;
	 ptsList=pointsList;
	 cirPtsList=circlePointsList;
	 cirPathsList=circlesPathsList;
	 nbrClosedPath=0;outlinePos=0;nbrCircles=0;
	 transMatrix.setMatrix(1,0,0,1,0,0);
	 /// to be used only when no rotation is done
      setCacheMode(DeviceCoordinateCache);	 
	 //
	 //LoopThread test(this);
	 
/// some pieces may not contain circular holes

	 if(cirPtsList.size()!=0){
		 gCodeEntities<<filterCircles();
		 //emit progressionStep(0);
		 //emit descStep("Circles parsed");
	 }
	 if(pointsList.size()!=0){
	 
	 /// here we start the thread :
	 // emit progressionStep(1);
	// emit descStep("Fliltering closed loops parsed");
	 //test.start();
	 gCodeEntities<<filterLoops();
	 /// This is the default route automaticlayy generated without any optimization
	 gCodeEntitiesOpt=gCodeEntities;
	 }
	 /**
			 Beforee quiting one last thing remains: have to move the part outline to the List ends as theoutline 
			 is the last shape to be cut by Comparing bound rect.
			 TOdo:Is useful in Plasma cutting=> add if mode=plasma
			 */
	 //qDebug()<<endPointslist;
	 
	 
	 if (plasmaMode){
		 findOutline();		 
	 }
	  ///emit progressionStep(2);
	 //emit descStep("Finding outline");
	 bestRoute=endPointslist;
	 ///emit(progressionStep());
	qDebug()<<"We have to deal with "<<bestRoute.size()<<"end Points";
	 
	   //emit progressionStep(2);
	 // emit descStep("Processeding to optimization");
	 ///We try to optimize only if ther is more than 1 loop 
 
	 qDebug()<<"Starting optimization";
	 optimize();
	 //qDebug()<<"optimization done"<<bestRoute;
	 ///Lead generation has to happen after optimizatin to keep loops order
	 if (plasmaMode){
		 generateLeads();
		}
		
	 gCodeEntitiesTrans=gCodeEntitiesOpt; 	 
}

 LoopThread::LoopThread(Part *piece){
	 qDebug()<<"parsing"<<piece->ptsList.size()<<"elements";
	 currentPiece=piece;
	}

void LoopThread::run(){
	 //currentPiece->optimize();
	 ///isn't there any more elegant way to do this
	 filterLoop<<currentPiece->filterLoops();
	 
	}

///Constructor used to add multiplie part to a shhet metal foil;
 Part::Part(const Part &parentPart):QGraphicsItem(){
	 setFlag(ItemIsMovable);
	 setFlag(ItemIsSelectable);
	 setFlag(ItemIsFocusable);
	 partShape=parentPart.partShape;
	 qtRect=parentPart.qtRect;
	 position=QPointF(0,0);
	 deltaPos=QPointF(0,0);
	 showText=false;
	 pathsList=parentPart.pathsList;
	 ptsList=parentPart.ptsList;
	 cirPtsList=parentPart.cirPtsList;
	 cirPathsList=parentPart.cirPathsList;
	 nbrClosedPath=0;outlinePos=0;nbrCircles=0;
	 transMatrix.setMatrix(1,0,0,1,0,0);
	 bestRoute=parentPart.bestRoute;
	 gCodeEntitiesOpt=parentPart.gCodeEntitiesOpt;
	 gCodeEntities=parentPart.gCodeEntities;
	 leadsPoints=parentPart.leadsPoints;
	 ///to keep track of the part Nbr
	 setData(0,parentPart.data(0));
	 ///NOTE:NO need to take the Trans part 
	 gCodeEntitiesTrans=parentPart.gCodeEntitiesOpt;
	 endPointslist=parentPart.endPointslist;
	 }
///startJob()


	
	/**  FIXME:something wrong with find outline with parts from folder  
	"/media/donnees/SOLID/PR6-5.1-D12/FABRICATION/DECOUPE/AISI 304/12" */
	 void Part::findOutline(){
	 QRectF outerBound=partLoopsListFinal.at(0).controlPointRect ();//boundingRect();//controlPointRect ();
	 QRectF outer=partLoopsListFinal.at(0).controlPointRect ();//boundingRect();//controlPointRect ();//boundingRect();//
	 /// COULD START from outlinePos?
	 
	 
	 for (int pos=0;pos<partLoopsListFinal.size();pos++){
		 outer=partLoopsListFinal.at(pos).controlPointRect ();//boundingRect();//.controlPointRect ();
		 
		 if (outerBound.height()* outerBound.width()< outer.height()*outer.width()) {
			 outerBound=outer;
			 outlinePos=pos;
			}		 
		}
		///we remove the outline from the TSp optimization
	
	
		 outlinePoint=(endPointslist.takeAt(outlinePos));

		 qDebug()<<"The outline is the " <<outlinePos+1 <<"th element:"<<outlinePoint;		
		///to be removed for testing 
			
		

		QPainterPath unionPath;
	
		///outLinePath=partLoopsListFinal.takeAt(posOuter);
		outLinePath=partLoopsListFinal.at(outlinePos);
		
		int i=0;
	
	/// TODO: take a look at xored regions and try to do something similar.=> Intersected then substract from 
	/// path outline
	
		foreach (QPainterPath loop,partLoopsListFinal){
		//unionPath=unionPath.subtracted(loop);
		/** We create the leadIn out points for each loop **/
		 ///WE can compare painterPaths!! but to avoid consulming coputation time=> avoid complex paths comp
		 /// and more imoortant we have to take at relative positionning not absolute one!!
		 ///may use simplified subpaths !!
		 ///comparing as is is non sens because of distances offsets
		 //if (oldLoop==loop) qDebug()<< "same one";
		 //oldLoop=loop;
		 
		 //createLeads(loop,i);
		 //scene->addPath(loop);//,contourPen,contourBrush);
		 unionPath=unionPath.united(loop);
		 //i++;		 
		}
		 
		 ///partShape=outLinePath.subtracted(unionPath);
		 //outlinePoint=(endPointslist.takeAt(posOuter));
		 update();
  }
 
/// NOTE: some parts may contains repeated lines (drawn above others) How to deal with such entities ?
    QList <QPFWPList> Part::filterLoops(){
	
	 /// those two have to be returned to be used by the gcode generator
	 QList <QPFWPList > entitiesListFinal;	 

	 QPointFWithParent currentPoint;
	 QPFWPList pointsListNew;
	 QPainterPath subLoop;
	

	 bool alreadyChecked=false;
	 int oldPos=0,found=1,pos=0;	 
	 
	 qDebug() << "Dealing with "<<pathsList.size()<<" Entities represented by "<< ptsList.size()<<"points";
	 //qDebug() <<ptsList;
	 ///NOTE: something really stange with while it works with for it only show even one!!
	 // for (int j=0; j <ptsList.size();j++){
	 //qDebug("Point %.20f,%.20f)",ptsList[j].x(),ptsList[j].y());
	 //j++;
	 //}
	   //int j=0;
	  //while( j <ptsList.size()){
	 //qDebug("Point %.20f,%.20f)",ptsList.at(j).x(),ptsList.at(j).y());
	 //j++;
	 //}
 	 ///pos=newPos(ptsList);
	 
	 while (ptsList.size()>=2) {
		 currentPoint=ptsList.at(pos);
		  qDebug()<<"Working with"<<currentPoint<< " at "<<pos;		  
		  
		  /** 
		  * If the list contains the point only one time we can't link between it and other shapes
		  * unless we stwitch to the other point definfing the shape, if it hadn't already been checked
		  *(avoiding infinte loops )
		  */
		 if (ptsList.count(currentPoint)==1) {
		     oldPos=pos;
			 qDebug()<<"No corresponding point.AlreadyChecked other coord:"<<alreadyChecked;
			/// change to the other the point definfig the entity if it havn't already been checked
		     if ( alreadyChecked==false ) {
				 if (pos%2==0) pos++; else pos--; 
				 alreadyChecked=true;
				}
			 currentPoint=ptsList.at(pos);
			 /// still havn't found a corresponding point have to close the current path and start another
			 if (ptsList.count(currentPoint)==1) { 		
				 qDebug()<<"Swaped but still no corresponding point.";
				 /// to garantee that we have swaped values before entering here even when we have alreadyChecked
				 if (oldPos==pos) {
				 if (pos%2==0) pos++; else pos--; 
				 }
				 currentPoint=ptsList.at(pos);
				 //qDebug()<<"Removing points";
				 shrink (ptsList,pointsListNew,pos,oldPos);
				 
				 /** Will be useful later for TSP optimization*/
				 pointsListNew.first().setLoopNbr(nbrClosedPath);
				  pointsListNew.last().setLoopNbr(nbrClosedPath);
				  //qDebug()<<"Loops nbr assigned";
				 /// if this is closed loop we add just one point elsewhere we add the start/end
				 if (pointsListNew.first()== pointsListNew.last()){
					 endPointslist.append(pointsListNew.first());	
					 
					}
				///FIXME; it probably won't work as desired as it will be optimized but when adding the loop 
				///the 2 points belong to the same parent loop
				else{
					 endPointslist.append(pointsListNew.first());
					 endPointslist.append(pointsListNew.last());
					 qDebug()<<"Found an open Loop";
				 }
				/**TODO: PUT this as an option EITHER to use lines or numbers
					toolLoop.lineTo(pointsListNew.first());
				 **/
				 
				 //qDebug()<<pointsListNew;
				  ///Redraw the shape loop by loop
				  
				  ///check for size>2 before!!!
				  QPointFWithParent p;
				 //qDebug()<<subLoop.currentPosition();

				  int f=0;
				  if (fillInBrush) {
				  subLoop.moveTo(pointsListNew.at(f));
				  while(f< pointsListNew.size()){
				     p =pointsListNew.at(f);
					if (p.parentType==QPointFWithParent::Arc) {
					qDebug()<<subLoop.currentPosition();
					 if (subLoop.currentPosition()!=pointsListNew.at(f)) {
					
						subLoop.moveTo(pointsListNew.at(f));
						///qDebug()<<"Moved to "<<subLoop.currentPosition();
						}
						
						//subLoop.moveTo(pointsListNew.at(f));
						///qDebug()<<"arc start at "<<subLoop.currentPosition();
						drawArc(pointsListNew.at(f),subLoop);
						//subLoop.addText(subLoop.currentPosition(),QFont("Helvetica", 1),(QString("%1").arg(f)));
						///to void redrawing the same aerc twxice
						///qDebug()<<"Arc end at "<<subLoop.currentPosition();
						f=f+2;
					}
					else{
					/// to to the littele diff between arc i use qfuzzycompre 
					 //if ((fabs(subLoop.currentPosition().x()-pointsListNew.at(f).x())>tolerance) && (fabs(subLoop.currentPosition().y()-pointsListNew.at(f).y())>tolerance)) {
						//subLoop.moveTo(pointsListNew.at(f));
						//qDebug()<<"moving";
						//}
					 //;else	
					 	 ///qDebug()<<"line from"<<subLoop.currentPosition();
					 subLoop.lineTo(pointsListNew.at(f+1));
					 //subLoop.addText(subLoop.currentPosition(),QFont("Helvetica", 1),(QString("%1").arg(f)));
					
					///qDebug()<<"to"<<subLoop.currentPosition();
					 f=f+2;
					 //f++;
					 //qDebug()<<"line";
					}
				}
				 ///if (pointsListNew.at(0).parentType==QPointFWithParent::Arc) {
				///	 drawArc(pointsListNew.at(0),subLoop);
				 ///}	 
				 }
				 
				 
				 /// FIXME: restore the above code when it will be effecient!!
				 
				 ///FIXME/ to be removed when get drawing loops correctly
				 subLoop.addPath(pathsList.takeAt(pos/2));
				 if (found==1) nbrClosedPath ++; /// increment only if it's composed of at least one intersection
				 /// Add the current path to entities list
				 entitiesListFinal<< pointsListNew;
				// qDebug()<<"The drawn Contour:"<< pointsListNew;
				 pointsListNew.clear();		
				  //qDebug()<<"Found another closed loop";
				 partLoopsListFinal<<subLoop;
				 subLoop=QPainterPath();
				 //qDebug()<<"Starting a new loop";
				
				 //toolLoop=QPainterPath();
				 found=1;alreadyChecked=false;//k=0;occurence=0;
				 /// Refind a better starting point than 0
				 pos=newPos(ptsList);
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
					 // qDebug()<<"Removing points";
					  shrink (ptsList,pointsListNew,pos,oldPos);
					  ///FIXME/ to be removed when get drawing loops correctly
					 subLoop.addPath(pathsList.takeAt(pos/2));
					 found=1;/// we still have one point to work with 
				}
				 /// get the corresponding point location and store the caller one to avoid infinte loop
				 if (ptsList.indexOf(currentPoint)==pos ) {
					 pos=ptsList.lastIndexOf(currentPoint);
					}
				 else {
					 pos=ptsList.indexOf(currentPoint);
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
			 shrink (ptsList,pointsListNew,pos,oldPos)	;
			 ///FIXME/ to be removed when get drawing loops correctly
			  qDebug () << "taking path at"<<pos<<"path size"<<pathsList.size()<<"ptsList size"<<ptsList.size();
			 subLoop.addPath(pathsList.takeAt(pos/2));
			 found=1;/// we still have one point to work with 
			}
			 /// get the corresponding point location and store the caller one to avoid infinte loop
		 if (ptsList.indexOf(currentPoint)==pos ) {
			 pos=ptsList.lastIndexOf(currentPoint);
			}
		 else {
			 pos=ptsList.indexOf(currentPoint);
			}
				 /// change to the other the point definfig the line
		 if (pos%2==0) pos++; else pos--; 
		 /// alreadyChecked the other coordinate as we're coming from
		 alreadyChecked=true;
		 continue; /// TODO:remove this as it will continue naturally
		}		 
	}
	 //qDebug () << "Found" << nbrClosedPath << "closed Paths";//linesListNew;
	 qDebug()<<"The end points lines list: "<<endPointslist;
	 // qDebug()<<"The parts paths list: "<<pathsListFinal;
	 /// mAybe should do further processing to simplify the path 
	 // qDebug()<<"The simplified parts paths list: "<<pathsListFinal.at(0).simplified();
			
	 return entitiesListFinal;
    }
 
  QPointFWithParent Part::translateEntity(QPointFWithParent oldPoint, QPointF offset){
	 QPointFWithParent temp(oldPoint);
	 temp+=offset;
	 return temp;
	}
 
 void Part::shrink(QPFWPList &pointsList,QPFWPList &pointsListNew,int pos,int oldPos){
	/// push the Two current points into the Qlist of the current path
	/// The translation has to be relative not absolute therfor it had to be done
	///when the part is inserted in the sheetMetal not before
				 ///pointsListNew <<translateEntity(pointsList.at(pos),offsets.at(currentPart));
				 ///pointsListNew <<translateEntity(pointsList.at(oldPos),offsets.at(currentPart));
				 pointsListNew<<pointsList.at(pos);
				 pointsListNew<<pointsList.at(oldPos);
				 if (oldPos<pos)  {
					 pointsList.removeAt(oldPos);
				     pointsList.removeAt(oldPos);
					}
			     else {
					 pointsList.removeAt(pos);
				     pointsList.removeAt(pos);
					}		
	return;
    }
	
	void Part::drawArc(QPointFWithParent point,QPainterPath &pathToModify) {	 
	 QRectF rect(point.centerX-point.parentRadius,point.centerY-point.parentRadius,2*point.parentRadius,2*point.parentRadius);
	 pathToModify.arcTo(rect,-( point.angle1),-fabs( point.angle1- point.angle2));	 
	 //pathToModify.arcMoveTo(rect,-fabs( point.angle1- point.angle2));
	 
	}
	
	
	int Part::newPos(QPFWPList pointsList){
 	 int k=0,occurence=0;
	 while ((k<pointsList.size()) &&(occurence!=1)){
		 //pos=k;
	     occurence=pointsList.count(pointsList.at(k));
	 	 k++;		 
		}
	 return k-1;
	}
	

 QList <QPFWPList>  Part::filterCircles(){
	 /**As we have to return a QList of Qlist we create a temporary one (for now the temp dimension is one
	 But when introducing circles lead-in lead-out a circle loop will contain 2 points the center and the lead in**/
	 QPFWPList temp;
	 /// the circles centers/radius start & end points &leadIn/out 
	 QList <QPFWPList> gCodeCirclesPoints;
	 QPointFWithParent originalPoint;

	 temp.append(cirPtsList[0]);
	  qDebug()<<"Adding "<<cirPtsList.size()<<" circles";
	  ///WE add each encountred circle center to our endPointslist adding part offset to it.
	 for (int pos=0; pos <cirPtsList.size();pos++){
		/**We take a point mark its parent loop umber (for later tsp processing) then 
		 appeend it to the endPointslist and add the closedPath counter**/		 
		 originalPoint=cirPtsList.at(pos);
		 originalPoint.setLoopNbr(nbrClosedPath);
		 /// willbe useful later when creating lead Have to add option if cncMode=truz
		 originalPoint.setParentType(QPointFWithParent::Circle);
		 endPointslist.append(originalPoint);
		 nbrClosedPath++;
		 temp[0]=cirPtsList.at(pos);
		 gCodeCirclesPoints.append(temp);
		 ///We now append the circular loop for both detecting if it's the part outline and animation needs
		 partLoopsListFinal<<cirPathsList.at(pos);
		}
	 nbrCircles=nbrClosedPath;
	 //qDebug()<<gCodeCirclesPoints;
	 return gCodeCirclesPoints;	 
	}
	
	   
	void Part::optimize(){
	 /// replaces the points list with the previously created one (inspired from genetic algo)
	 gCodeEntitiesOpt.clear();
	  QList<int> procededLoops;
	 ///endPointslist=test->createNew(endPointslist);
	 if (bestRoute.size()>1) {
		 popu=new Popu();
		 bestRoute=popu->init(endPointslist);
	 }
	 	int i=0; 
		 
		 ///TIEME to reorder the Paths the same order as the returned list fromo ptimization
		 while (i<bestRoute.size()) {
				///FIXME: merge before Circles and Points into gcode
			 if (!procededLoops.contains(bestRoute.at(i).parentLoop)) {
				 qDebug()<<"Order "<<bestRoute.at(i)<<"position"<<bestRoute.at(i).parentLoop;
				 gCodeEntitiesOpt.append(gCodeEntities.at(bestRoute.at(i).parentLoop));		 
				 partText.addText(bestRoute.at(i),QFont("Times", 6),(QString("%1").arg(i)));
				 procededLoops.append(bestRoute.at(i).parentLoop);
				}
			 i++;
			}
		 ///Now we add the part's outline
		 qDebug()<<"Procedded loops"<<procededLoops;
		 if (plasmaMode){
			 if (!procededLoops.contains(outlinePoint.parentLoop)) {
				 bestRoute.append(outlinePoint);
				 qDebug()<<"Finally the outline "<<outlinePos;
				 gCodeEntitiesOpt.append(gCodeEntities.at(outlinePos));
				 ///And it's number
				 partText.addText(outlinePoint,QFont("Times", 6),(QString("%1").arg(endPointslist.size())));
				}			
			}
		 else {
				//we must reappend the outlinepoint anyway!
				 bestRoute.append(outlinePoint);
			}
	 update();
	}
	
	
	
	Part::~Part(){
}

Part* Part::copy(){
	 Part* newPart=new Part(*this);
     return newPart;
	}


void Part::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *)
 {
	 painter->setPen( settings.value("Colors/pen").value<QColor>());
     painter->setBrush( settings.value("Colors/brush").value<QColor>());
	 //painter->setBrush(Qt::NoBrush);
	 //foreach (QPainterPath loop,partLoopsListFinal){
     
	 //painter->drawPath(loop);
	 //}
	 painter->drawPath(partShape);
	 /// add an option to the config Dialogdesig
	 painter->setPen( QPen(Qt::red));///settings.value("Colors/brush").value<QColor>());
	 if (showText) { painter->drawPath(partText);}
 }
 
 void Part::clearText(){
	 partText=QPainterPath();
	}
/*
Returns the shape of this item as a QPainterPath in local coordinates. The shape is used for many things, including collision detection, hit tests, */
 QPainterPath Part::shape() const {
     return partShape;
 }
///If you want to change the item's bounding rectangle, you must first call prepareGeometryChange(). This notifies the scene of the imminent change, so that its can update its item geometry index; otherwise, the scene will be unaware of the item's new geometry, and the results are undefined (typically, rendering artifacts are left around in the view)
 
 
 ///The mvt is based on bound rect
QRectF Part::boundingRect() const {
     return qtRect;
 }
 
 
 
QVariant Part::itemChange(GraphicsItemChange change, const QVariant &value)
 {
	 //qDebug()<<change;
     switch (change) {
     case ItemPositionHasChanged:
		 ///NOTE:We only need to update the matrix when we release the mouse buton
		 
		 update();
         break;
	 case ItemSelectedChange	:
		 //qDebug()<<"I'm selected";
		  break;
	 case ItemTransformHasChanged:
		 transMatrix=transform().toAffine();
		 //transMatrix=transform().rotate(90).toAffine();//.setMatrix(
		 ///transMatrix.setMatrix(transform().m11(),transform().m12(),transform().m21(),transform().m22(),0,0);
		 //qDebug()<<transform()<<transform().type();
		 applyTransform();
		 qDebug()<<"Transformation";
		 ///We chnage our matrix
		 break;
     default:
	       
         break;
     };

     return QGraphicsItem::itemChange(change, value);
 }

 void Part::applyTransform(){
	 ///We apply the transfromations the follownig way:
	 ///1-translate the end point
	 
///NOTE: USE 
///mapToScene
	 QPointFWithParent temp;
	 QList<QPointFWithParent> currentList;
	 for (int i=0;i<gCodeEntitiesTrans.size();i++) {
		 currentList= gCodeEntitiesTrans.at(i);		 
	//	  for (int i=0;i<gCodeEntitiesOpt.size();i++) {
		// currentList= gCodeEntitiesOpt.at(i);
		  for (int j=0;j<currentList.size();j++) {
			 temp=currentList.at(j);
			 temp.setX(transMatrix.map(temp).x());
			 temp.setY(transMatrix.map(temp).y());
			 
				if (currentList.at(j).parentType==QPointFWithParent::Arc ||  currentList.at(j).parentType==QPointFWithParent::Circle) {
				 /// we move both center and endPoint
				 ///FIXME: have to find a way to get rid of the message "discards qualifiers"
				  ///temp.setCenter(mapFromScene(temp.center));
				 temp.setCenter(transMatrix.map(temp.center));			
				}
			 currentList.replace(j,temp);
			}
		 gCodeEntitiesTrans.replace(i,currentList);
		}
		qDebug()<<"Old leadPoint"<<leadsPoints;
	  if (plasmaMode){
		 QPointF trans;
		/// we also apply transformations to lead-in points
		 for (int i=0;i<leadsPoints.size();i++) {
			 ///trans=transMatrix.map(leadsPoints.at(i));
			 temp=leadsPoints.at(i);
			 temp.setCenter(mapFromScene(temp.center));
			 temp.setX(transMatrix.map(temp).x());
			 temp.setY(transMatrix.map(temp).y());
			 temp.setLeadTouch(mapFromScene(temp));
			 ///temp.setX(mapFromScene(temp).x());
			/// temp.setY(mapFromScene(temp).y());
			 ///temp.setX(trans.x());
			/// temp.setY(trans.y());
			 leadsPoints.replace(i,temp);
			}
		}
		qDebug()<<"new leadPoint"<<leadsPoints;
	 
	}
 
 void Part::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
 {    
	 /// When we release the mouse it's time to compute our new coordinated.
	 ///The start-end points are recalculated.
	 //transMatrix.setMatrix(1,0,0,1,position.x(),position.y());
	 deltaPos=position-pos();
	 position=pos();
	 qDebug()<<deltaPos<<position;
	 transMatrix.translate(deltaPos.x(),deltaPos.y());
	 applyTransform();	 
	 update(); 
	 qDebug()<<"Coordinates updated";
	 //qDebug()<<gCodeEntitiesTrans.at(0).at(0);
	 //setSelected (false);
     QGraphicsItem::mouseReleaseEvent(event);
 }
 
	 void Part::moveMeBy(qreal dx, qreal dy){
		/// leave the actual move to Qt
		 qDebug()<<dx<<dy;
		 moveBy(dx-pos().x(),dy-pos().y());
		 setPartPos();
 }
 
 void Part::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
 /// each time update is called the paint function is called
     //event->ignore();
     //qDebug()<<"mouse pressed piece";
	 update();//setSelected (true);
	 QGraphicsItem::mousePressEvent(event);
	 
 }
 
 void Part::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	 update(); // qDebug()<<"mouse moving";
	 QGraphicsItem::mouseMoveEvent(event);	 
	 }

	
	
	
	
	
	
	
	
	
	
	
	
	///todo : make changes to loop or not ? QPainterPath &myLoopPath
	void Part::createLeads(QPainterPath myLoopPath,int loopPos){
	 
	 /**This is how my 7alazounesk algorithm works:
		 we take a random point from a loop.
		 We postulate that every point can give a lead in/out point
		 We take an offset at a given angle. If the point isn't in (the loop.contains return false)
		 then we add val to angle when we return to 0 angle , we add an increment DELTA to the radius
		 we do this unil we find a point insdie the shape.
		 TODO : nnce  a point inside a shpae is foucnd Have to check that the linebetwseen the point & the lead
		 in/out pij t dosn't intersect with the outline!!!!!
	 
	 **/
	 //QPainterPath boundingRect; 
	 //boundingRect.addRect(myLoopPath.boundingRect());
	 /// have to take a point from the loop ( we choose it's start point but can any point...²
	 QPointF leadPoint=endPointslist.at(loopPos);
	 QPointF startPoint=endPointslist.at(loopPos);
	 /// begin the search
	 ///Min Radius is to be user Defined
	 double angle=0,incrementRad=0.3, incrementAng=3,radius=2;
	 int iter=0;
	 leadPoint.setX(leadPoint.x()+radius*cos(angle));
	 leadPoint.setY(leadPoint.y()+radius*sin(angle));
	 while (myLoopPath.contains(leadPoint) && iter<10000){
			angle+=incrementAng;
		if (angle>360) {radius+=incrementRad;angle=0;}
		leadPoint.setX(leadPoint.x()+radius*cos(angle));
		leadPoint.setY(leadPoint.y()+radius*sin(angle));
		
		//qDebug()<<angle<<iter;
		iter++;
		}		
		qDebug()<<"Possible lead point at"<<leadPoint<<"with radius"<<radius<<"and anfgle"<<angle<<"after"<<iter;
		//scene->addLine(QLineF(leadPoint,startPoint));
		//(scene->addPixmap(QPixmap("/home/invite/Desktop/bazar/PFE/camnest/hole.png"))->setPos(leadPoint));
	 /// Now check for intersects()
	 /**bool QPainterPath::contains ( const QPointF & point ) const
Returns true if the given point is inside the path, otherwise returns false.**/	
	}
	
	
		 /** the lead-in distance is a constant, it's the angle that varies to avoid intersection with other
	 shapes */

	
	