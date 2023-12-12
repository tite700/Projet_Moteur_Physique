#pragma once

#include "ofMain.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../RegistreForce.h"
#include "../ForceRessort.h"
#include "../Blob.h"
#include "../ForceImpultion.h"
#include "../ForceElastique.h"
#include "../UnitTest.h"
#include "../CorpsRigide.h"
#include "../RegistreForceCorps.h"
#include "../ForceGraviteCorps.h"
#include "../ForceImpulsionCorps.h"
#include "../Cube.h"
#include "../OcTree.h"
#include <vector>
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	//--------------------------------------------------------------
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void FirstFrame();


public:

	ofSpherePrimitive sphere;
	ofRectangle customSquare;
	float timeKeyPressed = 0.0f;
	bool slingshotActive = true;
	bool mouseInSquare = false;
	float trainee = 1.0f;
	float couleur = 1.0f;
	ofColor groundColor = ofColor(0, 255, 0);

	Vecteur3D PointImpact=Vecteur3D(0,0,0);
	float Intensite=0.0;
	bool debut = true;

	ofxFloatSlider surface;
	ofxFloatSlider masse;
	ofxPanel gui;
	ofxToggle balleButton;
	ofxToggle bdfButton;
	ofxToggle laserButton;

	ofRectangle ground;

	//Forces particules
	RegistreForce registreForce;
	float espace = 12; // Espace entre les particules
	float k = 0.0001; // Constante de raideur
	float l0 = 12; // Longueur de repos entre particules
	float limiteElasticite = 10.0;; // Limite d'élasticité

	//Forces Corps
	RegistreForceCorps registreForceCorps;
private:

	//Management

	bool pause = false;

	void runUnitTests();

	//Primitives
	Cube* cube1;
	Sphere* sphere1;
	Sphere* sphere2;
	Sphere* sphere3;


	Cube * cube2;
	Sphere * sphere4;

	Plan* plan1;

	Plan* plan2;
	//OcTree

	OcTree* octree;

	std::vector<Primitive*> primitives = std::vector<Primitive*>();

	//RigidBody
	std::vector<CorpsRigide*> corpsRigides = std::vector<CorpsRigide*>();
	CorpsRigide* cubeRigide;
	CorpsRigide* sphereRigide;
	CorpsRigide* cubeRigide2;

	Vecteur3D hitPoint;
};

