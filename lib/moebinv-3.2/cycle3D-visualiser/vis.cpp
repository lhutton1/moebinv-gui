/**
 * @author Cameron Kumar
 * @version 1.0 5/3/16
 * @date 5 Mar 2016
 * @brief class definition for 3d elliptic non-Euclidean visualisation tool.
 *
 *  Function definitions for the visualisation class defined within the vis.h
 *  header file. All member function and slot code is defined here.
 */

#include "vis.h" // header file
#include <QMouseEvent> // qt includes
#include <QWheelEvent>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QtWidgets/QMenu>
#include <QtWidgets/QDialog>
#include <QtWidgets/QSlider>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFileDialog>
#include <cmath> // c++ includes
#include <vector>
#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

/**
 * class constructor
 *  
 * @param parent parent class, inherit from there 
 */
vis::vis(QWidget *parent): QGLWidget(parent) {} // simple constuctor

/**
 * creates the points of a sphere object, centre at origin, radius 1. this 
 * template sphere can be copied and used to represent all spheres in our
 * visualisation. The sphere points are created when the OpenGL widget
 * is initialised by the program.
 *  
 * @see initializeGL()
 * @param nPoints number of points per circle in the sphere
 * @return vector of double triplets defining the point coords in 3d 
 */
vector<Point> vis::makeSpherePoints(int nPoints) {
	
	vector<Point> spherePoints; // temp vector for points
	
	// loops to create the sphere points as a set of nPoints circles
	for(int i = 0; i < nPoints; i++) {
		// calculations for latitude location of circle of points
		float phi = (-(M_PI) / 2.0) + (((float)i / (float)nPoints) * M_PI);
		float cosPhi = cos(phi); // used for calculation
		float sinPhi = sin(phi); // used for calculation	
		for(int j = 0; j < nPoints; j++) {
			Point p; // temp point
			// calculate longtitude value of each point in circle
			float theta = -(M_PI) + (((float)j / (float)nPoints) * 2.0 * M_PI);
			float cosTheta = cos(theta); // used for calculation
			float sinTheta = sin(theta); // used for calculation
			// now to add coord to vector
			p.x = cosPhi * cosTheta;
			p.y = cosPhi * sinTheta;
			p.z = sinPhi;
			spherePoints.push_back(p); // add to temp vector
		}
	}
	
	return spherePoints; // return points
	
}

/**
 * create points of a cube about the origin with side length 1.
 * cube points added front to back, top to bottom, left to right.
 * this cube will be transformed and drawn about objects when they are
 * selected by the user. the cube points are created when the OpenGL widget
 * is initialised by the program.
 *  
 * @see initializeGL()
 * @return vector containing points of cube
 */
vector<Point> vis::makeCubePoints() {
	
	// create the points
	vector<Point> cube; // temp vector to hold points
	cube.push_back((Point){-0.5, 0.5, 0.5});
	cube.push_back((Point){0.5, 0.5, 0.5});
	cube.push_back((Point){-0.5, -0.5, 0.5});
	cube.push_back((Point){0.5, -0.5, 0.5});
	cube.push_back((Point){-0.5, 0.5, -0.5});
	cube.push_back((Point){0.5, 0.5, -0.5});
	cube.push_back((Point){-0.5, -0.5, -0.5});
	cube.push_back((Point){0.5, -0.5, -0.5});
	
	// return the cube points
	return(cube);
}	

/**
 * draws a sphere with specified centre and radius. used when spheres are
 * rendered to a buffer.
 *  
 * @see paintGL()
 * @param centre coordinate point of centre location
 * @param radius radius of sphere 
 */
void vis::drawSphere(Point centre, double radius) {
	
	// load modelview for translation and scaling
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); // push matrix to apply object specific transforms
	glTranslatef(centre.x, centre.y, centre.z);
	glScalef(radius, radius, radius);	
			
	// draw the strips of our sphere 
	glBegin(GL_QUAD_STRIP);
	// create circPoints-1 latitudinal strips of primitives
	for(int i = 0; i < (circPoints - 1); i++)  {
		/* creates quads between one sphere and sphere above. has to include
		the first point in sphere at start and at end hence why the for loop
		does circPoints+1 iterations */
		for(int j = 0; j < (circPoints + 1); j++)  {
			// get points
			Point lower = spherePoints.at((i * circPoints) + (j % circPoints));
			Point upper = spherePoints.at(((i+1) * circPoints) + (j % circPoints));
			// render vertices with normals, as the sphere points are for a sphere
			// with radius 1 and centre (0,0,0), normal vector is just each sphere point
			// interpretted as a vector
			glNormal3d(lower.x, lower.y, lower.z); 
			glVertex3d(lower.x, lower.y, lower.z);
			glNormal3d(upper.x, upper.y, upper.z);
			glVertex3d(upper.x, upper.y, upper.z);
		}
	}			
	glEnd();
	
	// fills the hole at the bottom of the sphere
	glBegin(GL_POLYGON);
	for(int i = 0; i < circPoints; i++) {
		Point p = spherePoints.at(i); // get point
		glVertex3d(p.x, p.y, p.z); // render vertex
	}
	glEnd();
	
	
	// fills the hole at the top of the sphere
	glBegin(GL_POLYGON);
	for(int i = 0; i < circPoints; i++){
		Point p = spherePoints.at(circPoints * (circPoints - 1) + i); // get point
		glVertex3d(p.x, p.y, p.z); // render vertex
	}
	glEnd();
	
	glPopMatrix(); // return to normal modelview matrix
}

/**
 * sets the flag to indicate whether a file has been loaded to visualise or
 * not. This determines what options appear on the context menu. Called 
 * at run time depending on whether a command line arg specified and called
 * again when a new file is loaded.
 *
 * @param file integer value for flag to be given
 */
void vis::setFileLoaded(int file) {
	fileLoaded = file;
}

/**
 * writes centre, radius, key and generation information from file to 
 * vectors. file specified as a command line argument. Sphere centre coordinates
 * stored in objCentre vector, radius data in objRadius, and key and generation
 * data in objGenKey. called by the program that instances this class. 
 * 
 * @param objData file containing object raw data 
 * @return returns 1 if there is a major error, else 0
 */
int vis::setData(char* objData) {
	
	double x, y, z, rad; // will temporarily hold file inputs
	int gen; // temporarily holds the generation value for inputs
	string key; // temporarily holds the key value for inputs
	int i = 0; // counter for error output
	
	ifstream dataFile(objData);
	if (dataFile.is_open()) { // opens file if location is valid
	
		/* data is read in this way so if a value is missed from the file it can be detected.
		   the x is read first as an eof check, then the error counter is incremented so we can
		   compare this later with the size of our vectors. If a value is missing, there will 
		   be a discrepency between the error counter and vector size */
		while(dataFile >> x) {
			i++; // adds to the increment counter, used for error testing
			if(dataFile >> y >> z >> rad >> gen >> key) { // reads lines of file
				if(rad > 0.0) { // only radius over 0 valid
					// write to vector
					objCentre.push_back((Point){x, y, z}); 
					objRadius.push_back(rad);
					objGenKey.push_back((genKey){gen, key});
					// set default colour and transparency values
					objColour.push_back((RGBA){1.0, 0.0, 0.0, 0.3});
				
				} else { // not enough space seperated values for line
					cout << "ERROR: line " << i << " of file is invalid and will be ignored!\n";
					i -= 1; // takes one off counter to ignore line
				}
			} 
		}
		
		dataFile.close();		
		
		// check if file has an incorrect number of doubles specified
		if((int)objRadius.size() < i) {
			cout << "ERROR: complete data not specified for all objects!\n";
			return 1; // exits qt program
		}
		
		// check file wasn't empty
		if(i == 0) {
			cout << "ERROR: file was empty!\n";
			return 1; // exits qt program
		}
		
	} else { // invalid file specified
		cout << "ERROR: file specified is invalid!\n";
		return 1; // exits qt program
	}
	
	setFileLoaded(1); // set flag to indicate file loaded
	return 0; // succesful return
}	

/**
 * populate the colours vector with a selection of RGBA values and creates colour
 * icons from png files to be used in colour selection. called when the OpenGL widget
 * is initialised by the program.
 *
 * @see initializeGL()
 */
void vis::initColours() {
	
	// populate RGBA colour vector
	colour.push_back((RGBA){1.0, 0.0, 0.0, 0.0}); // red (default)
	colour.push_back((RGBA){0.0, 1.0, 0.0, 0.0}); // green 
	colour.push_back((RGBA){0.0, 0.0, 1.0, 0.0}); // blue 
	colour.push_back((RGBA){0.2, 1.0, 1.0, 0.0}); // cyan
	colour.push_back((RGBA){1.0, 0.0, 1.0, 0.0}); // pink
	colour.push_back((RGBA){1.0, 1.0, 0.0, 0.0}); // yellow
	colour.push_back((RGBA){0.5, 0.3, 0.0, 0.0}); // brown
	colour.push_back((RGBA){1.0, 0.84, 0.0, 0.0}); // gold
	colour.push_back((RGBA){0.86, 0.08, 0.24, 0.0}); // crimson
	colour.push_back((RGBA){0.2, 0.8, 0.2, 0.0}); // lime 
	colour.push_back((RGBA){0.0, 0.392, 0.0, 0.0}); // dark green 
	colour.push_back((RGBA){0.0, 0.55, 0.55, 0.0}); // dark cyan
	colour.push_back((RGBA){1.0, 0.5, 0.0, 0.0}); // orange
	colour.push_back((RGBA){0.3, 0.3, 1.0, 0.0}); // purple
	colour.push_back((RGBA){1.0, 0.75, 0.8, 0.0}); // soft pink	
	colour.push_back((RGBA){0.73, 0.73, 0.73, 0.0}); // grey
	colour.push_back((RGBA){1.0, 1.0, 1.0, 0.0}); // white
	
	
	string sColour[16] = {"red", "green", "blue", "cyan", "pink", "yellow",
			      "brown", "gold", "crimson", "lime", "darkgreen", "darkcyan",
			      "orange", "purple", "softpink", "grey"};
			      
	// populate QIcon colour vector
	for(int i = 0; i < 16; i++) {
	
		// create filename
		stringstream file;
		file << "colours/" << sColour[i] << ".png";
		char const *fname = file.str().c_str(); // filename in char* format
		// create icon and add to vector
		QIcon *icon = new QIcon(fname);
		colourIcon.push_back(icon);
		
	}	
}

