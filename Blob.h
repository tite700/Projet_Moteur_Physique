#pragma once
#include "ofMain.h"
#include "Vecteur3D.h"
#include "Particule.h"
#include <vector>
#include "ForceRessort.h"

class Blob
{
public:
	Blob(float size, int nParticules, Vecteur3D position, float masse = 2, float couleur = 0, float trainee = 0.01);

	std::vector<ForceRessort*> generateForces();
	void draw();

	void addParticule(Particule* particule);

	//Accesseurs
	void setEspace(float espace);
	void setTrainee(float trainee);
	void setCouleur(float couleur);
	void setSurface(float surface);
	void setMasse(float masse);
	
	float getEspace();
	float getTrainee();
	float getCouleur();
	float getSurface();
	float getMasse();
	std::vector<Particule*> getParticules();
	Particule * getCenter();

private:


	std::vector<Particule*> particules;
	Particule* center;
	float distance;
	float centerDistance;
	float espace;
	float trainee;
	float couleur;
	float surface;
	float masse;
};

