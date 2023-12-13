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
#include "../Matrix4.h"
#include "../Quaternion.h"
#include "../ForceFrictionCinetiqueCorps.h"

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

	sphere1 = new Sphere(Vecteur3D(100, 0, 0), 50);
	sphere2 = new Sphere(Vecteur3D(50, 0, 0), 50);
	sphere3 = new Sphere(Vecteur3D(0, 0, 0), 50);
	primitives.push_back(sphere1);
	primitives.push_back(sphere2);
	primitives.push_back(sphere3);

	//Test unitaires
	runUnitTests();

	//Création des primitives
	cube1 = new Cube(Vecteur3D::zeros(), 200);
	cube2 = new Cube(Vecteur3D(0, 0, 0), 200);
	cube3 = new Cube(Vecteur3D(0, 0, 0), 200);
	cube4 = new Cube(Vecteur3D(0, 0, -500), 200);
	plan1 = new Plan(Vecteur3D(0, -100, 0), Quaternion::fromEulerAngles(Vecteur3D(90, 0, 0) * (PI/180)));

	//Création des corps rigides
	cubeRigide = new CorpsRigide(Vecteur3D(100, 400, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube1);
	cubeRigide2 = new CorpsRigide(Vecteur3D(0, 0, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion::fromEulerAngles(Vecteur3D(0,0,0)), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube2);
	cubeRigide3 = new CorpsRigide(Vecteur3D(-250, 0, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion::fromEulerAngles(Vecteur3D(0, 0, 0)), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube3);
	cubeRigide4 = new CorpsRigide(Vecteur3D(0, 50, 500), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion::fromEulerAngles(Vecteur3D(0, 0, 0)), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube4);
	corpsRigides.push_back(cubeRigide);
	corpsRigides.push_back(cubeRigide2);
	corpsRigides.push_back(cubeRigide3);
}

void ofApp::FirstFrame() {

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
	//Création de l'octree
	octree = new OcTree(Vecteur3D(0, 0, 0), 5000, 2, 3);


	for (CorpsRigide* corpsRigide : corpsRigides) {
		octree->addCorpsRigide(corpsRigide);
		corpsRigide->Integrate(ofGetLastFrameTime());
	}

	//Froces entre corpsRigides
	for (CorpsRigide* corpsRigide : corpsRigides) {
		for (CorpsRigide* corpsRigide2 : corpsRigides) {
			if (corpsRigide != corpsRigide2) {
				CollisionHandler::resolveCollisionCubes(corpsRigide, corpsRigide2, &registreForceCorps);
			}
		}

	}

	//Forces génériques
	for (CorpsRigide* corpsRigide : corpsRigides) {
		registreForceCorps.add(corpsRigide, new ForceGraviteCorps());
		registreForceCorps.add(corpsRigide, new ForceFrictionCinetiqueCorps(1, 0.001));
		CollisionHandler::resolveCollisionCubePlan(corpsRigide, plan1, &registreForceCorps);
	}
	registreForceCorps.updateForces(ofGetLastFrameTime());
	temps++;
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
	plan1->draw();

	for (Vecteur3D angle : dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getAngles())
	{
		angle.drawPoint();
	}
	if (displayOctree)
	{
		octree->draw();
	}


	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		std::cout << "Space pressed, pause" << std::endl;
		pause = !pause;
	}
	if (key == 'q') {
		displayOctree = !displayOctree;
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
	if (!send && button == 2)
	{
		corpsRigides.push_back(cubeRigide4);
		cubeRigide4->setVelocite(Vecteur3D(0, 0, -500));
		send = true;
	}
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
