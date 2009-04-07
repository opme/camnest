 #include "sheet.h"
 #include "qpointfwithparent.h"
 #include "gcode.h"
 #include "gatsp.h"
 #include "leads.h"

 #define ARROW_LENGHT 10
#include <QGLWidget>
 /// FIXME: In step loop there 's a reptition of loops in part tspOp.dxf
 
 /// @todo: use the genetic algo for a simple nesting algorithm!!
 
	 QPen myPen;
	 QBrush myBrush;
	 QPalette infoText (Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black);
	 QPalette  errorText(Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red);
	 QPalette successText (Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue);
	 DL_Dxf* dxf;
	 Test_CreationClass* creationClass;
	 /// represent the QGraphicsViews containing the scenes
	 Sheet *scene;
	 Sheet *previewScene;	
	
	 QGraphicsPixmapItem *toolPix;
	 QPointFWithParent endPoint;
	 QGraphicsLineItem toolLine;
	 
	 /// As the lead-points are independant from the part we create them on them own
	 Part *piece;
	 Lead *leadEllipse;
	  Lead *leadTouch;

	
 
	 /// weitherthere areseneted itmes or not
	 int selection_empty=1;
	 /// numberof selecteditems
	 int selected_nbr=0;
	 
	 bool PlasmaMode=true;

	 ///the parts appended to the sheetMetal
	 QList <Part *> parts;
	
	 ///havn't to be pointer reference as they entities are deleted after being read
	
	 int currentLoop=0;
    

	
