#pragma once
#include "Vector.h"
#include <time.h>
#include "ofMain.h"

class Particule
{
private:
	Vector pos;
	float inverseMasse;
	Vector velocite;
	Vector acceleration;

	ofSpherePrimitive body;

	clock_t lastFrame;
	
	bool hasStarted = false;


public:

	Particule(Vector pos, float masse);


	void start();
	void update();
	void draw();

	// Implémenter un intégrateur (intégration d'Euler) afin de mettre à jour la position et la vélocité de chaque particule à chaque frame.
	// Celui-ci peut être implémenté en tant que méthode void integrer(float temps) de la classe Particule.

	void integrer(float temps);


	//Getters & Setters
	Vector getPos();
	void setPos(Vector nPos);

	float getMasse();
	void setMasse(float nMasse);

	void setVelocite(Vector velocite);

	void setAcceleration(Vector accel);

	void setRadius(float radius);

	void Particule::setHasStarted(bool hasStarted);
	bool Particule::getHasStarted();


};

