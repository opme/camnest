#include "sheet.h"

//#include <QGLWidget>

/// @todo: use the genetic algo for a simple nesting algorithm!!
/// @todo change the name from camnest to ...


/// As the lead-points are independant from the part we create them on them own
Part *piece;

/// margin used to properly show piece in preview sheet @todo Add in option dialog
const int rectMarg=20;
/// Timer update interval @todo Add in option dialog
int animSpeed=600;
///@todo: reassign the parts list to sheet metal scen and do the appropriate cha,ges
///the parts appended to the sheetMetal
QList <Part *> parts;


int animStep=0;

void MainWindow::nextPoint(int currentLoop){

    if (plasmaMode){
        //check for animation end
        if (currentLoop/2 == piece->partLoops.size()) {
            //qDebug()<<"Stoping the animation";
            /// @todo use signals instead of direct access!
            previewScene->cleanUpAnim(true);
            previewScene->timer.stop();
            trigActions(true);
            stepAction->setText(tr("Animate"));
            stepAction->setIcon(QIcon(":iconsB/32x32/media-playback-start.png"));
            return;
        }

        if (animStep%2==0){
            previewScene->moveTool(piece->partLoops.at(currentLoop/2)->leadIn);
        }
        else {
            previewScene->moveTool(piece->partLoops.at(currentLoop/2)->touchPoint);
        }
        animStep++;
        loadingBar->setValue(currentLoop/2);
        piece->partLoops.at(currentLoop/2)->setVisible(true);
    }
    // if plasma mode is not active we go from one loop to another (no leads are present)
    else {

        if (currentLoop == piece->partLoops.size()) {
            //qDebug()<<"Stoping the animation";
            previewScene->cleanUpAnim(true);
            previewScene->timer.stop();
            trigActions(true);
            stepAction->setText(tr("Animate"));
            return;
        }
        previewScene->moveTool(piece->partLoops.at(currentLoop)->startPoint);

        loadingBar->setValue(currentLoop);
        piece->partLoops.at(currentLoop)->setVisible(true);
    }

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
        stepAction->setIcon(QIcon(":iconsB/32x32/media-playback-start.png"));
    }
    else{
        /// @bug have to disable everything or the application crashes=> disable listView and folderView
        trigActions(false);
        stepAction->setEnabled(true);
        stepAction->setText(tr("STOP"));
        stepAction->setIcon(QIcon(":iconsB/32x32/media-playback-stop.png"));
        qDebug()<<"Starting animation";
        loadingBar->setRange(0,piece->partLoops.size()-1);
        foreach (Loop* cLoop, piece->partLoops){
            cLoop->setVisible(false);
        }
        previewScene->cleanUpAnim();
        previewScene->timer.start(animSpeed, previewScene);
    }
}

void MainWindow::zoomFitScene() {
    ///@fixme: use signal /slots instead
    scene-> zoomFit();
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Zoomed"));
}

void MainWindow::zoomOutScene() {
    ///@fixme: use signal /slots instead
    scene-> zoom(true);
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Zoomed"));
}


void MainWindow::zoomRect(bool stat) {
    ///@fixme: use signal /slots instead
    if (stat)
        scene-> setMode(Sheet::Zoom);
    else
        scene-> setMode(Sheet::MoveItem);
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Draw the Zoom zone."));
}
void MainWindow::zoomInScene() {
    ///@fixme: use signal /slots instead
    scene-> zoom(false);
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Zoomed"));
}

void MainWindow::zoomFit() {
    ///@fixme: use signal /slots instead
    previewScene-> zoomFit();
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Zoomed"));
}

void MainWindow::zoomOut() {
    ///@fixme: use signal /slots instead
    previewScene-> zoom(true);
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Zoomed"));
}