///# used when drawing toolpath and for homing on G-code
	QPointF absoluteHome(0,0);
	QPointF homePoint(0,0);
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
         
		 if (currentLoop == piece->partLoops.size()) {
			 qDebug()<<"Stoping the animation";
			 //toolPix->setPos(absoluteHome);
			 removeItem(&toolLine);
			 removeItem(toolPix);			 
			 currentLoop=0;
			 timer.stop();
			}
		 else {
			 qDebug()<<"timer trigger";
			 endPoint=piece->partLoops.at(currentLoop)->startPoint;
			
				 toolLine.setLine( QLineF(homePoint,endPoint));				 
				 toolLine.setPen(toolPen);
				 ///as tooline is already inserted Qt gives us an info message				 
				 addItem(&toolLine);
			 //loadingBar->setValue(currentLoop);
			 emit progressionDone(currentLoop);
			 moveTool(endPoint);
			 piece->partLoops.at(currentLoop)->setVisible(true);
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
	 showPreviewDock();
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
		 loadingBar->setRange(0,piece->partLoops.size()-1);
		 foreach (Loop* cLoop, piece->partLoops){
			 cLoop->setVisible(false);
			}
		 previewScene->timer.start(400, previewScene);
		}
	}

  
  void MainWindow::openFile(){
     
	 openPart(QFileDialog::getOpenFileName(0,"Find Files", "/media/donnees/SL+TN","DXF Files (*.dxf)"));
   
   }
   
    void MainWindow::openPart(QString file) {
     
     if (file.isEmpty()) {
		
		 statusBar()->setPalette(errorText);
		 statusBar()->showMessage(tr("Please select a file to open"));
		 
		 return;
		}
	 else {
		 Test_CreationClass* creationClass = new Test_CreationClass();
		 DL_Dxf* dxf = new DL_Dxf();
		 
		 if (!dxf->in(file.toStdString(), creationClass)) { // if file open failed
			 qDebug() << "Could not open " << file;
			 statusBar()->setPalette(errorText);
			 statusBar()->showMessage(tr("Could not open the selected file"));
			 delete creationClass;
			 delete dxf;
			 return;
			}
		 else {
			 statusBar()->setPalette(successText);
			 statusBar()->showMessage(tr("File: ")+file);
			 qDebug() << "Reading file Done";
			}
		 if (creationClass->corrupted) {
			 statusBar()->setPalette(errorText);
			 statusBar()->showMessage(tr("Warning: The part contains Duplicate entities.It may be corrupted!"));
			 }
		 previewScene->clear();
		 ///@todo: copy the full file path but trim it on ther listView
		 QString partName=file.left((file.lastIndexOf(".")));
		 
		 qDebug()<<partName;
		 
		 
		 piece=new Part(creationClass->partPath,creationClass->pointsPathVector,creationClass->partPathsList,creationClass->pointsCircleVector,creationClass->circlePathsList);
		 piece->setPartName(partName);
		 ///Add little margin to show outline lead correctly
		 QRectF contRect=piece->boundingRect();
		 contRect.setHeight(contRect.height()+5);
		 contRect.setWidth(contRect.width()+5);
		 previewSheet->setSceneRect(contRect);
		 previewScene->addItem(piece);
		 ///connect((QObject*)piece,SIGNAL(progressionStep()),this,SLOT(progressionDone()));
		 previewScene-> zoomFit();
		 ///insertedParts=previewScene->items().size();//// FIXMEne marche plus lorsqu'on add le ttolPix		 
		 trigActions(true);
		}
	 delete creationClass;
	 delete dxf;
	}

	
	/** WE HAVE TO STORE THE LAST INSERTED PART COORDINATE + ITS4S RECT BOUND TO PLACE THE NEXT PART
	 THERE  unsless we bypass the scene widt/heitght.Then we copy the part in the previewScene and place it 
	 in the lastpoint if it's boundRect allows it.
	
	*/
	 void MainWindow::insert() {
	 /// TODO: ALlow only one part to be inserted in the previewScene
	 /// we cretae a copy of the currently (previewed)displayed part and append it to th epart list.
	 
	 qDebug() <<insertedParts <<"Parts in the scene";
	 insertedParts++;
	 nbrParts++;
	 parts.append(piece->copy());
	 QString name=parts.last()->partName;
	 name=name.right(name.size()-(name.lastIndexOf(QDir::separator())+1));
	 name+='('+QString("%1").arg(insertedParts)+')';
	 ///save the part number for deleting and list arrangign
	 parts.last()->setData(0,insertedParts);
	 ///save the part name and number between paranthese which will be used for tracking part in @see partsModel
	 parts.last()->setData(1,name);
	 ///finally add the part to the scen a nd to parts list dock
	 scene->addItem(parts.last());
	 scene-> zoomFit();
	 ///@fixme have to call list instead of model directly
	 partsModel->insertRow(partsModel->rowCount(),partsModel->index(1));
	 partsModel->setData(partsModel->index(partsModel->rowCount()-1),name);
	 statusBar()->setPalette(successText);
     statusBar()->showMessage(tr("Inserted ")+name);
	 if (nbrParts!=0){
			 clearAction->setEnabled(true);
			 saveAction->setEnabled(true);				 	 
			}
    }
 
 ///@todo: to keep the list sync with deleted items have to reorder parts numbers...
  void MainWindow::deleteItems(){
	 int nbr=scene->selectedItems().size();
     if  (nbr!=0) {
		 foreach (QGraphicsItem *item, scene->selectedItems()) {
			 ///@todo: see in Qt code if the item is also deleted !
			 ///FIXME have also to remove the item from the list using DATA to track it ;)
			 ///We search for parts with the corresponding DATA and remove them from the parts list			 
			 ///NOTE:We cant' simply use:	 parts.removeAt(item->data(0)); as it isn't ordered
			 for (int i=0; i <parts.size();i++){
				 if (parts.at(i)->data(0)==item->data(0)){
					 ///@fixme have to call list instead of model deirectly
					 if (!partsModel->removePart(parts.at(i)->data(1))){
					 	qDebug()<<"could not remove from list";
						}
					
					 ///Shouldn't update size??
					 parts.removeAt(i);	
					}
				}
			 scene->removeItem(item);
			}	
		 statusBar()->setPalette(successText);
		 statusBar()->showMessage(QString("%1").arg(nbr)+tr(" parts removed"));
		 //statusBar()->showMessage(tr("Removed"));
		 
		}
	 else {
		 statusBar()->setPalette(errorText);
		 statusBar()->showMessage(tr("No item selected "));
		}
	 nbrParts-=nbr;
	 if (nbrParts==0){
			 clearAction->setEnabled(false);
			 saveAction->setEnabled(false);				 	 
			}
	 qDebug()<<nbrParts<<" parts remains";
    }
	

 bool MainWindow::saveGCode() {
	
	 QString fileName (QFileDialog::getSaveFileName(this, tr("Save File"),parts.at(0)->partName+".nc",tr("Gcode Files (*.nc)")));
	 QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("CamNest"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
         return false;
		}
	 /// Create the Gcode File
	 GCode partGCode (& file);
	 partGCode.writeHeader(fileName);
	
	 qDebug()<<"Writing the Gcode of "<<parts.size()<<"parts";
	 for (int j=0; j<parts.size();j++){	
		 ///qDebug()<<"Part endPoints"<<parts.at(j)->endPointslist;
		 ///qDebug()<<"Part leads"<<parts.at(j)->leadsPoints;
		 //qDebug()<<"Writing the Gcode of part"<< j+1<<"containing"<<parts.at(j)->gCodeEntitiesTrans.size()<<"loops";
		  partGCode.comment("*******Starting the G-code of part "+parts.at(j)->partName+"******");
		  partGCode.setTrans(parts.at(j)->transform);
		  
		  ///TODO: Create an overloded method partGCode.write(Part part);
		 for (int i=0; i < parts.at(j)->partLoops.size();i++){
			 
			 partGCode.comment("Adding a Loop");
			 ///partGCode.comment("Turnin off torch");
			 ///First we go to the lead-in Point
			 partGCode.comment("Going to lead-in point");
			 partGCode.comment("Going to Z home");
			 if (PlasmaMode){
				//partGCode.comment("Going to leadPoint");
				qDebug()<<"Going to leadPoint "<<parts.at(j)->gLeadPoints.at(i);//parts.at(j)->partLoops[i]->leadIn;
				//partGCode.rapidMove (parts.at(j)->partLoops[i]->leadIn);
				partGCode.rapidMove (parts.at(j)->gLeadPoints.at(i));
			 }
			 
			 ///Importnat:FIXME For open path not to be generated 2 times  we have to skip items of the same Parent Loop
			 ///@todo place here a check on ISCircle and in that case write directly the Circle Loop
			 qDebug()<<"Writing a closed loop";//<<currentloop->entities;
			 
			 partGCode.writeClosedLoop(parts.at(j)->gLoops.at(i));
		}	 
	 }	
	 partGCode.writeEnd();
	 statusBar()->setPalette(successText);
	 statusBar()->showMessage(tr("File Succefully saved!"),4000);
	 
	 return true;
	}
 
 
	void MainWindow::clearScene() {
	 ///if the user confirms clearing scene
	 if (!confirmAction()) { return;}
	
	 ///FIXME: crashes
	 if (scene->timer.isActive()) scene->timer.stop();
	 ///FXIXME : produces a crash
	 scene->clear();
	 //previewScene->clear();	 
	 parts.clear();	  
	 insertedParts=0;
	 nbrParts=0;
	 /// Disable action
	 trigActions(false);
	 statusBar()->setPalette(infoText);
	 statusBar()->showMessage(tr("Cleared Scene"));
	}
	
