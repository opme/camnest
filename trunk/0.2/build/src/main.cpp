#include <QtGui>


#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
#include "renderpath.h"
#include "window.h"
#include "sheet.h" 

//RenderArea *renderAreas;
//QPushButton *draw;


int main( int argc, char** argv )
{
	 // create application
	 QApplication app( argc, argv );
	 app.setApplicationName( "camnest" );
	 MainWindow	 mainWindow;
     mainWindow.setGeometry( 100, 100, 1100, 850);
	 mainWindow.setWindowTitle( "Nested parts" );
     mainWindow.show();
	 
	 //sheet.setGeometry(300, 300, 320, 320);
	 //sheet.show();
	 //Window window;
	 //window.setWindowTitle( "camnest" );
     //window.show();
     return app.exec();
	
	 // connection
	 QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
     }