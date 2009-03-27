#include "gatsp.h"
#include "part.h"

int tolerance=0.01;

Part::Part(const QPainterPath path, QRectF rect,QPFWPList pointsList,QPPList partPathsList,QPFWPList circlePointsList,QPPList circlesPathsList):QGraphicsItem()//:partShape(path),qtRect(rect)
{
	 //setFlag(ItemIsMovable);
	 //setFlag(ItemIsSelectable);
	 partShape=path;
	 qtRect=rect;
	 showText=true;
	 position=QPointF(0,0);
	 deltaPos=QPointF(0,0);
	 pathsList=partPathsList;
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
		 gCodePoints<<filterCircles();
		 //emit progressionStep(0);
		 //emit descStep("Circles parsed");
	 }
	 if(pointsList.size()!=0){
	 
	 /// here we start the thread :
	 // emit progressionStep(1);
	// emit descStep("Fliltering closed loops parsed");
	 //test.start();
	 gCodePoints<<filterLoops();
	 /// This is the default route automaticlayy generated without any optimization
	 gCodePointsOpt=gCodePoints;
	 }
	 /**
			 Beforee quiting one last thing remains: have to move the part outline to the List ends as theoutline 
			 is the last shape to be cut by Comparing bound rect.
			 TOdo:Is useful in Plasma cutting=> add if mode=plasma
			 */
	 findOutline();
	  ///emit progressionStep(2);
	 //emit descStep("Finding outline");
	 bestRoute=endPointslist;
	 /// Add the outline (if no optimiztion is done and the file saved) add if mode=plasma
	 bestRoute.append(outlinePoint);
	   //emit progressionStep(2);
	// emit descStep("Processeding to optimization");
	 optimize();
	 //qDebug()<<"optimization done"<<bestRoute;
	 gCodePointsTrans=gCodePointsOpt;

	 
	 
	 
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
 Part::Part(const Part &parentPart){
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
	 gCodePointsOpt=parentPart.gCodePointsOpt;
	 gCodePoints=parentPart.gCodePoints;
	 ///to keep track of the part Nbr
	 setData(0,parentPart.data(0));
	 ///NOTE:NO need to take the Trans part 
	 gCodePointsTrans=parentPart.gCodePointsOpt;
	 endPointslist=parentPart.endPointslist;
	 }
