#include "ofApp.h"
#include "../Vecteur3D.h"
#include "../Particule.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// setup des elements du jeu
	ofSetBackgroundColor(100);
	sphere.setPosition(Vecteur3D(70, 700).vec3());
	customSquare.set(350, 620, 140, 140);

	//setup du menu 
	gui.setup();
	gui.add(surface.setup("Surface", 50, 10, 150));
	gui.add(masse.setup("Masse", 2, 0.5, 5));
	gui.add(balleButton.setup("Balle", false));
	gui.add(bdfButton.setup("Boule de feu", false));
	//gui.add(laserButton.setup("laser", false));

	// Créez une cible et ajoutez-la à votre conteneur de particules
	Particule cible(1, 500, 50, 0.5f, Vecteur3D(400, 100), Vecteur3D(0, 0));
	particules.push_back(cible);
}

//--------------------------------------------------------------
void ofApp::update() {

	// On vérifie les collisions pour chaque paire de particules dans la scène (stockées dans le vecteur particules)
	for (int i = 0; i < particules.size(); i++) {
		for (int j = i + 1; j < particules.size(); j++) {
			if (Particule::collision(&particules[i], &particules[j])) {
				std::cout << "collision" << std::endl;
				Particule::resolveCollision(&particules[i], &particules[j]);
			}
		}
	}

	//Gestion des boutons du menu
	if (bdfButton) {
		surface = 100;
		masse = 5;
		balleButton = false;
		couleur = 255;
	}
	if (balleButton) {
		surface = 50;
		masse = 2;
		bdfButton = false;
		couleur = 0;
	}

	// Mettez à jour la simulation à chaque frame
	for (auto& particule : particules) {
		particule.integrer(ofGetLastFrameTime()); // Utilisez la durée de la frame pour l'intégration		
	}

	// Vérifiez si la souris est entrée dans la zone du carré
	if (customSquare.inside(mouseX, mouseY)) {
		mouseInSquare = true;
	}
	else {
		mouseInSquare = false;
	}

	// Mettez à jour d'autres éléments de la simulation si nécessaire
	sphere.setPosition(sphere.getGlobalPosition() + Vecteur3D(1, 0).vec3());
}

//--------------------------------------------------------------
void ofApp::draw() {
	//desin du menu
	gui.draw();

	// Dessine les particules
	for (const auto& particule : particules) {
		// Dessinez chaque particule à sa position actuelle
		// Positionnez la boîte à la position de la particule
		ofSetColor(255, 255 - particule.getCouleur(), 255 - particule.getCouleur());
		sphere.set(particule.getSurface(), 32);
		sphere.setPosition(Vecteur3D(particule.getPosition().getX(), particule.getPosition().getY()).vec3());
		sphere.draw();
		ofSetColor(255, 255, 255);
	}

	// Dessine d'autres éléments de la simulation 
	ofSetColor(255, 255, 255);
	ofNoFill();
	ofDrawRectangle(325, 625, 140, 140); // Tete du lance particule
	ofFill();
	ofDrawRectangle(390, 740, 10, 700); // Pied du lance particule


	// Déclare les coordonnées du point de départ des particules qui vont être lancées
	float x1 = 400;
	float y1 = 700;

	// Coordonnées de la position actuelle de la souris
	float x2 = mouseX;
	float y2 = mouseY;

	// Vérifiez si la souris est dans la zone du carré
	if (mouseInSquare) {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(10);
		if (slingshotActive == false) {
			ofDrawBitmapString("CLIQUEZ POUR ARMER UNE PARTICULE ET TIRER !", 225, 600); // Affiche un message texte à l'écran
		}
	}
	else {
		ofSetLineWidth(3);
	}

	// Vérifiez si le bouton de la souris gauche est enfoncé et que le lance pierre est armé d'une particule
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT) && slingshotActive == true) {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(10);
		ofDrawLine(x1, y1, x2, y2); // Dessinez la ligne du lance particule

		ofSetColor(255, 255 - couleur, 255 - couleur);
		sphere.set(surface, 32);
		sphere.setPosition(Vecteur3D(mouseX, mouseY).vec3());
		sphere.draw(); // Dessine la particule (box) témoin pour l'utilisateur au niveau de la position de la souris
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("RELACHER POUR LANCER LA PARTICULE", 250, 600); // Affiche un message texte à l'écran

	}
	if (slingshotActive == false) {
		ofSetColor(255, 255 - couleur, 255 - couleur);
		sphere.set(surface, 32); //La particule statique
		sphere.setPosition(Vecteur3D(395, 700).vec3());
		sphere.draw();
		ofSetColor(255, 255, 255);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
	// Arme le tire
	if (button == OF_MOUSE_BUTTON_LEFT && mouseInSquare == true) {
		slingshotActive = true;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT && slingshotActive == true) {
		// Calculez la distance entre le point de départ et le point de relâchement
		float distance = ofDist(x, y, 400, 700);

		// Calculez l'intensité de la vélocité en fonction de la distance
		float velocityMagnitude = distance * 0.006; // Ajustez le facteur à votre convenance

		// Calculez la direction de la vélocité (unit vector)
		Vecteur3D direction(400 - x, 700 - y);
		direction.normalisation();

		// Créez une nouvelle particule avec la vélocité calculée
		Vecteur3D position(x, y);
		Vecteur3D velocity = direction * velocityMagnitude;

		Particule nouvelleParticule(trainee, couleur, surface, 1 / masse, position, velocity);
		particules.push_back(nouvelleParticule);

		// Ajoutez la nouvelle particule à votre conteneur de particules
		slingshotActive = false;
	}
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