/**
 * determines whether a string is already present within a list or not.
 * used when list of unique keys is being created
 *
 * @see getKeyList() 
 * @param val value to be searched for
 * @param list list to be searched in
 * @return 1 if true, else 0
 */
int vis::valPresent(string val, vector<string> list) {
	
	int present = 0; // flag to declare if item present or not
	
	if((int)list.size()!=0) // if list not empty
		for(int i = 0; i < (int)list.size(); i++) //loop through list
			if(val == list.at(i)) // if value present
				(present = 1); // sets flag if present
	
	return present; // returns flag			
}

/**
 * finds all unique key values for all objects in the visualisation.
 * this takes place when the OpenGL widget is initialized.
 *
 * @see initializeGL()
 * @return vector containing all unique key values
 */
vector<string> vis::getKeyList() {

	vector<string> list; // list of unique key values to be returned

	// add key to list if not present already
	for(int i = 0; i < (int)objGenKey.size(); i++) 
		if(valPresent(objGenKey.at(i).key, list) == 0)
			(list.push_back(objGenKey.at(i).key));
		
	return list; // return the completed list
}

/**
 * recursive function to be used for merge sorting of a vector. used to
 * order spheres by distance from the screen as part of rendering a new
 * frame.
 *  
 * @see paintGL()
 * @see sphereOrder()
 * @param vec vector to sort (structure of ints and doubles)
 * @return sorted vector (structure of ints and doubles)
 */
vector<idDist> vis::mergeSort(vector<idDist> vec) {
	
	// recursion terminates when only 1 element in list
	if(vec.size() == 1)
		return vec;
	else {
	
		// determine middle position and left and right vectors
		vector<idDist>::iterator mid = vec.begin() + (vec.size()/2);
		vector<idDist> l(vec.begin(), mid);
		vector<idDist> r(mid, vec.end());
		
		// merge sort each component (recursive step)
		l = mergeSort(l);
		r = mergeSort(r);
		
		// sort the left and right vectors into an order
		vector<idDist> sorted; // will hold sorted values
		int iL = 0, iR = 0; // increment variables for left and right loops
		
		// adding sorted objects to the sorted vector by comparison until end of one vector reached
		while(iL < (int)l.size() && iR < (int)r.size()) {
			if(l[iL].dist < r[iR].dist) {
				sorted.push_back(l[iL]);
				iL++;
			} else {
				sorted.push_back(r[iR]);
				iR++;
			}
		}
		
		// adding remaining contents of vectors to end of sorted list
		while(iL < (int)l.size()) {
			sorted.push_back(l[iL]);
			iL++;
		}
		while(iR < (int)r.size()) {
			sorted.push_back(r[iR]);
			iR++;
		}
		
		return sorted; // returning the completed sorted vector
	}
	
}

/**
 * orders the spheres based on opacity and which is closest to the camera.
 * this is done to order the spheres so they may be drawn from furthest to
 * nearest to provide the see-through effect when rendered. required to render
 * each new frame.
 *
 * @see paintGL() 
 * @return returns a vector of integers representing the order of object rendering.
 */
vector<int> vis::sphereOrder() {
	
	vector<idDist> translucentid; // will hold id and distance of translucent objects
	
	// need to create list of objects for all objects within the visualisation
	for(int i = 0; i < (int)objCentre.size(); i++) {
		translucentid.push_back((idDist){i, 0.0});
	}	
	
	// to sort objects, first calculate the distance from camera.
	// we will work out order based on point-plane distance from the cameras
	// parallel plane at origin, need to work out plane normal first
	Point norm = {(sin((-yRot*M_PI)/180.0))*cos((pRot*M_PI)/180.0), // x
		      sin((pRot*M_PI)/180.0), // y
		      cos((-yRot*M_PI)/180.0)*cos((pRot*M_PI)/180.0)}; // z
	// we also need to calculate the normal vectors magnitude for the equation
	double normMag = sqrt(pow(norm.x, 2) + pow(norm.y, 2) + pow(norm.z, 2)); 
	
	for(int i = 0; i < (int)translucentid.size(); i++) {
	
		Point cen = objCentre.at(translucentid.at(i).id); // get centre
		double rad = objRadius.at(translucentid.at(i).id); // get radius
		
		// calculate signed distance from plane
		double d = (norm.x*cen.x + norm.y*cen.y + norm.z*cen.z)/normMag;
		translucentid.at(i).dist = d + rad; // update vector
	
	}
	
	// now need to sort the vector, for this we use mergesort recursion
	translucentid = mergeSort(translucentid);
	
	// write the sorted vector ids to a vector of integers
	vector<int> order; // initialise vector that will store final order list
	for(int i = 0; i < (int)translucentid.size(); i++) 
		order.push_back(translucentid.at(i).id);

	return order; // returning ordered list
}

/**
 * changes the RGB colour of object with index id to the RGB value provided.
 * used when an objects colour is changed from context menu options.
 *  
 * @see createContextMenu()
 * @see colChangeSlot()
 * @param id identifier of object whose colour we want to change
 * @param rgb RGB colour we want the object to have
 */
void vis::changeColour(int id, RGBA rgb) {
	objColour.at(id).R = rgb.R;
	objColour.at(id).G = rgb.G;
	objColour.at(id).B = rgb.B;
}

/**
 * changes the transparency value of object to alpha value provided. 
 * used when an objects transparency is changed from context menu options.
 *  
 * @see createContextMenu()
 * @see transChangeSlot()
 * @param id identifier of object whose transparency we want to change
 * @param alpha alpha value we want to change object to
 */
void vis::changeTransparency(int id, double alpha) {
	objColour.at(id).A = alpha;
}

/**
 * calculates the centre, radius, and orthogonal vector for an intersection.
 * stores details in global vector coi. this is carried out at initialization
 * but the information in coi is later used to draw or print intersections.
 * 
 * @see initializeGL()
 * @see printIntersections()
 * @see drawIntersections()
 * @param id index of object to calculate intersections for
 * @param inter list of intersecting objects
 */
void vis::calculateIntersection(int id, vector<idOverVecLen> inter) {
	
	// get the centre coordinates and radius for calculations
	Point cen = objCentre.at(id); 
	double rad = objRadius.at(id);
	
	// loop through all intersections and append string with information
	for(int i = 0; i < (int)inter.size(); i++) {
		
		// read intersection details from vector for calculations
		idOverVecLen currentInt = inter.at(i);
		
		if(abs(inter.at(i).over) < 0.0001) { // tangent case, 0.0001 value to catch rounding error
			
			// calculating tangent point
			Point pTangent = (Point){cen.x+rad*currentInt.vec.x, // x
					 	 cen.y+rad*currentInt.vec.y, // y
					 	 cen.z+rad*currentInt.vec.z};// z
			// add tangent to intersection vector for drawing, relatively small radius
			coi.push_back((intDraw){pTangent, currentInt.vec, 0.0, id, currentInt.id});
				
		} else { 
				
			// get radius of intersecting sphere
			double iRad = objRadius.at(currentInt.id);
			// now calculate the distance from the centre of sphere i to coi 
			double coiDist = pow(currentInt.len, 2) - (pow(iRad,2) - pow(rad,2));
			coiDist = coiDist/(2*currentInt.len);
			// also calculate the radius using the distance calculation as this is a part of the equation
			double coiRad = sqrt(pow(rad,2) - pow(coiDist,2));
			// use this to calculate the centre of the circle
			Point coiCen = (Point){cen.x + coiDist*currentInt.vec.x,
				       	       cen.y + coiDist*currentInt.vec.y,
				       	       cen.z + coiDist*currentInt.vec.z};
			
			// case of tangency between one sphere inside another, 0.0001 value to catch rounding error
			if(abs(rad - (iRad + currentInt.len)) < 0.0001 || abs(rad - (iRad - currentInt.len)) < 0.0001) { 
				// add to vector
				coi.push_back((intDraw){coiCen, currentInt.vec,  0.0, id, currentInt.id});						
			} else if(rad < iRad + currentInt.len) { // intersection case
				// add intersection to intersection vector for drawing
				coi.push_back((intDraw){coiCen, currentInt.vec, coiRad, id, currentInt.id});
			}
			// nothing done if sphere completely contained in another sphere		
		}
	}
	
	return; 
}

