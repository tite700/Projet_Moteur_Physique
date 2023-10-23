#pragma once

#include "ofMain.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../RegistreForce.h"
#include "../ForceRessort.h"

#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	//--------------------------------------------------------------
	void setup() {
		// setup des elements du jeu
		ofSetBackgroundColor(100);
		sphere.setPosition(Vecteur3D(70, 700).vec3());
		customSquare.set(350, 620, 140, 140);

		//Creer un amas de particules qui forme un blop de particules
		float espace = 10;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				float x = 200 + i * espace;
				float y = 400 + j * espace;

				Particule nouvelleParticule(trainee, couleur, 10, 1.0 / 2.0, Vecteur3D(x, y, 0), Vecteur3D());
				particules.push_back(nouvelleParticule);
			}
		}

		for (int i = 0; i < particules.size(); i++) {
			for (int j = i + 1; j < particules.size(); j++) {
				float k = 0.1; // Constante de raideur
				float l0 = espace; // Longueur de repos entre particules
				float limiteElasticite = 10.0; // Limite d'élasticité

				// Ajouter la force de ressort entre les particules i et j
				ForceRessort* forceRessort = new ForceRessort(k, l0, limiteElasticite, &particules[i], &particules[j]);
				registreForce.add(&particules[i], forceRessort);
				registreForce.add(&particules[j], forceRessort);

			}
		}

		//setup du menu 
		gui.setup();
		gui.add(surface.setup("Surface", 50, 10, 150));
		gui.add(masse.setup("Masse", 2, 0.5, 5));
		gui.add(balleButton.setup("Balle", false));
		gui.add(bdfButton.setup("Boule de feu", false));
		//gui.add(laserButton.setup("laser", false));

		// Cr�ez une cible et ajoutez-la � votre conteneur de particules
		Particule cible(1, 500, 50, 0.01f, Vecteur3D(400, 100), Vecteur3D(0, 0));
		//particules.push_back(cible);

		ground.set(0, 850, 2000, 140);


	}
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

	//Forces

	RegistreForce registreForce;

private:
	// Déclarez ici les variables nécessaires pour gérer la simulation
	std::vector<Particule> particules; // Un conteneur pour stocker les particules
};

