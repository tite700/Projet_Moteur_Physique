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

public:

	ofSpherePrimitive sphere;
	ofRectangle customSquare;
	float timeKeyPressed = 0.0f;
	bool slingshotActive = false;
	bool mouseInSquare = false;
	float trainee = 1.0f;
	float couleur = 1.0f;

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

	void runUnitTests();

	// Déclarez ici les variables nécessaires pour gérer la simulation
	std::vector<Particule*> particules; // Un conteneur pour stocker les particules
	Blob blob = Blob(10, 9, Vecteur3D(400, 400), 10.0, couleur, trainee);

	Particule* balle1 = new Particule(0.01, 1, 10, 0.5, Vecteur3D(700, 400, 0), Vecteur3D(0, 0, 0));
	Particule* accroche1 = new Particule(0.01, 1, 10, 1, Vecteur3D(700, 200, 0), Vecteur3D(0, 0, 0));

	Particule* balle2 = new Particule(0.01, 1, 10, 0.5, Vecteur3D(800, 400, 0), Vecteur3D(0, 0, 0));
	Particule* accroche2 = new Particule(0.01, 1, 10, 1, Vecteur3D(800, 200, 0), Vecteur3D(0, 0, 0));

	Particule* balle3 = new Particule(0.01, 1, 10, 0.5, Vecteur3D(910, 100, 0), Vecteur3D(0, 0, 0));
	Particule* balle4 = new Particule(0.01, 1, 10, 0.5, Vecteur3D(900, 400, 0), Vecteur3D(0, 0, 0));

	Particule* balle5 = new Particule(0.01, 1, 10, 0.5, Vecteur3D(1000, 400, 0), Vecteur3D(0, 0, 0));
	Particule* accroche5 = new Particule(0.01, 1, 10, 1, Vecteur3D(1000, 200, 0), Vecteur3D(0, 0, 0));

	Particule* balle6 = new Particule(0.01, 1, 50, 1.0, Vecteur3D(271, 520, 0), Vecteur3D(0, 0, 0));

	Particule* bigParticule = new Particule(0.01, 1, 50, 0.0001, Vecteur3D(200, 800, 0), Vecteur3D(0, 0, 0));


	std::vector<CorpsRigide*> corpsrigides; // Un conteneur pour stocker les particules
	CorpsRigide* box1 = new CorpsRigide(Vecteur3D(271, 520, 0), Vecteur3D(200, -100, 0), Vecteur3D(0, 0, 0), Quaternion(0.0, 0.0, 1.0, 0.0), 0.01, Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0));
	CorpsRigide* box2 = new CorpsRigide(Vecteur3D(320, 520, 0), Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0),Quaternion(0.0,0.0,1.0,0.0), 0.01, Vecteur3D(1.0, 0, 0), Vecteur3D(0, 0, 0));
};

