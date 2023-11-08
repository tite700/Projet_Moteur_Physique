#include "Matrix3.h"

Matrix3::Matrix3()
{
	std::vector<float> ligne1;
	ligne1.push_back(0);
	ligne1.push_back(0);
	ligne1.push_back(0);
	std::vector<float> ligne2;
	ligne2.push_back(0);
	ligne2.push_back(0);
	ligne2.push_back(0);
	std::vector<float> ligne3;
	ligne3.push_back(0);
	ligne3.push_back(0);
	ligne3.push_back(0);
	matrice.push_back(ligne1);
	matrice.push_back(ligne2);
	matrice.push_back(ligne3);
}

Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	std::vector<float> ligne1;
	ligne1.push_back(a);
	ligne1.push_back(b);
	ligne1.push_back(c);
	std::vector<float> ligne2;
	ligne2.push_back(d);
	ligne2.push_back(e);
	ligne2.push_back(f);
	std::vector<float> ligne3;
	ligne3.push_back(g);
	ligne3.push_back(h);
	ligne3.push_back(i);
	matrice.push_back(ligne1);
	matrice.push_back(ligne2);
	matrice.push_back(ligne3);
}

Matrix3::Matrix3(Vecteur3D vecteur1, Vecteur3D vecteur2, Vecteur3D vecteur3, bool col)
{
	if (!col)
	{
		matrice.push_back({ vecteur1.getX(), vecteur1.getY(), vecteur1.getZ() });
		matrice.push_back({ vecteur2.getX(), vecteur2.getY(), vecteur2.getZ() });
		matrice.push_back({ vecteur3.getX(), vecteur3.getY(), vecteur3.getZ() });
	}
	else
	{
		matrice.push_back({ vecteur1.getX(), vecteur2.getX(), vecteur3.getX() });
		matrice.push_back({ vecteur1.getY(), vecteur2.getY(), vecteur3.getY() });
		matrice.push_back({ vecteur1.getZ(), vecteur2.getZ(), vecteur3.getZ() });
	}
}

Matrix3::Matrix3(std::vector<std::vector<float>> matrice)
{
		this->matrice = matrice;
}

Matrix3::Matrix3(Matrix3* matrice)
{
	std::vector<float> ligne1;
	ligne1.push_back(matrice->getMatrice()[0][0]);
	ligne1.push_back(matrice->getMatrice()[0][1]);
	ligne1.push_back(matrice->getMatrice()[0][2]);
	std::vector<float> ligne2;
	ligne2.push_back(matrice->getMatrice()[1][0]);
	ligne2.push_back(matrice->getMatrice()[1][1]);
	ligne2.push_back(matrice->getMatrice()[1][2]);
	std::vector<float> ligne3;
	ligne3.push_back(matrice->getMatrice()[2][0]);
	ligne3.push_back(matrice->getMatrice()[2][1]);
	ligne3.push_back(matrice->getMatrice()[2][2]);
	this->matrice.push_back(ligne1);
	this->matrice.push_back(ligne2);
	this->matrice.push_back(ligne3);

}

Matrix3 Matrix3::transpose()
{
	std::vector<float> ligne1;
	ligne1.push_back(matrice[0][0]);
	ligne1.push_back(matrice[1][0]);
	ligne1.push_back(matrice[2][0]);
	std::vector<float> ligne2;
	ligne2.push_back(matrice[0][1]);
	ligne2.push_back(matrice[1][1]);
	ligne2.push_back(matrice[2][1]);
	std::vector<float> ligne3;
	ligne3.push_back(matrice[0][2]);
	ligne3.push_back(matrice[1][2]);
	ligne3.push_back(matrice[2][2]);
	std::vector<std::vector<float>> matrice;
	matrice.push_back(ligne1);
	matrice.push_back(ligne2);
	matrice.push_back(ligne3);
	Matrix3 matriceTransposee(matrice);
	return matriceTransposee;
}

Matrix3 Matrix3::operator*(const Matrix3& matrice2) const
{
	std::vector<float> ligne1;
	ligne1.push_back(matrice[0][0] * matrice2.getMatrice()[0][0] + matrice[0][1] * matrice2.getMatrice()[1][0] + matrice[0][2] * matrice2.getMatrice()[2][0]);
	ligne1.push_back(matrice[0][0] * matrice2.getMatrice()[0][1] + matrice[0][1] * matrice2.getMatrice()[1][1] + matrice[0][2] * matrice2.getMatrice()[2][1]);
	ligne1.push_back(matrice[0][0] * matrice2.getMatrice()[0][2] + matrice[0][1] * matrice2.getMatrice()[1][2] + matrice[0][2] * matrice2.getMatrice()[2][2]);
	std::vector<float> ligne2;
	ligne2.push_back(matrice[1][0] * matrice2.getMatrice()[0][0] + matrice[1][1] * matrice2.getMatrice()[1][0] + matrice[1][2] * matrice2.getMatrice()[2][0]);
	ligne2.push_back(matrice[1][0] * matrice2.getMatrice()[0][1] + matrice[1][1] * matrice2.getMatrice()[1][1] + matrice[1][2] * matrice2.getMatrice()[2][1]);
	ligne2.push_back(matrice[1][0] * matrice2.getMatrice()[0][2] + matrice[1][1] * matrice2.getMatrice()[1][2] + matrice[1][2] * matrice2.getMatrice()[2][2]);
	std::vector<float> ligne3;
	ligne3.push_back(matrice[2][0] * matrice2.getMatrice()[0][0] + matrice[2][1] * matrice2.getMatrice()[1][0] + matrice[2][2] * matrice2.getMatrice()[2][0]);
	ligne3.push_back(matrice[2][0] * matrice2.getMatrice()[0][1] + matrice[2][1] * matrice2.getMatrice()[1][1] + matrice[2][2] * matrice2.getMatrice()[2][1]);
	ligne3.push_back(matrice[2][0] * matrice2.getMatrice()[0][2] + matrice[2][1] * matrice2.getMatrice()[1][2] + matrice[2][2] * matrice2.getMatrice()[2][2]);	
	Matrix3 matriceProduit;
	matriceProduit.matrice.push_back(ligne1);
	matriceProduit.matrice.push_back(ligne2);
	matriceProduit.matrice.push_back(ligne3);
	return matriceProduit;
}

Vecteur3D Matrix3::operator*(const Vecteur3D& vecteur) const
{
	Vecteur3D vecteurProduit;
	vecteurProduit.setX(matrice[0][0] * vecteur.getX() + matrice[0][1] * vecteur.getY() + matrice[0][2] * vecteur.getZ());
	vecteurProduit.setY(matrice[1][0] * vecteur.getX() + matrice[1][1] * vecteur.getY() + matrice[1][2] * vecteur.getZ());
	vecteurProduit.setZ(matrice[2][0] * vecteur.getX() + matrice[2][1] * vecteur.getY() + matrice[2][2] * vecteur.getZ());
	return vecteurProduit;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& matrice)
{
	os << matrice.getMatrice()[0][0] << " " << matrice.getMatrice()[0][1] << " " << matrice.getMatrice()[0][2] << std::endl;
	os << matrice.getMatrice()[1][0] << " " << matrice.getMatrice()[1][1] << " " << matrice.getMatrice()[1][2] << std::endl;
	os << matrice.getMatrice()[2][0] << " " << matrice.getMatrice()[2][1] << " " << matrice.getMatrice()[2][2] << std::endl;
	return os;
}
