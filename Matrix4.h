#pragma once

#include "Matrix3.h"

class Matrix4
{
public:
	Matrix4();
	Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j,
				float k, float l, float m, float n, float o, float p);
	Matrix4(Vecteur3D vecteur1, Vecteur3D vecteur2, Vecteur3D vecteur3, Vecteur3D vecteur4, bool col = false);
	Matrix4(Matrix4* matrice);
	Matrix4(Matrix3* matrice);

	// Getters
	std::vector<std::vector<float>> getMatrice() const { return matrice; }

	Matrix4 transpose();
	Matrix4 operator*(const Matrix4& matrice2) const;
	Vecteur3D operator*(const Vecteur3D& vecteur);

private:
	std::vector<std::vector<float>> matrice;
};

