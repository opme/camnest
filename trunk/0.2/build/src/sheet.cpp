 // #include "renderpath.h";
 #include "sheet.h"
 #include "qpointfwithparent.h"
 #include "gcode.h"
 //#define RAND_MAX 255
#define ARROW_LENGHT 10
  DL_Dxf* dxf;
  Test_CreationClass* creationClass;
  /// represent the QGraphicsViews containing the scenes
  Sheet *scene;
  Sheet *pathScene;
 // QGraphicsView *view;
  QPainterPath path2;
  
  QPainterPath toolLoop;
  
  QGraphicsItem *generatedPath;
  QGraphicsItem  *toolPathItem;
  QGraphicsItem  *contoursPathItem;
  
  /// ho<w many loop in a part
  int numberClosedPath=0;
  
	QGraphicsPathItem *piece;
  ///Holds the nulber of inserted parts in the drawing
  int insertedParts=0;
  int currentPart=0;
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
 QList<Test_CreationClass *> partsList;
 
  /// holds the organised entities paths between tow end points 
 QList <QPainterPath > partPathsListFinal;
 /// holds the organised loops paths entity by entity
  QList <QPainterPath > partLoopsListFinal;
   /// holds the organised loops paths (loops driven)
  ///QList <QPainterPath > partLoopsListFinal;
int currentLoop=0;
  
  /// stiores the organised entities Start/end points.
  QList <QList<QPointFWithParent  > > gCodePoints;
  /// stiores the circles centers/radius start & end points bieng the attaque points
   QList<QPointF > gCodeCirclesPoints;
   QList<qreal > gCodeCirclesRadius;
  /// the first closed loop in a piece
 QList<QPointF > closedLoop;
 QPen toolPen(Qt::blue,1);//, Qt::DashDotLine);
 QPen contourPen(Qt::red);

QPointFWithParent offset(0,0);
QList<QPointF > offsets;
 /// used when drawing toolpath and for homing on G-code
 QPointF homePoint(0,0);
/// See http://www.linuxcnc.org/handbook/gcode/g-code.html for more infos about G-code



