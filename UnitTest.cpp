#include "UnitTest.h"
#include "Vecteur3D.h"
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
