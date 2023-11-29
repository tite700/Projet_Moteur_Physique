#include "UnitTest.h"

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


    // Test de la transpos�e
    Matrix3 transposee = matrice3.transpose();
    assert(transposee.getMatrice() == std::vector<std::vector<float>>({{1.0f, 4.0f, 7.0f}, { 2.0f, 5.0f, 8.0f }, { 3.0f, 6.0f, 9.0f }}));

    // Test de l'identit�
    Matrix3 matrice3Id = Matrix3::identite();
    assert(matrice3Id.getMatrice() == std::vector<std::vector<float>>({{1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }}));

    //Test de l'op�rateur *
    Matrix3 matrice8(1.0f, 2.0f, 3.0f, 4.0f, 5.0f,6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 matrice9(&matrice8);
    Matrix3 matrice10 = matrice8 * matrice9;
    assert(matrice10.getMatrice() == std::vector<std::vector<float>>({{30.0f, 36.0f, 42.0f}, { 66.0f, 81.0f, 96.0f }, { 102.0f, 126.0f, 150.0f }}));
}

void testMatrix4() {
    //// Test des constructeurs de la classe Matrix4
    Matrix4 matrice1;
    assert(matrice1.getMatrice() == std::vector<std::vector<float>>({ {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f}, {0.0f, 0.0f,0.0f, 0.0f} }));

    Matrix4 matrice2(1.0f, 2.0f, 3.0f, 4.0f,5.0f, 6.0f, 7.0f, 8.0f,9.0f, 10.0f, 11.0f, 12.0f,13.0f, 14.0f, 15.0f, 16.0f);
    assert(matrice2.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    Vecteur3D vecteur1(1.0f, 2.0f, 3.0f);
    Vecteur3D vecteur2(4.0f, 5.0f, 6.0f);
    Vecteur3D vecteur3(7.0f, 8.0f, 9.0f);
    Vecteur3D vecteur4(10.0f, 11.0f, 12.0f);
    Matrix4 matrice3(vecteur1, vecteur2, vecteur3, vecteur4);
    assert(matrice3.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 0.0f}, { 4.0f, 5.0f, 6.0f, 0.0f }, { 7.0f, 8.0f, 9.0f, 0.0f }, { 10.0f, 11.0f, 12.0f, 0.0f }}));

    Matrix4 matrice4(std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));
    assert(matrice4.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    Matrix4 matrice5(&matrice4);
    assert(matrice5.getMatrice() == std::vector<std::vector<float>>({{1.0f, 2.0f, 3.0f, 4.0f}, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f }, { 13.0f, 14.0f, 15.0f, 16.0f }}));

    // Test de la transpos�e
    Matrix4 transposee = matrice3.transpose();
    assert(transposee.getMatrice() == std::vector<std::vector<float>>({ {1.0f, 4.0f, 7.0f, 10.0f}, { 2.0f, 5.0f, 8.0f, 11.0f }, { 3.0f, 6.0f, 9.0f, 12.0f }, { 0.0f, 0.0f, 0.0f, 0.0f } }));

    // Test de l'identit�
    Matrix4 matrice4Id = Matrix4::identite();
    assert(matrice4Id.getMatrice() == std::vector<std::vector<float>>({ {1.0f, 0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f }, {0.0f, 0.0f, 0.0f, 1.0f} }));

    //Test de l'op�rateur *
    Matrix4 matrice8(1.0f, 2.0f, 3.0f, 4.0f,5.0f, 6.0f, 7.0f, 8.0f,9.0f, 10.0f, 11.0f, 12.0f,13.0f, 14.0f, 15.0f, 16.0f);
    Matrix4 matrice9(&matrice8);
    Matrix4 matrice10 = matrice8 * matrice9;
    assert(matrice10.getMatrice() == std::vector<std::vector<float>>({{90.0f, 100.0f, 110.0f, 120.0f}, {202.0f, 228.0f, 254.0f, 280.0f}, {314.0f, 356.0f, 398.0f, 440.0f}, {426.0f, 484.0f, 542.0f, 600.0f}}));

}