/**
 * identifies which objects intersect specified object by comparing the
 * sum of their radii with the distance between their centres. the number of 
 * intersections is returned to keep track of where each objects 
 * intersections appear in the vector. done as part of the intersections
 * calculations when OpenGL widget initialized.
 *  
 * @see initializeGL()
 * @see calculateIntersections()
 * @param id identifier of object we will calculate intersections for
 * @return number of objects this object intersects with
 */
int vis::intersectsWith(int id) {
	
	// error check to ensure valid id specified
	if(id < 0 || id >= (int)objCentre.size()) {
		cout << "Error! ID specified for intersection check out of range!\n";
		return 0;
	} else {
		// get the object's centre and radius
		Point c = objCentre.at(id); 
		double r = objRadius.at(id);
		// create a vector to store details of which objects intersect
		vector<idOverVecLen> inter;
	
		// this for loop calculates which intersections occur
		for(int i = 0; i < (int)objCentre.size(); i++) {
			if(i != id) { // don't want to compare with self
		
				// get centre and radius for current i
				Point iC = objCentre.at(i);
				double iR = objRadius.at(i);
			
				// calculate length between spheres, normalize direction vector and compare to sum of radii
				Point cenVec = (Point){iC.x - c.x, iC.y - c.y, iC.z - c.z};
				double cenVecLength = sqrt(pow(cenVec.x,2) + pow(cenVec.y,2) + pow(cenVec.z,2));
				cenVec = (Point){cenVec.x/cenVecLength, cenVec.y/cenVecLength, cenVec.z/cenVecLength};
				double overlap = (r+iR) - cenVecLength; 
				
				// determining if an intersection occurs, if so added to vector
				// also checks for case of sphere completely inside another sphere!
				if(overlap >= -0.0001 && cenVecLength > max(r-iR, iR-r)-0.0001) // 0.0001 value to catch rounding error
					inter.push_back((idOverVecLen){i, overlap, cenVec, cenVecLength});
					
			}	
		}
		
		// calculate details of specific intersection
		if((int)inter.size() != 0)
			calculateIntersection(id, inter);
	
		// return number of intersections
		return((int)inter.size()); 
	}
}

/**
 * draws a circle given a specified centre and radius. called from
 * the function drawIntersections when a new frame is rendered.
 *
 * @see paintGL()
 * @see drawIntersections()
 * @param cen centre of circle to draw
 * @param rad radius of circle to draw
 */
void vis::drawCircle(intDraw circ) {
	
	// get the direction vector as this will be orthogonal vector of coi
	Point dirVec = circ.vec;	
	
	// set up the translation matrix to move the circle to correct location
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glTranslatef(circ.cen.x, circ.cen.y, circ.cen.z); // translate to centre point
	glScalef(circ.rad, circ.rad, circ.rad);	// scale to radius size
	/* current orthogonal vector (0, 0, 1), we need to pitch & yaw rotate to dirVec,
	   this can be done using vector cross products to give us the axis of rotation */
	glRotatef((180*acos(dirVec.z)/M_PI), -dirVec.y, dirVec.x, 0.0); // cross product 
	
	// standard circle of with radius 1 about (0, 0, 0) on y x-y plane
	// as translation matrix has been set up above this will be drawn at position & orientation
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < circPoints; i++) {		
		
		double angle = ((double)i/(double)circPoints)*2*M_PI; // calc current angle
			
		// calc current point on polygon
		Point p = (Point){sin(angle), cos(angle), 0.0};
		
		// add point to GL_POLYGON
		glNormal3d(p.x, p.y, p.z);
		glVertex3d(p.x, p.y, p.z);
		
	}
	glEnd();
	
	glPopMatrix(); // return to normal modelview matrix
	
	return;	
}

/** 
 * makes calls to draw the intersections saved in the global variable 
 * coiDraw when rendering each new frame.
 *
 * @see drawCircle()
 * @see paintGL()
 */
void vis::drawIntersections() {

	// for each intersection
	for(int i = 0; i < (int)coiDraw.size(); i++) {
	
		// get details of circle of intersection from vector
		intDraw iCoi = coiDraw.at(i);
		
		// if tangent case then set appropriate circle diametre
		if(iCoi.rad == 0.0)
			iCoi.rad = 0.05*objRadius.at(iCoi.id1);
		
		drawCircle(iCoi); // draw circle
	}
	return;	
}

/**
 * renders for picking using the colour hack. creates unique colour for 
 * each object then determines which object the user has picked depending
 * on the colour of the pixel under the mouse. triggered by right click.
 * 
 * @see paintGL()
 * @see mouseReleaseEvent()
 * @return integer id of picked object
 */
