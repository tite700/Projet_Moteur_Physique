#include "UnitTest.h"
#include "Vecteur3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <cassert>
#include <iostream>
#include <cmath>

void testConstructors() {

    Vecteur3D vecteur(1.0f, 2.0f, 3.0f);
    assert(vecteur.getX() == 1.0f);
    assert(vecteur.getY() == 2.0f);
    assert(vecteur.getZ() == 3.0f);

    Vecteur3D vecteur2;
    assert(vecteur2.getX() == 0.0f);
    assert(vecteur2.getY() == 0.0f);
    assert(vecteur2.getZ() == 0.0f);
}

void testOperations() {

    Vecteur3D vecteur1(1.0f, 2.0f, 3.0f);
    Vecteur3D vecteur2(4.0f, 5.0f, 6.0f);
    Vecteur3D somme = vecteur1 + vecteur2;
    assert(somme == Vecteur3D(5.0f, 7.0f, 9.0f));


    Vecteur3D difference = vecteur1 - vecteur2;
    assert(difference == Vecteur3D(-3.0f, -3.0f, -3.0f));


    Vecteur3D produit = vecteur1 * 2.0f;
    assert(produit == Vecteur3D(2.0f, 4.0f, 6.0f));
}

void testMethods() {

    Vecteur3D vecteur1(1.0f, 2.0f, 3.0f);
    Vecteur3D vecteur2(4.0f, 5.0f, 6.0f);
    float prodScalaire = vecteur1.prodscal(vecteur2);
    assert(fabs(prodScalaire - 32.0f) < 1e-6);


    Vecteur3D prodVectoriel = vecteur1.prodvect(vecteur2);
    assert(prodVectoriel == Vecteur3D(-3.0f, 6.0f, -3.0f));


    Vecteur3D vecteur3(3.0f, 4.0f, 5.0f);
    float norme = vecteur3.norme();
    assert(fabs(norme - 7.0710678f) < 1e-6);
}


void testMatrix3() {
    // Test des constructeurs de la classe Matrix3
    Matrix3 matrice1;
    assert(matrice1.getMatrice() == std::vector<std::vector<float>>({ {0.0f, 0.0f,0.0f}, {0.0f, 0.0f,0.0f}, {0.0f, 0.0f,0.0f} }));

    Matrix3 matrice2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    assert(matrice2.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f}, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }}));

    Vecteur3D vecteur1(1.0f, 2.0f, 3.0f);
    Vecteur3D vecteur2(4.0f, 5.0f, 6.0f);
    Vecteur3D vecteur3(7.0f, 8.0f, 9.0f);

    Matrix3 matrice3(vecteur1, vecteur2, vecteur3);
    assert(matrice3.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f}, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }}));

    Matrix3 matrice4(vecteur1, vecteur2, vecteur3, true);
    assert(matrice4.getMatrice() == std::vector<std::vector<float>>({{1.0f, 4.0f, 7.0f}, { 2.0f, 5.0f, 8.0f }, { 3.0f, 6.0f, 9.0f }}));

    Matrix3 matrice5(std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f}, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }}));
    assert(matrice5.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f}, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }}));

    Matrix3 matrice6(&matrice5);
    assert(matrice6.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f}, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }}));


    // Test de la transposée
    Matrix3 transposee = matrice3.transpose();
    assert(transposee.getMatrice() == std::vector<std::vector<float>>({{1.0f, 4.0f, 7.0f}, { 2.0f, 5.0f, 8.0f }, { 3.0f, 6.0f, 9.0f }}));

    // Test de l'identité
    Matrix3 matrice3Id = Matrix3::identite();
    assert(matrice3Id.getMatrice() == std::vector<std::vector<float>>({{1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }}));

    //Test de l'opérateur *
    Matrix3 matrice8(1.0f, 2.0f, 3.0f, 4.0f, 5.0f,6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 matrice9(&matrice8);
    Matrix3 matrice10 = matrice8 * matrice9;
    assert(matrice10.getMatrice() == std::vector<std::vector<float>>({{30.0f, 36.0f, 42.0f}, { 66.0f, 81.0f, 96.0f }, { 102.0f, 126.0f, 150.0f }}));
}

void testMatrix4() {
    // Test des constructeurs de la classe Matrix4
    Matrix4 matrice1;
    assert(matrice1.getMatrice() == std::vector<std::vector<float>>({ {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f} }));

    Matrix4 matrice2(1.0f, 2.0f, 3.0f, 4.0f,5.0f, 6.0f, 7.0f, 8.0f,9.0f, 10.0f, 11.0f, 12.0f,13.0f, 14.0f, 15.0f, 16.0f);
    assert(matrice2.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    Vecteur3D vecteur1(1.0f, 2.0f, 3.0f);
    Vecteur3D vecteur2(4.0f, 5.0f, 6.0f);
    Vecteur3D vecteur3(7.0f, 8.0f, 9.0f);
    Vecteur3D vecteur4(10.0f, 11.0f, 12.0f);
    Matrix4 matrice3(vecteur1, vecteur2, vecteur3, vecteur4);
    assert(matrice3.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 0.0f}, { 4.0f, 5.0f, 6.0f, 0.0f }, { 7.0f, 8.0f, 9.0f, 0.0f }, { 10.0f, 11.0f, 12.0f, 1.0f }}));

    Matrix4 matrice4(std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));
    assert(matrice4.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    Matrix4 matrice5(&matrice4);
    assert(matrice5.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    // Test de la transposée
    Matrix4 transposee = matrice3.transpose();
    assert(transposee.getMatrice() == std::vector<std::vector<float>>({ {1.0f, 4.0f, 7.0f, 10.0f}, { 2.0f, 5.0f, 8.0f, 11.0f }, { 3.0f, 6.0f, 9.0f, 12.0f }, { 0.0f, 0.0f, 0.0f, 1.0f } }));

    // Test de l'identité
    Matrix4 matrice4Id = Matrix4::identite();
    assert(matrice4Id.getMatrice() == std::vector<std::vector<float>>({ {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }));

    //Test de l'opérateur *
    Matrix4 matrice8(1.0f, 2.0f, 3.0f, 4.0f,5.0f, 6.0f, 7.0f, 8.0f,9.0f, 10.0f, 11.0f, 12.0f,13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4 matrice9(&matrice8);
    Matrix4 matrice10 = matrice8 * matrice9;
    assert(matrice10.getMatrice() == std::vector<std::vector<float>>({{90.0f, 100.0f, 110.0f, 120.0f}, {202.0f, 228.0f, 254.0f, 280.0f}, {314.0f, 356.0f, 398.0f, 440.0f}, {426.0f, 484.0f, 542.0f, 600.0f}}));

}