void testQuaternion() {

    // Test des constructeurs de la classe Quaternion
    Quaternion quat1;
    assert(quat1.getA() == 0.0f);
    assert(quat1.getB() == 0.0f);
    assert(quat1.getC() == 0.0f);
    assert(quat1.getD() == 0.0f);

    Quaternion quat2(1.0f, 2.0f, 3.0f, 4.0f);
    assert(quat2.getA() == 1.0f);
    assert(quat2.getB() == 2.0f);
    assert(quat2.getC() == 3.0f);
    assert(quat2.getD() == 4.0f);

    // Test des op�rations sur les quaternions
    Quaternion quat3(2.0f, 3.0f, 4.0f, 5.0f);

    // Test de l'addition
    Quaternion sum = quat2 + quat3;
    assert(sum.getA() == 3.0f);
    assert(sum.getB() == 5.0f);
    assert(sum.getC() == 7.0f);
    assert(sum.getD() == 9.0f);

    // Test de la soustraction
    Quaternion diff = quat2 - quat3;
    assert(diff.getA() == -1.0f);
    assert(diff.getB() == -1.0f);
    assert(diff.getC() == -1.0f);
    assert(diff.getD() == -1.0f);

    // Test de la multiplication par un scalaire
    Quaternion scaled = quat2 * 2.0f;
    assert(scaled.getA() == 2.0f);
    assert(scaled.getB() == 4.0f);
    assert(scaled.getC() == 6.0f);
    assert(scaled.getD() == 8.0f);

    // Test de la multiplication de quaternions
    Quaternion product = quat2 * quat3;
    assert(product.getA() == -36.0f);
    assert(product.getB() == 6.0f);
    assert(product.getC() == 12.0f);
    assert(product.getD() == 12.0f);

    // Test des op�rations compos�es
    quat2 += quat3;
    assert(quat2.getA() == 3.0f);
    assert(quat2.getB() == 5.0f);
    assert(quat2.getC() == 7.0f);
    assert(quat2.getD() == 9.0f);

    quat2 -= quat3;
    assert(quat2.getA() == 1.0f);
    assert(quat2.getB() == 2.0f);
    assert(quat2.getC() == 3.0f);
    assert(quat2.getD() == 4.0f);

    // Test de la multiplication par un scalaire � gauche
    Quaternion scaledLeft = 2.0f * quat2;
    assert(scaledLeft.getA() == 2.0f);
    assert(scaledLeft.getB() == 4.0f);
    assert(scaledLeft.getC() == 6.0f);
    assert(scaledLeft.getD() == 8.0f);

    // Test de l'affichage
    std::cout << "Quaternion: " << quat2 << std::endl;
}

