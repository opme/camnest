 // #include "renderpath.h";
 #include "sheet.h"
 #include "qpointfwithparent.h"
 #include "gcode.h"
 #include "gatsp.h"

 //#include "part.h"
 //#define RAND_MAX 255
 #define ARROW_LENGHT 10

 /// FIXME: In step loop there 's a reptition of loops in part tspOp.dxf
 
	DL_Dxf* dxf;
	Test_CreationClass* creationClass;
	/// represent the QGraphicsViews containing the scenes
	Sheet *scene;
	Sheet *previewScene;	
	
	QGraphicsPixmapItem *toolPix;
	QPointFWithParent endPoint;
	QGraphicsLineItem toolLine;

	Part *piece;
  
  
  ///Holds the nulber of inserted parts in the drawing
	int insertedParts=0;
	///Holds the nulber of current present parts in the drawing
	int nbrParts=0;
	
 
	/// weitherthere areseneted itmes or not
	int selection_empty=1;
	/// numberof selecteditems
	int selected_nbr=0;
	

	///the parts appended to the sheetMetal
	QList<Part *> parts;
	
	///havn't to be pointer reference as they entities are deleted after being read
	
	int currentLoop=0;
    
	/// mAybe useful for TSP between PArts
	QPFWPList endPointslist;	
	

	
	
///# used when drawing toolpath and for homing on G-code
	QPointF absoluteHome(0,0);
	QPointF homePoint(0,0);
	QPointF lastPartPos(0,0);
/// See http://www.linuxcnc.org/handbook/gcode/g-code.html for more infos about G-code

/**
the outer loop has to be treated lastly.
the home point have to be the first point in every tsp instance
*/

/**
05-03-09:
Parts are represented on the GUI by QgraphicsItems and on the processing part by QpointsList
Have to merge them to ensure that editing one (the Gui) makes the appropriate changes on the
other (the Qpoint lists).
The creation class have to return only A list of QpointWithParent
Another class have to deal with the GUI part!
*/

