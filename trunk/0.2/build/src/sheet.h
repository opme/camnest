#ifndef SHEET_H
#define SHEET_H
#include <QtGui>
#include <QWidget>
   ///CONFIG DIALOG INTERFACE
  #include "ui_settingsdialog.h"
///LibDxf headers  
#include "dl_dxf.h"
#include "part.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
  //

typedef QList <QPointFWithParent > QPFWPList;
typedef  QList <QPainterPath > QPPList;
  

/**
T qgraphicsitem_cast ( QGraphicsItem * item )

Returns the given item cast to type T if item is of type T; otherwise, 
0 is returned.

Note: To make this function work correctly with custom items, reimplement
the {QGraphicsItem::}{type()} function for each custom QGraphicsItem subclass.

See also QGraphicsItem::type() and QGraphicsItem::UserType.

*/

  class SheetMetal: public QWidget  /// could be a Qview directly ???
 {
     Q_OBJECT

 public:
     SheetMetal(QGraphicsScene *scene,QWidget *parent = 0);
     QSize sizeHint()  ;
	 QSize minimumSizeHint(); 
	 
	 //QGraphicsItem *selectedItem;
  private:     
	  
     // QList<QGraphicsItem *> selectedItems;
  
  };
  
    
 class Sheet: public QGraphicsScene {
  Q_OBJECT
  
  public:
     Sheet(QWidget *parent = 0);
	 void moveTool(QPointFWithParent endPoint);
	 QBasicTimer timer;
	 void zoomFit();
	 QPen toolPen;
	 QSettings settings;
	 
	 protected:
     // void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	 //void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void wheelEvent(QGraphicsSceneWheelEvent *mouseEvent);
	 void timerEvent(QTimerEvent *event);
	
	signals:
	void progressionDone(const int currentLoop);
	
     
 
 };
 
  class SettingsDialog : public QWidget {
     Q_OBJECT

	 public:
     SettingsDialog(QWidget *parent = 0);
	 QSettings settings;
	 public slots:
	 void setPenColor();
	 void setBrushColor();
	 void setInner();
	 void save();
	 void loadSettings();
	 
     //void on_inputSpinBox1_valueChanged(int value);
     //void on_inputSpinBox2_valueChanged(int value);
	 private:
     Ui::SettingsDialog ui;
 };
 
 
 
 class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	 MainWindow();
	 void createStatusBar();
	 void createToolBars();
	 void createMenus();
	 void createActions();
	 void createConnections();
	 void readSettings();
	 void writeSettings();
	 void createDockWindows();
	 void openPart(QString file);
	 void trigActions (bool status);
	 //SheetMetal *sheet;
	 //SheetMetal *pathSheet;
     QGraphicsView *previewSheet;
     QGraphicsView *sheet;
	  QDockWidget *dock ;
	  
	  
	  QPen contourPen;
	  QBrush contourBrush;
	  
   private:
     QAction *aboutAction;
     QAction *openAction;
     QAction *clearAction;  
	 QAction *deleteAction;  
	 QAction *optimizeAction;  
	 //QAction *stepAction; 
     QAction *mirrorAction;
	 QAction *yMirror;
	 QAction *rotateAction; 
	 QAction *previewDockAction;
     // QAction *generateAction;
	 QAction *saveAction;
	 QAction *stepAction;
	 QAction *simulateAction;
	 QAction *zoomFitAction;
	 QAction *insertAction;
	 QAction *settingsAction;
	 
     QMenu *fileMenu;
	 
     QToolBar *fileToolBar;
     QToolBar *editToolBar;
	 
	 QProgressBar *loadingBar;
	 QDirModel *model ;
	 QListView *piecesList;
	 QSplitter *horSplitter;
	 QListView *tree;
	 SettingsDialog settingsDlg; 
	
	 QSettings settings;
	 
	 
	 public slots:
	 void openFile();
	 void progressionDone(int currentLoop);
	 
   private slots:
   /// TODO: check for type return
     void about();
	 void openSelected(const QModelIndex & index);
	  void descStep( const QString desc);
	  
	
	 bool saveFile();
	 void clearScene();
	 void rotateParts();
	 void showSettings();
	 //void generatePath();
	 void stepByStep();
	 void zoomFit();
	 void optimize();
	 void deleteItems();
	 void insert();
	 bool maybeSave();
	 protected:
	 virtual void closeEvent(QCloseEvent *event);
  };

     double getAngle(QPointF start_point,QPointF end_point);
	 QPointF ArrowWing1(double line_angle,QPointF end_point);
	 QPointF ArrowWing2(double line_angle,QPointF end_point);
	 void drawArc(QPointFWithParent point,QPainterPath &pathToModify);
	 
  
  #endif 
