#include <QtGui>


#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
#include "sheet.h" 



int main( int argc, char** argv )
{
	 // create application
	 QApplication app( argc, argv );
	 QCoreApplication::setOrganizationName("Camnest");
	 QCoreApplication::setOrganizationDomain("Camnest");
	 QCoreApplication::setApplicationName("Camnest");
	 app.setApplicationName( "camnest" );
	 MainWindow	 mainWindow;
     mainWindow.show();
     return app.exec();
	 QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
     }