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
