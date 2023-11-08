#include "Matrix4.h"

Matrix4::Matrix4()
{
	for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			matrice[index][index2] = 0;
		}
	}
}

Matrix4::Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	std::vector<float> ligne1;
	ligne1.push_back(a);
	ligne1.push_back(b);
	ligne1.push_back(c);
	ligne1.push_back(d);
	std::vector<float> ligne2;
	ligne2.push_back(e);
	ligne2.push_back(f);
	ligne2.push_back(g);
	ligne2.push_back(h);
	std::vector<float> ligne3;
	ligne3.push_back(i);
	ligne3.push_back(j);
	ligne3.push_back(k);
	ligne3.push_back(l);
	std::vector<float> ligne4;
	ligne4.push_back(m);
	ligne4.push_back(n);
	ligne4.push_back(o);
	ligne4.push_back(p);
	matrice.push_back(ligne1);
	matrice.push_back(ligne2);
	matrice.push_back(ligne3);
	matrice.push_back(ligne4);
}

Matrix4::Matrix4(Vecteur3D vecteur1, Vecteur3D vecteur2, Vecteur3D vecteur3, Vecteur3D vecteur4, bool col)
{
	if (!col)
	{
		matrice.push_back({ vecteur1.getX(), vecteur1.getY(), vecteur1.getZ(), vecteur1.getW() });
		matrice.push_back({ vecteur2.getX(), vecteur2.getY(), vecteur2.getZ(), vecteur2.getW() });
		matrice.push_back({ vecteur3.getX(), vecteur3.getY(), vecteur3.getZ(), vecteur3.getW() });
		matrice.push_back({ vecteur4.getX(), vecteur4.getY(), vecteur4.getZ(), vecteur4.getW() });
	}
	else
	{
		matrice.push_back({ vecteur1.getX(), vecteur2.getX(), vecteur3.getX(), vecteur4.getX() });
		matrice.push_back({ vecteur1.getY(), vecteur2.getY(), vecteur3.getY(), vecteur4.getY() });
		matrice.push_back({ vecteur1.getZ(), vecteur2.getZ(), vecteur3.getZ(), vecteur4.getZ() });
		matrice.push_back({ vecteur1.getW(), vecteur2.getW(), vecteur3.getW(), vecteur4.getW() });
	}
}

Matrix4::Matrix4(Matrix4* matrice)
{
	for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			this->matrice[index][index2] = matrice->matrice[index][index2];
		}
	}
}

Matrix4::Matrix4(Matrix3* matrice)
{
	for (int index = 0; index < 3; index++)
	{
		for (int index2 = 0; index2 < 3; index2++)
		{
			this->matrice[index][index2] = matrice->getMatrice()[index][index2];
		}
	}
	this->matrice[3][3] = 1;
}

Matrix4 Matrix4::transpose()
{
	Matrix4 matriceTranspose;
	for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			matriceTranspose.matrice[index][index2] = matrice[index2][index];
		}
	}
	return matriceTranspose;
}

Matrix4 Matrix4::operator*(const Matrix4& matrice2)
{
	Matrix4 matriceResultante;
	for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			matriceResultante.matrice[index][index2] = matrice[index][0] * matrice2.matrice[0][index2] + matrice[index][1] * matrice2.matrice[1][index2] + matrice[index][2] * matrice2.matrice[2][index2] + matrice[index][3] * matrice2.matrice[3][index2];
		}
	}
	return matriceResultante;
}

Vecteur3D Matrix4::operator*(const Vecteur3D& vecteur)
{
	Vecteur3D vecteurResultant;
	vecteurResultant.setX(matrice[0][0] * vecteur.getX() + matrice[0][0] * vecteur.getY() + matrice[0][1] * vecteur.getZ() + matrice[0][2] * vecteur.getW() * matrice[0][3]);
	vecteurResultant.setY(matrice[1][0] * vecteur.getX() + matrice[1][0] * vecteur.getY() + matrice[1][1] * vecteur.getZ() + matrice[1][2] * vecteur.getW() * matrice[1][3]);
	vecteurResultant.setZ(matrice[2][0] * vecteur.getX() + matrice[2][0] * vecteur.getY() + matrice[2][1] * vecteur.getZ() + matrice[2][2] * vecteur.getW() * matrice[2][3]);
	vecteurResultant.setW(matrice[3][0] * vecteur.getX() + matrice[3][0] * vecteur.getY() + matrice[3][1] * vecteur.getZ() + matrice[3][2] * vecteur.getW() * matrice[3][3]);
	return vecteurResultant;
}
