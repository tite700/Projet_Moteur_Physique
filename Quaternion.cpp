#include "Quaternion.h"

Quaternion::Quaternion()
{
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}

Quaternion::Quaternion(float a, float b, float c, float d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	
	Vecteur3D vecteur1(a, -d, c, b);
	Vecteur3D vecteur2(d, a, -b, c);
	Vecteur3D vecteur3(-c, b, a, d);
	Vecteur3D vecteur4(-b, -c, -d, a);

	matrice = Matrix4(vecteur1, vecteur2, vecteur3, vecteur4);
}