SettingsDialog::SettingsDialog(QWidget *parent)   : QWidget(parent)
 {
     ui.setupUi(this);
	 //("camnest", "camnest");
	 qDebug()<< settings.fileName();
	 loadSettings();
	 connect (ui.penPB,SIGNAL(clicked()),this, SLOT( setPenColor())); 
	 connect (ui.brushPB,SIGNAL(clicked()),this, SLOT( setBrushColor())); 
	 connect (ui.texturePB,SIGNAL(clicked()),this, SLOT( setInner()));
	 connect (ui.okButton,SIGNAL(clicked()),this, SLOT( save()));
 }
 
  void SettingsDialog:: setInner(){
	 
	}
	
 void SettingsDialog:: save(){
	 
     settings.beginGroup("Colors");
     settings.setValue("pen", ui.penPB->palette().background().color());
     settings.setValue("brush",ui.brushPB->palette().background().color());
	 //settings.setValue("brush Color",ui.texturePB->palette().background().color());
	 settings.endGroup();
	 
	 settings.beginGroup("Fonts");
	 settings.setValue("Font", ui.fontCB->currentFont());
	 settings.setValue("Index", ui.fontCB-> currentIndex () );
     settings.setValue("Size",5);
     settings.endGroup();
	 close ();
	}
	
	
 void SettingsDialog:: loadSettings(){
	
	 ui.penPB->setPalette(QPalette( settings.value("Colors/pen").value<QColor>()));
	 ui.brushPB->setPalette(QPalette( settings.value("Colors/brush").value<QColor>()));

	 ui.fontSizeSpin->setValue(settings.value("Fonts/Size").toInt());
	 ui.fontCB->setCurrentIndex(settings.value("Fonts/Index").toInt());
	 QFont font = settings.value("Fonts/Size").value<QFont>();
	 }
	 
	 
   
 void SettingsDialog::setPenColor(){
	 QColor color = QColorDialog::getColor(ui.penPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
		 ///How to make it work§
	 ///sender ()->setPalette(QPalette(color)); 
	 ui.penPB->setPalette(QPalette(color)); 
     }
	}
   
   void SettingsDialog::setBrushColor(){
	 QColor color = QColorDialog::getColor(ui.brushPB->palette().color(QPalette::Active,QPalette::Window), this);
     if (color.isValid()) {
		 ///How to make it workÂ§
	 ///sender ()->setPalette(QPalette(color)); 
	 ui.brushPB->setPalette(QPalette(color)); 
     }
	}
   
   void Sheet::timerEvent(QTimerEvent *event)
 { 
     if (event->timerId() == timer.timerId()) {
         
		 if (currentLoop == piece->bestRoute.size()) {
			 qDebug()<<"Stoping the animation";
			 //toolPix->setPos(absoluteHome);
			 removeItem(&toolLine);
			 removeItem(toolPix);			 
			 currentLoop=0;
			 timer.stop();
			}
		 else {
			 qDebug()<<"timer trigger";
			 endPoint=piece->bestRoute.at(currentLoop);
			
				 toolLine.setLine( QLineF(homePoint,endPoint));				 
				 toolLine.setPen(toolPen);
				 ///as tooline is already inserted Qt gives us an info message				 
				 addItem(&toolLine);
			 //loadingBar->setValue(currentLoop);
			 emit progressionDone(currentLoop);
			 moveTool(endPoint);
			 currentLoop++;
			}
		 
     } else {
         /// deal with other event...this way it will make it's way and propagate
		 qDebug()<<"other timer";
		 event->ignore();
     }
	 
	}
   

   
   void Sheet::moveTool(QPointFWithParent endP){
	 
	 qDebug()<<"Moving to point "<<endP;
	 ///Fixme there's a crash in setPos when animating clearing then reanomating
	 toolPix->setPos(endP);
	 ///To ensure that we start at the core'ct position when going to the next part
	 homePoint=endP;
	}

	 
   void MainWindow::stepByStep (){
     qDebug()<<"begin step";
	 currentLoop=0;
	 if (previewScene->timer.isActive()){
		 previewScene->timer.stop();
		}
	 else{
		 //if (toolPix==0){
			qDebug()<<"adding tool pix";
			toolPix=previewScene->addPixmap(QPixmap("/home/invite/Desktop/bazar/PFE/camnest/tool.png"));
			//}
			///to guarantee that the tool is on top
		 toolPix->setZValue(1);
		 toolLine.setZValue(1);
		 toolPix->setPos(absoluteHome);
		 homePoint=absoluteHome;
		 loadingBar->setRange(0,piece->bestRoute.size()-1);
		 previewScene->timer.start(400, previewScene);
		}
	}

  
  void MainWindow::openFile(){
     
	 openPart(QFileDialog::getOpenFileName(0,"Find Files", "/media/donnees/SL+TN","DXF Files (*.dxf)"));
   
   }
   
    void MainWindow::openPart(QString file) {
     
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

		 previewScene->clear();
		 piece=new Part(creationClass->partPath,creationClass->partPath.boundingRect(),creationClass->pointsPathList,creationClass->partPathsList,creationClass->pointsCircleList,creationClass->circlePathsList);//, previewScene-> views().at(0));
		 ///connect(piece,SIGNAL(progressionStep( int )),this,SLOT(progressionDone(int)));
		 previewScene->addItem(piece);
		 qDebug() << "Showing part preview";
		 previewScene-> zoomFit();
		 ///insertedParts=previewScene->items().size();//// FIXMEne marche plus lorsqu'on add le ttolPix
		 
		 trigActions(true);

		}
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
	 
	 qDebug()<<"Writing the Gcode of "<<parts.size()<<"parts";
	 for (int j=0; j<parts.size();j++){	
		 qDebug()<<"Writing the Gcode of part"<< j<<"containing"<<parts.at(j)->gCodePointsTrans.size()<<"loops";
		  partGCode.comment("Starting a new part");
		 for (int i=0; i < parts.at(j)->gCodePointsTrans.size();i++){
			 partGCode.comment("Adding a Loop");
			 partGCode.comment("Turnin off torch");
			 partGCode.comment("Going to Z home");
			 ///Importnat:FIXME For open path not to be generated 2 times  we have to skip items of the same Parent Loop
		  	 partGCode.writeClosedLoop( parts.at(j)->gCodePointsTrans.at(i));
		}	 
	 }	
	 partGCode.writeEnd();
	 statusBar()->showMessage(tr("File saved"),4000);
	 return true;
	}
 


    void MainWindow::clearScene() {
	 ///todo: add a warning Yes/no
	 
	
	 ///FIXME: crashes
	 if (scene->timer.isActive()) scene->timer.stop();
	 //endPointslist.clear ();	 	 
	 ///FXIXME : produces a crash
	 scene->clear();
	 previewScene->clear();	 
	 parts.clear();
	  
	 insertedParts=0;
	 nbrParts=0;
	 trigActions(false);
	
	 statusBar()->showMessage(tr("Emptied Scene"));
	}
	
