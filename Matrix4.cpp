#include "Matrix4.h"

Matrix4::Matrix4()
{
    matrice.resize(4, std::vector<float>(4, 0.0f));
}

Matrix4::Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
    matrice.push_back({ a, b, c, d });
    matrice.push_back({ e, f, g, h });
    matrice.push_back({ i, j, k, l });
    matrice.push_back({ m, n, o, p });
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

Matrix4::Matrix4(std::vector<std::vector<float>> matrice)
{
    this->matrice = matrice;
}

Matrix4::Matrix4(Matrix4* matrice)
{
    this->matrice.resize(4, std::vector<float>(4, 0.0f));
    for (int index = 0; index < 4; index++)
    {
        for (int index2 = 0; index2 < 4; index2++)
        {
            this->matrice[index][index2] = matrice->matrice[index][index2];
        }
    }
}
/*
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
*/

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

Matrix4 Matrix4::operator*(const Matrix4& matrice2) const
{
    Matrix4 matriceResultante;
    for (int index = 0; index < 4; index++)
    {
        for (int index2 = 0; index2 < 4; index2++)
        {
            matriceResultante.matrice[index][index2] =
                matrice[index][0] * matrice2.matrice[0][index2] +
                matrice[index][1] * matrice2.matrice[1][index2] +
                matrice[index][2] * matrice2.matrice[2][index2] +
                matrice[index][3] * matrice2.matrice[3][index2];
        }
    }
    return matriceResultante;
}

Vecteur3D Matrix4::operator*(const Vecteur3D& vecteur)
{
    Vecteur3D vecteurResultant;
    vecteurResultant.setX(matrice[0][0] * vecteur.getX() + matrice[0][1] * vecteur.getY() + matrice[0][2] * vecteur.getZ() + matrice[0][3] * vecteur.getW());
    vecteurResultant.setY(matrice[1][0] * vecteur.getX() + matrice[1][1] * vecteur.getY() + matrice[1][2] * vecteur.getZ() + matrice[1][3] * vecteur.getW());
    vecteurResultant.setZ(matrice[2][0] * vecteur.getX() + matrice[2][1] * vecteur.getY() + matrice[2][2] * vecteur.getZ() + matrice[2][3] * vecteur.getW());
    vecteurResultant.setW(matrice[3][0] * vecteur.getX() + matrice[3][1] * vecteur.getY() + matrice[3][2] * vecteur.getZ() + matrice[3][3] * vecteur.getW());
    return vecteurResultant;
}

Matrix4 Matrix4::identite()
{
    Matrix4 matriceIdentite;
    for (int index = 0; index < 4; index++)
    {
        matriceIdentite.matrice[index][index] = 1;
    }
    return matriceIdentite;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& matrice)
{
    for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			os << matrice.getMatrice()[index][index2] << " ";
		}
		os << std::endl;
	}
	return os;
}

bool operator==(const Matrix4& matrice1, const Matrix4& matrice2)
{
    for (int index = 0; index < 4; index++)
	{
		for (int index2 = 0; index2 < 4; index2++)
		{
			if (matrice1.getMatrice()[index][index2] != matrice2.getMatrice()[index][index2])
			{
				return false;
			}
		}
	}
	return true;
}
