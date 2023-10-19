#pragma once

#include "ofMain.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../RegistreForce.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
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
	ofBoxPrimitive box;
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

	//Forces

	RegistreForce registreForce;

private:
	// Déclarez ici les variables nécessaires pour gérer la simulation
	std::vector<Particule> particules; // Un conteneur pour stocker les particules
};

