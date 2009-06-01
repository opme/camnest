#ifndef SHEET_H
#define SHEET_H


///@todo: keep only essential headers
#include <QtGui>
#include <QWidget>
 

#include "test_creationclass.h"
#include "part.h"
#include "window.h"
#include "settingsdlg.h"
#include "gcode.h"

 

 /// @bug resolve file include issue
 class PartsListModel;
 
 
 
 ///@todo: move  to an independant headre file
 /// the main window GUI class
 class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	 MainWindow();
	 
	 //***********************QGraphicsViews*************
	 ///@todo move to private section and create own Graphics view
	 ///The graphicView holding the preview scene @see 
	 QGraphicsView *previewSheet;
	 ///The graphicView holding the sheet metal scene @see
     	 QGraphicsView *sheet;
	 
	 //***********************GraphicScenes*************
	 /// GraphicScene showing the inserted items
	 Sheet *scene;
	 /// GraphicScene showing the previewed items
	 Sheet *previewScene;	

	 
	
	 //***********************Docks************* 
	 ///Dock containg the part preview and a progress bar for animation purposes
	 QDockWidget *previewDock ;
	 /// Dock with a list of scen's inserted parts @see piecesList
	 QDockWidget *dockInsertedParts;
	 ///Dock with a folder explore view @see dirLisView
	 QDockWidget *filesListDock;
	 
	 
	 //***********************COLORS************* 
	  /// parts Pen 
	  QPen contourPen;
	  /// parts brush
	  QBrush contourBrush;
	  ///status bar Palette on success message
	  QPalette successText;
	   ///status bar Palette on Info message
	  QPalette infoText ;
	  ///status bar Palette when showing error message
	  QPalette  errorText;
	  //signals:
	  //void partInserted();
	  
	 ///create the mainWindow status bar
	 void createStatusBar();
	 ///create the mainWindow tool bars
	 void createToolBars();
	  ///create the mainWindow meuns
	 void createMenus();
	 ///create the dock widgets
	 void createDockWindows();
	 ///create actions associated with the menus/buttons
	 void createActions();
	 /// create connection between signals and slots
	 void createConnections();
	 ///read config files to restore savec settings
	 void readSettings();
	 ///write setting to config file
	 void writeSettings();
	 ///@fixme: has it to be within windows class?
	 void openPart(QString file);
	 /// enable/disable buttons/menus actions
	 void trigActions (bool status);
     	 ///Give objexts names to allow restoring their properties from saved settings
	 void nameObjects();
	 ///Setup the QGrahicsViews/Scenes
	 void createSheets() ;
	  
	  
   private:
	 //***********************File menu ACTIONS************* 
	 ///Shows about dialog
     	 QAction *aboutAction;
	 ///Shows open file dialog
     	 QAction *openAction;
	 ///gGnerate G-code 
	 QAction *saveAction;
	  /// show the settings dialog
	 QAction *settingsAction;
	 ///show the What's this help button
	 QAction *littleHelpAction;
	 
	 QDoubleSpinBox *stepValue;
	 
	 
	 //***********************EDIT menu ACTIONS************* 
	 ///clears the sheet metal scene @see scene keeping the preview scene as is
     	 QAction *clearAction;
	 /// Remove selected parts from sheet metal scene @see scene
	 QAction *deleteAction;
	 ///regenrate another optimized route
	 QAction *optimizeAction;
	 ///Rotate currently selected part by a given angle
	 QAction *rotateByAction;
	 ///Rotate the part by the default angle (90°)
	 QAction *rotateAction; 
	 /// start a minimalistic animation
	 QAction *stepAction;
	 /// Zoom in Scenes to fit contents
	 QAction *zoomFitAction;
	  /// Zoom in 
	 QAction *zoomInAction;
	  /// Zoom out
	 QAction *zoomOutAction;
	 /// insert the previewed part into the sheet metal scene 
	 QAction *insertAction;
	 ///@todo add mirror X / Y actions
	 //QAction *mirrorAction;

         /// switch from rubberBand to hand selection mode
         QAction *selectModeAction;
	 
	  //***********************Dock menu ACTIONS************* 
	 ///Show/hide @see previewDock
	 QAction *previewDockAction;
	 ///Show/hide @see dockInsertedParts
	 QAction *insertedDockAction;
	 ///Show/hide @see filesListDock
	 QAction *filesDockAction;
	
	
	//***********************Toolbars************* 
	/// file toolbar
	 QToolBar *fileToolBar;
	 /// edit toolbar
     	 QToolBar *editToolBar;
	 /// docks toolbar
	 QToolBar *docksToolBar;
	 /// Misc toolbar
	 QToolBar *miscToolBar;
	 
	  /// A toolbar on top off preview window
	 QToolBar *previewToolBar;
     	 QMenu *myMenu;
	 
	 /// a progress bar showing animation status 
	 ///@todo: use progress bar when implmenting threads to show process status
	 QProgressBar *loadingBar;
	 
	 
	 //***********************MODEL************* 
	 /// directory model used by list View @see dirLisView
	 QDirModel *dirModel ;
	 /// list model used by list View @see piecesList
	 PartsListModel *partsModel;
	 /// String List of parts names @see piecesList
	 QStringList partsNames;
	 
	 
	 //***********************ListVeiws************* 
	 /// String List of the currently displayed part names
	 QListView *piecesList;
	 /// list showing files & directory (explorer like)
	 QListView *dirLisView;
	 
	 
	 //***********************UI************* 
	 /// setting dialog UI 
	 SettingsDialog settingsDlg;	 
	 ///appplication settings manager
	 QSettings settings;
	 ///last directory
	 QString filesDir;
	 
	 ///@fixme: merge nbrParts & insertedParts
	 ///Total number of inserted parts in the drawing(counting deleted ones)
	 unsigned int insertedParts;
	 ///Holds the nulber of current present parts in the drawing
	 unsigned int nbrParts;
        /// Affect animation and G-code saving options
         bool plasmaMode;
	 
	 /// @note have to stay public 
	 public slots:
	 void openFile();
         /// returns the starting point of loop i of the previewn part and update the progress bar (for animation)
	 void nextPoint(int currentLoop);


	 
   	private slots:
	void updateMoveVal(double val=20);
        void moveValSet();
   	/// @todo: enforce return type
	 void about();
	 void openSelected(const QModelIndex & index);
	 void showPreviewDock();
	 void showPart(const QModelIndex & index);
	 void setRotAngle();
	 bool saveGCode();
	 void clearScene();
	 void rotateParts(int angle=90);
	 void showSettings();
	 void stepByStep();
	 void zoomFit();

	 void zoomOut();
	 void zoomIn();
         void setSelectionMode(bool mode);

	 void optimize();
	 void deleteItems();
	 void insert();
	 bool confirmAction();
         void updateRectDims();
	 protected:
	 virtual void closeEvent(QCloseEvent *event);
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
	 
 
  
  #endif 
