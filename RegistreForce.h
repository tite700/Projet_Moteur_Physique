#pragma once
#include "Particule.h"
#include "Vecteur3D.h"
#include "GenerateurForce.h"
#include <vector>

class RegistreForce
{
	public:
		struct Force
		{
			Particule* particule;
			GenerateurForce* force;
		};

		typedef std::vector<Force> Registre;

		void add(Particule* particule, GenerateurForce* force);
		void clear();
		void remove(Particule* particule, GenerateurForce* force);
		void updateForces(float duration);

	private:

		Registre registre;


};