void Sheet::zoomFit(){
	 views().at(0)->fitInView(itemsBoundingRect(),Qt::KeepAspectRatio);
 }
	
	
	 void MainWindow::zoomFit() {
	 previewScene-> zoomFit();
	 scene-> zoomFit();
     statusBar()->showMessage(tr("Zoomed"));
	}	
	
	///The default mouse move event on diagScene handle a one by one item move. To move mutiple items
	/// we implment outr own one.
	
	void Sheet::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 if ((selectedItems()).size()==1){
		 QGraphicsScene::mouseMoveEvent(mouseEvent);
		}
	else if((selectedItems()).size()>1){
		 qDebug()<<"moving multi items";
		 foreach ( QGraphicsItem *item ,selectedItems()){			  
			 qgraphicsitem_cast<Part *>(item)->moveMeBy(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
			}
		 
		}
	}
	
	
    /**The default implementation handles basic item interaction, such as selection and moving.
	We have to draw each part separately as a QGraphicsItem
	*/
	

	void Sheet::wheelEvent(QGraphicsSceneWheelEvent *mouseEvent)    {
	 //if(mouseEvent->modifiers()==Qt::ControlModifier){

	 qreal scaleFactor=pow((double)2, -mouseEvent->delta() / 240.0);
		  qreal factor =views().at(0)->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
     if (factor < 0.07 || factor > 10)
         return;

     views().at(0)->scale(scaleFactor, scaleFactor);
	 views().at(0)->centerOn(mouseEvent->scenePos());
		/// mWhy do we need theset Accepted???ouseEvent->setAccepted(true);=> to avoid propagating event²
		return;
}
 
     void MainWindow::rotateParts() {
	 if (scene->selectedItems().size()!=0) { 
		 QPointF center;
	 	 foreach (QGraphicsItem *item, scene->selectedItems()) {
	 		 center=item->boundingRect().center();
			 /// Add an input box visible when rotation is desired
			 item->rotate(90);
			 ///item->setTransform(QTransform().translate(center.x(),center.y()).rotate(90).translate(-center.x(),-center.y()),true);
			 statusBar()->showMessage(tr("Rotated"));
	 		}
	 	}
		else{
		  statusBar()->showMessage(tr("Please make a selection"));
		}
	}
 
 
  void MainWindow::deleteItems(){
	 int nbr=scene->selectedItems().size();
     if  (nbr!=0) {
		 foreach (QGraphicsItem *item, scene->selectedItems()) {
			 scene->removeItem(item);
			 ///FIXME have also to remove the item from the list using DATA to track it ;)
			 ///We search for parts with the corresponding DATA and remove them from the parts list
			 
			 ///NOTE:We cant' simply use:	 parts.removeAt(item->data(0)); as it isn't ordered
			 for (int i=0; i <parts.size();i++){
				 if (parts.at(i)->data(0)==item->data(0)){
					 ///Shouldn't update size??
					 parts.removeAt(i);
					}
				}
			}	
		 statusBar()->showMessage(tr("Removed "));
		 if (nbr==nbrParts){
			 clearAction->setEnabled(false);
			 saveAction->setEnabled(false);	
			 	 
			}
		}
	 else {
		 statusBar()->showMessage(tr("No item selected "));
		}
	 nbrParts-=nbr;
	 
	 qDebug()<<nbrParts<<" parts remains";
    }
 
 void MainWindow::createStatusBar() {
     statusBar()->showMessage(tr("Ready"));
	
    }

	
	/** WE HAVE TO STORE THE LAST INSERTED PART COORDINATE + ITS4S RECT BOUND TO PLACE THE NEXT PART
	 THERE  unsless we bypass the scene widt/heitght.Then we copy the part in the previewScene and place it 
	 in the lastpoint if it's boundRect allows it.
	
	*/
	 void MainWindow::insert() {
	 /// TODO: ALlow only one part to be inserted in the previewScene
	 /// we cretae a copy of the currently (previewed)displayed part and append it to th epart list.
	 piece->setData(0,insertedParts);
	 qDebug() <<insertedParts <<"Parts in the scene";
	 insertedParts++;nbrParts++;
	 parts.append(piece->copy());
	 scene->addItem(parts.last());
	 //qDebug()<<piece->data(0);
	 /// we check for th eposition where we'll place our part we put the part on the lower left rect poit
	 //if (lastPart.
	 
	 ///we stil have horizontal space to fill
	 //else {
		 
		// lastPartPos
		//}
     statusBar()->showMessage(tr("Part inserted"));
    }
	
	void MainWindow::optimize(){
	 /// replaces the points list with the previously created one (inspired from genetic algo)
	 piece->clearText();
	 piece->optimize();	 
	}

	void MainWindow::openSelected(const QModelIndex & index){
	 //qDebug()<<"selection changed"<<index.data();
	 if (model->isDir(index)) {
		  tree->setRootIndex(index);
		 qDebug()<<"going to dir "<<model->filePath(index);
		 }
	 else {
		 openPart(model->filePath(index));
		 qDebug()<<"Opening file "<<model->filePath(index);
		 }
	}
 
 
 void MainWindow::createToolBars(){
	 fileToolBar = addToolBar(tr("File"));
     fileToolBar->addAction(openAction);
	 
     editToolBar = addToolBar(tr("Edit"));
     editToolBar->addAction(clearAction);
	editToolBar->addAction(previewDockAction);
	 editToolBar->addAction(rotateAction);
	 editToolBar->addAction(saveAction);
	 editToolBar->addAction(stepAction);	
	 editToolBar->addAction(zoomFitAction);
	 editToolBar->addAction(deleteAction);
	 editToolBar->addAction(optimizeAction);
	  editToolBar->addAction(insertAction);
	 
	 
	 trigActions(false);
	//editToolBar = addToolBar(tr("Edit"));
	}
	 
 void MainWindow::trigActions (bool status) {
	 clearAction->setEnabled(status);
	 saveAction->setEnabled(status);
	 stepAction->setEnabled(status);
	 optimizeAction->setEnabled(status);
	 deleteAction->setEnabled(status);
	 rotateAction->setEnabled(status);
	 zoomFitAction->setEnabled(status);
	 insertAction->setEnabled(status);
	}
	 
	 void MainWindow::createDockWindows(){
	
     dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     addDockWidget(Qt::LeftDockWidgetArea, dock);

	 previewSheet->setMinimumSize(250,250);
	 previewSheet->resize(300,300);
	 previewSheet->setMaximumSize(400,300);
	 previewSheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 previewSheet->setDragMode(QGraphicsView::RubberBandDrag);
	 

	 model->setSorting(QDir::Type);

	 model->setFilter(QDir::AllDirs | QDir::Files);
	 model->setNameFilters (QStringList()<<"*.dxf");
     tree->setModel(model);	 
	 tree->setViewMode(QListView::ListMode);
	  ///make it an option..
     ///tree->setViewMode(QListView::IconMode);
     tree->show();
	 
     tree->setRootIndex(model->index(settings.value("MainWindow/Dir").toString()));
	 
	 //loadingBar->setMinimumSize(200,20);
	 //loadingBar->resize(250,20);
	 loadingBar->setMaximumSize(450,30);
	 
	
	 horSplitter->setOrientation(Qt::Vertical);
	 horSplitter->addWidget(tree);
	 horSplitter->addWidget(previewSheet);
	 /// we always show the previewWindow
	 horSplitter->setCollapsible (1,false);
	 
	 //horSplitter->setGeometry(20, 60, 200, 200);
	 
	 horSplitter->addWidget(loadingBar);
	 dock->setWidget(horSplitter);
	 }
	 
 void MainWindow::progressionDone(int currentLoop){
	 loadingBar->setValue(currentLoop);
	 
	}
	 
 void MainWindow::showSettings(){
	 
	 settingsDlg.show();
	 
	}
	
	 void MainWindow::writeSettings()
 {
     //QSettings settings("camnest", "camnest");

     settings.beginGroup("MainWindow");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
	 settings.setValue("dir", model->filePath(tree->currentIndex()));
     settings.endGroup();
 }

 void MainWindow::readSettings(){     

     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
     settings.endGroup();
	 }
	

	 
	  void MainWindow::descStep( const QString desc) {
	  statusBar()->showMessage(desc);
	  }
	 
	 
 void MainWindow::closeEvent(QCloseEvent *event){
     if (maybeSave()) {
         writeSettings();
         event->accept();
		} 
	 else {
         event->ignore();
		}
	}
	 
	 
	 bool MainWindow::maybeSave(){
     
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Application"),tr("Do you really want to quit?"),QMessageBox::Yes | QMessageBox::Cancel);
         ///if (ret == QMessageBox::Save)
             ///return save();
         if (ret == QMessageBox::Cancel)
             return false;
		   else  return true;
 }
	 
  void MainWindow::createActions(){
	 
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
	 	
	 optimizeAction= new QAction(tr("&Optimize"), this);
	 optimizeAction->setShortcut(tr("Ctrl+Z"));
	 insertAction= new QAction(tr("&Insert"), this);
	 insertAction->setShortcut(tr("Ctrl+I"));
	 deleteAction= new QAction(tr("&Delete"), this);
	 deleteAction->setShortcut(tr("Ctrl+D"));
	 zoomFitAction = new QAction(tr("&Zoom Fit"), this);
	 zoomFitAction->setShortcut(tr("Ctrl+F"));
	 rotateAction = new QAction(tr("&Rotate"), this);
	 rotateAction->setShortcut(tr("Ctrl+R"));
	 
	 settingsAction = new QAction(tr("&settingsDlg"), this);
	 settingsAction->setShortcut(tr("Ctrl+t"));
	 
	 
	}
  
  
  void MainWindow::createConnections(){
	 /// connecting the signals
	 connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));  
	 connect(openAction, SIGNAL(triggered()),this, SLOT(openFile())); 
	 connect(clearAction, SIGNAL(triggered()),this, SLOT(clearScene())); 
	 connect(stepAction, SIGNAL(triggered()),this, SLOT( stepByStep())); 
	 connect(rotateAction, SIGNAL(triggered()),this, SLOT(rotateParts())); 
	 
	 connect(settingsAction, SIGNAL(triggered()),this, SLOT(showSettings()));
	 
	 connect(zoomFitAction, SIGNAL(triggered()),this, SLOT(zoomFit())); 
	 connect(saveAction, SIGNAL(triggered()),this, SLOT( saveFile())); 
     connect(deleteAction, SIGNAL(triggered()),this, SLOT( deleteItems())); 
     connect(optimizeAction, SIGNAL(triggered()),this, SLOT( optimize()));
	 connect(insertAction, SIGNAL(triggered()),this, SLOT( insert()));
	}
  
   void MainWindow::createMenus() {
	 fileMenu = menuBar()->addMenu(tr("&File"));
	 fileMenu->addAction(openAction);
	 fileMenu->addAction(saveAction);
	 fileMenu->addAction(clearAction);
	 
	 fileMenu->addAction(settingsAction);
     fileMenu = menuBar()->addMenu(tr("&Help"));
	 fileMenu->addAction(aboutAction);//qDebug()<<subLoop.currentPosition();
	}
  
  MainWindow::MainWindow(){
     
	 createActions();
	 createConnections();
	
	 dock = new QDockWidget(tr("Preview"), this);
	 previewDockAction= dock->toggleViewAction ();
	 previewDockAction->setShortcut(tr("D"));
	 
	 
	 setWindowTitle(tr("CamNest"));
	 
	  /// setup theGUI
	 createMenus() ;
	 createStatusBar(); 
	 createToolBars();
	 ///there is no toColor(), toImage(), or toPixmap() functions in QVariant.
	 
	 
	 contourPen = QPen (Qt::red);
	 contourBrush = QBrush(Qt::cyan, Qt::SolidPattern);
	 readSettings();
	 

	 
	 qDebug()<< "Interface ready";
     /// create the view  in the mainWindow
	 /// resize to the sheet value
	 QRect previewRect(-400, -400, 800, 800); 
	 QRect sceneRect(-2000, -2000, 3600, 3600); 
     scene=new  Sheet ();
	 scene->setSceneRect(sceneRect);
	 previewScene=new  Sheet ();	  
	 previewScene->setSceneRect(previewRect);
	  
	 connect(previewScene,SIGNAL(progressionDone(const int )),this,SLOT(progressionDone(int)));
	 
	 //connect(piece,SIGNAL(descStep()),this,SLOT(descStep()));
	 ///testScene = new QGraphicsScene();
	 /// testScene->setSceneRect(sceneRect);
	  ///previewSheet= new  SheetMetal (previewScene);
	  ///previewSheet->setGeometry(20, 60, 600,600);
	  
     ///sheet= new  SheetMetal (scene);
	 ///sheet->setGeometry(670, 60, 600, 600);
	  
	 ///QHBoxLayout *layout = new QHBoxLayout;  
	  ///QGraphicsView *previewSheet = new QGraphicsView(testScene);
	  
	 previewSheet = new QGraphicsView(previewScene);
	 loadingBar=new QProgressBar();
	 horSplitter = new QSplitter(this);
	 model = new QDirModel;
	 tree = new QListView;
	 
	 connect(tree,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(openSelected(const QModelIndex &)));
	 
	 createDockWindows();
	 
	 
	 sheet = new QGraphicsView(scene);	 
	 setCentralWidget(sheet);
	 //QSplitter *verSplitter = new QSplitter(this);
	 //verSplitter->setGeometry(20, 60, 1000,600);
	 //verSplitter->addWidget(horSplitter);
	 //verSplitter->addWidget(sheet);
	  ///layout->addWidget(previewSheet);  
	 ///previewSheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	/// previewSheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	 ///sheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 ///sheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 sheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 sheet->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
	 sheet->setDragMode(QGraphicsView::RubberBandDrag);
      ///layout->addWidget(previewSheet);
	  ///layout->addWidget(sheet); 
	 /// QWidget *widget = new QWidget(this);
     ///widget->setLayout(layout);
	 ///widget->setGeometry(670, 60, 600, 600);
	 
	 ///setCentralWidget(widget);

	 // QGridLayout *mainLayout = new QGridLayout;
     //mainLayout->addWidget(test, 0, 0, 1, 4);
	 //QPushButton *quit = new QPushButton("Quit");
	 //mainLayout->addWidget(quit, 0, 0, 1, 4);
    ///setCentralWidget(previewSheet);
    }
     /*
   the seetMetal declarations
  */
   Sheet::Sheet (QWidget *parent):QGraphicsScene () {
	 toolPen = QPen  (Qt::blue,1, Qt::DotLine);
	}
	
 SheetMetal::SheetMetal(QGraphicsScene *scene,QWidget *parent): QWidget(parent)   {     
	 /// put the scen in the view
	 ///scene = new  Sheet (this);
	 ///QRect sceneRect(0,0,440,440);
	 //previewScene= new  Sheet (this);	 
     ///scene->setSceneRect(sceneRect);
	 //previewScene->setSceneRect(sceneRect);
	 QGraphicsView *view= new QGraphicsView (scene,this);   
	 view->setCacheMode(QGraphicsView::CacheBackground);
	 view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 
	  //setViewportUpdateMode(BoundingRectViewportUpdate);
	 // pathview = new QGraphicsView (previewScene,this);  
	 //QPushButton *quit = new QPushButton("Quit",this);
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
 
 
 
	///todo : make changes to loop or not ? QPainterPath &myLoopPath
	void createLeads(QPainterPath myLoopPath,int loopPos){
	 
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
		scene->addLine(QLineF(leadPoint,startPoint));
		//(scene->addPixmap(QPixmap("/home/invite/Desktop/bazar/PFE/camnest/hole.png"))->setPos(leadPoint));
	 /// Now check for intersects()
	 /**bool QPainterPath::contains ( const QPointF & point ) const
Returns true if the given point is inside the path, otherwise returns false.**/	
	}
	
	
		 /** the lead-in distance is a constant, it's the angle that varies to avoid intersection with other
	 shapes */

	
	void drawArc(QPointFWithParent point,QPainterPath &pathToModify) {
	 
	 pathToModify.arcTo(QRectF(point.centerX-point.parentRadius,point.centerY-point.parentRadius,2*point.parentRadius,2*point.parentRadius),-( point.angle1),-fabs( point.angle1- point.angle2));	 
	 
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
	 
	 

 