int vis::getPicked() {

	glDisable(GL_DITHER); // disable dithering to ensure all objects drawn in true colour
	
	// render each object in unique colour, index in vector determines red and green value
	for(int i = 0; i < (int)objCentre.size(); i++) {
		int r = i%255; // generate r value
		int g = i/255; // generate g value
		glColor3ub(r, g, 0); // set unique colour
		drawSphere(objCentre.at(i), objRadius.at(i)); // draw sphere		
	}
	
	glEnable(GL_DITHER); // reenable dithering
	
	// create variable to store pick data
	unsigned char data[3];
	// get viewport size, will be needed to calculate mouse position
	GLint view[4];
	glGetIntegerv(GL_VIEWPORT, view);
	// get pixel colour under mouse location (y coordinates inverted)
	glReadPixels(pickXY.x, view[3]-pickXY.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	int pickObj = (int)(data[0]+(255*data[1])); // convert back to id
	colourPicking = 0; // reset flag	
	return(pickObj);// return picked object
}

/**
 * draws cube with side lengths 1 about the origin from points held in
 * cubePoints variable. 
 *  
 * @see selectionCube()
 * @param p array of int containing each point on cube face
 */
void vis::drawCubeFace(int *p) {
	
	// loop through each point to draw the face
	for(int i = 0; i < 4; i++) {
		Point pi = cubePoints.at(p[i]); // get point
		glNormal3d(pi.x, pi.y, pi.z);
		glVertex3d(pi.x, pi.y, pi.z);
	}
	
	return;
}

/**
 * renders a wireframe cube around currently selected object (if any) by 
 * drawing each face one at a time.
 *  
 * @see paintGL()
 * @see drawCubeFace()
 * @param id of sphere that cube should be drawn around
 */
void vis::selectionCube(int id) {
	
	// set up transformation radius to draw cube correctly
	glMatrixMode(GL_MODELVIEW); // load matrix
	glPushMatrix(); // save current modelview matrix
	glTranslatef(objCentre.at(id).x, objCentre.at(id).y, objCentre.at(id).z);
	double side = 2*(objRadius.at(id)); // compute side length
	glScalef(side, side, side);
	
	// creating face point loops for rendering
	int face[4][4] = {{0, 1, 3, 2},
			  {1, 5, 7, 3},
			  {5, 4, 6, 7},
			  {4, 0, 2, 6}};
	
	// draw each face one at a time, each is a different line loop primitive
	for(int i=0; i<4; i++) {
		glBegin(GL_LINE_LOOP);
		drawCubeFace(face[i]);
		glEnd();
	}
	
	glPopMatrix(); // reload previous modelview matrix	
	
	return;
}

/**
 * creates the context menu when picking occurs. available options depend
 * upon whether an object or the background is selected. handles signals 
 * depending what option is picked by the user and calls corresponding 
 * slot.
 *
 * @see colChangeSlot()
 * @see transChangeSlot()
 * @see printIntersectionSlot()
 * @see updateDrawList()
 * @see printAllIntersections()
 * @see drawAllIntersections()
 * @see createSlideDialog()
 * @see takeScreenshot()
 * @see fileLoader()
 */
void vis::createContextMenu() {
	
	QMenu menu; // create the menu widget
	
	// create menu actions, these will be the options on our menu
	QAction* changeColour = new QAction("Change Colour", this);
	QAction* changeTransparency = new QAction("Change Transparency", this);
	QAction* printIntersections = new QAction("Print Intersections", this);
	QAction* drawIntersections = new QAction("Draw Intersections", this);
	QAction* printAllIntersections = new QAction("Print All Intersections", this);
	QAction* drawAllIntersections = new QAction("Draw All Intersections", this);
	QAction* slideshowMode = new QAction("Slideshow Mode", this);
	QAction* screenshot = new QAction("Take Screenshot", this);
	QAction* loadNewFile = new QAction("Load New File", this);
	
	// if no particular object selected disable object specific options
	if(pickID == -1) { 
		changeColour->setEnabled(0);
		changeTransparency->setEnabled(0);
		printIntersections->setEnabled(0);
		drawIntersections->setEnabled(0);	
	}
	
	if(slideshowFlag == 1) {  // if in slideshow mode disable all but screenshot
		changeColour->setEnabled(0);
		changeTransparency->setEnabled(0);
		printIntersections->setEnabled(0);
		drawIntersections->setEnabled(0);	
		printAllIntersections->setEnabled(0);
		drawAllIntersections->setEnabled(0);
		slideshowMode->setEnabled(0);
		loadNewFile->setEnabled(0);
	}
	
	if(fileLoaded == 0) { // case where no file loaded
		changeColour->setEnabled(0);
		changeTransparency->setEnabled(0);
		printIntersections->setEnabled(0);
		drawIntersections->setEnabled(0);	
		printAllIntersections->setEnabled(0);
		drawAllIntersections->setEnabled(0);
		slideshowMode->setEnabled(0);
		screenshot->setEnabled(0);
	}
	
	// populate menu with actions and seperators
	menu.addAction(changeColour);
	menu.addAction(changeTransparency);
	menu.addSeparator();
	menu.addAction(printIntersections);
	menu.addAction(drawIntersections);
	menu.addSeparator();
	menu.addAction(printAllIntersections);
	menu.addAction(drawAllIntersections);
	menu.addSeparator();
	menu.addAction(slideshowMode);
	menu.addSeparator();
	menu.addAction(screenshot);
	menu.addSeparator();
	menu.addAction(loadNewFile);
	
	// create QSignalMapper type to pass parameters to for print intersections slot
	QSignalMapper *pickMapper = new QSignalMapper(this);
	
	// link each menu option to respective slot to control action
	connect(changeColour, SIGNAL(triggered()), this, SLOT(colChangeSlot()));
	connect(changeTransparency, SIGNAL(triggered()), this, SLOT(transChangeSlot()));
	connect(printIntersections, SIGNAL(triggered()), pickMapper, SLOT(map()));
	connect(drawIntersections, SIGNAL(triggered()), this, SLOT(updateDrawList()));
	connect(printAllIntersections, SIGNAL(triggered()), this, SLOT(printAllIntersections()));
	connect(drawAllIntersections, SIGNAL(triggered()), this, SLOT(drawAllIntersections()));
	connect(slideshowMode, SIGNAL(triggered()), this, SLOT(createSlideDialog()));
	connect(screenshot, SIGNAL(triggered()), this, SLOT(takeScreenshot()));
	connect(loadNewFile, SIGNAL(triggered()), this, SLOT(fileLoader()));
	
	// link the current pick id with the slot via mapper
	pickMapper -> setMapping(printIntersections, pickID);
	connect(pickMapper, SIGNAL(mapped(int)), this, SLOT(printIntersectionSlot(int)));
	
	// create context menu at cursor
	menu.exec(QCursor::pos());
	
	return;	
}

/**
 * scroll mode command to move selection to next object. either moves one
 * index value forwards if wheel scrolled up or one id value backwards if
 * wheel scrolled down. also scrolls if "+" or "-" key pressed. changes 
 * transparency values accordingly.
 *  
 * @see wheelEvent()
 * @see keyPressEvent()
 * @param delta the rotation amount of the scroll wheel
 */
void vis::scroll(float delta) {

	// if not in scroll mode already, save rgba properties and setup scroll mode
	if(scrollFlag==0) {
		RGBAHold = objColour;
		for(int i = 0; i < (int)objColour.size(); i++) // lower transparency of all objects
			objColour.at(i).A = 0.18; 
	} else // set previous objects transparency back to low transparency
		objColour.at(pickID).A = 0.18; 
		
	scrollFlag=1; // set flag
			
	if(delta > 0.0) { // wheel scrolled forward
	
		if(pickID != (int)objCentre.size()-1) // normal case
			pickID++;
		else // last object in vector selected case
			pickID = 0;
			
	} else { // wheel scrolled backwards
	
		if(pickID!=0) // normal case
			pickID--;
		else // first object in vector selected case
			pickID = (int)objCentre.size()-1;
	}
	
	// set currently selected objects transparency to near opaque
	objColour.at(pickID).A = 0.95;
	
	// update the screen text vector to display picked information
	screenTextSelect(pickID);
	
	updateGL(); // redraw cube
}

/**
 * function to print specific intersection between two objects and add interstion
 * to draw list. used when a new slide is created in slideshow pair mode.
 *  
 * @see createSlide()
 * @param a index of first sphere
 * @param b index of second sphere
 */
void vis::handleIntersection(int a, int b) {
	
	screenText.clear(); // clear screen text vector
	
	// print intersection first, initialize iterator
	vector<intDraw>::iterator it = coi.begin();
	advance(it, coiBegin.at(a)); // move to positon of a's intersections
	int intFlag = 0; // flag that indicates whether intersection is present
	stringstream sInter; // string stream to hold intersection output string
	
	if(it!=coi.end()) { // error check, if it is not pointing to end of vector
		intDraw itCoi = *it; // get coi at positon
		// loop through coi vector until intersection found or end of intersections
		while(itCoi.id1 == a && intFlag == 0) {
		
			if(itCoi.id2 == b) { // if specific intersection found
			
				if(itCoi.rad == 0.0) // tangent case
					sInter << "Sphere " << itCoi.id1 << " is tangent to sphere " 
				               << itCoi.id2 << " at point (" << itCoi.cen.x << 
				               ", " << itCoi.cen.y << ", " << itCoi.cen.z << ")\n";
				else // intersection case
					sInter << "Sphere " << itCoi.id1 << " intersects sphere " 
				     	       << itCoi.id2  << " with circle of intersection located about (" 
				     	       << itCoi.cen.x << ", " << itCoi.cen.y << ", " << itCoi.cen.z 
				     	       << ") with radius " << itCoi.rad << "\n";
				intFlag = 1; // intersection occurs, set flag	
				screenTextIntersect(itCoi); // updates screenText vector
				
			} else { // if intersection not found
			
				it++; // iterate iterator
				itCoi = *it; // get new coi
		
			}
		}
		
		if(intFlag == 0) // if no intersection occurs
			sInter << "No intersection occurs between sphere " << a << 
			       " and sphere " << b << "\n";
	}
	
	// print intersection information
	cout << sInter.str() << endl;
	
	return;
}

/** 
 * resets all variables back to their original state when slideshow mode
 * is finished and resets flags. this is either triggered by the timer on the 
 * last slide ending or cycling through all slides by keypress.
 *
 * @see setSlideshow()
 * @see keyPressEvent()
 */
void vis::stopSlideshow() {
	slideshowFlag = 0; // reset flag
	objColour = RGBAHold; // reset transparencies
	keySphereList.clear(); // reset the key list vector
	keyPairList.clear(); // reset the key pair vector
	screenText.clear(); // clear text being drawn on screen
}

/**
 * function that makes the program wait for specified number of seconds through
 * use of clock_t variables and the get clock ticks function clock().
 * required for time transition slideshow mode.
 *  
 * @see setSlideshow()
 * @param s number of seconds to wait
 */
void vis::waitFunc(int s) {

	clock_t start, end; // two clock vars for timing
	start = clock(); // get current time
	end = clock(); // initialize counter clock
	while((double)(end-start)/CLOCKS_PER_SEC < s) // wait program s seconds
		end = clock();
		
}

/**
 * sets up objects so the next slide may be rendered in slideshow mode.
 * sets transparencies and draws intersections.
 *
 * @see setSlideshow()
 * @see stopSlideshow()
 */
void vis::createSlide() {
	
	// reset transparencies
	for(int i = 0; i < (int)keySphereList.size(); i++)
		objColour.at(keySphereList.at(i)).A = 0.05;
	
	// individual mode case: set transparency for current slide, print and draw intersections
	if(slideData.group == 0) {
	
		objColour.at(keySphereList.at(keyListPos)).A = 0.95; // set transparency 
		printIntersections(keySphereList.at(keyListPos)); // print intersections
		
	// pair mode case: set transparencies, print intersection between objects and draw	
	} else { 
		
		intPair slidePair = keyPairList.at(keyListPos); // get pair
		objColour.at(slidePair.x).A = 0.95; // set transparencies
		objColour.at(slidePair.y).A = 0.95;
		handleIntersection(slidePair.x, slidePair.y); // pass to function to handle intersection
		
	}
	
	keyListPos++; // increment key list position
	return;
}

/**
 * moves specified value from current position in vector to the front of the
 * specified vector. required when rendering a new frame in either slideshow or 
 * scroll mode, as the object we wish to highlight should be bought to front
 * of render queue.
 *
 * @see paintGL()
 * @param val specified value to be swapped to front
 * @param vec vector for swap takes place in
 * @return reordered vector
 */
vector<int> vis::bringToFront(int val, vector<int> vec) {

	// find and erase current pos
	for(int i = 0; i < (int)vec.size(); i++) 
		if(vec.at(i) == val) 
			vec.erase(vec.begin() + i);
		
	vec.insert(vec.begin(), val); // put value at start of order
	
	return vec; // return reordered vector	
}

/**
 * calculates the number of lines required and prints the contents of the screenText 
 * vector to the bottom left of the opengl widget. required each time a new
 * frame is drawn
 *
 * @see paintGL()
 */
void vis::createText() {

	int lines = (int)screenText.size(); // get number of strings needed to print
	glColor3f(1.0, 1.0, 1.0); // set text colour to white
	
	// get viewport size to get y value at bottom of screen
	// will be needed to calculate text position
	GLint view[4];
	glGetIntegerv(GL_VIEWPORT, view);
	
	// print each line in descending height (variable y position)
	for(int i = 0; i < lines; i++) {
		int y = view[3]-20*(lines-i); // calculate y position
		QString text = QString::fromStdString(screenText.at(i)); // convert to QString
		renderText(10, y, text); // render text on screen
	}
}

/**
 * updates the screenText vector by replacing current contents with those
 * of the the object with index specified. does this when an object is picked or 
 * scrolled to.
 *
 * @see getPicked()
 * @see paintGL()
 * @see scroll()
 * @param id index of object that screenText vector to be updated for
 */
void vis::screenTextSelect(int id) {
	
	screenText.clear(); // clear currently held text
	
	// create a stringstream variable and write object information to it
	stringstream text;
	text << "Sphere " << id << ": centre (" << objCentre.at(id).x  << ", " << 
	     objCentre.at(pickID).y << ", " << objCentre.at(id).z << ") radius " 
	     << objRadius.at(id);
	
	// update screenText variable with this string
	screenText.push_back(text.str());
	
	return;	
}

/**
 * updates the screenText vector by adding brief details of specified 
 * intersection to the vector as a string. required in pair slideshow mode
 * and when intersections are printed.
 *
 * @see createSlide()
 * @see printIntersections()
 * @param inter information about the intersection whos details we wish to add to screenText
 */
void vis::screenTextIntersect(intDraw inter) {
	
	stringstream sInter; // string stream to create the string 
	sInter << setprecision(3); // set low precision
		
	// create the string for intersection
	if(inter.rad == 0.0) // tangent case
		sInter << inter.id1 << " tangent to " << inter.id2 << " at (" << inter.cen.x
		        << ", " << inter.cen.y << ", " << inter.cen.z << ")";
	else // intersection case
		sInter << inter.id1 << " intersects " << inter.id2 << ": centre (" << inter.cen.x 
	       	       << ", " << inter.cen.y << ", " << inter.cen.z << ") radius " << inter.rad;
	       	       
	// add string to vector
	screenText.push_back(sInter.str());
	return;	
}

/**
 * prints intersections for currently selected object to standard output.
 * called from context menu. also adds intersections details to screenText vector.
 * called when print options on context menu selected  
 *
 * @see createContextMenu()
 * @see printIntersectionSlot()
 * @see printAllIntersections()
 * @param id id of currently selected object
 */
void vis::printIntersections(int id) {
	
	screenText.clear(); // clears screenText variable so we may update it with new strings
	
	// create string stream that will hold output string, set precision for reals
	stringstream sInter; 
	sInter << setprecision(4);
	
	// initalise iterator for looping through coi, starting at coiBegin location for id
	vector<intDraw>::iterator it = coi.begin();
	advance(it, coiBegin.at(id));
	int interFlag = 0; // flag to indicate if an intersection occurs
	
	if(it!=coi.end()) {
		intDraw itCoi = *it; // get coi at positon
		// loop through coi vector until all intersection strings created
		while(itCoi.id1 == id) {
		
			if(itCoi.rad == 0.0)  // tangent case
				sInter << "Sphere " << itCoi.id1 << " is tangent to sphere " << itCoi.id2 << " at point ("
				       << itCoi.cen.x << ", " << itCoi.cen.y << ", " << itCoi.cen.z << ")\n";
			else // intersection case
				sInter << "Sphere " << itCoi.id1 << " intersects sphere " << itCoi.id2 
				       << " with circle of intersection located about (" << itCoi.cen.x << ", " 
				       << itCoi.cen.y << ", " << itCoi.cen.z << ") with radius " << itCoi.rad << "\n";
				       
			screenTextIntersect(itCoi); // update screenText vector with intersection
		
			interFlag = 1; // set flag to indicate that intersection occurs
			it++; // iterate iterator
			itCoi = *it; // get new coi
		}
	}
	
	// if no intersections take place and not in slideshow mode, add string to indicate this
	if(interFlag==0 && slideshowFlag == 0) { 
		sInter << "Sphere " << id << " does not intersect with any other objects!\n";
		screenText.push_back(sInter.str()); // add this string to screenText
	}
	
	sInter << endl; // add some spacing
	cout << sInter.str(); // print out the intersection information
	
	return;
}

/**
 * clears vectors not reset by initialize function, sets up program to load a new 
 * arrangement. called from file loader when new file chosen
 *
 * @see fileLoader()
 */
void vis::resetVis() {

	// clear vectors
	objCentre.clear(); 
	objRadius.clear();
	objGenKey.clear();
	objColour.clear();
	coiBegin.clear();
	coi.clear();
	coiDraw.clear();
	colour.clear();
	screenText.clear();

}

/**
 * slot to set colour of selected object, called from colour dialog.
 *
 * @see colChangeSlot()
 * @param colID index of object whos colour shall be changed
 */
void vis::setColSlot(int colID) {
	changeColour(pickID, colour.at(colID));
	updateGL(); // redraw frame
}

/**
 * slot to control creation of the colour change dialog, spawned from
 * context menu. colour updates as the value of the the combobox changes via
 * setColSlot function, the current colour is saved if user presses the 
 * confirm button, else the colour returns to its original value if the 
 * "x" button or esc key is pressed.
 *
 * @see createContextMenu()
 * @see setColSlot()
 */
void vis::colChangeSlot() {
	
	// save initial colour value, in case of dialog rejected
	Point startCol = (Point){objColour.at(pickID).R, objColour.at(pickID).G,
				 objColour.at(pickID).B};
	int startColID = 0; // will hold the id of the colour object currently has
	
	// find the index of the original colour, do this by seeing which colour matches
	// the rgb of the object
	for(int i = 0; i<(int)colour.size(); i++) {
		if(startCol.x == colour.at(i).R) {
			if(startCol.y == colour.at(i).G)
				if(startCol.z == colour.at(i).B)
			 		startColID = i;	
		}	
	}
	
	// create the QDialog for changing colour
	QDialog *colDialog = new QDialog(0);
	colDialog->setWindowFlags(Qt::WindowCloseButtonHint); // x button
	// title change and create layout
	colDialog->setWindowTitle("Change Colour"); // title
	QVBoxLayout *colLayout = new QVBoxLayout; // vertical layout
	colLayout->setSizeConstraint(QLayout::SetFixedSize); // fix size
	colLayout->addSpacerItem(new QSpacerItem(150, 0)); // spacer for layout
	colDialog->setLayout(colLayout);
	
	// create the combobox
	QString colourString[16] = {"Red", "Green", "Blue", "Cyan", "Pink", "Yellow",
			            "Brown", "Gold", "Crimson", "Lime", "Dark Green", "Dark Cyan",
			            "Orange", "Purple", "Soft Pink", "Grey"}; // used for combo item creation
	QComboBox *colCombo = new QComboBox; // create our combobox
	// populate combobox with icon and string items
	for(int i = 0; i < 16; i++) {
		colCombo->insertItem(i, colourString[i]);
		colCombo->setItemIcon(i, *colourIcon.at(i)); // icons created when class instanced
	}
	colCombo->setCurrentIndex(startColID);
	colCombo->setMinimumWidth(100); // width set for formattinh
	
	// create the confirm button
	QPushButton *confirm = new QPushButton;
	confirm->setText("Confirm");
	confirm->setMaximumWidth(70); // format button width
	
	// add widgets to dialog
	colDialog->layout()->addWidget(colCombo);
	colDialog->layout()->addWidget(confirm);
	
	// align widgets in centre
	colDialog->layout()->setAlignment(colCombo, Qt::AlignHCenter);
	colDialog->layout()->setAlignment(confirm, Qt::AlignHCenter); 
	
	// connect signals for changes, acceptance and rejection with their slots
	connect(colCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setColSlot(int)));
	connect(confirm, SIGNAL(clicked()), colDialog, SLOT(accept()));
	
	// handle rejection signals with signal mapper, pass original colour to setColSlot
	QSignalMapper *colMapper = new QSignalMapper(this);	
	connect(colDialog, SIGNAL(rejected()), colMapper, SLOT(map()));
	colMapper->setMapping(colDialog, startColID);
	connect(colMapper, SIGNAL(mapped(int)), this, SLOT(setColSlot(int)));
	
	colDialog->show(); // show the dialog
	
}

