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

void ofApp::setup() {

	Matrix3 matrice1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	std::cout << matrice1 << std::endl;
	std::cout << matrice1.transpose() << std::endl;
	// setup des elements du jeu
	ofSetBackgroundColor(100);
	sphere.setPosition(Vecteur3D(70, 700).vec3());
	customSquare.set(350, 620, 140, 140);


	for (auto& particule : blob.getParticules()) {
		particules.push_back(particule);
	}
	particules.push_back(blob.getCenter());


	//setup du menu 
	//gui.setup();
	//gui.add(surface.setup("Surface", 50, 10, 150));
	//gui.add(masse.setup("Masse", 2, 0.5, 5));
	//gui.add(balleButton.setup("Balle", false));
	//gui.add(bdfButton.setup("Boule de feu", false));
	//gui.add(laserButton.setup("laser", false));

	ground.set(0, 850, 2000, 140);

	particules.push_back(balle1);
	particules.push_back(accroche1);
	particules.push_back(balle2);
	particules.push_back(accroche2);
	particules.push_back(balle3);
	particules.push_back(balle4);
	particules.push_back(balle5);
	particules.push_back(accroche5);
	particules.push_back(bigParticule);

	runUnitTests();
}


//--------------------------------------------------------------
void ofApp::update() {

	//Ressort
	registreForce.add(balle1, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle1, new ForceRessort(2, 100, 1000, balle1, accroche1, 0.2));

	//Cable
	registreForce.add(balle2, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle2, new ForceCable(300, 0.0f, balle2, accroche2));
	std::cout << "Vitesse : " << balle2->getVitesse() << std::endl;
	std::cout << "Force : " << balle2->getForce() << std::endl;
	
	//Collision
	registreForce.add(balle3, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle4, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));

	//Elastique
	registreForce.add(balle5, new ForceElastique(400, 2, balle5, accroche5, 0.2));
	registreForce.add(balle5, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));


	//Big particule
	registreForce.add(bigParticule, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));

	//Blob

	std:vector<ForceRessort*> forces = blob.generateForces();
	for (int count  = 0; count < blob.getParticules().size(); count++)
	{
		registreForce.add(blob.getParticules()[count], forces.at(count * 4));
		registreForce.add(blob.getParticules()[(count + 1) % blob.getParticules().size()], forces.at(count * 4 +1));
		registreForce.add(blob.getParticules()[count], forces.at(count * 4 + 2));
		registreForce.add(blob.getCenter(), forces.at(count * 4 + 3));
		registreForce.add(blob.getParticules()[count], new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
		registreForce.add(blob.getParticules()[count], new ForceFrictionCinetique(0.001f * blob.getParticules()[count]->getSurface(), 0.01f));
	}

	
	registreForce.updateForces(ofGetLastFrameTime());

	// on v�rifie les collisions pour chaque paire de particules dans la sc�ne (stockees dans le vecteur particules)
	
	for (int i = 0; i < particules.size(); i++) {
		for (int j = i + 1; j < particules.size(); j++) {
			if (Particule::collision(particules[i], particules[j])) {
				Particule::resolveCollision(particules[i], particules[j]);
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
		particule->integrer(ofGetLastFrameTime()); // Utilisez la dur�e de la frame pour l'int�gration		
	}

	// V�rifiez si la souris est entr�e dans la zone du carr�
	//if (customSquare.inside(mouseX, mouseY)) {
	//	mouseInSquare = true;
	//}
	//else {
	//	mouseInSquare = false;
	//}

	// Mettez � jour d'autres �l�ments de la simulation si n�cessaire
	//sphere.setPosition(sphere.getGlobalPosition() + Vecteur3D(1, 0).vec3());

	//Collision avec le sol
	for (auto& particule : particules)
	{
		if (particule->getPosition().getY() + particule->getSurface() > 850)
		{
			particule->setPosition(Vecteur3D(particule->getPosition().getX(), 850 - particule->getSurface()));
			particule->setVelocite(Vecteur3D(particule->getVelocite().getX(), -particule->getVelocite().getY()*0.7));
			if (std::fabsl(particule->getVelocite().getY()) < 150.0f)
			{
				particule->setVelocite(Vecteur3D(particule->getVelocite().getX(), 0));
			}
		}

	}
	//On supprime les forces des particules


	for (auto& particule : particules) {
		particule->clearForce();
	}


}

//--------------------------------------------------------------
void ofApp::draw() {
	//desin du menu
	//gui.draw();
	ofDrawRectangle(ground);
	// Dessine les particules
	for (const auto& particule : particules) {
		// Dessinez chaque particule � sa position actuelle
		// Positionnez la bo�te � la position de la particule
		ofSetColor(255, 255 - particule->getCouleur(), 255 - particule->getCouleur());
		sphere.set(particule->getSurface(), 32);
		sphere.setPosition(Vecteur3D(particule->getPosition().getX(), particule->getPosition().getY()).vec3());
		sphere.draw();
		ofSetColor(255, 255, 255);
	}

	//// Dessine d'autres �l�ments de la simulation 
	//ofSetColor(255, 255, 255);
	//ofNoFill();
	//ofDrawRectangle(325, 625, 140, 140); // Tete du lance particule
	//ofFill();
	//ofDrawRectangle(390, 740, 10, 700); // Pied du lance particule


	//// D�clare les coordonn�es du point de d�part des particules qui vont �tre lanc�es
	//float x1 = 400;
	//float y1 = 700;

	//// Coordonn�es de la position actuelle de la souris
	//float x2 = mouseX;
	//float y2 = mouseY;

	//// V�rifiez si la souris est dans la zone du carr�
	//if (mouseInSquare) {
	//	ofSetColor(255, 255, 255);
	//	ofSetLineWidth(10);
	//	if (slingshotActive == false) {
	//		ofDrawBitmapString("CLIQUEZ POUR ARMER UNE PARTICULE ET TIRER !", 225, 600); // Affiche un message texte � l'�cran
	//	}
	//}
	//else {
	//	ofSetLineWidth(3);
	//}

	//// V�rifiez si le bouton de la souris gauche est enfonc� et que le lance pierre est arm� d'une particule
	//if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT) && slingshotActive == true) {
	//	ofSetColor(255, 0, 0);
	//	ofSetLineWidth(10);
	//	ofDrawLine(x1, y1, x2, y2); // Dessinez la ligne du lance particule

	//	ofSetColor(255, 255 - couleur, 255 - couleur);
	//	sphere.set(surface, 32);
	//	sphere.setPosition(Vecteur3D(mouseX, mouseY).vec3());
	//	sphere.draw(); // Dessine la particule (box) t�moin pour l'utilisateur au niveau de la position de la souris
	//	ofSetColor(255, 255, 255);
	//	ofDrawBitmapString("RELACHER POUR LANCER LA PARTICULE", 250, 600); // Affiche un message texte � l'�cran

	//}
	//if (slingshotActive == false) {
	//	ofSetColor(255, 255 - couleur, 255 - couleur);
	//	sphere.set(surface, 32); //La particule statique
	//	sphere.setPosition(Vecteur3D(395, 700).vec3());
	//	sphere.draw();
	//	ofSetColor(255, 255, 255);
	//}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	float x = 300;
	if (key == OF_KEY_RIGHT) {
		blob.getCenter()->setVelocite(Vecteur3D(x, 0));
		for (auto& particule : blob.getParticules())
		{
			particule->setVelocite(Vecteur3D(x, 0));
		}
	}
	if (key == OF_KEY_LEFT) {
		blob.getCenter()->setVelocite(Vecteur3D(-x, 0));
		for (auto& particule : blob.getParticules())
		{
			particule->setVelocite(Vecteur3D(-x, 0));
		}
	}
	if (key == OF_KEY_UP) {
		blob.getCenter()->setVelocite(Vecteur3D(0, -x));
		for (auto& particule : blob.getParticules())
		{
			particule->setVelocite(Vecteur3D(0, -x));
		}
	}
	if (key == OF_KEY_DOWN) {
		blob.getCenter()->setVelocite(Vecteur3D(0, x));
		for (auto& particule : blob.getParticules())
		{
			particule->setVelocite(Vecteur3D(0, x));
		}
	}
}

void ofApp::runUnitTests() {
	testConstructors();
	testOperations();
	testMethods();
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

		Particule* nouvelleParticule = new Particule(trainee, couleur, surface, 1 / masse, position, velocity);
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
