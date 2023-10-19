#include "ofApp.h"
#include "../Vecteur3D.h"
#include "../Particule.h"
#include "../GraviteParticule.h"
#include "../ForceFrictionCinetique.h"

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

	// Cr�ez une cible et ajoutez-la � votre conteneur de particules
	Particule cible(1, 500, 50, 0.01f, Vecteur3D(400, 100), Vecteur3D(0, 0));
	particules.push_back(cible);

	ground.set(0, 850, 2000, 140);
}

//--------------------------------------------------------------
void ofApp::update() {
	//On supprime les forces des particules
	for (auto& particule : particules) {
		particule.clearForce();
	}

	for (auto& particule : particules) {
		registreForce.add(&particule, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
		registreForce.add(&particule, new ForceFrictionCinetique(0.000001f * particule.getSurface(), 0.0f));
	}

	registreForce.updateForces(ofGetLastFrameTime());

	std::cout << particules.size() << std::endl;
	// On v�rifie les collisions pour chaque paire de particules dans la sc�ne (stock�es dans le vecteur particules)
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

	// Mettez � jour la simulation � chaque frame
	for (auto& particule : particules) {
		particule.integrer(ofGetLastFrameTime()); // Utilisez la dur�e de la frame pour l'int�gration		
	}

	// V�rifiez si la souris est entr�e dans la zone du carr�
	if (customSquare.inside(mouseX, mouseY)) {
		mouseInSquare = true;
	}
	else {
		mouseInSquare = false;
	}

	// Mettez � jour d'autres �l�ments de la simulation si n�cessaire
	sphere.setPosition(sphere.getGlobalPosition() + Vecteur3D(1, 0).vec3());
	for (auto& particule : particules)
	{
		if (particule.getPosition().getY() + particule.getSurface() > 850)
		{
			std::cout << particule.getVelocite().getY() << std::endl;
			particule.setPosition(Vecteur3D(particule.getPosition().getX(), 850 - particule.getSurface()));
			particule.setVelocite(Vecteur3D(particule.getVelocite().getX(), -particule.getVelocite().getY()*0.5f));
			if (std::fabsl(particule.getVelocite().getY()) < 150.0f)
			{
				particule.setVelocite(Vecteur3D(particule.getVelocite().getX(), 0));
			}
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//desin du menu
	gui.draw();
	ofDrawRectangle(ground);
	// Dessine les particules
	for (const auto& particule : particules) {
		// Dessinez chaque particule � sa position actuelle
		// Positionnez la bo�te � la position de la particule
		ofSetColor(255, 255 - particule.getCouleur(), 255 - particule.getCouleur());
		sphere.set(particule.getSurface(), 32);
		sphere.setPosition(Vecteur3D(particule.getPosition().getX(), particule.getPosition().getY()).vec3());
		sphere.draw();
		ofSetColor(255, 255, 255);
	}

	// Dessine d'autres �l�ments de la simulation 
	ofSetColor(255, 255, 255);
	ofNoFill();
	ofDrawRectangle(325, 625, 140, 140); // Tete du lance particule
	ofFill();
	ofDrawRectangle(390, 740, 10, 700); // Pied du lance particule


	// D�clare les coordonn�es du point de d�part des particules qui vont �tre lanc�es
	float x1 = 400;
	float y1 = 700;

	// Coordonn�es de la position actuelle de la souris
	float x2 = mouseX;
	float y2 = mouseY;

	// V�rifiez si la souris est dans la zone du carr�
	if (mouseInSquare) {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(10);
		if (slingshotActive == false) {
			ofDrawBitmapString("CLIQUEZ POUR ARMER UNE PARTICULE ET TIRER !", 225, 600); // Affiche un message texte � l'�cran
		}
	}
	else {
		ofSetLineWidth(3);
	}

	// V�rifiez si le bouton de la souris gauche est enfonc� et que le lance pierre est arm� d'une particule
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT) && slingshotActive == true) {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(10);
		ofDrawLine(x1, y1, x2, y2); // Dessinez la ligne du lance particule

		ofSetColor(255, 255 - couleur, 255 - couleur);
		sphere.set(surface, 32);
		sphere.setPosition(Vecteur3D(mouseX, mouseY).vec3());
		sphere.draw(); // Dessine la particule (box) t�moin pour l'utilisateur au niveau de la position de la souris
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("RELACHER POUR LANCER LA PARTICULE", 250, 600); // Affiche un message texte � l'�cran

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
		// Calculez la distance entre le point de d�part et le point de rel�chement
		float distance = ofDist(x, y, 400, 700);

		// Calculez l'intensit� de la v�locit� en fonction de la distance
		float velocityMagnitude = distance * 0.006; // Ajustez le facteur � votre convenance

		// Calculez la direction de la v�locit� (unit vector)
		Vecteur3D direction(400 - x, 700 - y);
		direction.normalisation();

		// Cr�ez une nouvelle particule avec la v�locit� calcul�e
		Vecteur3D position(x, y);
		Vecteur3D velocity = direction * velocityMagnitude;

		Particule nouvelleParticule(trainee, couleur, surface, 1 / masse, position, velocity);
		particules.push_back(nouvelleParticule);

		// Ajoutez la nouvelle particule � votre conteneur de particules
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