/**
 * slot to handle a change in the translider value, called from transparency
 * dialog. changes the transparency of the object specified.
 *
 * @see transChangeSlot()
 * @param val index of object whos transparency shall be changed
 */
void vis::transSliderChanged(int val) {
	objColour.at(pickID).A = (double)val/100.0; // set new transparency
	updateGL(); // redraw frame
}

/**
 * slot to control creation of the transparency change dialog, spawned from
 * context menu. transparency of object changes as the slider does, the 
 * transparency value is reset if the dialog is exited by esc key or "x" 
 * button. user confirms transparency change by pressing confirm button.
 *
 * @see createContextMenu()
 * @see transSliderChanged()
 */
void vis::transChangeSlot() {

	// save initial transparency value, in case change cancelled
	int startTrans = (int)(objColour.at(pickID).A*100);

	// create the QDialog for changing transparency with x button
	QDialog *transDialog = new QDialog(0);
	transDialog->setWindowFlags(Qt::WindowCloseButtonHint);
	// change title and create layout for dialog and set layout
	transDialog->setWindowTitle("Change Transparency"); // set title
	QVBoxLayout *transLayout = new QVBoxLayout; // create a new vertical layout
	transLayout->addSpacerItem(new QSpacerItem(200, 0)); // spacer for layout
	transLayout->setSizeConstraint(QLayout::SetFixedSize); // fix dialog size
	transDialog->setLayout(transLayout); 
	
	// create the slider 
	QSlider *transSlider = new QSlider;
	transSlider->setRange(5,95);// range of values
	transSlider->setSliderPosition(startTrans); // start position
	transSlider->setOrientation(Qt::Horizontal); // orientations	
	transSlider->setMaximumWidth(160); // fix sizer slide
	transSlider->setMinimumWidth(160);
		
	// create confirm button
	QPushButton *confirm = new QPushButton;
	confirm->setText("Confirm");
	confirm->setMaximumWidth(70); // format button width
	
	// add widgets to dialog
	transDialog->layout()->addWidget(transSlider);
	transDialog->layout()->addWidget(confirm);
	
	// align widgets centre
	transDialog->layout()->setAlignment(confirm, Qt::AlignHCenter); 
	transDialog->layout()->setAlignment(transSlider, Qt::AlignHCenter); 
	 
	// connect the widgets signals with slots to handle change
	connect(transSlider, SIGNAL(valueChanged(int)), this, SLOT(transSliderChanged(int)));
	connect(confirm, SIGNAL(clicked()), transDialog, SLOT(accept())); // closes window
	
	// handle the signal when "x" button pressed, reset value of transparency
	// need a signal mapper to passes start trans value to transSliderChanged slot
	QSignalMapper *transMapper = new QSignalMapper(this);	
	connect(transDialog, SIGNAL(rejected()), transMapper, SLOT(map()));
	transMapper->setMapping(transDialog, startTrans);
	connect(transMapper, SIGNAL(mapped(int)), this, SLOT(transSliderChanged(int)));
	
	transDialog->show();
}