void MainWindow::zoomIn() {
    ///@fixme: use signal /slots instead
    previewScene-> zoom(false);
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
             partInfos->setPalette(errorText);
            partInfos->setText(tr("Could not open the selected file"));
            delete creationClass;
            delete dxf;
            return;
        }
        else {
            statusBar()->setPalette(successText);
            statusBar()->showMessage(tr("File: ")+file);
            qDebug() << "Reading file Done";
        }

        partInfos->clear();
        previewScene->clear();
        ///@todo: copy the full file path but trim it on ther listView
        QString partName=file.left((file.lastIndexOf(".")));

        qDebug()<<partName;


        piece=new Part(creationClass->partPath,creationClass->pointsPathVector,creationClass->partPathsList,creationClass->pointsCircleVector,creationClass->circlePathsList);
        piece->setPartName(partName);
        //******Add little margin to show outline lead correctly
        QRectF contRect=piece->boundingRect();
        contRect.setHeight(contRect.height()+rectMarg);
        contRect.setWidth(contRect.width()+rectMarg);
        previewSheet->setSceneRect(contRect);

        piece->setPos(rectMarg/2,rectMarg/2);
        previewScene->addItem(piece);
        if (creationClass->corrupted && dupliError) {
            //statusBar()->setPalette(errorText);
            partInfos->setPalette(errorText);
            partInfos->setText(tr("Warning: The part contains Duplicate entities.It may be corrupted! \n"));
            //statusBar()->showMessage(tr("Warning: The part contains Duplicate entities.It may be corrupted!"));
        }
        else {
             partInfos->setPalette(infoText);
             partInfos->setText(tr("Dimensions : ")+(QString("%1").arg(contRect.height())+ " x " + (QString("%1").arg(contRect.width())))+ (tr(" --- Route Length: ")+(QString("%1").arg(piece->tpLength))));
        }
        if (piece->errorsFound && plasmaMode) {
           // statusBar()->setPalette(errorText);
            partInfos->setPalette(errorText);
            partInfos->setText(partInfos->text()+tr(" \n Warning: The part contains Too small Radius that can't be cut!"));
            //statusBar()->showMessage(tr("Warning: The part contains Too small Radius that can't be cut!"));
        }
        if (piece->openLoopError && openLoopError) {
            //statusBar()->setPalette(errorText);
            partInfos->setPalette(errorText);
            partInfos->setText(partInfos->text()+tr("\n  The part contains Open Loops!"));
            //statusBar()->showMessage(tr("Warning: The part contains Open Loops!"));
        }
        //connect((QObject*)piece,SIGNAL(progressionStep()),this,SLOT(progressionDone()));
        previewScene-> zoomFit();
        //insertedParts=previewScene->items().size();/ FIXMEne marche plus lorsqu'on add le ttolPix
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
    // We deslect any previously added part if any
    if (parts.size()!=0)
    parts.last()->setSelected(false);
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
    // We make the part selected and give the scene View the focus to allow mvments
    parts.last()->setSelected(true);
     sheet->setFocus();
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

/// @todo removethis event
void  MainWindow::moveValSet (){
    sheet->setFocus();
}