void TestCorpsRigide()
{
	// Test des constructeurs de la classe CorpsRigide
    CorpsRigide corpsRigide0;

    assert(corpsRigide0.getPosition() == Vecteur3D(0, 0, 0));
    assert(corpsRigide0.getVelocite() == Vecteur3D(0, 0, 0));
    assert(corpsRigide0.getAcceleration() == Vecteur3D(0, 0, 0));
    assert(corpsRigide0.getOrientationQuat() == Quaternion(1, 0, 0, 0));
    assert(corpsRigide0.getForceAccum() == Vecteur3D(0.0, 0, 0));
	assert(corpsRigide0.getTorqueAccum() == Vecteur3D(0, 0, 0));
    assert(corpsRigide0.getInverseMass() == 1.0);
    assert(corpsRigide0.getMass() == 1.0);
	assert(corpsRigide0.getOrientation() == Matrix3(1, 0, 0, 0, -1, 0, 0, 0, -1));
 

    CorpsRigide corpsRigide1(Vecteur3D(320, 520, 0), Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), Quaternion(0.0, 0.0, 1.0, 0.0), 1.0, Vecteur3D(0.0, 0, 0), Vecteur3D(0, 0, 0));

    assert(corpsRigide1.getPosition() == Vecteur3D(320, 520, 0));
    assert(corpsRigide1.getVelocite() == Vecteur3D(0, 0, 0));
    assert(corpsRigide1.getAcceleration() == Vecteur3D(0, 0, 0));
    assert(corpsRigide1.getOrientationQuat() == Quaternion(0.0, 0.0, 1.0, 0.0));
    assert(corpsRigide1.getForceAccum() == Vecteur3D(0.0, 0, 0));
    assert(corpsRigide1.getTorqueAccum() == Vecteur3D(0, 0, 0));
    assert(corpsRigide1.getInverseMass() == 1.0);
    assert(corpsRigide1.getMass() == 1.0);
    assert(corpsRigide1.getOrientation() == Matrix3(-1, 0, 0, 0, -1.0, 0, 0, 0, 1.0));
    assert(corpsRigide1.getOrientation().transpose() == Matrix3(-1.0, 0, 0, 0, -1.0, 0, 0, 0, 1.0));

    corpsRigide1.addForce(Vecteur3D(1.0, 0, 0));
    corpsRigide1.addTorque(Vecteur3D(1.0, 0, 0));

    assert(corpsRigide1.getForceAccum() == Vecteur3D(1.0, 0, 0));
    assert(corpsRigide1.getTorqueAccum() == Vecteur3D(1.0, 0, 0));
    
    corpsRigide1.clearAccumulators();
    
    assert(corpsRigide1.getForceAccum() == Vecteur3D(0.0, 0, 0));
	assert(corpsRigide1.getTorqueAccum() == Vecteur3D(0.0, 0, 0));

	corpsRigide1.setInverseMass(2.0);
	assert(corpsRigide1.getInverseMass() == 2.0);
	assert(corpsRigide1.getMass() == 0.5);

	corpsRigide1.setVelocite(Vecteur3D(1.0, 0, 0));
	assert(corpsRigide1.getVelocite() == Vecteur3D(1.0, 0, 0));

	corpsRigide1.setAcceleration(Vecteur3D(1.0, 0, 0));
	assert(corpsRigide1.getAcceleration() == Vecteur3D(1.0, 0, 0));

	corpsRigide1.setPosition(Vecteur3D(1.0, 0, 0));
    assert(corpsRigide1.getPosition() == Vecteur3D(1.0, 0, 0));
    
    //Integration

    corpsRigide1.Integrate(1.0);
    assert(corpsRigide1.getPosition() == Vecteur3D(2.0, 0, 0));
    assert(corpsRigide1.getVelocite() == Vecteur3D(1.0, 0, 0));
    assert(corpsRigide1.getAcceleration() == Vecteur3D(0.0, 0, 0));

    assert(corpsRigide1.getOrientationQuat() == Quaternion(0.0, 0.0, 1.0, 0.0));
    assert(corpsRigide1.getOrientation() == Matrix3(-1, 0, 0, 0, -1.0, 0, 0, 0, 1.0));

    corpsRigide1.addTorque(Vecteur3D(0.0, 0, 1.0));
    corpsRigide1.Integrate(1.0);

    assert(corpsRigide1.getPosition() == Vecteur3D(3.0, 0, 0));
    assert(corpsRigide1.getVelocite() == Vecteur3D(1.0, 0, 0));
    assert(corpsRigide1.getAcceleration() == Vecteur3D(0.0, 0, 0));
    assert(corpsRigide1.getOrientationQuat() == Quaternion(0.0, 0.0, 1.0, 0.0));

    corpsRigide1.Integrate(1.0);
    float A = corpsRigide1.getOrientationQuat().getA();
    float B = corpsRigide1.getOrientationQuat().getB();
    float C = corpsRigide1.getOrientationQuat().getC();
    float D = corpsRigide1.getOrientationQuat().getD();

    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;
    std::cout << "C: " << C << std::endl;
    std::cout << "D: " << D << std::endl;
    assert(std::abs(A + 0) < 0.01);
    assert(std::abs(B + 1) < 0.01);
    assert(std::abs(C - 0.02) < 0.01);
    assert(std::abs(D + 0) < 0.01);




}