/**
 * slot that calls printIntersections function for selected object and redraws 
 * to screen. this slot is triggered by selection from the context menu.
 *
 * @see createContextMenu()
 * @see printIntersections()
 * @param id id of currently selected object
 */
void vis::printIntersectionSlot(int id) {
	printIntersections(id); // prints intersections to standard output
	updateGL();
}

/**
 * slot that updates coiDraw vector depending on currently selected object.
 * if object's intersections already drawn then it removes them by clearing them 
 * from the coi vector, else it adds them to the vector. called from context menu.
 *
 * @see createContextMenu()
 */
void vis::updateDrawList() {
	
	/* flag that indicates whether we are adding or removing from coiDraw, 1 if
	   removing, 0 if adding */
	int removeFlag = 0; 
	
	// initalise iterator for looping through intDraw vectors, starting with coiDraw
	vector<intDraw>::iterator it = coiDraw.begin();
	
	// if vec not empty, check if intersections for this object already drawn
	while(removeFlag!=1 && it!=coiDraw.end()) {
		intDraw currentInt = *it; // get current intersection
		if(currentInt.id1 == pickID) // if intersections already present
			removeFlag = 1; // set flag
		else
			it++; // else increment counter
	}
	
	if(removeFlag == 1) { // case where we want to remove from draw list
	
		// calculate number of items to erase then erase them
		int nInts = (coiBegin.at(pickID+1) - coiBegin.at(pickID)); 
		coiDraw.erase(it, it+nInts);
		
	} else { // case where we want to add intersections to draw list

		if(coiBegin.at(pickID) == coiBegin.at(pickID+1)) // case where nothing to add
			cout << "Sphere " << pickID << " does not intersect any objects!\n\n";
		else {
			// add each coi for this object to the coiDraw vector
			for(int i=coiBegin.at(pickID); i<coiBegin.at(pickID+1); i++)
				coiDraw.push_back(coi.at(i));
		}	
	}
	
	/* renders a new frame if slideshow mode isn't enabled, rendering at this 
	   point with slideshow mode enabled would result in error */
	updateGL();
	
	return;
}

/**
 * slot that prints intersections for all objects to standard output. uses 
 * the printIntersections function to do so. called from context menu. 
 *
 * @see printIntersections()
 * @see createContextMenu()
 */
void vis::printAllIntersections() {

	for(int i = 0; i < (int)objCentre.size(); i++) {
		printIntersections(i); // print intersections for each objects
	}
	// clear screenText vector, dont want this text to be drawn to screen
	screenText.clear(); 

	return;
}

/**
 * slot that updates coiDraw vector to include all objects. however if all 
 * objects are currently drawn, clears coiDraw. called from context menu
 *
 * @see createContextMenu()
 */
void vis::drawAllIntersections() {
	
	if(coiDraw.size() == coi.size()) // case where all objects are drawn already
		coiDraw.clear(); // empty vector
	else // case where objects not all drawn
		coiDraw = coi; // add all objects to draw list
	
	updateGL(); // render to screen
	return;
}

/**
 * slot that creates the dialog that gets user parameters for slideshow mode. 
 * employs a grid layout within a box layout containing 3 QLabels and 3 comboboxes.
 * the user confirms their parameters and starts slideshow mode by pressing the confirm
 * button, which triggers the setSlideshow slot to initialize variables for
 * slideshow mode. called from context menu.
 *
 * @see createContextMenu()
 * @see setSlideshow()
 */
void vis::createSlideDialog() {

	// create the dialog, set title and create layout
	QDialog *slideDialog = new QDialog(0);
	slideDialog->setWindowFlags(Qt::WindowCloseButtonHint);
	slideDialog->setWindowTitle("Slideshow Mode");
	QVBoxLayout *slideLayout = new QVBoxLayout; // vertical box layout
	slideLayout->setSizeConstraint(QLayout::SetFixedSize); // fix dialog size
	
	// create layout for the labels and comboboxes
	QGridLayout *comboLayout = new QGridLayout;
	
	// create the labels for each parameter and add to layout
	comboLayout->addWidget(new QLabel(" Key:  "), 1, 1, Qt::AlignRight);
	comboLayout->addWidget(new QLabel(" Transition:  "), 2, 1, Qt::AlignRight);
	comboLayout->addWidget(new QLabel(" Grouping:  "), 3, 1, Qt::AlignRight);
	
	// create the key combobox and then add to the layout
	QComboBox *keyCombo = new QComboBox;
	for(int i = 0; i < (int)key.size(); i++) // add combobox items from list of unique keys
		keyCombo->insertItem(i, QString::fromStdString(key.at(i)));
	keyCombo->setMinimumWidth(120); // set width for formatting
	comboLayout->addWidget(keyCombo, 1, 2, Qt::AlignHCenter);
	
	// create the transition combo box and add to layout	
	QComboBox *transCombo = new QComboBox;
	transCombo->insertItem(0, "Key Press"); // add items
	transCombo->insertItem(1, "Timer");
	transCombo->setMinimumWidth(120); // set width for formatting
	comboLayout->addWidget(transCombo, 2, 2, Qt::AlignHCenter);
	
	// create the grouping combo box and add to layout	
	QComboBox *groupCombo = new QComboBox;
	groupCombo->insertItem(0, "Individual"); // add items
	groupCombo->insertItem(1, "Pair");
	groupCombo->setMinimumWidth(120); // set width for formatting
	comboLayout->addWidget(groupCombo, 3, 2, Qt::AlignHCenter);
	
	// create the confirm button
	QPushButton *confirm = new QPushButton;
	confirm->setText("Confirm");
	confirm->setMaximumWidth(70); // format button width
	
	// add combo layout and confirm button to dialog layout and set layout
	slideLayout->addLayout(comboLayout);
	slideLayout->addWidget(confirm);
	slideLayout->setAlignment(confirm, Qt::AlignHCenter); 
	slideDialog->setLayout(slideLayout);
	
	// create a variable storing user selected parameters, transition and group data stored as int
	int transVal, groupVal;
	(transCombo->currentText() == "Key Press") ? (transVal = 0) : (transVal = 1);
	(groupCombo->currentText() == "Individual") ? (groupVal = 0) : (groupVal = 1);
	string keyVal = keyCombo->currentText().toStdString(); // get key from combo as a string
	slideData = (slideParam){keyVal, transVal, groupVal}; // create slide data var
	
	// connecting change in combobox values to trigger change in slideData
	connect(keyCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(keyChange(QString)));
	connect(transCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(transChange(QString)));
	connect(groupCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(groupChange(QString)));
	
	// connecting confirmation signal so dialog closes and slideshow mode setup
	connect(confirm, SIGNAL(pressed()), slideDialog, SLOT(accept()));
	connect(slideDialog, SIGNAL(accepted()), this, SLOT(setSlideshow()));
	
	slideDialog->show(); // show slideshow mode dialog
}

/**
 * slot that sets up program for slideshow mode by setting variables and flags
 * required depending on user specified parameters. creates lists of which
 * objects need to be highlighted for each slide and carries out entire 
 * slideshow if time transition selected.
 *
 * @see createSlideDialog()
 * @see createSlide()
 */
void vis::setSlideshow() {

	// save initial RGBA values of all objects
	RGBAHold = objColour;
	
	// set the slideshow mode flag and set key list position to 0
	slideshowFlag = 1;	
	keyListPos = 0;	
	pickID = -1; // deselect object
	
	// get list of objects with key value specified, store in keySphereList vec
	for(int i = 0; i < (int)objGenKey.size(); i++) 
		if(objGenKey.at(i).key == slideData.key) 
			keySphereList.push_back(i); // add to key list
	
	if(slideData.group == 1) { // if pair mode selected
	
		if((int)keySphereList.size() == 1) {// error catching, cant do pairs if solo object!
			cout << "Error! Only One Object Exists With Specified Key!\n";
			stopSlideshow(); // exit slideshow mode
			return;
		} else { // create list of pairs, stored in keyPairList vector
			for(int i = 0; i < (int)keySphereList.size() - 1; i++) // scroll through objects making pairs
				for(int j = i + 1; j < (int)keySphereList.size(); j++)
					keyPairList.push_back((intPair){keySphereList.at(i),keySphereList.at(j)});
		}		
	}
	
	// either create first slide and draw to screen if keypress mode
	if(slideData.trans == 0) {
		createSlide();
		updateGL();
	} else { // else carry out entire slideshow if timer mode
	
		// create and draw first slide
		createSlide();
		updateGL();
		
		// get the number of loops required
		int numSlides;
		if(slideData.group == 0) 
			numSlides = (int)keySphereList.size();
		else
			numSlides = (int)keyPairList.size();
		
		// loop through remaining slides on timer
		while(keyListPos!=numSlides) {
		
			waitFunc(10); // wait 10 secs
			// create slide and update screen	
			createSlide();
			updateGL();
		}
		
		waitFunc(10); // wait 10 secs
		stopSlideshow(); // reset variables
	}
	
	return;
}

