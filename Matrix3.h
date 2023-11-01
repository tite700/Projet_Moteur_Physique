#pragma once
#include <vector>
#include "Vecteur3D.h"
class Matrix3
{
public:
	Matrix3();
	Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	Matrix3(Vecteur3D vecteur1, Vecteur3D vecteur2, Vecteur3D vecteur3, bool col = false);
	Matrix3(std::vector<std::vector<float>> matrice);
	Matrix3(Matrix3* matrice);

	// Getters
	std::vector<std::vector<float>> getMatrice() const { return matrice; }

	Matrix3 transpose();
	Matrix3 operator*(const Matrix3& matrice2);
	Vecteur3D operator*(const Vecteur3D& vecteur);

	

private:
	std::vector<std::vector<float>> matrice;
};

std::ostream& operator<<(std::ostream& os, const Matrix3& matrice);

