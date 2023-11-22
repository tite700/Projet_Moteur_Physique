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
ofEasyCam easyCam;
void ofApp::setup() {

	// setup des elements du jeu
	ofSetBackgroundColor(100);
	ground.set(0, 850, 2000, 140);
	easyCam.setDistance(800); // Ajustez la distance initiale de la caméra
	// Définissez la position initiale de la caméra
	easyCam.setPosition(462, 230, 1000);
	// Ajustez la distance initiale de la caméra


	//Elements optionnels
	sphere.setPosition(Vecteur3D(70, 700).vec3());
	customSquare.set(350, 620, 140, 140);
	easyCam.reset();

	//Blob
	for (auto& particule : blob.getParticules()) {
		particules.push_back(particule);
	}

	//Particules
	particules.push_back(blob.getCenter());
	particules.push_back(balle1);
	particules.push_back(accroche1);
	particules.push_back(balle2);
	particules.push_back(accroche2);
	particules.push_back(balle3);
	particules.push_back(balle4);
	particules.push_back(balle5);
	particules.push_back(balle6);
	particules.push_back(accroche5);
	particules.push_back(bigParticule);

	//CorpsRigides
	corpsrigides.push_back(box1);
	corpsrigides.push_back(box2);

	//Test unitaires
	runUnitTests();
	//setup du menu 
	//gui.setup();
	//gui.add(surface.setup("Surface", 50, 10, 150));
	//gui.add(masse.setup("Masse", 2, 0.5, 5));
	//gui.add(balleButton.setup("Balle", false));
	//gui.add(bdfButton.setup("Boule de feu", false));
	//gui.add(laserButton.setup("laser", false));
}

//--------------------------------------------------------------
void ofApp::update() {
	ofLogNotice("m_orientation") << "\n" << box1->getOrientation() << "\n";
	ofLogNotice("Testquaternion") << "\n" << Quaternion(0.0, 0.0, 1.0, 0.0).toMatrix3() << "\n";
	float a = (1.0 / 12.0)*(1.0/0.01);
	ofLogNotice("TestI_inverse") << "\n" << Matrix3(1 / (a * (10 + 10)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10))) << "\n";
	ofLogNotice("TorqueAccum") << "\n" << box1->getTorqueAccum() << "\n";
	ofLogNotice("VelocityAngulaire") << "\n" << box1->getVelocityAngulaire()<< "\n";
	//Ressort
	registreForce.add(balle1, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle1, new ForceRessort(2, 100, 1000, balle1, accroche1, 0.2));

	//Cable
	registreForce.add(balle2, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle2, new ForceCable(300, 0.0f, balle2, accroche2));
	
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
	// On update les forces de toutes les particules
	registreForce.updateForces(ofGetLastFrameTime());

	// on verifie les collisions pour chaque paire de particules dans la scene (stockees dans le vecteur particules)
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

	// Mettez a jour la simulation a chaque frame
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

	//CoprsRigide
	registreForceCorps.add(box1, new ForceGraviteCorps());
	// On update les forces de tous les corpsRigides
	registreForceCorps.updateForces(ofGetLastFrameTime());
	// Mettez a jour la simulation a chaque frame
	for (auto& corpsrigide : corpsrigides) {
		corpsrigide->Integrate(ofGetLastFrameTime()); // Utilisez la dur�e de la frame pour l'int�gration		
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	easyCam.begin();
	//dessin du menu
	//gui.draw();
	ofDrawRectangle(ground);
	
	// Dessine les particules
	for (const auto& particule : particules) {
		// Dessinez chaque particule a sa position actuelle
		// Positionnez la boite a la position de la particule
		ofSetColor(255, 255 - particule->getCouleur(), 255 - particule->getCouleur());
		sphere.set(particule->getSurface(), 32);
		sphere.setPosition(Vecteur3D(particule->getPosition().getX(), particule->getPosition().getY()).vec3());
		sphere.draw();
		ofSetColor(255, 255, 255);
	}

	// Dessine les coordonnées de la souris en temps réel
	ofSetColor(255);
	std::string mouseCoords = "Mouse Coords: (" + ofToString(ofGetMouseX()) + ", " + ofToString(ofGetMouseY()) + ")";
	ofDrawBitmapString(mouseCoords, 10, 20);
	
	for (const auto& corprigide : corpsrigides) {
		// Position du corps rigide
		Vecteur3D position = corprigide->getPosition();
		// Matrice de rotation du corps rigide
		Matrix3 matriceRotation = corprigide->getOrientation();

		// Encapsuler les opérations de dessin dans une matrice de transformation
		ofPushMatrix();
		// Translatez à la position du corps rigide
		ofTranslate(position.getX(), position.getY(), position.getZ());

		// Alignez l'axe bleu avec le plan de l'écran (Z vers l'extérieur)
		ofRotate(90, 1, 0, 0);

		// Alignez l'axe rouge avec les X croissants
		ofRotate(90, 0, 0, 1);

		// Convertissez la matrice 3x3 en une matrice 4x4
		ofMatrix4x4 ofRotationMatrix;
		ofRotationMatrix.set(matriceRotation.getMatrice()[0][0], matriceRotation.getMatrice()[0][1], matriceRotation.getMatrice()[0][2], 0,
			matriceRotation.getMatrice()[1][0], matriceRotation.getMatrice()[1][1], matriceRotation.getMatrice()[1][2], 0,
			matriceRotation.getMatrice()[2][0], matriceRotation.getMatrice()[2][1], matriceRotation.getMatrice()[2][2], 0,
			0, 0, 0, 1);

		// Appliquez la matrice de rotation
		ofMultMatrix(ofRotationMatrix);

		
		// Dessinez le cube avec des flèches sur chaque axe
		ofSetColor(255);
		ofDrawBox(50);

		// Dessinez les flèches des axes
		ofSetColor(255, 0, 0); // Axe X en rouge
		ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(50, 0, 0), 5);

		ofSetColor(0, 255, 0); // Axe Y en vert
		ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 50, 0), 5);

		ofSetColor(0, 0, 255); // Axe Z en bleu
		ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 0, 50), 5);

		// Dessinez chaque face du cube avec une couleur différente
		// (le reste du code reste inchangé)

		// Ajouter des lignes de repère sur chaque face
		ofSetColor(255);
		ofDrawBox(50);

		// Dessinez les arêtes du cube avec une couleur différente (par exemple, noir)
		ofSetColor(0);
		ofNoFill();
		ofDrawBox(50);
	
		// Restaurer la matrice de transformation
		ofPopMatrix();
		
	}







	//// Dessine d'autres elements de la simulation 
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
	easyCam.end();
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
	if (key == 'z') {
		easyCam.move(ofVec3f(0, 0, 50)); // Déplacement vers l'avant
	}
	else if (key == 's') {
		easyCam.move(ofVec3f(0, 0, -50)); // Déplacement vers l'arrière
	}
	else if (key == 'q') {
		easyCam.move(ofVec3f(-50, 0, 0)); // Déplacement vers la gauche
	}
	else if (key == 'd') {
		easyCam.move(ofVec3f(50, 0, 0)); // Déplacement vers la droite
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
