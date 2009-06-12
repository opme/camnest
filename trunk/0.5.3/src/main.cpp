#include <QtGui>


#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
#include "sheet.h" 

/*! \mainpage Camnest Documentation
 *
 *
 * \section install_sec Installation
 *
 * \subsection step1  Getting the source :
 * The camnest project is hosted on google code at at http://code.google.com/camnest .\n
 * You can easily get the source code by executing in a terminal window the following command, assuming that you already had installed the svn revision control system :\n
 * \b svn \b checkout \b http://camnest.googlecode.com/svn/trunk/ \n
 * 
* \subsection step2  Dependencies :
 * In order to compile the source you must have ,\b Qt>4.2 developpement headers, normally provided by your distribution. In addition you must have minimum build tool as \b g++ (GNU C++ compiler) and \b qmake . For windows users you can easily get Qt developement SDK at \b www.qtsoftware.com \n
 * 
* \subsection step3 Compiling :
 * Type the following commands in the directory where you extracted the source files :\n
 * \em .qmake \n
 * when the configuration script show the success message, type :\n
 * \em make \n
 * If you want to install camnest in your system tree type after granting administrative privileges:\n
 * \em make \em install \n
 */	


int main( int argc, char** argv )
{
	 // create application
	 QApplication app( argc, argv );
	 QCoreApplication::setOrganizationName("Camnest");
	 QCoreApplication::setOrganizationDomain("Camnest");
	 QCoreApplication::setApplicationName("Camnest");
         QDir::addResourceSearchPath(QDir::currentPath()+"/icons");

         // Internationalization
         QTranslator qtTranslator;
     qtTranslator.load("qt_" + QLocale::system().name(),
             QLibraryInfo::location(QLibraryInfo::TranslationsPath));
     app.installTranslator(&qtTranslator);

     QTranslator myappTranslator;
     myappTranslator.load("camnest_"+ QLocale::system().name());
     app.installTranslator(&myappTranslator);

         //app.setApplicationName( "CamNest" );
	 MainWindow	 mainWindow;
     mainWindow.show();
     return app.exec();
	 QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
     }
