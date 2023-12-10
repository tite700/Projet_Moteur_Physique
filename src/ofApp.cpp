#include "ofApp.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../GraviteParticule.h"
#include "../ForceFrictionCinetique.h"
#include "../ForceRessort.h"
#include "../GenerateurForce.h"
#include "../RegistreForce.h"
#include "../ForceCable.h"
#include "../ofMain.h"
#include "../UnitTest.cpp"
#include "../Matrix3.h"

ofEasyCam cam;  // Declare an ofEasyCam object
void ofApp::setup() {

	// Set up the camera
	cam.setPosition(0, 0, 1000);
	cam.setDistance(1000);  // Set the initial distance from the camera to the center
	//cam.disableMouseInput();  // Disable the default mouse interaction for camera control


	//cam.enableOrtho();
	//cam.setNearClip(-100000);
	//cam.setFarClip(100000);
	//cam.setVFlip(true);

	//Primitives tests


	std::vector<Vecteur3D> normals = std::vector<Vecteur3D>();
	normals.push_back(Vecteur3D(1, 0, 0));
	normals.push_back(Vecteur3D(0, 1, 0));
	normals.push_back(Vecteur3D(0, 0, 1));
	//cube1 = new Cube(Vecteur3D(0, 0, 0), 1000);

	sphere1 = new Sphere(Vecteur3D(100, 0, 0), 50);
	sphere2 = new Sphere(Vecteur3D(50, 0, 0), 50);
	sphere3 = new Sphere(Vecteur3D(0, 0, 0), 50);
	primitives.push_back(sphere1);
	primitives.push_back(sphere2);
	primitives.push_back(sphere3);
	//cube2 = new Cube(Vecteur3D(0, 0, 0), 1000);

	//Test unitaires
	//runUnitTests();

	//octree = new OcTree(Vecteur3D(0, 0, 0), 1000, 2, 4);
	//octree->subdivide();
	////Cube* cube3 = new Cube(Vecteur3D(0, 0, 0), 1000);
	//for (Primitive* primitive : primitives) {
	//	octree->addPrimitive(primitive);
	//}

	//octree->print(std::cout);

	//cube2 = new Cube(Vecteur3D(250, 250, 250), 500, Quaternion(0 ,0, 0, 1));
	//sphere4 = new Sphere(Vecteur3D(-30, -25, -25), 50);
	//std::cout << sphere4->intersect(*cube2) << std::endl;
	//std::cout << cube2->intersect(*sphere4) << std::endl;

	cube1 = new Cube(Vecteur3D::zeros(), 200);
	cube2 = new Cube(Vecteur3D(0, 0, 0), 200);
	sphere4 = new Sphere(Vecteur3D(160, 0, 0), 50);
	plan1 = new Plan(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 1));

	cubeRigide = new CorpsRigide(Vecteur3D::zeros(), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube1);
	sphereRigide = new CorpsRigide(Vecteur3D(160, 0, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), sphere4);
	cubeRigide2 = new CorpsRigide(Vecteur3D(0, 0, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube2);
	//corpsRigides.push_back(cubeRigide);
	//corpsRigides.push_back(sphereRigide);
	corpsRigides.push_back(cubeRigide2);
	cubeRigide2->setVelocite(Vecteur3D(0, 0, 0));
	cubeRigide2->setOrientation(Quaternion(0, 0, 0, 1));

	hitPoint = Vecteur3D(0, 0, 100);
}

void ofApp::FirstFrame() {
	pause = true;
	registreForceCorps.add(cubeRigide2, new ForceImpulsionCorps(hitPoint, 200, Vecteur3D(0, 0, -1)));
}

//--------------------------------------------------------------
int temps = 0;
void ofApp::update() {

	if (pause) {
		return;
	}
	if (temps == 1)
	{
		FirstFrame();
	}
	registreForceCorps.updateForces(ofGetLastFrameTime());
	temps++;
	octree = new OcTree(Vecteur3D(0, 0, 0), 1000, 2, 3);


	for (CorpsRigide* corpsRigide : corpsRigides) {
		corpsRigide->Integrate(ofGetLastFrameTime());
		octree->addCorpsRigide(corpsRigide);
	}

	registreForceCorps.clear();

}

//--------------------------------------------------------------
void ofApp::draw() {

	cam.begin();

	// draw the x-axis in red
	ofSetColor(255, 0, 0);
	ofDrawLine(-2000, 0, 0, 2000, 0, 0);

	// draw the y-axis in green
	ofSetColor(0, 255, 0);
	ofDrawLine(0, -2000, 0, 0, 2000, 0);

	// draw the z-axis in blue
	ofSetColor(0, 0, 255);
	ofDrawLine(0, 0, -2000, 0, 0, 2000);

	for (CorpsRigide* corpsRigide : corpsRigides) {
		corpsRigide->draw();
	}
	hitPoint.drawPoint();
	//plan1->draw();
	//octree->draw();
	//for (Primitive* primitive : primitives) {
	//	primitive->draw();
	//}

	//sphere4->draw();
	//cube2->draw();
	//cube1->draw();

	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		std::cout << "Space pressed, pause" << std::endl;
		pause = !pause;
	}

}

void ofApp::runUnitTests() {
	testConstructors();
	testOperations();
	testMethods();
	testMatrix3();
	testMatrix4();
	TestCorpsRigide();
	testQuaternion();
}	

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {


}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