void Sheet::zoomFit(){
	 views().at(0)->fitInView(itemsBoundingRect(),Qt::KeepAspectRatio);
 }
	
	
	 void MainWindow::zoomFit() {
	 previewScene-> zoomFit();
	 scene-> zoomFit();
	 statusBar()->setPalette(infoText);
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
		/// foreach ( QGraphicsItem *item ,selectedItems()){			  
			/// qgraphicsitem_cast<Part *>(item)->moveMeBy(mouseEvent->scenePos().x(),mouseEvent->scenePos().y());
			///}
		 
		}
	}
	
	void Sheet::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	 QGraphicsScene::mouseReleaseEvent(mouseEvent);	
	}
 
	void Sheet::wheelEvent(QGraphicsSceneWheelEvent *mouseEvent)    {
	 /// @todo: add option to change modifier key to activate zoom
	 if(mouseEvent->modifiers()==Qt::ControlModifier){

	 qreal scaleFactor=pow((double)2, -mouseEvent->delta() / 240.0);
		  qreal factor =views().at(0)->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
     if (factor < 0.07 || factor > 10)
         return;

     views().at(0)->scale(scaleFactor, scaleFactor);
	 views().at(0)->centerOn(mouseEvent->scenePos());
	 ///necerrary to avoid  propagating event to child items although no mouse whell is implmenton parts for now...
	 mouseEvent->setAccepted(true);
		return;
	 }
}
 
     void MainWindow::rotateParts(int angle) {
	 ///@todo: add rotate by specified angle
	 if (scene->selectedItems().size()!=0) { 
		 QPointF center;
	 	 foreach (QGraphicsItem *item, scene->selectedItems()) {
	 		 center=item->boundingRect().center();
			 /// Add an input box visible when rotation is desired
			 item->setTransform(QTransform().translate(center.x(),center.y()).rotate(angle).translate(-center.x(),-center.y()),true);
			 statusBar()->setPalette(infoText);
			 statusBar()->showMessage(tr("Rotated"));
	 		}
	 	}
		else{
			 statusBar()->setPalette(errorText);
			 statusBar()->showMessage(tr("Please make a selection"));
		}
	}
 
 
 
 void MainWindow::createStatusBar() {
	 statusBar()->setPalette(infoText);
     statusBar()->showMessage(tr("Welcome to Camnest"));	
    }

	
	
	void MainWindow::optimize(){
	 /// replaces the points list with the previously created one (inspired from genetic algo)
	 piece->optimizeRoute();	 
	}

	void MainWindow::showPart(const QModelIndex & index){
	
	if (index.isValid()) {
		 //qDebug()<<"Showing part "<<partsModel->data(index,Qt::DisplayRole).toString();
		for (int i=0; i <parts.size();i++){
			 ///unselect all other parts first
			 parts.at(i)->setSelected(false);
				 if (parts.at(i)->data(1)==partsModel->data(index,Qt::DisplayRole).toString()){
					 parts.at(i)->setSelected(true);
					}
			}
		} 
	}
	
	void MainWindow::openSelected(const QModelIndex & index){
	 //qDebug()<<"selection changed"<<index.data();
	 
	 showPreviewDock();
	 if (model->isDir(index)) {
		  tree->setRootIndex(index);
		 qDebug()<<"going to dir "<<model->filePath(index);
		 }
	 else {
		 openPart(model->filePath(index));
		 qDebug()<<"Opening file "<<model->filePath(index);
		 }
	}
	 
	 void MainWindow::createDockWindows(){
	 QSplitter *previewHS= new QSplitter(this);
	
	 
	 ///Start Preview Dock organisation
	 dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     addDockWidget(Qt::LeftDockWidgetArea, dock);
	 
	 /// PreviewSheet sizeHint
	 previewSheet->setMinimumSize(200,200);
	 previewSheet->resize(300,300);
	 previewSheet->setMaximumSize(1000,1000);
	 

	 model->setSorting(QDir::Type);
	 model->setFilter(QDir::AllDirs | QDir::Files);
	 model->setNameFilters (QStringList()<<"*.dxf");
     tree->setModel(model);	 
	 tree->setViewMode(QListView::ListMode);
	  ///make it an option..
     ///tree->setViewMode(QListView::IconMode);
     tree->show();	 
     tree->setRootIndex(model->index(settings.value("MainWindow/Dir").toString()));
	
	 
	 //parts << "piece"<<"2";
	 partsModel= new PartsListModel(partsNames);
	 //loadingBar->setMinimumSize(200,20);
	 //loadingBar->resize(250,20);
	 loadingBar->setMaximumSize(450,30);
	 
	
	 previewHS->setOrientation(Qt::Vertical);
	 previewHS->addWidget(previewSheet);
	 /// we always show the previewWindow
	 previewHS->setCollapsible (0,false);
	 previewHS->addWidget(loadingBar);
	 //previewHS->setGeometry(20, 60, 200, 200);
	 
	 dock->setWidget(previewHS);
	 
	  ///Start Preview Dock organisation
	  // QSplitter *InsertedPartsHS= new QSplitter(this);
	 //InsertedPartsHS->setOrientation(Qt::Vertical);
	 //InsertedPartsHS->addWidget(tree);
	 //InsertedPartsHS->setCollapsible (0,false);	 
	 
	 piecesList->setModel(partsModel);
	 dockInsertedParts->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	 filesListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	 ///dockInsertedParts->setWidget(tree);
	 dockInsertedParts->setWidget(piecesList);
	 filesListDock->setWidget(tree);
	 filesListDock->resize(QSize(400, 400));
	 addDockWidget(Qt::LeftDockWidgetArea, filesListDock); 
     addDockWidget(Qt::LeftDockWidgetArea, dockInsertedParts); 
	 
	 
	 }
	 
	 int PartsListModel::rowCount(const QModelIndex &parent) const {
     return stringList.count();
	}
	 
	QVariant PartsListModel::data(const QModelIndex &index, int role) const {
     if (!index.isValid())
         return QVariant();
     if (index.row() >= stringList.size())
         return QVariant();
     if (role == Qt::DisplayRole)
         return stringList.at(index.row());
     else
         return QVariant();
	}
	
	bool PartsListModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.insert(position, "");
     }

     endInsertRows();
     return true;
 }
 	///@fixme make this inside listView and not Model
 	bool PartsListModel::removePart(QVariant partStr){
	for (int row = 0; row < rowCount(); ++row) {
	//qDebug()<<data(index(row),0);
		if (data(index(row),0)==partStr) {
			qDebug()<<"removing part at index "<<row;
			return removeRows(row,1);
			}
		}
	 return false;
	}
 
	bool PartsListModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row = 0; row < rows; ++row) {
         stringList.removeAt(position);
     }

     endRemoveRows();
     return true;
 }
	
	//Qt::ItemFlags PartsListModel::flags(const QModelIndex &index) const {
    // if (!index.isValid())     return Qt::ItemIsEnabled;
    // return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	//}
	
	
	bool PartsListModel::setData(const QModelIndex &index,const QVariant &value, int role){
	qDebug()<<index<<value;
     if (index.isValid() && role == Qt::EditRole) {
         stringList.replace(index.row(), value.toString());
         emit dataChanged(index, index);
         return true;
     }
	 else {
		 qDebug()<<"invalid index";
		 return false;
		}
	}
	
	
 void MainWindow::progressionDone(int currentLoop){
	 loadingBar->setValue(currentLoop);
	 
	}
	 
 void MainWindow::showSettings(){
	 settingsDlg.setObjectName("setting_dialog");
	 ///move the setting dialog to main window center
	 settingsDlg.move(geometry().center().x()-settingsDlg.width()/2,geometry().center().y()-settingsDlg.height()/2);
	 settingsDlg.show();
	 
	}
	
	 void MainWindow::writeSettings()
 {
     //QSettings settings("camnest", "camnest");

     settings.beginGroup("MainWindow");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
	 ///save the window state
	 settings.setValue("state",saveState(0));
	 
	 QString filesDir=model->filePath(tree->currentIndex());	 
	 filesDir.chop(filesDir.size()-(filesDir.lastIndexOf(QDir::separator()))-1);
	 /// have to keep the older folder value 
	 if (filesDir!="") 	 settings.setValue("dir", filesDir);
     settings.endGroup();
	 
	 //settings.beginGroup("Docks");
	 // settings.setValue("previewPos",dockWidgetArea(dock));
	 //settings.setValue("previewSize", dock->size());
	 // settings.endGroup();
 }

 void MainWindow::readSettings(){     
	///@todo use default geometry constarin
		
     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());     
	 ///restore dock and toolbars positions
	 restoreState(settings.value("state").toByteArray(),0);
	 settings.endGroup();
	
	 
	 if(settings.value("Colors/openGl", false).toBool()){
	  previewSheet->setViewport( new QGLWidget() );
	  }
	  
	 switch (settings.value("Colors/openGl", 1).toInt()){
		 case 1 :
		 previewSheet->setRenderHints(QPainter::Antialiasing );
		 break;
		 case 2 : 
		 previewSheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		 break;
		 case 3 : 
		 previewSheet->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		 case 4 : 
		 previewSheet->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing| QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		 break;
		 default:
		 previewSheet->setRenderHints(QPainter::Antialiasing );
		}
	 
	 previewSheet->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	  contourPen = QPen (Qt::red);
	  contourBrush = QBrush(Qt::cyan, Qt::SolidPattern);
	  myPen =QPen (settings.value("Colors/brush").value<QColor>());
	  myBrush=QBrush (settings.value("Colors/pen").value<QColor>());

	
	 
	 }
	

	 
	  void MainWindow::descStep( const QString desc) {
	  statusBar()->showMessage(desc);
	  }
	 
	 
 void MainWindow::closeEvent(QCloseEvent *event){
     ///if (confirmAction()) {
         writeSettings();
         event->accept();
		///} 
	 ///else {
        /// event->ignore();
		///}
	}
	 
	 
 bool MainWindow::confirmAction(){     
	 QMessageBox::StandardButton ret;
	 /// @todo: add parametre string to change confirm string
     ret = QMessageBox::warning(this, tr("Confirmation"),tr("Are you sure?"),QMessageBox::Yes | QMessageBox::Cancel);
	 if (ret == QMessageBox::Cancel) {
         return false;
		}
	 else {
		 return true;
		}
 }
	
  /// Actions have to be first declared before setting the menus	
  void MainWindow::createActions(){
	///@todo: add what's this hints
	 aboutAction = new QAction(tr("&About"), this);
	 aboutAction->setShortcut(tr("Ctrl+B"));
     openAction = new QAction(tr("&Open"), this);
	 openAction->setShortcut(tr("Ctrl+O"));
	 saveAction = new QAction(tr("&Save"), this);
	 saveAction->setShortcut(tr("Ctrl+S"));
	 //saveAction->setToolTip(tr("Save the G code"));
	 saveAction->setWhatsThis(tr("Save the scene to a G-code file"));
	 
	 clearAction = new QAction(tr("&Clear"), this);
	 clearAction->setShortcut(tr("Ctrl+C"));
	 clearAction->setWhatsThis(tr("Remove all parts from the scene."));
	 
	 stepAction = new QAction(tr("&Animate"), this);
	 stepAction->setShortcut(tr("Ctrl+A"));
	 	
	 optimizeAction= new QAction(tr("&Optimize"), this);
	 optimizeAction->setShortcut(tr("Ctrl+Z"));
	 
	 insertAction= new QAction(tr("&Insert"), this);
	 insertAction->setShortcut(tr("Ctrl+I"));
	 insertAction->setWhatsThis(tr("Insert the currently previewed part in the scene."));
	 
	 deleteAction= new QAction(tr("&Delete"), this);
	 deleteAction->setShortcut(Qt::Key_Delete);
	 
	 zoomFitAction = new QAction(tr("&Zoom Fit"), this);
	 zoomFitAction->setShortcut(tr("Ctrl+F"));
	 
	 rotateAction = new QAction(tr("&Rotate"), this);
	 rotateAction->setShortcut(tr("Ctrl+R"));
	 
	 rotateByAction = new QAction(tr("&Rotate by..."), this);
	 rotateByAction->setShortcut(tr("Ctrl+B"));
	 
	 settingsAction = new QAction(tr("&Settings"), this);
	 settingsAction->setShortcut(tr("Ctrl+M"));
	 
	 littleHelpAction=QWhatsThis::createAction(this);
	}
  
  ///ensure to show the previewDock if inserted in a tab.
  void MainWindow::showPreviewDock(){
 	 dock->setVisible(true);
	 dock->raise();
	 dock->setFocus(Qt::OtherFocusReason);
	 }
	 
	  ///@todo: Use QResource to show icons next to strings
 void MainWindow::createToolBars(){
	 fileToolBar = addToolBar(tr("File"));
     fileToolBar->addAction(openAction);
	 fileToolBar->addAction(saveAction);
	 
	
     editToolBar = addToolBar(tr("Edit"));
	 editToolBar->addAction(insertAction);
	 editToolBar->addAction(rotateAction);
	 editToolBar->addAction(stepAction);	
	 editToolBar->addAction(zoomFitAction);
	 editToolBar->addAction(deleteAction);
	 ///editToolBar->addAction(optimizeAction);
	 editToolBar->addAction(clearAction);
	 

	 
	 docksToolBar = addToolBar(tr("Docks"));
	 docksToolBar->addAction(previewDockAction);
	 docksToolBar->addAction(insertedDockAction);
	 docksToolBar->addAction(filesDockAction);
	 docksToolBar->setOrientation(Qt::Horizontal);
	 
	 miscToolBar= addToolBar(tr("Misc."));
	  miscToolBar->addAction(settingsAction);
	 miscToolBar->addAction(littleHelpAction);
	 
	 trigActions(false);
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
	
  /// connecting the signals
  void MainWindow::createConnections(){
	 
	 connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));  
	 connect(openAction, SIGNAL(triggered()),this, SLOT(openFile())); 
	 connect(clearAction, SIGNAL(triggered()),this, SLOT(clearScene())); 
	 connect(stepAction, SIGNAL(triggered()),this, SLOT( stepByStep())); 
	 connect(rotateAction, SIGNAL(triggered()),this, SLOT(rotateParts())); 	
	 connect(rotateByAction, SIGNAL(triggered()),this, SLOT(setRotAngle())); 	
	 connect(settingsAction, SIGNAL(triggered()),this, SLOT(showSettings()));	 
	 connect(zoomFitAction, SIGNAL(triggered()),this, SLOT(zoomFit())); 
	 connect(saveAction, SIGNAL(triggered()),this, SLOT( saveGCode()));
     connect(deleteAction, SIGNAL(triggered()),this, SLOT( deleteItems())); 
     connect(optimizeAction, SIGNAL(triggered()),this, SLOT( optimize()));
	 connect(insertAction, SIGNAL(triggered()),this, SLOT( insert()));
	}
	
	
  void MainWindow::setRotAngle(){
	 bool ok;
	 int i=QInputDialog::getInteger(0,tr("Set rotation angle"),QString("Angle :"), 90, 0, 100, 1, &ok);
	 if (ok) rotateParts(i);
	}
  
   void MainWindow::createMenus() {
	 fileMenu = menuBar()->addMenu(tr("&File"));
	 fileMenu->addAction(openAction);
	 fileMenu->addAction(saveAction);
	 
	 
	 fileMenu = menuBar()->addMenu(tr("&Edit"));
	 fileMenu->addAction(insertAction);	
	 fileMenu->addAction(stepAction);	
	 fileMenu->addAction(zoomFitAction);
	 fileMenu->addAction(deleteAction);
	 fileMenu->addAction(rotateAction);
	 fileMenu->addAction(rotateByAction);
	 ///fileMenu->addAction(optimizeAction);
	 fileMenu->addAction(clearAction);
	 

	 
     fileMenu = menuBar()->addMenu(tr("&Help"));
	 fileMenu->addAction(aboutAction);//qDebug()<<subLoop.currentPosition();
	}
  
  MainWindow::MainWindow(){
     
	 createActions();
	 createConnections();
	
	 dock = new QDockWidget(tr("Preview"), this);
	 previewDockAction= dock->toggleViewAction ();
	 previewDockAction->setShortcut(tr("ctrl+P"));
	 
	 dockInsertedParts = new QDockWidget(tr("Parts List"), this);
	 insertedDockAction= dockInsertedParts->toggleViewAction ();
	 insertedDockAction->setShortcut(tr("ctrl+L"));
	 
	 filesListDock= new QDockWidget(tr("File View"), this);
	 filesDockAction= filesListDock->toggleViewAction ();
	 filesDockAction->setShortcut(tr("ctrl+V"));
	 
	 
	 setWindowTitle(tr("CamNest"));
	 
	  /// setup theGUI
	 createMenus() ;
	 createStatusBar(); 
	 createToolBars();
	 ///there is no toColor(), toImage(), or toPixmap() functions in QVariant.
	 
	 QRect previewRect(-400, -400, 800, 800); 
	 QRect sceneRect(-2000, -2000, 3600, 3600); 
     scene=new  Sheet ();
	 scene->setSceneRect(sceneRect);
	 
	 previewScene=new  Sheet ();	  
	 previewScene->setSceneRect(previewRect);
	
	 previewSheet = new QGraphicsView(previewScene);
	 sheet = new QGraphicsView(scene);
	 	 
	 qDebug()<< "Interface ready";
     /// create the view  in the mainWindow
	 /// resize to the sheet value
	
	
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
	  
	 nbrParts=0;
	 insertedParts=0;
	 
	 loadingBar=new QProgressBar();
	 model = new QDirModel;
	 tree = new QListView;
	 piecesList =new QListView;
	 
	 connect(tree,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(openSelected(const QModelIndex &)));
	 
	 //connect(this,partInserted(),test,dataChanged(index, index));
	 createDockWindows();
	 ///Connect the click signal to allow part highlighting on scene
	 connect(piecesList,SIGNAL(clicked(const QModelIndex &)),this,SLOT(showPart(const QModelIndex &)));
	 
	 ///setting objects names for save/restoreState
	 dock->setObjectName("previewDock");
	 filesListDock->setObjectName("filesListDock");
	 dockInsertedParts->setObjectName("dockInsertedParts");
	 
	 fileToolBar->setObjectName("fileToolBar");
	 docksToolBar->setObjectName("docksToolBar");
	 editToolBar->setObjectName("editToolBar");
	 miscToolBar->setObjectName("miscToolBar");
	 ///restore settings
	 readSettings();
		
	  /// ADD OPTION USE OPENGL
	 //sheet->setViewport( new QGLWidget());
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
	 previewSheet->setDragMode(QGraphicsView::RubberBandDrag);//->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
	 
	 sheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 ///@todo add selection mode in config dialog Qt::ContainsItemShape  Qt::IntersectsItemBoundingRect)
	 sheet->setRubberBandSelectionMode(Qt::IntersectsItemShape);
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
   Sheet::Sheet (QWidget *parent):QGraphicsScene (parent) {
	 
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
     return QSize(300, 300);
     }
	 
	 QSize SheetMetal::minimumSizeHint() 
 {
     return QSize(200, 150);
 }
 


 