/**
 * slot that handles  value changes in the key combo box within the slideshow
 * mode dialog.
 *
 * @see createSlideDialog()
 * @param key newly selected string value of key
 */
void vis::keyChange(QString key) {
	string keyVal = key.toStdString();
	slideData.key = keyVal;
}

/**
 * slot that handles value changes in the transition combo box within the slideshow
 * mode dialog.
 *
 * @see createSlideDialog()
 * @param trans newly selected transition parameter
 */
void vis::transChange(QString trans) {
	int transVal;
	(trans == "Key Press") ? (transVal = 0) : (transVal = 1);
	slideData.trans = transVal;
}

/**
 * slot that handles value changes in the group combo box within the slideshow
 * mode dialog.
 *
 * @see createSlideDialog()
 * @param group newly selected grouping parameter
 */
void vis::groupChange(QString group) {
	int groupVal;
	(group == "Individual") ? (groupVal = 0) : (groupVal = 1);
	slideData.group = groupVal;
}

/**
 * slot that takes a screenshot of the current frame and saves it as a png
 * in the screenshots folder. the current date and time are used as a filename.
 * called from context menu.
 *
 * @see createContextMenu()
 */
void vis::takeScreenshot() {
	
	// grab the currently rendered frame and save as QImage
	QImage frame = grabFrameBuffer(true);
	
	// get the current time and convert it into filename string
	char stringTime[100]; // will hold the time as a string
	time_t currentTime = time(NULL); // get raw time data
	 // convert time to string (as filename)
	strftime(stringTime, 100, "screenshots/image_%m-%d_%H%M%S.png", localtime(&currentTime));
	QString filename = QString::fromUtf8(stringTime); // convert to QString format
	
	// create a dialog to state that the screenshot has either been saved or failed
	QDialog *screenDialog = new QDialog(0);	
	screenDialog->setWindowTitle("Screenshot");
	
	// create a dialog layout
	QVBoxLayout *screenLayout = new QVBoxLayout; // vertical box layout
	screenLayout->setSizeConstraint(QLayout::SetFixedSize); // fix dialog size
	
	// create "OK" button to accept the dialog
	QPushButton *okButton = new QPushButton;
	okButton->setText("OK");
	okButton->setMaximumWidth(50); // format button width	
	
	// save image to file, if statement true then file saved succesfully
	if(frame.save(filename, "PNG")) // saved succesfully case
		screenLayout->addWidget(new QLabel("Screenshot saved succesfully!"));
	else // saving failed case
		screenLayout->addWidget(new QLabel("Screenshot save failed!"));
		
	// add OK button to layout and centre it
	screenLayout->addWidget(okButton);
	screenLayout->setAlignment(okButton, Qt::AlignHCenter);
	screenDialog->setLayout(screenLayout); // set layout
	
	// connect OK button to slot that dismisses dialog
	connect(okButton, SIGNAL(pressed()), screenDialog, SLOT(accept()));
	
	screenDialog->show(); // display dialog
}

/**
 * slot that creates a file loader to load a new arrangement to the 
 * screen. file loader allows navigation through files to select a text
 * file.
 *
 * @see createContextMenu()
 * @return 0 if a file loaded succesfully, else 1
 */
int vis::fileLoader() {
	
	QString QStrFileName; // QString to hold desired file name to be opened
	
	// use Qt QFileDialog to get file user wishes to load
	QStrFileName = QFileDialog::getOpenFileName(this, tr("Open New Arrangement"),
		   "", tr("Text files (*.txt);;All files (*.*)"));
	
	if(QStrFileName != NULL) { // case when something is selected and the dialog is not cancelled
	
		// convert from QString to char*
		char* fileName; // char* that will be used to set new data
		QByteArray array = QStrFileName.toLocal8Bit(); // intemediary conversion to byte array
		fileName = array.data(); // convert to char*
	
		// reset necessary vectors
		resetVis();
	
		// load data from new file
		if(setData(fileName) == 1) { // if error
			cout << "ERROR: file could not be loaded!\n";
			return 1;
		} else {// normal case
			initializeGL(); // reinitialize program
			screenText.push_back("Right click for menu"); // display prompt
			updateGL(); // redraw screen
		}
		
	} else { // case where nothing specified
		cout << "ERROR: no file specified!\n";
		return 1;
	}
	
	return 0;
}	

/**
 * protected function, required to define a QGLWidget. initialises environment 
 * for OpenGL rendering when instance called. determines which sphere geometry 
 * to use. initializes variables and flags. creates points for sphere and cube
 * geometry. sets up camera and lighting.
 */
void vis::initializeGL() {

	// determine the value of circpoints depending on how many objects to render
	int sphereNumber[6] = {175, 150, 125, 100, 75, 50};
	int circNumber[6] = {41, 45, 50, 58, 71, 100};
	circPoints = 38; // value if over 175 objects
	for(int i = 0; i < 6; i++) { // determine geometry based on number of spheres
		if((int)objCentre.size() <= sphereNumber[i])
			circPoints = circNumber[i];
	}	
	
	// initialise sphere and cube points
	spherePoints = makeSpherePoints(circPoints);
	cubePoints = makeCubePoints();
	
	// get list of unique key values
	key = getKeyList();
	
	// initialize counter to hold each object's cois starting position in vector
	int startPos = 0;
	
	// calculate intersections between spheres and store for later
	for(int i = 0; i < (int)objCentre.size(); i++) {
		coiBegin.push_back(startPos); // save the coi start pos
		startPos += intersectsWith(i); // calculations done here and counter incremented
	}
	/* add an extra item into coiBegin that is the end of the vector,
	   allows us to calculate how many intersections one object has for last object */
	coiBegin.push_back(coi.size());
	
	glClearColor(0.0,0.0,0.0,0.0); // black background
	glMatrixMode(GL_PROJECTION); // projection mode to set clipping plane
	glLoadIdentity();
	glFrustum(-2.0,2.0,-1.0,1.0,2.0,1000.0); // sets the clipping plane
	glTranslatef(0.0, 0.0, -10.0); // moves camera back to view scene better
	glMatrixMode(GL_MODELVIEW); // initialise modelview matrix
	glLoadIdentity();
	
	// initialising variables and flags
	scaleFactor = 1.0; // initialise the zoom factor variable
	pRot = yRot = 0.0; // initialise rotation variables
	initColours(); // initialise colour vector
	trans = 0; // initialise translation flag
	colourPicking = 0; // initialise colour picking flag
	pickID = -1; // initialise selected object variable
	scrollFlag = 0; // initialize scroll mode flag, set false
	
	glEnable(GL_DEPTH_TEST); // allows for depth comparison when rendering
	QGLWidget::setAutoBufferSwap(false); // dont autoswap buffers. for picking
	
	// setting up lighting
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); // creating one light, light0
	// now to specify ambient and diffuse intensities, all white
	GLfloat fiAmbient[4] = {0.2, 0.2, 0.2, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, fiAmbient); 
	GLfloat fiDiffuse[4] = {0.8, 0.8, 0.8, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fiDiffuse);
	// set global ambient lighting to illuminate scene more
	GLfloat global_ambient[4] = {0.5, 0.5, 0.5, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	
	// enable blending, this will be used for translucent objects
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/* assign colour for each object based on their key. if there are more than
	   16 keys, some colours will represent 2 key values */
	for(int i = 0; i < (int)objCentre.size(); i++) {
		
		string k = objGenKey.at(i).key; // get key value
		
		for(int j = 0; j < (int)key.size(); j++) { // set colour based on index of key
			if(k == key.at(j)) {
				objColour.at(i).R = colour.at(j%16).R;
				objColour.at(i).G = colour.at(j%16).G;
				objColour.at(i).B = colour.at(j%16).B;
			}
		}
	}
	
}

/**
 * changes size of viewport when widget resized
 * 
 * @param w the new width of the widget
 * @param h the new height of the widget
 */
void vis::resizeGL(int w, int h) {
	
	glViewport(0, 0, w, h); // sets viewport to window size
	
	float ratio = (float)w/(float)h; // calculate window resolution
	
	// now change the frustum to reflect the width and height, this avoids squashing
	glMatrixMode(GL_PROJECTION); // projection mode to set clipping plane
	glLoadIdentity();
	glFrustum(-ratio,ratio,-1.0,1.0,2.0,1000.0); // sets the clipping plane
	glTranslatef(0.0, 0.0, -10.0); // moves camera back to view scene
	glScalef(scaleFactor, scaleFactor, scaleFactor);

}

/**
 * draw a new frame. if standard rendering then a new frame is created based
 * on the current variable settings of the program and swapped to front buffer.
 * if picking render requested, objects rendered by getPicked function to 
 * determine what object the user has selected by drawing to the back buffer.
 */ 