///@todo see if movevalSet isn't sufficeinet ?
void  MainWindow::updateMoveVal(double val){
sheet->setFocus();
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
    if (nbrParts==0){
        statusBar()->setPalette(errorText);
        statusBar()->showMessage(tr("No Parts inserted! "));
        return false;
    }
    QString fileName (QFileDialog::getSaveFileName(this, tr("Save File"),parts.at(0)->partName+".nc",tr("Gcode Files (*.nc)")));
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("CamNest"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    /// Create the Gcode File
    GCode partGCode (& file);
    partGCode.writeHeader(fileName);


    /// @todo; HIGH PRIORITY : REWRITE THIS HOLE SECTION and use loops Leads,touchpoint,...

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
            partGCode.comment("Turnin off torch");
            ///First we go to the lead-in Point
            partGCode.comment("Going to lead-in point");
            partGCode.comment("Going to Z home");
            //
            /// We read plasma mode from Gcode as a gcode Object is generated each time we want to sve
            if (plasmaMode){
                partGCode.comment("Going to leadPoint");
                qDebug()<<"Going to leadPoint "<<parts.at(j)->gLeadPoints.at(i);//parts.at(j)->partLoops[i]->leadIn;
                //partGCode.rapidMove (parts.at(j)->partLoops[i]->leadIn);
                partGCode.rapidMove (parts.at(j)->gLeadPoints.at(i));
            }
            partGCode.comment("Turnin torch ON");

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
    /// restore the sheet foil
    updateRectDims(false);
    //previewScene->clear();
    parts.clear();
    insertedParts=0;
    nbrParts=0;
    partsModel->removeRows(0,partsModel->rowCount());
    /// Disable action
    //trigActions(false);

    saveAction->setEnabled(false);
    statusBar()->setPalette(infoText);
    statusBar()->showMessage(tr("Cleared Scene"));
}

void MainWindow::setRotAngle(){
    bool ok;
    int i=QInputDialog::getInteger(0,tr("Set rotation angle"),QString("Angle :"), 90, 0, 360, 1, &ok);
    if (ok) rotateParts(i);
}

void MainWindow::rotateParts(int angle) {

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


/// @todo: remove this entry
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
    //save the window state
    settings.setValue("state",saveState(0));

    filesDir=dirModel->filePath(dirLisView->currentIndex());
    filesDir.chop(filesDir.size()-(filesDir.lastIndexOf(QDir::separator()))-1);
    // have to keep the older folder value
    if (filesDir!="") 	 settings.setValue("dir", filesDir);
    settings.setValue("moveVal", stepValue->value());
    settings.endGroup();

    //settings.beginGroup("Docks");
    // settings.setValue("previewPos",dockWidgetArea(previewDock));
    //settings.setValue("previewSize", previewDock->size());
    // settings.endGroup();
}

void MainWindow::readSettings(){
    ///@todo use default geometry constarins if no config file is found

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    //******restore previewDock and toolbars positions
    restoreState(settings.value("state").toByteArray(),0);
    //********restore last directory
    filesDir=(settings.value("dir","").toString());
    stepValue->setValue( settings.value("moveVal").toInt());

    settings.endGroup();

    dirLisView->setRootIndex(dirModel->index(filesDir));//settings.value("MainWindow/Dir").toString()));

    if(settings.value("Colors/openGl", false).toBool()){
        //previewSheet->setViewport( new QGLWidget() );
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

    contourPen =QPen (settings.value("Colors/brush").value<QColor>());
    contourBrush=QBrush (settings.value("Colors/pen").value<QColor>());
    plasmaMode=settings.value("Options/plasmaMode").toBool();
    dupliError=settings.value("Options/dupliError").toBool();
    openLoopError=settings.value("Options/openLoopError").toBool();
    //****Statusbar clolors

    infoText =QPalette(Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black);
    errorText =QPalette(Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red);
    successText  =QPalette(Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue,Qt::blue);

}



void MainWindow::closeEvent(QCloseEvent *event){
    //if (confirmAction()) {
    writeSettings();
    event->accept();
    //}
    //else {
    // event->ignore();
    //}
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
    dirLisView = new QTreeView;
    piecesList =new QListView;


    //Start Preview Dock organisation
    previewDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, previewDock);

    // PreviewSheet sizeHint
   //  previewSheet->setMinimumSize(200,200);
   //  previewSheet->resize(300,300);
   //  previewSheet->setMaximumSize(1000,1000);


    //dirModel->setSorting(QDir::Type);
    dirModel->setFilter(QDir::AllDirs | QDir::Files);
    dirModel->setNameFilters (QStringList()<<"*.dxf");
    dirLisView->setModel(dirModel);
    //dirLisView->setViewMode(QListView::ListMode);
    //make it an option..
    //dirLisView->setViewMode(QListView::IconMode);
    dirLisView->show();


    partsModel= new PartsListModel(partsNames);
    //loadingBar->setMinimumSize(200,20);
    //loadingBar->resize(250,20);
    /// @todo use max screen width
     loadingBar->setMaximumSize(3000,20);



    previewToolBar=new QToolBar(previewHS);
    previewToolBar->addAction(zoomPrevFitAction);
    previewToolBar->addAction(zoomPrevOutAction);
    previewToolBar->addAction(zoomPrevInAction);

    previewToolBar->addAction(selectModeAction);
    previewToolBar->setMaximumSize(3000,30);


    partInfos=new QLabel(previewHS);
    partInfos->setMaximumSize(3000,50);
    partInfos->setAlignment(Qt::AlignHCenter);
    partInfos->setToolTip(tr("Show the part dimension (HeigthxWidth) and errors messages if any"));
    previewHS->setOrientation(Qt::Vertical);

    previewHS->addWidget(previewSheet);
    // we always show the previewWindow Toolbar
    previewHS->setCollapsible (0,false);
    previewHS->addWidget(loadingBar);
    previewDock->setWidget(previewHS);

    //*******Start Preview Dock organisation
    // QSplitter *InsertedPartsHS= new QSplitter(this);
    //InsertedPartsHS->setOrientation(Qt::Vertical);
    //InsertedPartsHS->addWidget(dirLisView);
    //InsertedPartsHS->setCollapsible (0,false);

    piecesList->setModel(partsModel);
    dockInsertedParts->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    filesListDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //dockInsertedParts->setWidget(dirLisView);
    dockInsertedParts->setWidget(piecesList);
    filesListDock->setWidget(dirLisView);
    filesListDock->resize(QSize(400, 400));
    addDockWidget(Qt::LeftDockWidgetArea, filesListDock);
    addDockWidget(Qt::LeftDockWidgetArea, dockInsertedParts);
}


/// @note: Actions have to be first declared before setting the menus
void MainWindow::createActions(){
    ///@todo: Add what's this hints to every action
    aboutAction = new QAction(QIcon(":iconsB/32x32/help-about.png"),tr("&About"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));

    openAction = new QAction(QIcon(":iconsB/32x32/document-open.png"),tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));

    saveAction = new QAction(QIcon(":iconsB/32x32/document-save.png"),tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    //saveAction->setToolTip(tr("Save the G code"));
    saveAction->setWhatsThis(tr("Save the scene to a G-code file"));

    clearAction = new QAction(QIcon(":iconsB/32x32/process-stop.png"),tr("&Clear"), this);
    clearAction->setShortcut(tr("Ctrl+C"));
    clearAction->setWhatsThis(tr("Remove all parts from the scene."));

    stepAction = new QAction(QIcon(":iconsB/32x32/media-playback-start.png"),tr("&Animate"), this);
    stepAction->setShortcut(tr("Ctrl+A"));

    //optimizeAction= new QAction(tr("&Optimize"), this);
    //optimizeAction->setShortcut(tr("Ctrl+Z"));

    insertAction= new QAction(QIcon(":iconsB/32x32/list-add.png"),tr("&Insert"), this);
    insertAction->setShortcut(tr("Ctrl+I"));
    insertAction->setWhatsThis(tr("Insert the currently previewed part in the scene."));

    deleteAction= new QAction(QIcon(":iconsB/32x32/list-remove.png"),tr("&Delete"), this);
    deleteAction->setShortcut(Qt::Key_Delete);

    rotateAction = new QAction(QIcon(":iconsB/32x32/object-rotate-right.png"),tr("&Rotate"), this);
    rotateAction->setShortcut(tr("Ctrl+R"));

    rotateByAction = new QAction(tr("&Rotate by..."), this);
    rotateByAction->setShortcut(tr("Ctrl+B"));

    settingsAction = new QAction(QIcon(":iconsB/32x32/configure.png"),tr("&Settings"), this);
    settingsAction->setShortcut(tr("Ctrl+M"));

    zoomOutAction= new QAction(QIcon(":iconsB/32x32/zoom-out.png"),tr("Zoom &Out"), this);
    zoomOutAction->setShortcut(tr("Ctrl+I"));

    zoomInAction=new QAction(QIcon(":iconsB/32x32/zoom-in.png"),tr("Zoom &In"), this);
    zoomInAction->setShortcut(tr("Ctrl+U"));

    zoomFitAction = new QAction(QIcon(":iconsB/32x32/zoom-original.png"),tr("&Zoom Fit"), this);
    zoomFitAction->setShortcut(tr("Ctrl+F"));

    zoomPrevOutAction= new QAction(QIcon(":iconsB/32x32/zoom-out.png"),tr("Zoom &IN"), this);
    zoomPrevOutAction->setShortcut(tr("Ctrl+I"));

    zoomPrevInAction=new QAction(QIcon(":iconsB/32x32/zoom-in.png"),tr("Zoom O&ut"), this);
    zoomPrevInAction->setShortcut(tr("Ctrl+U"));

    zoomPrevFitAction = new QAction(QIcon(":iconsB/32x32/zoom-original.png"),tr("&Zoom Fit"), this);
    zoomPrevFitAction->setShortcut(tr("Ctrl+F"));

    zoomRectAction= new QAction(QIcon(":iconsB/32x32/zoom-fit-best.png"),tr("&Zoom Rect"), this);
    zoomRectAction->setCheckable(true);

    selectModeAction=new QAction(QIcon(":iconsB/32x32/transform-move.png"),tr("Hand &Move"), this);
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
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    editToolBar->addAction(zoomFitAction);
    editToolBar->addAction(zoomRectAction);
    editToolBar->addAction(zoomInAction);
    editToolBar->addAction(zoomOutAction);
    editToolBar->addAction(rotateAction);
    editToolBar->addAction(stepAction);

    editToolBar->addAction(insertAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(clearAction);

    //add the spin box that set the move (left, right up , down) value and don't give it focus
    stepValue= new QDoubleSpinBox();
    stepValue->setFocusPolicy ( Qt::NoFocus);
    stepValue->setPrefix(tr("Move "));
    editToolBar->addWidget(stepValue);


    docksToolBar = addToolBar(tr("Docks"));
    docksToolBar->addAction(previewDockAction);
    docksToolBar->addAction(insertedDockAction);
    docksToolBar->addAction(filesDockAction);
    docksToolBar->setOrientation(Qt::Horizontal);

    miscToolBar= addToolBar(tr("Misc."));
    miscToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    miscToolBar->addAction(settingsAction);
    miscToolBar->addAction(littleHelpAction);
    miscToolBar->addAction(aboutAction);



    //keep the part in touch with spinBox value change
    connect(stepValue, SIGNAL(valueChanged(double)),this, SLOT(updateMoveVal(double)));
    //connect(stepValue, SIGNAL(editingFinished ()),this,SLOT(moveValSet()));


    trigActions(false);
}


void MainWindow::trigActions (bool status) {
    clearAction->setEnabled(status);
    saveAction->setEnabled(status);
    stepAction->setEnabled(status);
    //optimizeAction->setEnabled(status);
    deleteAction->setEnabled(status);
    rotateAction->setEnabled(status);
    //zoomFitAction->setEnabled(status);
    //zoomInAction->setEnabled(status);
    //zoomOutAction->setEnabled(status);
    insertAction->setEnabled(status);
    rotateByAction->setEnabled(status);
}


void MainWindow::createConnections(){

    connect(aboutAction, SIGNAL(triggered()),this, SLOT(about()));
    connect(openAction, SIGNAL(triggered()),this, SLOT(openFile()));
    connect(clearAction, SIGNAL(triggered()),this, SLOT(clearScene()));
    connect(stepAction, SIGNAL(triggered()),this, SLOT( stepByStep()));
    connect(rotateAction, SIGNAL(triggered()),this, SLOT(rotateParts()));
    connect(rotateByAction, SIGNAL(triggered()),this, SLOT(setRotAngle()));

    connect(settingsAction, SIGNAL(triggered()),this, SLOT(showSettings()));
    connect(&settingsDlg, SIGNAL(accepted()),this,SLOT(updateRectDims()));

    connect(zoomFitAction, SIGNAL(triggered()),this, SLOT(zoomFitScene()));
    connect(zoomOutAction, SIGNAL(triggered()),this, SLOT(zoomOutScene()));
    connect(zoomInAction, SIGNAL(triggered()),this, SLOT(zoomInScene()));

    connect(zoomPrevFitAction, SIGNAL(triggered()),this, SLOT(zoomFit()));
    connect(zoomRectAction, SIGNAL(toggled(bool)),this, SLOT(zoomRect(bool)));
    //connect(scene, SIGNAL(zoomRect(QPointF,QPointF)),this, SLOT(doZoomRect(QPointF,QPointF)));
    connect(zoomPrevOutAction, SIGNAL(triggered()),this, SLOT(zoomOut()));
    connect(zoomPrevInAction, SIGNAL(triggered()),this, SLOT(zoomIn()));

    connect(saveAction, SIGNAL(triggered()),this, SLOT( saveGCode()));
    connect(deleteAction, SIGNAL(triggered()),this, SLOT( deleteItems()));
    //connect(optimizeAction, SIGNAL(triggered()),this, SLOT( optimize()));
    connect(insertAction, SIGNAL(triggered()),this, SLOT( insert()));


    connect(selectModeAction, SIGNAL(toggled(bool)),this, SLOT(setSelectionMode(bool)));

    connect(previewScene,SIGNAL(progressionDone(const int )),this,SLOT(nextPoint(int)));

    connect(dirLisView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(openSelected(const QModelIndex &)));
    //Connect the click signal to allow part highlighting on scene
    connect(piecesList,SIGNAL(clicked(const QModelIndex &)),this,SLOT(showPart(const QModelIndex &)));
}



void MainWindow::createMenus() {
    myMenu = menuBar()->addMenu(tr("&File"));
    myMenu->addAction(openAction);
    myMenu->addAction(saveAction);
    myMenu->addSeparator ();
    myMenu->addAction(settingsAction);


    myMenu = menuBar()->addMenu(tr("&Edit"));
    myMenu->addAction(insertAction);
    myMenu->addAction(stepAction);
    myMenu->addAction(zoomFitAction);
    myMenu->addAction(deleteAction);
    myMenu->addAction(rotateAction);
    myMenu->addAction(rotateByAction);
    myMenu->addAction(clearAction);



    myMenu = menuBar()->addMenu(tr("&Help"));
    myMenu->addAction(aboutAction);
}


void MainWindow::nameObjects(){

    previewDock->setObjectName("previewDock");
    ///@Todo set file list and folder view max Size
    filesListDock->setObjectName("filesListDock");
    dockInsertedParts->setObjectName("dockInsertedParts");

    fileToolBar->setObjectName("fileToolBar");
    docksToolBar->setObjectName("docksToolBar");
    editToolBar->setObjectName("editToolBar");
    miscToolBar->setObjectName("miscToolBar");

}

MainWindow::MainWindow(){
    setWindowTitle(tr("CamNest V0.5.3 alpha"));


    /// @todo find a way to put qactions for docks after creating GUI compoment like toolbars and menus.
    previewDock = new QDockWidget(tr("Preview"), this);
    previewDockAction= previewDock->toggleViewAction ();
    previewDockAction->setShortcut(tr("ctrl+P"));

    dockInsertedParts = new QDockWidget(tr("Parts List"), this);
    insertedDockAction= dockInsertedParts->toggleViewAction ();
    insertedDockAction->setShortcut(tr("ctrl+L"));

    filesListDock= new QDockWidget(tr("File View"), this);
    filesDockAction= filesListDock->toggleViewAction ();
    filesDockAction->setShortcut(tr("ctrl+V"));

    //**** setup theGUI ********
    createActions();
    createMenus() ;
    createStatusBar();
    createToolBars();
    nameObjects();


    createSheets();
    createDockWindows();
    createConnections();

    setCentralWidget(sheet);

    /// restore settings
    readSettings();

    qDebug()<< "Interface ready";


    nbrParts=0;
    insertedParts=0;

}

void MainWindow:: updateRectDims(bool rem) {
// We remove the old sheet rect before adding the new one
if (rem){
    scene->removeItem( scene-> sheetRect);
}
    scene->setSheetRect();
    // btw We update this option
    plasmaMode=settings.value("Options/plasmaMode").toBool();
    dupliError=settings.value("Options/dupliError").toBool();
    openLoopError=settings.value("Options/openLoopError").toBool();
}


void MainWindow::createSheets() {

    scene=new  Sheet (false);

    sheet = new QGraphicsView(scene);
    //We draw the recatnagle representing the sheetMetak
    ///@todo: Add option for background color
    previewScene=new  Sheet ();
    previewScene->setSceneRect( QRect (0, 0, 400, 400));

    previewSheet = new QGraphicsView(previewScene);
    previewSheet->setCacheMode( QGraphicsView::CacheBackground);
    previewSheet->setCacheMode( QGraphicsView::CacheNone);
    previewSheet->setDragMode(QGraphicsView::RubberBandDrag);//->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
    //previewSheet->setDragMode(QGraphicsView::ScrollHandDrag);

    //previewSheet->setViewportUpdateMode (QGraphicsView::SmartViewportUpdate);

    /// @todo:ADD OPTION USE OPENGL
    //sheet->setViewport( new QGLWidget());

    //previewSheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // previewSheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //sheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //sheet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    sheet->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ///@todo add selection mode in config dialog Qt::ContainsItemShape  Qt::IntersectsItemBoundingRect)
    sheet->setRubberBandSelectionMode(Qt::IntersectsItemShape);
    sheet->setDragMode(QGraphicsView::RubberBandDrag);
}


void MainWindow::about()
{

    QMessageBox::about(this, tr("About CamNest"),
                       tr("<b>CamNest</b> DXF file Viewer and G-code generation software"));
}