///startJob()


	
	
	 void Part::findOutline(){
	 QRectF outerBound=partLoopsListFinal.at(0).controlPointRect ();//boundingRect();//controlPointRect ();
	 QRectF outer=partLoopsListFinal.at(0).controlPointRect ();//boundingRect();//controlPointRect ();//boundingRect();//
	 /// COULD START from outlinePos?
	 int posOuter=0;
	 for (int pos=0;pos<partLoopsListFinal.size();pos++){
		 outer=partLoopsListFinal.at(pos).controlPointRect ();//boundingRect();//.controlPointRect ();
		 if (outerBound.height()* outerBound.width()< outer.height()*outer.width()) {
			 outerBound=outer;
			 posOuter=pos;
			}		 
		}
		///we remove the outline from the TSp optimization
		
		outlinePos=posOuter;
		 qDebug()<<"The outline is the " <<posOuter <<"th element of"<<nbrClosedPath;		
		///to be removed for testing 
			
		QPainterPath outLinePath;

		QPainterPath unionPath;
	
		outLinePath=partLoopsListFinal.takeAt(posOuter);
		
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
		 unionPath=unionPath.united(loop);i++;
		 
		}
	
		 outLinePath=outLinePath.subtracted(unionPath);
		 outlinePoint=(endPointslist.takeAt(posOuter));
		 qDebug()<<"end of outline";
		 partShape=outLinePath;
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
	
 	 pos=newPos(ptsList);
	 
	 while (ptsList.size()>=2) {
		 currentPoint=ptsList.at(pos);
		 // qDebug()<<"Working with"<<currentPoint<< " at "<<pos;		  
		  /** 
		  * If the list contains the point only one time we can't link between it and other shapes
		  * unless we stwitch to the other point definfing the shape, if it hadn't already been checked
		  *(avoiding infinte loops )
		  */
		 if (ptsList.count(currentPoint)==1) {
		     oldPos=pos;
			 //qDebug()<<"No corresponding point.AlreadyChecked other coord:"<<alreadyChecked;
			/// change to the other the point definfig the entity if it havn't already been checked
		     if ( alreadyChecked==false ) {
				 if (pos%2==0) pos++; else pos--; 
				 alreadyChecked=true;
				}
			 currentPoint=ptsList.at(pos);
			 /// still havn't found a corresponding point have to close the current path and start another
			 if (ptsList.count(currentPoint)==1) { 		
				 //qDebug()<<"Swaped but still no corresponding point.";
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
				 }
				/**TODO: PUT this as an option EITHER to use lines or numbers
					toolLoop.lineTo(pointsListNew.first());
				 **/
				 
				 qDebug()<<pointsListNew;
				  ///Redraw the shape loop by loop
				  
				  ///check for size>2 before!!!
				  QPointFWithParent p;
		//qDebug()<<subLoop.currentPosition();

				  int f=0;subLoop.moveTo(pointsListNew.at(f));
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
				 
				 if (found==1) nbrClosedPath ++; /// increment only if it's composed of at least one intersection
				 /// Add the current path to entities list
				 entitiesListFinal<< pointsListNew;
				// qDebug()<<"The drawn Contour:"<< pointsListNew;
				 pointsListNew.clear();				
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
	 //qDebug()<<"The end points lines list: "<<endPointslist;
	 // qDebug()<<"The parts paths list: "<<partPathsListFinal;
	 /// mAybe should do further processing to simplify the path 
	 // qDebug()<<"The simplified parts paths list: "<<partPathsListFinal.at(0).simplified();
			
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
	
	   Popu *popu;
	   
	void Part::optimize(){
	 /// replaces the points list with the previously created one (inspired from genetic algo)
	 gCodePointsOpt.clear();
	 ///endPointslist=test->createNew(endPointslist);
	 int i=0;
	 popu=new Popu();
	 bestRoute=popu->init(endPointslist);
	 

	 while (i<bestRoute.size()){
			///FIXME: merge before Circles and Points into gcode
			qDebug()<<"Order "<<bestRoute.at(i)<<"position"<<bestRoute.at(i).parentLoop;
		 gCodePointsOpt.append(gCodePoints.at(bestRoute.at(i).parentLoop));
		 
		 partText.addText(bestRoute.at(i),QFont("Times", 6),(QString("%1").arg(i)));
		 i++;
		}
		
	 ///(scene->addPath(partsList.at(0)->partPath,contourPen))->setPos(offsets.at(0));
		///Now we add the part's outline
	 bestRoute.append(outlinePoint);
	 
	 qDebug()<<"Finally the outline "<<outlinePos;
	 gCodePointsOpt.append(gCodePoints.at(outlinePos));
	 ///And it's number
	 partText.addText(outlinePoint,QFont("Times", 6),(QString("%1").arg(i)));
	/// (scene->addText((QString("%1").arg(outlinePos)),QFont("Times", 6)))->setPos(outlinePoint);
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
	 //foreach (QPainterPath loop,partLoopsListFinal){
     
	 //painter->drawPath(loop);
	 //}
	 painter->drawPath(partShape);
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

void Part::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
 /// each time update is called the paint function is called
     
     qDebug()<<"mouse pressed updated";
	 update();//setSelected (true);
	 QGraphicsItem::mousePressEvent(event);
 }

 void Part::applyTransform(){
	 ///We apply the transfromations the follownig way:
	 ///1-translate the end point
	 QPointFWithParent temp;
	 QList<QPointFWithParent> currentList;
	 for (int i=0;i<gCodePointsOpt.size();i++) {
		 currentList= gCodePointsOpt.at(i);
		  for (int j=0;j<currentList.size();j++) {
			 temp=currentList.at(j);
				if (currentList.at(j).parentType==QPointFWithParent::Arc) {
				 /// we move both center and endPoint
				 ///FIXME: have to find a way to get rid of the message "discards qualifiers"
				 temp.setCenter(transMatrix.map(temp.center));
				 temp=transMatrix.map(temp);
				 currentList.replace(j,temp);
				}
				else{
				 temp=transMatrix.map(temp);
				 currentList.replace(j,temp);	 
				}
			}
		 gCodePointsTrans.replace(i,currentList);
		}
	 
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
	 //qDebug()<<gCodePointsTrans.at(0).at(0);
	 //setSelected (false);
     QGraphicsItem::mouseReleaseEvent(event);
 }
 
	 void Part::moveMeBy(qreal dx, qreal dy){
		/// leave the actual move to Qt
		 qDebug()<<dx<<dy;
		 moveBy(dx-pos().x(),dy-pos().y());
		 setPartPos();
 }
 
 void Part::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	 update(); // qDebug()<<"mouse moving";
	 QGraphicsItem::mouseMoveEvent(event);	 
	 }
 
	
	