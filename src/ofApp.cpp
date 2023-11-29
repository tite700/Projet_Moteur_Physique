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

ofEasyCam cam;  // Declare an ofEasyCam object
void ofApp::setup() {
	// setup des elements du jeu
	ground.set(0, 850, 2000, 140);
	ground.set(0, ofGetHeight() - 140, ofGetWidth(), 0);

	// Set up the camera
	cam.setPosition(0, 0, 1000);
	cam.setDistance(1000);  // Set the initial distance from the camera to the center
	cam.disableMouseInput();  // Disable the default mouse interaction for camera control

	

	/////////////////////////////////////////// CorpsRigides //////////////////////////////////////
	//Elements optionnels
	cam.enableOrtho();
	cam.setNearClip(-100000);
	cam.setFarClip(100000);
	cam.setVFlip(true);

	// CorpsRigide
	corpsrigides.push_back(box1);
	corpsrigides.push_back(box2);
	corpsrigides.push_back(box3);
	corpsrigides.push_back(box4);
	float Intensite = 10.0;
	Vecteur3D PointImpact = Vecteur3D(10, 0, 0);
	///////////////////////////////////////////////////////////////////////////////////////////////
	// 
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

	//Test unitaires
	runUnitTests();
}

//--------------------------------------------------------------
int temps = 0;
void ofApp::update() {
	/////////////////////////////////// CORPS RIGIDE ///////////////////////////////////////////////////////////////////////////
	//CorpsRigide
	if (debut == false) {
		if (temps < 4) {
			registreForceCorps.add(box1, new ForceImpulsionCorps(PointImpact, Intensite));
			ofLogNotice("pointImpact.()") << "\n" << PointImpact << "\n";
		}
		registreForceCorps.add(box1, new ForceGraviteCorps());
		temps += 1;
	}
	// On update les forces de tous les corpsRigides
	registreForceCorps.updateForces(ofGetLastFrameTime());
	// Mettez a jour la simulation a chaque frame

	for (auto& corpsrigide : corpsrigides) {
		corpsrigide->Integrate(ofGetLastFrameTime()); // Utilisez la duree de la frame pour l'integration		
	}

	for (auto& corpsrigide : corpsrigides) {
		corpsrigide->clearAccumulators();
	}

	registreForceCorps.clear();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	ofLogNotice("m_orientation") << "\n" << box1->getOrientation() << "\n";
	ofLogNotice("Testquaternion") << "\n" << Quaternion(0.0, 0.0, 1.0, 0.0).toMatrix3() << "\n";
	float a = (1.0 / 12.0)*(1.0/0.01);
	ofLogNotice("TestI_inverse") << "\n" << Matrix3(1 / (a * (10 + 10)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10))) << "\n";
	ofLogNotice("TorqueAccum") << "\n" << box1->getTorqueAccum() << "\n";
	ofLogNotice("VelocityAngulaire") << "\n" << box1->getVelocityAngulaire()<< "\n";
	//Ressort
	registreForce.add(balle1, new GraviteParticule(Vecteur3D(0, 9.81f, 0)));
	registreForce.add(balle1, new ForceRessort(2, 100, 1000, balle1, accroche1, 0.2));
	*/
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

	
	// Verifiez si la souris est entree dans la zone du carre
	customSquare.set(-150, -150, 300, 300);
	if (customSquare.inside(mouseX-960, mouseY-560)) {
		mouseInSquare = true;
	}
	else {
		mouseInSquare = false;
	}

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

	// Ajoutez ceci pour permettre à la caméra de tourner en fonction des mouvements de la souris
	float rotationSpeed = 0.1;
	float mouseXNormalized = ofMap(ofGetMouseX(), 0, ofGetWidth(), -1, 1);
	float mouseYNormalized = ofMap(ofGetMouseY(), 0, ofGetHeight(), -1, 1);

	float rotationAmountX = rotationSpeed * mouseXNormalized;
	float rotationAmountY = rotationSpeed * mouseYNormalized;

	// Nouveau code pour la rotation de la caméra
	static float prevMouseX = ofGetMouseX();
	static float prevMouseY = ofGetMouseY();

	float diffX = ofGetMouseX() - prevMouseX;
	float diffY = ofGetMouseY() - prevMouseY;



	prevMouseX = ofGetMouseX();
	prevMouseY = ofGetMouseY();
	

}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	// Dessinez le carré vert en bas
	ofSetColor(0, 255, 0);
	// Dessinez le fond bleu
	ofBackground(135, 206, 235);

	// Dessinez le carré vert en bas
	ofSetColor(0, 255, 0);
	ofFill();  // Activez le remplissage
	ofDrawRectangle(-1000, 450, 2000, 140);
	// Exemple pour dessiner des nuages
	ofSetColor(255);  // Réglez la couleur sur blanc
	ofDrawEllipse(600, -400, 90, 40);  // Exemple d'ellipse pour un nuage
	ofDrawEllipse(400, -400, 90, 40);
	ofDrawEllipse(200, -400, 90, 40);
	ofDrawEllipse(-100, -400, 90, 40);
	ofDrawEllipse(-300, -400, 90, 40);
	ofDrawEllipse(700, -400, 90, 40);
	ofDrawEllipse(400, -400, 90, 40);
	ofDrawEllipse(200, -400, 90, 40);
	ofDrawEllipse(-150, -400, 90, 40);
	ofDrawEllipse(-350, -400, 90, 40);
	ofDrawEllipse(650, -400, 90, 40);
	ofDrawEllipse(-400, -400, 90, 40);
	ofDrawEllipse(600, -400, 90, 40);
	ofDrawEllipse(-850, -400, 90, 40);
	ofDrawEllipse(-900, -400, 90, 40);
	ofDrawEllipse(200, -400, 90, 40);
	// Exemple pour dessiner le soleil
	ofSetColor(255, 255, 0);  // Réglez la couleur sur jaune
	ofDrawCircle(800, -400, 100);  // Exemple de cercle pour le soleil
	ofNoFill();  // Desactivez le remplissage





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
	///////////////////////////////////////////// CORPS RIGIDES //////////////////////////////////////////////////////////////////
	for (const auto& corprigide : corpsrigides)
	{
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

		int size = 300;
		size = size - (corprigide->getPosition().getZ()) / 3;
		if (size < 50) {
			size = 50;
		}

		// Activer le test de profondeur (depth test)
		ofEnableDepthTest();

		// Face avant (gray)
		ofSetColor(150, 150, 150);
		ofFill();
		ofPushMatrix();
		ofTranslate(0, 0, size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Face arrière (red)
		ofSetColor(150, 150, 150);
		ofPushMatrix();
		ofTranslate(0, 0, -size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Face du dessus (green)
		ofSetColor(150, 150, 150);
		ofPushMatrix();
		ofRotate(90, 1, 0, 0);
		ofTranslate(0, 0, -size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Face du dessous (blue)
		ofSetColor(150, 150, 150);
		ofPushMatrix();
		ofRotate(90, 1, 0, 0);
		ofTranslate(0, 0, size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Face de droite (yellow)
		ofSetColor(150, 150, 150);
		ofPushMatrix();
		ofRotate(90, 0, 1, 0);
		ofTranslate(0, 0, -size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Face de gauche (cyan)
		ofSetColor(150, 150, 150);
		ofPushMatrix();
		ofRotate(90, 0, 1, 0);
		ofTranslate(0, 0, size / 2);
		ofDrawBox(size, size, 2);
		ofPopMatrix();

		// Désactiver le test de profondeur après avoir dessiné le cube
		ofDisableDepthTest();

		// Dessiner les axes
		ofSetColor(0, 0, 255); // Bleu pour l'axe Z
		ofDrawLine(0, 0, 0, 0, 0, 100); // Dessiner l'axe Z

		ofSetColor(255, 0, 0); // Rouge pour l'axe X
		ofDrawLine(0, 0, 0, 100, 0, 0); // Dessiner l'axe X

		ofSetColor(0, 255, 0); // Vert pour l'axe Y
		ofDrawLine(0, 0, 0, 0, 100, 0); // Dessiner l'axe Y


		// Restaurer la matrice de transformation
		ofPopMatrix();
	}
	// Verifiez si la souris est dans la zone du carre
	if (mouseInSquare) 
	{
		ofDrawBitmapString("CLIQUEZ POUR TIRER !", 0, -200); // Affiche un message texte a l'ecran
	}
	/*
	// Dessine les coordonnées de la souris en temps réel
	ofSetColor(255);
	std::string mouseCoords = "Mouse Coords: (" + ofToString(ofGetMouseX()-960) + ", " + ofToString(ofGetMouseY()-560) + ")";
	ofDrawBitmapString(mouseCoords, -500, -370);
	*/
	// Dessinez le carré personnalisé
	ofNoFill();
	ofSetColor(255, 0, 0);  // Couleur rouge, par exemple
	ofDrawRectangle(customSquare);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cam.end();

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
	if (key == 'r') {
		debut = true;
		box1->setPosition(Vecteur3D(0, 0, 0));
		box1->setVelocite(Vecteur3D(0, 0, 0));
		box1->setAcceleration(Vecteur3D(0, 0, 0));
		box1->setForceAccum(Vecteur3D(0, 0, 0));
		box1->setOrientation(Quaternion(0.0, 0.0, 1.0, 0.0));
		box1->setAccelerationAngulaire(Vecteur3D(0, 0, 0));
		box1->setVelocityAngulaire(Vecteur3D(0, 0, 0));
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
	if (button == OF_MOUSE_BUTTON_RIGHT) {
		// Rotate the camera based on mouse movement
		float rotationSpeed = 0.5;
		float mouseXNormalized = ofMap(x, 0, ofGetWidth(), -1, 1);
		float mouseYNormalized = ofMap(y, 0, ofGetHeight(), -1, 1);

		float rotationAmountX = rotationSpeed * mouseXNormalized;
		float rotationAmountY = rotationSpeed * mouseYNormalized;

		cam.rotateDeg(rotationAmountY, 1, 0, 0);  // Rotate around X-axis
		cam.rotateDeg(rotationAmountX, 0, 1, 0);  // Rotate around Y-axis
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	// Coordonnees de la position actuelle de la souris
	float sourisX = mouseX - 960;
	float sourisY = mouseY - 560;
	debut = false;
	temps = 0;

	if (mouseInSquare) {
		// Point d'Impact et intensite
		Intensite = 3000;
		PointImpact = Vecteur3D(x - 960, y - 560,0.0);
		// Creer un nouveau corps
		box1->setPosition(Vecteur3D(0, 0, 0));
		box1->setVelocite(Vecteur3D(0, 0, 0));
		box1->setAcceleration(Vecteur3D(0, 0, 0));
		box1->setForceAccum(Vecteur3D(0, 0, 0));
		box1->setOrientation(Quaternion(0.0, 0.0, 1.0, 0.0));
		box1->setAccelerationAngulaire(Vecteur3D(0, 0, 0));
		box1->setVelocityAngulaire(Vecteur3D(0, 0, 0));
		//box1 = new CorpsRigide(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), Quaternion(0.0, 0.0, 1.0, 0.0), 0.001, Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0));
	}
	
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	/*
	if (button == OF_MOUSE_BUTTON_LEFT && slingshotActive == true) {
		// Calculez la distance entre le point de depart et le point de relachement
		float intensite = ofDist(x, y, 400, 700);

	

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
	*/
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