void vis::paintGL() {
	
	glDrawBuffer(GL_BACK); // set to draw on back buffer then swap buffers
	if(colourPicking == 0) {
		
		// create the render order
		vector<int> renderOrder = sphereOrder();
		
		// if in scroll mode, need to reorder so the selected is the first object rendered
		if(scrollFlag == 1) {
		
			renderOrder = bringToFront(pickID, renderOrder);
			
		// if in slideshow mode, need to reorder so current slide sphere(s) rendered first
		} if(slideshowFlag == 1 ) {
			
			if(slideData.group == 0) // if in individual mode
				renderOrder = bringToFront(keySphereList.at(keyListPos-1), renderOrder);
			if(slideData.group == 1) { // if in pair mode
				renderOrder = bringToFront(keyPairList.at(keyListPos-1).x, renderOrder);
				renderOrder = bringToFront(keyPairList.at(keyListPos-1).y, renderOrder);
			}
		}
	
		// clearing screen first
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// initialise standard surface properties and light position for all objects
		GLfloat fPosition[4] = {1.0, 1.0, 1.0, 0.0}; // light position
		glLightfv(GL_LIGHT0, GL_POSITION, fPosition); // setting light position
	
		// drawing intersections first, draw them solid white
		RGBA white = (RGBA){1.0, 1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat*)&white);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&white);
		drawIntersections();
		
		// drawing selection cube if an object is currently selected
		if(pickID != -1)
			selectionCube(pickID);
	
		// draw objects from vectors, specify surface properties from vector
		for(int i = 0; i < (int)renderOrder.size(); i++) {
			// get colour from vector and set properties
			RGBA col = objColour.at(renderOrder.at(i));
			glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat*)&col);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&col);
			// draw the sphere
			drawSphere(objCentre.at(renderOrder.at(i)), objRadius.at(renderOrder.at(i)));
		}
		
		// generate text needed to be printed to screen, if any
       		createText();
	
		// draw frame and render to screen
		QGLWidget::swapBuffers();
		
	} else { // case where colour picking flag is set
	
		glDisable(GL_LIGHTING); // disable lighting for the colour pick
		glClearColor(1.0,1.0,1.0,0.0); // white background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clearing screen
		
		int pick = getPicked(); // determine picked object
		
		// set selected object or deselect if no object selected
		if(pick!=256*255) {// case where obj selected
			pickID = pick; // save id of picked object
			screenTextSelect(pick); // update screen text value with pick id
		} else {// no object selected
			pickID = -1; // set selected object variable to indicate nothing selected
			screenText.clear(); // clear screen text vector
		}
		
		glEnable(GL_LIGHTING); // restore original settings
		glClearColor(0.0,0.0,0.0,0.0);	
		
		updateGL(); // draw new frame to screen to display box selection
		
		createContextMenu(); // call to function to create menu
	}
}

/**
 * interaction handling for the mouses's scroll wheel, used for 
 * camera zoom and scroll mode.
 *  
 * @see scroll()
 * @param event information about the mouse button click
 */
void vis::wheelEvent(QWheelEvent *event) {
	
	if(pickID!=-1) { // allow for scrolling objects when an object selected
		scroll(event->delta()); // pass to scroll function				
	} else { // zoom case
	
		// deg +120 for one roll forward, -120 for one roll back, read this here
		float deg = (float)event->delta();
		deg = deg/120.0; // deg now number of scrolls in + or - dir'n
	
		glMatrixMode(GL_PROJECTION); // change to projection matrix
		if(deg > 0.0) {// wheel scrolled forward
			glScalef(pow(1.1, deg), pow(1.1, deg), pow(1.1, deg)); 
			scaleFactor = scaleFactor*pow(1.1, deg); // update scale factor
		}
		else {// wheel scrolled backward
			glScalef(pow(0.9, -deg), pow(0.9, -deg), pow(0.9, -deg));
			scaleFactor = scaleFactor*pow(0.9, -deg); // update scale factor
		}
	
		event->accept(); // accepts the event
		updateGL(); // redraw to screen
	}
}

/**
 * interaction handling for when a button on the keyboard is pressed,  
 * used for camera zooming and scroll mode, moving between slides in slideshow
 * mode, and exiting scroll and slideshow mode.
 *
 * @see scroll()
 * @see createSlide()
 * @see stopSlideshow()
 * @param event information about the key pressed
 */
void vis::keyPressEvent(QKeyEvent *event) {
	
	int key = event->key(); // get the integer value of key pressed
	glMatrixMode(GL_PROJECTION); // change to projection matrix
	
	if(key == Qt::Key_Equal) { // "+" button pressed
	
		if(pickID == -1) { // nothing selected
			glScalef(1.1f, 1.1f, 1.1f); // zoom in 
			scaleFactor = scaleFactor*1.1; // update scale factor
		} else  // scroll mode, scroll selected
			scroll(1.0);
		
	} else if(key == Qt::Key_Minus) {// "-" button pressed
	
		if(pickID == -1) { // nothing selected
			glScalef(0.9f, 0.9f, 0.9f); // zoom out
			scaleFactor = scaleFactor*0.9; // update scale factor
		} else
			scroll(-1.0);
		
	} else if(key == Qt::Key_Space) { // select in scroll mode
	
		if(slideshowFlag == 1 && slideData.trans == 0) { // if in key press slideshow
			
			// if last slide drawn, exit slideshow mode
			if(slideData.group==0 && keyListPos==(int)keySphereList.size())
				stopSlideshow();
			else if(slideData.group==1 && keyListPos==(int)keyPairList.size())
				stopSlideshow();
				
			else  // otherwise prepare new slide
				createSlide(); 		
		}
		
	} else if(key == Qt::Key_Escape) {// quit scroll or slideshow mode
	
		if(scrollFlag == 1) { // if in scroll mode
		
			scrollFlag = 0; // deset scroll flag
			objColour = RGBAHold; // reset transparencies
			pickID=-1; // deselect item
			screenText.clear(); // clear screen text variable
			
		} else if(slideshowFlag == 1) { // if in slideshow mode
			stopSlideshow(); // reset sideshow variables
		
		} else { // case of no mode, deselects the object and clears screen text
			pickID=-1;
			screenText.clear();
			updateGL(); // draw new frame 
		}
	}
		
	event->accept(); // accepts the event
	updateGL(); // redraw to screen
}

/**
 * interaction handling for when a button on the mouse is pressed,  
 * stores the start position of the mouse for translations and rotations
 * 
 * @param event information about the mouse button press
 */
void vis::mousePressEvent(QMouseEvent *event) { 
	startPos = event->pos(); // records position that mouse was clicked
}

/**
 * interaction handling for when mouse movements take place, used for
 * camera translations and rotations.
 *  
 * @param event information about the mouse button press
 */
void vis::mouseMoveEvent(QMouseEvent *event) {
		
	// calculate change in x and y from start point to current mouse pos
	float xPos = (float)(event->x() - startPos.x());
	float yPos = (float)(event->y() - startPos.y());
	
	// translate camera case, translates based on current zoom scale and rotation about y
	// we translate in 2 dimensions, up and down in y direction, and left and right in axis
	// parallel to screen. This axis direction needs to be calculated from y rotation
	if(event->buttons() == Qt::RightButton) {
	
		trans = 1; // set flag to indicate a camera translation is taking place
	
		glMatrixMode(GL_MODELVIEW); // load modelview matrix to be translated
		glTranslatef(cos((yRot*M_PI)/180.0)*(1.0/scaleFactor)*(xPos/68.0), // x direction translation
		             (1.0/scaleFactor)*(-yPos/68.0), // y direction translation
		             sin((yRot*M_PI)/180.0)*(1.0/scaleFactor)*(xPos/68.0)); // z direction translation
		
	} else if (event->buttons() == Qt::LeftButton) {
	
		glMatrixMode(GL_PROJECTION); // load projection matrix to be translated
		// rotate x direction movement about yaw axis
		glRotatef(xPos, 0.0, 1.0, 0.0); 
		// we want to keep track of the rotation about the yaw axis, so update var
		yRot += xPos;
		
		// rotate about pitch axis if rotation doesnt exceed limits
		if(-90.0<pRot+yPos && pRot+yPos<90.0) {
			glRotatef(yPos, cos((yRot*M_PI)/180.0), 0.0, sin((yRot*M_PI)/180.0));
			// we want to keep track of pitch rotation so it doesnt go over 90 either way
			pRot += yPos;
		}
		
	}
	
	event->accept(); // accepts event
	updateGL(); // redraw screen
	startPos = event->pos(); // update the start position
	
}

/**
 * interaction handling for when mouse button released, used for picking
 *  
 * @see getPicked()
 * @see createContextMenu()
 * @param event information about the mouse button released
 */
void vis::mouseReleaseEvent(QMouseEvent *event) {

	if(event->button() == Qt::RightButton) { 
		
		if(trans==1){ // case of translation currently taking place
		
			trans = 0; // reset translation flag to 0 as it has ended
			
		} else if(scrollFlag == 1) { // if in scroll mode
		
			scrollFlag = 0; // deset scroll flag
			objColour = RGBAHold; // reset transparencies
			updateGL(); // redraw frame
			createContextMenu(); // spawn context menu for selected
		
		} else if(slideshowFlag!=1) { // case of picking when no "mode" enabled
		
			colourPicking = 1; // set colour picking flag
			pickXY = (intPair){event->x(), event->y()}; // save mouse location
			updateGL(); // render for colour picking
			
		} else { // slideshow mode case, create context menu with only screenshot option
			createContextMenu();
		}	
	}
}