/**
05-03-09:
Parts are represented on the GUI by QgraphicsItems and on the processing part by QpointsList
Have to merge them to ensure that editing one (the Gui) makes the appropriate changes on the
other (the Qpoint lists).
The creation class have to return only A list of QpointWithParent
Another class have to deal with the GUI part!


*/

 QPointF endPoint(0,0);QGraphicsLineItem *toolLine;QGraphicsItemGroup* toolPathGroup;QList<QGraphicsItem*> temporary;
   void MainWindow::stepByStep (){
		
		///pathScene->addPath(partPathsListFinal.at(currentLoop));
		if (currentLoop ==  toolLoop.elementCount()-1) {
			 //pathScene->clear();
			 currentLoop=0;
			 
			 homePoint=QPointF(0,0);
			 qDebug()<<"removing group";
			 pathScene->removeItem(toolPathGroup);
			 toolPathGroup=pathScene->createItemGroup (temporary);
		}
		else {
			 currentLoop++;	
		}
			
		 /// we need to cast as the element At returns at QpainterPath elment
		 //QPainterPath *test=dynamic_cast<QPainterPath *> &(toolLoop.elementAt(currentLoop));
		 ///As all the tool path is composed of lines we simpl add them one by one;
		 ///TODO: create curved paths when oing on arcs/circles<== easy to tell...but to code!!!
		 if (toolLoop.elementAt(currentLoop).isLineTo()) {
			 endPoint=toolLoop.elementAt(currentLoop);
			 toolLine=pathScene->addLine(QLineF(homePoint,endPoint),toolPen);
			 //toolLine->setParentItem(toolPathItem);
			 /// toolPathGroup->addToGroup(toolLine);
			 homePoint=endPoint;
			}
	}

  
    void MainWindow::openFile() {
     QString file = QFileDialog::getOpenFileName(0,"Find Files", "/media/donnees/SL+TN","DXF Files (*.dxf)");
     if (file.isEmpty()) {
		 statusBar()->showMessage(tr("Please select a file"));
		 return;
		}
	 else {
		 Test_CreationClass* creationClass = new Test_CreationClass();
		 DL_Dxf* dxf = new DL_Dxf();
		 if (!dxf->in(file.toStdString(), creationClass)) { // if file open failed
			 qDebug() << "Could not open " << file;
			 statusBar()->showMessage(tr("Could not open the selected file"));
			 return;
			}
		 else {
			 statusBar()->showMessage(tr("File: ")+file);
			 qDebug() << "Reading file Done";
			}
			 ///Add the part to files list
			 partsList.append(creationClass);
			 
			 /// Display the parsed part path as is. 
			 ///pathScene->addPath(creationClass->partPath)->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
			 piece=(pathScene->addPath(creationClass->partPath));			 
			 piece->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
			 ///0 holds the part index
			 piece->setData(0,insertedParts);
			 insertedParts=pathScene->items().size();//// ou bien partsList .size()
			  qDebug() <<insertedParts <<"Parts in the scene";
			 qDebug() << "Part inserted"<<piece;
			
			 clearAction->setEnabled(true);
			 generateAction->setEnabled(true);
			 /// a surveiller Havn't it to be a QPOINTwith Parent 
			 offset=QPointF(0,0);
			 offsets<<offset;
			 currentLoop=0;empty=0;
			 //path2 =creationClass->partPath;
			 //part= new QGraphicsPathItem(path2);
			 //part->setFlag(QGraphicsItem::ItemIsMovable, true);
			 //part->setFlag(QGraphicsItem::ItemIsSelectable, true);
			 ///pathScene->addItem(part);
			 ///itemsBoundingRect() sums the items rectBounds =>> very slow on large sceen selon Qt
			 /// if (insertedParts!=0) part->setPos(pathScene->itemsBoundingRect().bottomRight ());
			 ///part->setPos(300,300);
			 //pathScene-> views().at(0)->fitInView(pathScene->itemsBoundingRect(),Qt::KeepAspectRatio);
			 ///QGraphicsRectItem *rectBound = new QGraphicsRectItem(creationClass->partBoundingRect);
		}
		///qDebug() << "removing item group ";
	 ///pathScene->removeItem(toolPathGroup);
	 ///qDebug() << "removed item group ";
	 ///toolPathGroup=pathScene->createItemGroup (temporary);
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
	 // partGCode.fileName=fileName;
	 partGCode.writeHeader(fileName);
	 partGCode.writeCircleLoop( gCodeCirclesPoints,gCodeCirclesRadius,1);
	 int i=0;
	 qDebug()<<"Writing the Gcode of "<<gCodePoints.size()<<"parts";
	 while (i < gCodePoints.size()){
		 partGCode.comment("Adding a Loop");
		 partGCode.comment("Turnin off torch");
		 partGCode.comment("going to Z home");
	 	 partGCode.writeClosedLoop( gCodePoints.at(i));
		 i++;
		}	 
	 partGCode.writeEnd();
	 statusBar()->showMessage(tr("File saved"),4000);
	 return true;
	}
 

	void MainWindow::generatePath() {	 
	 if (insertedParts!=0){
		 //qDebug()<<"Generating the path"<<partsList.at(0)->pointsPathList;
		 scene->clear();toolLoop=QPainterPath();
		 //toolLoop.clear();
		 gCodeCirclesPoints.clear();
		 gCodeCirclesRadius.clear();
		 gCodePoints.clear();
		 partPathsListFinal.clear();
		 partLoopsListFinal.clear();
		 //scene->setPos(offset);
		//qDebug()<<"the linked lines list:"<<gCodePoints;
		 qDebug()<<"adding circular holes";
		 /// some pieces may not contain circular holes
		 currentPart=0;
		 while (currentPart<insertedParts){
			 qDebug()<<"Generating Gcode of part"<<currentPart+1<<"from "<<insertedParts;
			 if(partsList.at(currentPart)->pointsCircleList.size()!=0){
				 gCodeCirclesPoints<<addCircles(partsList.at(currentPart)->pointsCircleList,partsList.at(currentPart)->circlePathsList);
		 //qDebug()<<"the circles cut list:"<<addCircles(partsList.at(0)->pointsCircleList,partsList.at(0)->circlePathsList);
		 /// todo: reimplment withparent
				 gCodeCirclesRadius<<partsList.at(currentPart)->radiusCircleList;
			 }
			 qDebug()<<"generating tool Path";
			 /// some pieces may only contain circular holes
			 if(partsList.at(currentPart)->pointsPathList.size()!=0){
				 gCodePoints<<organiseEntities(partsList.at(currentPart)->pointsPathList,partsList.at(currentPart)->partPathsList);
				// qDebug()<< gCodePoints;///gCodePoints+=organiseEntities(partsList.at(1)->pointsPathList,partsList.at(1)->partPathsList);
				}
			 /// Draw the QPainterPath of the part
			 (scene->addPath(partsList.at(currentPart)->partPath,contourPen))->setPos(offsets.at(currentPart));
		     scene-> views().at(0)->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
		     currentPart++;
			 
			}
		}	
		else{
		statusBar()->showMessage(tr("No path to generate"));
		}
     statusBar()->showMessage(tr("Path generated"));
	 stepAction->setEnabled(true);
	 
	}	
	
    void MainWindow::rotateParts() {
	 if (!selectParts.isEmpty ()) { 
	 	 foreach(QGraphicsItem *part,selectParts){
	 		 part->rotate(90);
			 statusBar()->showMessage(tr("Rotated"));
	 		}
	 	}
		else{
		  statusBar()->showMessage(tr("Please make a selection"));
		}
	}
	
    void MainWindow::clearScene() {
	 ///todo: add a warning Yes/no
	 partsList.clear ();
	 partLoopsListFinal.clear();
	 partPathsListFinal.clear();
	 insertedParts=0;
	 scene->clear();
	 pathScene->clear();	 
	 clearAction->setEnabled(false);
	 generateAction->setEnabled(false);
	 stepAction->setEnabled(false);
	 statusBar()->showMessage(tr("Emptied Scene"));
	}
	
	
	 void MainWindow::zoomFit() {
	 pathScene-> views().at(0)->fitInView(pathScene->itemsBoundingRect(),Qt::KeepAspectRatio);
	 //scene-> views().at(0)->fitInView(pathScene->itemsBoundingRect(),Qt::KeepAspectRatio);
	 //pathScene-> views().at(0)->ensureVisible(pathScene->itemsBoundingRect(),Qt::KeepAspectRatio);
	 qDebug()<<pathScene->itemsBoundingRect();
	 pathScene-> views().at(0)->centerOn(pathScene->itemsBoundingRect().center());
     statusBar()->showMessage(tr("Zoom to fit"));
	}	
	
	
    
	void Sheet::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 QPointF p1=mouseEvent->scenePos();QPointF p2=mouseEvent->lastScenePos();
	 
	 if (mouseEvent->button() == Qt::RightButton)
	  {
	      views().at(0)->fitInView(QRectF(p1,p2),Qt::KeepAspectRatio);
		  views().at(0)->setDragMode(QGraphicsView::NoDrag);
	  } 
	  
	  if (mouseEvent->button() == Qt::LeftButton) { 
	     //mode=0;
		 /// or couldbe simply retrived from scene->selectedItems()
	     selectParts=selectedItems();
		///selectedItems= scene->items ( QRectF(p1,p2), Qt::IntersectsItemShape  );
		 
	     if (!selectParts.isEmpty ()) { 	      
			  
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
	     //views().at(0)->fitInView(QRectF(0,0,800,800),Qt::KeepAspectRatio);
		  //views().at(0)->setDragMode(QGraphicsView::NoDrag);
		 // views().at(0)->centerOn(scene->
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
		 if ((selectedItem->flags().testFlag(QGraphicsItem::ItemIsMovable)))
		  selectedItem->setPos(mouseEvent->scenePos());
		  //qDebug()<<selectedItem->pos();
		  offsets.replace((selectedItem->data(0).toInt()),selectedItem->pos());
	     //qDebug()<<offsets;
		 // selection->setPos(mouseEvent->scenePos());
	     }
		}
		/// emit signal with position to statubarqDebug () <<MainWindow::statusBar();
		//qDebug () << mouseEvent->scenePos();
	}

	void Sheet::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
		if (mouseEvent->button() == Qt::RightButton){ qDebug()  << "right"; 
	
	     views().at(0)->setDragMode(QGraphicsView::RubberBandDrag); 
	        mode=0;
	    }
		if (mouseEvent->button() == Qt::LeftButton) { 
		  qDebug()  << "left";
		  mode=1 ; /// moveitem
		 views().at(0)->setDragMode(QGraphicsView::RubberBandDrag);
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
	
	 QPointF topLeft     = views().at(0)->mapToScene( 0, 0 );
	 QPointF bottomRight = views().at(0)->mapToScene( views().at(0)->viewport()->width() - 1, views().at(0)->viewport()->height() - 1 );
	 qreal width=bottomRight.x()-topLeft.x();
	 qreal height=bottomRight.y()-topLeft.y();
	 //std::cout << width << "/" << height << " : " << factor << std::endl;
	 if((width/factor<=5000)&&(height/factor<=5000)){
		QMatrix oldMatrix = views().at(0)->matrix();
		qreal newScale=oldMatrix.m11()*factor;
		views().at(0)->resetMatrix();
		views().at(0)->translate(oldMatrix.dx(), oldMatrix.dy());
		views().at(0)->scale(newScale, newScale);		
	}
		
		/// mWhy do we need theset Accepted???ouseEvent->setAccepted(true);
		return;
}
 
 
  void MainWindow::deleteItems(){
	 int nbr=pathScene->selectedItems().size();
     if  (nbr!=0) {
		 foreach (QGraphicsItem *item, pathScene->selectedItems()) {
			 pathScene->removeItem(item);
			}
		 statusBar()->showMessage(tr("Removed "));
		 if (nbr==insertedParts){
			 clearAction->setEnabled(false);
			 generateAction->setEnabled(false);
			 stepAction->setEnabled(false);
			 
			}
		}
	 else {
		 statusBar()->showMessage(tr("No item selected "));
		}
	 insertedParts-=nbr;
	 qDebug()<<insertedParts<<" parts remains";
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
	 editToolBar->addAction(stepAction);	
	 editToolBar->addAction(zoomFitAction);
	  editToolBar->addAction(deleteAction);
	 
	 
	 clearAction->setEnabled(false);
	 generateAction->setEnabled(false);
	 stepAction->setEnabled(false);
	//editToolBar = addToolBar(tr("Edit"));
	}
	

  MainWindow::MainWindow(){
  
     /// Actions have to be first declared before setting the menus
	 aboutAction = new QAction(tr("&About"), this);
	 aboutAction->setShortcut(tr("Ctrl+B"));
     openAction = new QAction(tr("&Open"), this);
	 openAction->setShortcut(tr("Ctrl+O"));
	 saveAction = new QAction(tr("&Save"), this);
	 saveAction->setShortcut(tr("Ctrl+S"));
	 saveAction->setStatusTip(tr("Save the G code"));
	 clearAction = new QAction(tr("&Clear"), this);
	 clearAction->setShortcut(tr("Ctrl+C"));	
	 stepAction = new QAction(tr("&Step loop"), this);
	 stepAction->setShortcut(tr("Ctrl+L"));
	 rotateAction = new QAction(tr("&Rotate"), this);
	 rotateAction->setShortcut(tr("Ctrl+R"));
	 zoomFitAction = new QAction(tr("&Zoom Fit"), this);
	 zoomFitAction->setShortcut(tr("Ctrl+F"));
	 generateAction = new QAction(tr("&Generate path"), this);
	 generateAction->setShortcut(tr("Ctrl+G"));
	 deleteAction= new QAction(tr("&Delete"), this);
	 deleteAction->setShortcut(tr("Ctrl+D"));
	 
	 /// connecting the signals
	 connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));  
	 connect(openAction, SIGNAL(triggered()),this, SLOT(openFile())); 
	 connect(clearAction, SIGNAL(triggered()),this, SLOT(clearScene())); 
	 connect(stepAction, SIGNAL(triggered()),this, SLOT( stepByStep())); 
	 connect(rotateAction, SIGNAL(triggered()),this, SLOT(rotateParts())); 
	 connect(generateAction, SIGNAL(triggered()),this, SLOT(generatePath())); 
	 connect(zoomFitAction, SIGNAL(triggered()),this, SLOT(zoomFit())); 
	 connect(saveAction, SIGNAL(triggered()),this, SLOT( saveFile())); 
     connect(deleteAction, SIGNAL(triggered()),this, SLOT( deleteItems())); 

	 setWindowTitle(tr("CamNest"));
	  /// setup theGUI
	 createMenus() ;
	 createStatusBar(); 
	 createToolBars();
	 qDebug()<< "Interface ready";
     /// create the view  in the mainWindow
	/// resize to the sheet value
	
	 QRect sceneRect(0, 0, 1600, 1600); 
     scene=new  Sheet ();
	 scene->setSceneRect(sceneRect);
	 pathScene=new  Sheet ();	  
	 pathScene->setSceneRect(sceneRect);
	  
	 ///pathSheet= new  SheetMetal (pathScene);
	/// pathSheet->setGeometry(20, 60, 600,600);
	  QHBoxLayout *layout = new QHBoxLayout;
     ///sheet= new  SheetMetal (scene);
	 ///sheet->setGeometry(670, 60, 600, 600);
	  QGraphicsView *pathSheet = new QGraphicsView(pathScene);
	  QGraphicsView *sheet = new QGraphicsView(scene);
	  ///layout->addWidget(pathSheet);  
	 pathSheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 pathSheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 pathSheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 sheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 sheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 sheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
     layout->addWidget(pathSheet);
	 layout->addWidget(sheet); 
	  QWidget *widget = new QWidget;
     widget->setLayout(layout);
	 //QGraphicsView *sheetView= new QGraphicsView(scene);
	
	 setCentralWidget(widget);
	
	 // QGridLayout *mainLayout = new QGridLayout;
     //mainLayout->addWidget(test, 0, 0, 1, 4);
	 //QPushButton *quit = new QPushButton("Quit");
	 //mainLayout->addWidget(quit, 0, 0, 1, 4);
    ///setCentralWidget(pathSheet);
    }
     /*
   the seetMetal declarations
  */
  
 SheetMetal::SheetMetal(QGraphicsScene *scene,QWidget *parent): QWidget(parent)   {     
	 /// put the scen in the view
	 ///scene = new  Sheet (this);
	 ///QRect sceneRect(0,0,440,440);
	 //pathScene= new  Sheet (this);	 
     ///scene->setSceneRect(sceneRect);
	 //pathScene->setSceneRect(sceneRect);
	 QGraphicsView *view= new QGraphicsView (scene,this);   
	 view->setCacheMode(QGraphicsView::CacheBackground);
	 view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 // pathview = new QGraphicsView (pathScene,this);  
	 //QPushButton *quit = new QPushButton("Quit",this);
	}  
	
	
 void MainWindow::createMenus() {
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
 
 
	  QSize SheetMetal::sizeHint() 
	  {
     //return QSize(300, 300);
     }
	 
	 QSize SheetMetal::minimumSizeHint() 
 {
     //return QSize(200, 150);
 }
  
	
	QList <QPointF >  MainWindow::addCircles(QList <QPointF > circlePointsList,QList <QPainterPath > circlesPathsList){

	 QPainterPath subLoop;
	 //QPainterPath toolLoop;
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
		 /// Do we need to call translateEntity(pointsList.at(pos),offsets.at(currentPart))??
		 circlePointsList.replace(pos,(circlePointsList.at(pos)+offsets.at(currentPart)));
		 circlePointsList.replace(pos+1,(circlePointsList.at(pos+1)+offsets.at(currentPart)));
		 
		 angle=getAngle(circlePointsList.at(pos),circlePointsList.at(pos+1));// shoukld be +2 but then go oaftre size
		 toolLoop.lineTo(circlePointsList.at(pos));		
		/// arrowPath.moveTo(circlePointsList.at(pos));
		/// arrowPath.lineTo(ArrowWing1(angle,circlePointsList.at(pos)));
		/// arrowPath.moveTo(circlePointsList.at(pos));
		/// arrowPath.lineTo(ArrowWing2(angle,circlePointsList.at(pos)));
		 //scene->addPath(createArrow(circlePointsList.at(pos),circlePointsList.at(pos+1)),QPen(Qt::blue,1));
	  /// inspired from edges.cpp @qt examles
		 QLineF line(circlePointsList.at(pos),circlePointsList.at(pos+1));
	  qreal arrowSize=9.0;
		 double angle = ::acos(line.dx() / line.length());
		 qDebug()<<angle;
		 if (line.dy() >= 0)       angle = 2*M_PI - angle;
		 QPointF destArrowP1 = circlePointsList.at(pos)+ QPointF(sin(angle + M_PI / 3) * arrowSize,cos(angle + M_PI / 3) * arrowSize);
		 QPointF destArrowP2 =circlePointsList.at(pos) + QPointF(sin(angle + M_PI -M_PI / 3) * arrowSize,cos(angle + M_PI - M_PI / 3) * arrowSize);
		 arrowPath.addPolygon(QPolygonF() << circlePointsList.at(pos) << destArrowP1 << destArrowP2);
		  ///touch the circle 
		// toolLoop.lineTo(circlePointsList.at(pos+1));
		  ///add the circle to the scene
		 /// scene->addPath(circlesPathsList.at(pos/2));
		 pos=pos+2;	
		 //qDebug()<<pos;
		}
		// arrow.setPos(toolLoop.currentPosition());
		
	scene->addPath(arrowPath,QPen(Qt::blue,1));
	 //scene->addPath(createArrow(circlePointsList.at(2),circlePointsList.at(3)),QPen(Qt::blue,1));
	 scene->addPath(toolLoop,toolPen);
	 return circlePointsList;
	}
	
	
