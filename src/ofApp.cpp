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
	plan1 = new Plan(Vecteur3D(0, -100, 0), Quaternion::fromEulerAngles(Vecteur3D(90, 0, 0) * (PI/180)));

	cubeRigide = new CorpsRigide(Vecteur3D(0, 400, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube1);
	sphereRigide = new CorpsRigide(Vecteur3D(160, 0, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion(0, 0, 0, 1), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), sphere4);
	
	cubeRigide2 = new CorpsRigide(Vecteur3D(100, 700, 0), Vecteur3D::zeros(), Vecteur3D::zeros(), Quaternion::fromEulerAngles(Vecteur3D(0,0,0)), 1, Vecteur3D::zeros(), Vecteur3D::zeros(), cube2);
	
	corpsRigides.push_back(cubeRigide);
	//corpsRigides.push_back(sphereRigide);
	corpsRigides.push_back(cubeRigide2);
	cubeRigide2->setVelocite(Vecteur3D(0, 0, 0));
	cubeRigide2->setOrientation(Quaternion::fromEulerAngles(Vecteur3D(0, 0, 0) * (PI/180)));
	cubeRigide->setOrientation(Quaternion::fromEulerAngles(Vecteur3D(0, 0, 0) * (PI / 180)));

	hitPoint = Vecteur3D(100, 0, 100);
}

void ofApp::FirstFrame() {
	//pause = true;
	//registreForceCorps.add(cubeRigide2, new ForceImpulsionCorps(hitPoint, 200, Vecteur3D(0, 0, -1)));
	//registreForceCorps.add(cubeRigide2, new ForceImpulsionCorps(Vecteur3D(-100, 0, 100), 200, Vecteur3D(0, 0, -1)));
	//cubeRigide2->setVelocite(Vecteur3D(0, 0, -50));
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
	std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
	octree = new OcTree(Vecteur3D(0, 0, 0), 1000, 2, 3);


	for (CorpsRigide* corpsRigide : corpsRigides) {
		corpsRigide->Integrate(ofGetLastFrameTime());
		octree->addCorpsRigide(corpsRigide);
	}

	//octree->resolveCollisions(&registreForceCorps);
	
	//std::set<std::pair<Primitive*, Primitive*>> possibleCollisions = octree->getPossibleCollisions();
	//std::cout << possibleCollisions.size() << std::endl;
	//std::vector<std::pair<Primitive*, Primitive*>> input(possibleCollisions.begin(), possibleCollisions.end());
	//for (std::pair<Primitive*, Primitive*> pair : input)
	//{
	//	std::cout << pair.first << " and " << pair.second << std::endl;
	//}
	//for (it = octree->getPossibleCollisions().begin(); it != octree->getPossibleCollisions().end(); it = std::next(it))
	//{
	//	std::cout << it->first << " and " << it->second << std::endl;
	//}




	std::vector<CollisionData> collisions = dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->collide(*plan1);
	for (const CollisionData &collision : collisions) {
		std::cout << "Collision" << std::endl;

		//Calcule intensite
		float e = 0;
		//std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
		float v = cubeRigide2->getVelocite().prodscal(plan1->getNormal());
		std::cout << "V:" << v << std::endl;
		float Kup = (e + 1) * v;
		float Kdown = cubeRigide2->getInverseMass();
		float K = Kup / Kdown;
		std::cout << "K:" << K << std::endl;

		registreForceCorps.add(cubeRigide2, new ForceImpulsionCorps(collision.getPointImpact(), K* collision.getInterpenetration()/collisions.size(), (plan1->getNormal() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
	}

	std::vector<CollisionData> collisions2 = dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->collide(*dynamic_cast<Cube*>(cubeRigide->getPrimitive()));
	for (const CollisionData& collision : collisions2) {
		std::cout  << "Collision2" << std::endl;
		float e = 0;
		//std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
		float v = cubeRigide2->getVelocite().prodscal(plan1->getNormal());
		std::cout << "V:" << v << std::endl;
		float Kup = (e + 1) * v;
		float Kdown = cubeRigide2->getInverseMass() + cubeRigide->getInverseMass();
		float K = Kup / Kdown;
		std::cout << "K:" << K << std::endl;
		std::cout << "Interpenetration:" << collision.getInterpenetration() << std::endl;
		registreForceCorps.add(cubeRigide2, new ForceImpulsionCorps(collision.getPointImpact(), K * collision.getInterpenetration()* 15, (plan1->getNormal() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
		registreForceCorps.add(cubeRigide, new ForceImpulsionCorps(collision.getPointImpact(), -K * collision.getInterpenetration()* 15, (-1 * plan1->getNormal() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
	}

	std::vector<CollisionData> collisions3 = dynamic_cast<Cube*>(cubeRigide->getPrimitive())->collide(*plan1);
	for (const CollisionData& collision : collisions3) {
		std::cout << "Collision" << std::endl;

		//Calcule intensite
		float e = 0;
		//std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
		float v = cubeRigide->getVelocite().prodscal(plan1->getNormal());
		std::cout << "V:" << v << std::endl;
		float Kup = (e + 1) * v;
		float Kdown = cubeRigide->getInverseMass();
		float K = Kup / Kdown;
		std::cout << "K:" << K << std::endl;

		registreForceCorps.add(cubeRigide, new ForceImpulsionCorps(collision.getPointImpact(), K * collision.getInterpenetration() / collisions3.size(), (plan1->getNormal() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
	}

		registreForceCorps.add(cubeRigide2, new ForceGraviteCorps());
		registreForceCorps.add(cubeRigide, new ForceGraviteCorps());
		registreForceCorps.add(cubeRigide2, new ForceFrictionCinetiqueCorps(0.1,0.0002));
		registreForceCorps.add(cubeRigide, new ForceFrictionCinetiqueCorps(0.1, 0.0002));
		std::cout << dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->intersect(*dynamic_cast<Cube*>(cubeRigide->getPrimitive())) << std::endl;
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

	for (Plan plan : dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getPlanes()) {
		//plan.draw();
	}

	//dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getPlanes(*dynamic_cast<Cube*>(cubeRigide->getPrimitive()))[0].draw();
	//dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getPlanes(*dynamic_cast<Cube*>(cubeRigide->getPrimitive()))[1].draw();
	//dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getPlanes(*dynamic_cast<Cube*>(cubeRigide->getPrimitive()))[2].draw();
	for (Vecteur3D angle : dynamic_cast<Cube*>(cubeRigide2->getPrimitive())->getAngles())
	{
		angle.drawPoint();
	}
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
