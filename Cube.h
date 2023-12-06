#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Plan.h"

class Cube :
    public Primitive

{
public:
	Cube();
	~Cube();

private:
	Vecteur3D centre;
	float taille;
};

