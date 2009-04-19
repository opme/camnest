 #include "sheet.h"

//#include <QGLWidget>
 
 /// @todo: use the genetic algo for a simple nesting algorithm!!
 ///@todo change the name from camnest to ...

	 
	 /// As the lead-points are independant from the part we create them on them own
	 Part *piece;
	///@todo: get from settings dialog
	 bool PlasmaMode=true;

	 ///@todo: reassign the parts list to sheet metal scen and do the appropriate cha,ges
	 ///the parts appended to the sheetMetal
	 QList <Part *> parts;

  	
	 void MainWindow::nextPoint(int currentLoop){
	 ///check for animation end
	  if (currentLoop == piece->partLoops.size()) {
			 qDebug()<<"Stoping the animation";			 
			 ///Fixme use signals instead of direct access!
			  previewScene->cleanUpAnim(true);
			  previewScene->timer.stop();
                          trigActions(true);
			  stepAction->setText(tr("Animate"));	
			  return;
			} 
	 loadingBar->setValue(currentLoop);
	 previewScene->moveTool(piece->partLoops.at(currentLoop)->startPoint);
	 piece->partLoops.at(currentLoop)->setVisible(true);
	
	 
	}
	
	 ///@todo: rename button Animate to Stop and disable all other buttons
   void MainWindow::stepByStep (){
	 showPreviewDock();
	 
	 if (previewScene->timer.isActive()){
	 	 previewScene->cleanUpAnim(true);
		 previewScene->timer.stop();
		 ///remake items visible
		  foreach (Loop* cLoop, piece->partLoops){
			 cLoop->setVisible(true);
			}		 
		 ///@fixme connect timer end signal from preview scen to a slot that reEnable buttons
		trigActions(true);
		stepAction->setText(tr("Animate"));
		}
	 else{
		 ///@fixme have to disable everything or the application crashes=> disable listView and folderView
		 trigActions(false);
		 stepAction->setEnabled(true);
		 stepAction->setText(tr("STOP"));
		 qDebug()<<"Starting animation";	
		 loadingBar->setRange(0,piece->partLoops.size()-1);
		 foreach (Loop* cLoop, piece->partLoops){
			 cLoop->setVisible(false);
			}
		 previewScene->cleanUpAnim();
		 previewScene->timer.start(400, previewScene);
		}
	}

	 
	 
	 void MainWindow::zoomFit() {
	 ///@fixme: use signal /slots instead 
	 previewScene-> zoomFit();
	 scene-> zoomFit();
	 statusBar()->setPalette(infoText);
         statusBar()->showMessage(tr("Zoomed"));
	}	
	
  void MainWindow::zoomOut() {
	 ///@fixme: use signal /slots instead 
	 previewScene-> zoom(false);
	 statusBar()->setPalette(infoText);
         statusBar()->showMessage(tr("Zoomed"));
	}
  
  void MainWindow::zoomIn() {
	 ///@fixme: use signal /slots instead 
	 previewScene-> zoom(true);
	 statusBar()->setPalette(infoText);
         statusBar()->showMessage(tr("Zoomed"));
	}

      void MainWindow::setSelectionMode(bool mode){
          qDebug()<<"selection mode"<<mode;
          if (!mode){
         previewSheet->setDragMode(QGraphicsView::RubberBandDrag);
            }
          else{
            previewSheet->setDragMode(QGraphicsView::ScrollHandDrag);
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
        //@todo check for binary file with QFile
    //  else if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                 //statusBar()->setPalette(errorText);
                // statusBar()->showMessage(tr("Please choose a non binary file!"));
           // return;
               // }
	 else {
	 	///@note created pointers are automatically deleted on else barcket end
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
		 contRect.setHeight(contRect.height()+9);
		 contRect.setWidth(contRect.width()+9);
		 previewSheet->setSceneRect(contRect);
		 previewScene->addItem(piece);
		 
		 
		 ///connect((QObject*)piece,SIGNAL(progressionStep()),this,SLOT(progressionDone()));
		 previewScene-> zoomFit();
		 ///insertedParts=previewScene->items().size();//// FIXMEne marche plus lorsqu'on add le ttolPix		 
		 trigActions(true);
		}
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
	 parts.last()->setPos(scene->sheetRect->rect().topLeft());
	 ///finally add the part to the scen  putting it on the top left of the rectSheet and to parts list dock
	 (scene->addItem(parts.last()));
	 ///@fixme: use signal instead
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
 
 void  MainWindow::moveValSet (){
    scene->setFocus();
    }
 
        ///@todo see if movevalSet isn't sufficeinet ?
	 void  MainWindow::updateMoveVal(double val){	 
	 Part::setMovePartVal(val);	
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
 
	///@todo: have also to remove all the parts from part list
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
	 ///@todo: if a part is being preview enable the insert button
	 statusBar()->setPalette(infoText);
	 statusBar()->showMessage(tr("Cleared Scene"));
	}
		 
  void MainWindow::setRotAngle(){
	 bool ok;
	 int i=QInputDialog::getInteger(0,tr("Set rotation angle"),QString("Angle :"), 90, 0, 100, 1, &ok);
	 if (ok) rotateParts(i);
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
	 if (dirModel->isDir(index)) {
		  dirLisView->setRootIndex(index);
		 qDebug()<<"going to dir "<<dirModel->filePath(index);
		 }
	 else {
		 openPart(dirModel->filePath(index));
		 qDebug()<<"Opening file "<<dirModel->filePath(index);
		 }
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
	 
	 filesDir=dirModel->filePath(dirLisView->currentIndex());	 
	 filesDir.chop(filesDir.size()-(filesDir.lastIndexOf(QDir::separator()))-1);
	 /// have to keep the older folder value 
	 if (filesDir!="") 	 settings.setValue("dir", filesDir);
     	settings.endGroup();
	 
	 //settings.beginGroup("Docks");
	 // settings.setValue("previewPos",dockWidgetArea(previewDock));
	 //settings.setValue("previewSize", previewDock->size());
	 // settings.endGroup();
 }

 void MainWindow::readSettings(){     
	///@todo use default geometry constarin
		
     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());     
	 ///restore previewDock and toolbars positions
	 restoreState(settings.value("state").toByteArray(),0);
	 ///restore last directory
	 filesDir=(settings.value("dir","").toString());
	 settings.endGroup();
	
	 dirLisView->setRootIndex(dirModel->index(filesDir));//settings.value("MainWindow/Dir").toString()));
	
	 if(settings.value("Colors/openGl", false).toBool()){
	  ///previewSheet->setViewport( new QGLWidget() );
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
	
	 ///@note:there is no toColor(), toImage(), or toPixmap() functions in QVariant.
	  contourPen =QPen (settings.value("Colors/brush").value<QColor>());
	  contourBrush=QBrush (settings.value("Colors/pen").value<QColor>());

	///@todo: get from settings
	  infoText =QPalette(Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black);
	   errorText =QPalette(Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red);
	  successText  =QPalette(Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue);
	 
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
	
	
	///@todo : add a toolbar ontop of preview windows with: zoom in zoom out fit zoom buttons (tooltip to indicate that mouse wheel also works)
	 void MainWindow::createDockWindows(){
	 QSplitter *previewHS= new QSplitter(this);
	
	 loadingBar=new QProgressBar();
	 dirModel = new QDirModel;
	 dirLisView = new QListView;
	 piecesList =new QListView;
	 
	 
	 ///Start Preview Dock organisation
	 previewDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     	 addDockWidget(Qt::LeftDockWidgetArea, previewDock);
	 
	 /// PreviewSheet sizeHint
	 previewSheet->setMinimumSize(200,200);
	 previewSheet->resize(300,300);
	 previewSheet->setMaximumSize(1000,1000);
	 

	 dirModel->setSorting(QDir::Type);
	 dirModel->setFilter(QDir::AllDirs | QDir::Files);
	 dirModel->setNameFilters (QStringList()<<"*.dxf");
     	 dirLisView->setModel(dirModel);	 
	 dirLisView->setViewMode(QListView::ListMode);
	  ///make it an option..
     	 ///dirLisView->setViewMode(QListView::IconMode);
     	 dirLisView->show();	 
     	 
	 
	 partsModel= new PartsListModel(partsNames);
	 //loadingBar->setMinimumSize(200,20);
	 //loadingBar->resize(250,20);
	 loadingBar->setMaximumSize(450,30);
	 
	
	 previewHS->setOrientation(Qt::Vertical);

	 previewToolBar=new QToolBar(previewHS);
	 //previewToolBar->addAction(zoomFitAction);
	 previewToolBar->addAction(zoomOutAction);
	 previewToolBar->addAction(zoomInAction);
         previewToolBar->addAction(selectModeAction);
	 previewToolBar->setMaximumSize(450,30);
	 
	 previewHS->addWidget(previewSheet);
	 /// we always show the previewWindow
	 previewHS->setCollapsible (0,false);
	 previewHS->addWidget(loadingBar);
	 //previewHS->setGeometry(20, 60, 200, 200);
	 
	 previewDock->setWidget(previewHS);
	 
	  ///Start Preview Dock organisation
	  // QSplitter *InsertedPartsHS= new QSplitter(this);
	 //InsertedPartsHS->setOrientation(Qt::Vertical);
	 //InsertedPartsHS->addWidget(dirLisView);
	 //InsertedPartsHS->setCollapsible (0,false);	 
	 
	 piecesList->setModel(partsModel);
	 dockInsertedParts->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	 filesListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	 ///dockInsertedParts->setWidget(dirLisView);
	 dockInsertedParts->setWidget(piecesList);
	 filesListDock->setWidget(dirLisView);
	 filesListDock->resize(QSize(400, 400));
	 addDockWidget(Qt::LeftDockWidgetArea, filesListDock); 
     	 addDockWidget(Qt::LeftDockWidgetArea, dockInsertedParts); 	 
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
	 
	 zoomOutAction= new QAction(tr("Zoom &IN"), this);
	 zoomOutAction->setShortcut(tr("Ctrl+I"));
	 
	 zoomInAction=new QAction(tr("Zoom O&ut"), this);
	 zoomInAction->setShortcut(tr("Ctrl+U"));

         selectModeAction=new QAction(tr("Hand &Move"), this);
         selectModeAction->setShortcut(tr("Ctrl+M"));
         selectModeAction->setCheckable(true);

         littleHelpAction=QWhatsThis::createAction(this);
	}
  
  ///ensure to show the previewDock if inserted in a tab.
  void MainWindow::showPreviewDock(){
 	 previewDock->setVisible(true);
	 previewDock->raise();
	 previewDock->setFocus(Qt::OtherFocusReason);
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
	 

         ///add the spin box that set the move (left, right up , down) value and don't give it focus
	 stepValue= new QDoubleSpinBox();
         stepValue->setFocusPolicy ( Qt::NoFocus);
	 stepValue->setPrefix(tr("Move "));         
	 ///keep the part in touch with spinBox value change
         connect(stepValue, SIGNAL(valueChanged(double)),this, SLOT(updateMoveVal(double)));
         connect(stepValue, SIGNAL(editingFinished ()),this,SLOT(moveValSet()));
         miscToolBar->addWidget(stepValue);
	 
	 trigActions(false);
	}
	 
	 
 void MainWindow::trigActions (bool status) {
	 clearAction->setEnabled(status);
	 saveAction->setEnabled(status);
	 stepAction->setEnabled(status);
	 optimizeAction->setEnabled(status);
	 deleteAction->setEnabled(status);
	 rotateAction->setEnabled(status);
	 //zoomFitAction->setEnabled(status);
	 //zoomInAction->setEnabled(status);
	 //zoomOutAction->setEnabled(status);
	 insertAction->setEnabled(status);
	 rotateByAction->setEnabled(status);
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
         connect(&settingsDlg, SIGNAL(accepted()),this,SLOT(updateSettings()));

	 connect(zoomFitAction, SIGNAL(triggered()),this, SLOT(zoomFit())); 
         connect(saveAction, SIGNAL(triggered()),this, SLOT( saveGCode()));
    	 connect(deleteAction, SIGNAL(triggered()),this, SLOT( deleteItems())); 
     	 connect(optimizeAction, SIGNAL(triggered()),this, SLOT( optimize()));
	 connect(insertAction, SIGNAL(triggered()),this, SLOT( insert()));
	 	
         connect(zoomOutAction, SIGNAL(triggered()),this, SLOT(zoomOut()));
         connect(zoomInAction, SIGNAL(triggered()),this, SLOT(zoomIn()));
         connect(selectModeAction, SIGNAL(toggled(bool)),this, SLOT(setSelectionMode(bool)));

	 connect(previewScene,SIGNAL(progressionDone(const int )),this,SLOT(nextPoint(int)));
	  
	 connect(dirLisView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(openSelected(const QModelIndex &)));
	 ///Connect the click signal to allow part highlighting on scene
	 connect(piecesList,SIGNAL(clicked(const QModelIndex &)),this,SLOT(showPart(const QModelIndex &)));
	}
	
	
 
   void MainWindow::createMenus() {
	 myMenu = menuBar()->addMenu(tr("&File"));
	 myMenu->addAction(openAction);
	 myMenu->addAction(saveAction);
	 
	 
	 myMenu = menuBar()->addMenu(tr("&Edit"));
	 myMenu->addAction(insertAction);	
	 myMenu->addAction(stepAction);	
	 myMenu->addAction(zoomFitAction);
	 myMenu->addAction(deleteAction);
	 myMenu->addAction(rotateAction);
	 myMenu->addAction(rotateByAction);
	 ///myMenu->addAction(optimizeAction);
	 myMenu->addAction(clearAction); 

	 
     	 myMenu = menuBar()->addMenu(tr("&Help"));
	 myMenu->addAction(aboutAction);
	}
  
   ///Add objects names for save/restoreState
  	void MainWindow::nameObjects(){
	
	 previewDock->setObjectName("previewDock");
	 filesListDock->setObjectName("filesListDock");
	 dockInsertedParts->setObjectName("dockInsertedParts");
	 
	 fileToolBar->setObjectName("fileToolBar");
	 docksToolBar->setObjectName("docksToolBar");
	 editToolBar->setObjectName("editToolBar");
	 miscToolBar->setObjectName("miscToolBar");
	 
	 }
  
  MainWindow::MainWindow(){
        setWindowTitle(tr("CamNest V0.5.1 debug"));
	 
	  
	 ///@fixme find a way to put qactions for docks after creating GUI compoment like toolbars and menus.
	 previewDock = new QDockWidget(tr("Preview"), this);
	 previewDockAction= previewDock->toggleViewAction ();
	 previewDockAction->setShortcut(tr("ctrl+P"));
	 
	 dockInsertedParts = new QDockWidget(tr("Parts List"), this);
	 insertedDockAction= dockInsertedParts->toggleViewAction ();
	 insertedDockAction->setShortcut(tr("ctrl+L"));
	 
	 filesListDock= new QDockWidget(tr("File View"), this);
	 filesDockAction= filesListDock->toggleViewAction ();
	 filesDockAction->setShortcut(tr("ctrl+V"));
	 
	 /// setup theGUI
	 createActions();
	 createMenus() ;
	 createStatusBar(); 
	 createToolBars();
	 nameObjects();
	 

	 createSheets();
	 createDockWindows();
	 createConnections();
	 
	 setCentralWidget(sheet);
	 
	 ///restore settings
	 readSettings();
	 
	 qDebug()<< "Interface ready";
   
	 
	 nbrParts=0;
	 insertedParts=0;	 
	 
    }
    
 void MainWindow:: updateSettings() {
     //@fixme the signal is emited twice
         int h=2000;
         int w=3600;
         qDebug()<<"changing sheet dims";
         if (settings.value("Options/sheetH").toInt()!=0 && settings.value("Options/sheetW").toInt()!=0){
         h=settings.value("Options/sheetH").toInt();
         w=settings.value("Options/sheetW").toInt();
         ///@check if setting to (0,0,h,w) makes a diff
         scene->setSceneRect(QRect(-h/2,-w/2,h/2, w/2));
                }
         else {
                scene->setSceneRect(QRect(-h/2,-w/2,h/2, w/2));
          }

          scene->setSheetRect(QRect(-h/2,-w/2,h/2, w/2));
          //scene->zoomFit();

 }


    	 void MainWindow::createSheets() {	 
	 ///@todo: take the sheet metal size from config dialog
     	 scene=new  Sheet (false);
         updateSettings();
	 sheet = new QGraphicsView(scene);
	 ///We draw the recatnagle representing the sheetMetak
	 ///@todo: add option for background color
	 

                  previewScene=new  Sheet ();

         previewScene->setSceneRect( QRect (0, 0, 400, 400));

        previewSheet = new QGraphicsView(previewScene);
        previewSheet->setDragMode(QGraphicsView::RubberBandDrag);//->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
        //previewSheet->setDragMode(QGraphicsView::ScrollHandDrag);
        //previewSheet->setCacheMode( QGraphicsView::CacheNone);
        //previewSheet->setViewportUpdateMode (QGraphicsView::SmartViewportUpdate);

        /// @todo:ADD OPTION USE OPENGL
	 //sheet->setViewport( new QGLWidget());
	 
	 ///previewSheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	/// previewSheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	 ///sheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	 ///sheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	 sheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	 ///@todo add selection mode in config dialog Qt::ContainsItemShape  Qt::IntersectsItemBoundingRect)
         sheet->setRubberBandSelectionMode(Qt::IntersectsItemShape);
	 sheet->setDragMode(QGraphicsView::RubberBandDrag);
    	}
	
    

 
   
 
  void MainWindow::about()
{
  
     QMessageBox::about(this, tr("About CamNest"),
                       tr("<b>CamNest</b> Dxf Viewer and Parts neting software "));
}
 
