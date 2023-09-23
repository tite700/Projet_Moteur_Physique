#include "Particule.h"

Particule::Particule(Vector pos, float masse) : pos(pos), inverseMasse(1 / masse), hasStarted(false)
{
	velocite = Vector::zeros();
	acceleration = Vector::zeros();
	lastFrame = clock();
	body.setRadius(10);
	hasStarted = false;
}

void Particule::start()
{
	if (!hasStarted) {
		hasStarted = true;
	}
}

void Particule::update()
{
	clock_t deltaTime = clock() - lastFrame;
	lastFrame = clock();

	if (hasStarted) {

		pos += deltaTime * velocite * 0.001;

		velocite += deltaTime * acceleration * 0.001;
	}
	

	body.setPosition(pos.x, pos.y, pos.z);

}

Vector Particule::getPos()
{
	return pos;
}

void Particule::draw()
{
	body.draw();
}

void Particule::integrer(float temps)
{
	pos += velocite * temps;
	velocite += acceleration * temps;
}

void Particule::setPos(Vector nPos)
{
	pos = nPos;
}

float Particule::getMasse()
{
	return 1 / inverseMasse;
}

void Particule::setMasse(float nMasse)
{
	inverseMasse = 1 / nMasse;
}

void Particule::setVelocite(Vector velocite)
{
	this->velocite = velocite;
}

void Particule::setAcceleration(Vector accel)
{
	acceleration = accel;
}

void Particule::setRadius(float radius)
{
	body.setRadius(radius);
}

void Particule::setHasStarted(bool hasStarted)
{
	this->hasStarted = hasStarted;
}

bool Particule::getHasStarted()
{
	return hasStarted;
}