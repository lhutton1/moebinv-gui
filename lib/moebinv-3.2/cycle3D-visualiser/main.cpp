/**
   Qt GUI and interactive OpenGL visualisation for non-Euclidean geometry   
   defined by the moebinv library in 3D space
   
   @author Cameron Kumar
   @version 1.0 5/3/16
*/

#include <QtWidgets/QApplication> // this is a Qt application
#include "vis.h" // header defining the visualisation
#include <iostream>

using namespace std;

/**
 * main function. sets up the Qt context, checks whether a file has been specified 
 * as a command line argument and creates an instance of the openGL visualisation.
 *  
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @return exit status of function, normal 0
 */
int main(int argc, char *argv[]) {
	
	QApplication app(argc, argv); // creating the application
	vis *visualisation = new vis(NULL); // create vis instance
	
	// want to read sphere data from command line argument if present, handled here
	if(argc > 1) { // case where arguments specified
		
		// load data from file into visualisation
		if((visualisation -> setData(argv[1])) == 1) // if error then exit application
			return 1;
		
	} else { // no command line argument specified case
	
		cout << "specify a file from the menu!\n"; // output to user
		visualisation -> setFileLoaded(0); // set flag to indicate no file loaded
		/* opens the file loader to allow user to specify a file
		   if no file specified program closes */
		if(visualisation -> fileLoader() == 1) 
			return 1;
	}
	
	// display the visualisation in app
	visualisation -> show();
	visualisation -> resize(1024,512);
	// run the application
	return app.exec();	

}
