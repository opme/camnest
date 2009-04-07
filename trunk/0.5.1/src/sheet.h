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
	 void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
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
 
 
	  class PartsListModel : public QAbstractListModel{
     Q_OBJECT
	 public:
     PartsListModel(const QStringList &strings, QObject *parent = 0): QAbstractListModel(parent), stringList(strings) {}
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     QVariant data(const QModelIndex &index, int role) const;
	 //Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
	 bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
     bool removePart(QVariant data);
	 private:
     QStringList stringList;
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
	  QDockWidget *dockInsertedParts;
	  QDockWidget *filesListDock;

	  
	  QPen contourPen;
	  QBrush contourBrush;
	  
	  signals:
	  void partInserted();
	  
   private:
     QAction *aboutAction;
     QAction *openAction;
     QAction *clearAction;  
	 QAction *deleteAction;  
	 QAction *optimizeAction;  
	 //QAction *stepAction; 

	 
	 QComboBox *fontSizeCombo;
	 
	 QAction *rotateByAction;
	 QAction *rotateAction; 
	 QAction *mirrorAction;
	 
	 QAction *previewDockAction;
	 QAction *insertedDockAction;
	 QAction *filesDockAction;
     // QAction *generateAction;
	 QAction *saveAction;
	 QAction *stepAction;
	 QAction *zoomFitAction;
	 QAction *insertAction;
	 QAction *settingsAction;
	 QAction *littleHelpAction;
	
	 QToolBar *fileToolBar;
     QToolBar *editToolBar;
	 QToolBar *docksToolBar;
	 QToolBar *miscToolBar;
	  
     QMenu *fileMenu;
	 
	 QProgressBar *loadingBar;
	 QDirModel *model ;
	 QListView *piecesList;
	 
	 QListView *tree;
	 SettingsDialog settingsDlg; 
	 PartsListModel *partsModel;
	 
	 QSettings settings;
	 QStringList partsNames;
	 
	 ///Holds the nulber of inserted parts in the drawing
	 unsigned int insertedParts;
	 ///Holds the nulber of current present parts in the drawing
	 unsigned int nbrParts;
	
	 
	 
	 
	 public slots:
	 void openFile();
	 void progressionDone(int currentLoop);
	 
   private slots:
   /// TODO: check for type return
     void about();
	 void openSelected(const QModelIndex & index);
	  void descStep( const QString desc);
	 void showPreviewDock();
	 void showPart(const QModelIndex & index);
	 void setRotAngle();
	 bool saveGCode();
	 void clearScene();
	 void rotateParts(int angle=90);
	 void showSettings();
	 //void generatePath();
	 void stepByStep();
	 void zoomFit();
	 void optimize();
	 void deleteItems();
	 void insert();
	 bool confirmAction();
	 protected:
	 virtual void closeEvent(QCloseEvent *event);
  };

  #endif 