/// NOTE: some parts may contains repeated lines (drawn above others) How to deal with such entities ?
    QList <QList<QPointFWithParent  > > MainWindow::organiseEntities(QList <QPointFWithParent > pointsList,QList <QPainterPath > partPathsList){
	
	 /// those two have to be returned to be used by the gcode generator
	 QList <QList<QPointFWithParent > > entitiesListFinal;	 
	 /// stores the end points list that is used to optimize toolpath TSP optimization
	 QList <QPointFWithParent > pointsEndList;
	 
	 QPainterPath subLoop;
	
	 //generatedPath=new QGraphicsItem();
	 //toolPathItemGroup=new QGraphicsItemGroup();
	 bool alreadyChecked=false;
	 int oldPos=0,found=1;
	 
	 QPointFWithParent currentPoint(0,0);
	 QList <QPointFWithParent > pointsListNew;
	 numberClosedPath=0; 
	 ///Do we really need that?
	  ///entitiesListFinal.clear();
	 qDebug() << "Dealing with "<<partPathsList.size()<<" Entities represented by "<< pointsList.size()<<"points";
	 int pos=0;
	  /**
	  *for the algorithm to be efficient on open loops we have to start by an unique end point!
	  *loop until we find a unique point in the list to start with elsewhere go with the first
	  */
 	 pos=newPos(pointsList);
	 /**
	  *Some shapes can contains an odd number of points (intersection) the user may be interted by
	  *being notified of their presence FIXME: TO be removed ?
	  */ 
	 ///int occurences=0;
	  /**
	  *Start the entities reorganisation process until the last 2 points in the list
	  */ 
	  /// continue from the last point on circle if had some
	  if(!gCodeCirclesPoints.isEmpty()) toolLoop.moveTo(gCodeCirclesPoints.last());
	  qDebug()<< "Continuing from circular holes";
	 while (pointsList.size()>=2) {
		 currentPoint=pointsList.at(pos);
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
				 //qDebug()<<"Removing points";
				 shrink (pointsList,pointsListNew,pos,oldPos);
				 
				 /** Will be useful later for TSP optimization*/
				 pointsEndList.append(pointsListNew.first());
				 pointsEndList.append(pointsListNew.last());
				 
				 toolLoop.lineTo(pointsListNew.first());
				 
				 ///It's time to draw the corresponding entity
				 subLoop.addPath(partPathsList.at(pos/2));
				 partPathsListFinal<< partPathsList.at(pos/2);
				 partPathsList.removeAt(pos/2);
				 
				 ///subLoop.moveTo(linesListNew.first());				 
				 
				 if (found==1) numberClosedPath ++; /// increment only if it's composed of at least one intersection
				 /// Add the current path to entities list
				 entitiesListFinal<< pointsListNew;
				// qDebug()<<"The drawn Contour:"<< pointsListNew;
				 pointsListNew.clear();
				 //contoursPathItem=scene->addPath(subLoop,contourPen);				 
				 //toolPathItem=scene->addPath(toolLoop,toolPen);
				 ///(scene->addPath(subLoop,contourPen))->setFlags(QGraphicsItem::ItemIsSelectable );
				 ///(scene->addPath(toolLoop,toolPen))->setFlag(QGraphicsItem::ItemIsSelectable, false);
				 //toolPathItem->setParentItem(generatedPath);
				 //contoursPathItem->setParentItem(generatedPath);
				
				 //toolPathItem.addToGroup(scene->addPath(subLoop,QPen(color,1)));
				 //contoursPathItem.addToGroup(scene->addPath(toolLoop,QPen(Qt::red,1)));	
				 partLoopsListFinal<<subLoop;
				 
				 //qDebug()<<"Starting a new loop";
				 subLoop=QPainterPath();
				 //toolLoop=QPainterPath();
				 found=1;alreadyChecked=false;//k=0;occurence=0;
				 /// Refind a better starting point than 0
				 pos=newPos(pointsList);
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
					  shrink (pointsList,pointsListNew,pos,oldPos);
		 			 
					 ///It's time to draw the corresponding entity
					 subLoop.addPath(partPathsList.at(pos/2));
					 partPathsListFinal<< partPathsList.at(pos/2);
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
			 shrink (pointsList,pointsListNew,pos,oldPos)	;		 
		     ///It's time to draw the corresponding entity
			 subLoop.addPath(partPathsList.at(pos/2));
			 partPathsListFinal<< partPathsList.at(pos/2);
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
	 /**
		Beforee quiting one last thing remains: have to move the part outline to the List ends as theoutline 
		is the last shape to be cut by Comparing bound rect.
		TOdo:Is useful in Plasma cutting=> add if mode=plasma
	 */
	 
	 ///Note have to restart from posOuterthat becam the last element to be cut
	 ///and thus a separation between entities paths.
	 QRectF outerBound=partLoopsListFinal.at(0).controlPointRect ();
	 QRectF outer=partLoopsListFinal.at(0).controlPointRect ();
	 ///reuse pos as we do no lnger need it
	 pos=1; int posOuter=0;
	 while (pos<partLoopsListFinal.size()){
		 outer=partLoopsListFinal.at(pos).controlPointRect ();
		 if (outerBound.height()* outerBound.width()< outer.height()*outer.width()) {
		 	 outerBound=outer;
			 posOuter=pos;
			}
		 pos++;
		}
	  qDebug()<<"The outline is the " <<posOuter <<"th element"<<entitiesListFinal.size();
	  ///UNCOMMENT ME
	  /// Rearranging list TODO : THE endPoints list have to be rreaaranged too.
	  ///  entitiesListFinal.append(entitiesListFinal.takeAt(posOuter));
	  ///  partLoopsListFinal.append(partLoopsListFinal.takeAt(posOuter));
	  //qDebug()<<pointsEndList;
	  ///  qDebug()<< "Rearranging";
	 ///  pointsEndList.append(pointsEndList.takeAt(posOuter*2));
	  ///  pointsEndList.append(pointsEndList.takeAt(posOuter*2));
	  //qDebug()<<pointsEndList;
	 
	 return entitiesListFinal;
    }
 
 QPointFWithParent translateEntity(QPointFWithParent oldPoint, QPointF offset){
	 QPointFWithParent temp(oldPoint);
	 temp+=offset;
	 return temp;
	}
 
 void MainWindow::shrink(QList <QPointFWithParent > &pointsList,QList <QPointFWithParent > &pointsListNew,int pos,int oldPos){
	/// push the Two current points into the Qlist of the current path
	/// fixme : there  have to be a more elega	nt way to do this
				 pointsListNew <<translateEntity(pointsList.at(pos),offsets.at(currentPart));
				 pointsListNew <<translateEntity(pointsList.at(oldPos),offsets.at(currentPart));
				 
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
	
	
	int MainWindow::newPos(QList <QPointFWithParent > pointsList){
 	 int k=0,occurence=0;
	 while ((k<pointsList.size()) &&(occurence!=1)){
		 //pos=k;
	     occurence=pointsList.count(pointsList.at(k));
	 	 k++;		 
		}
	 return k-1;
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
	