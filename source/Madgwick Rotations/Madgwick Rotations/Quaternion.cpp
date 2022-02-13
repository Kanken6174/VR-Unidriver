/**
 * @file Quaternion.cpp
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief Defines the methods of struct Quaternion, along with quaternion operators. For doc regarding them see Quaternion.h
 * @version 0.2
 * @date 2022-02-13
 */
#include "Quaternion.h"

using namespace madgwickRotations;

madgwickRotations::Quaternion::Quaternion(double x, double y, double z, double w)
	: x(x), y(y), z(z), w(w){}

madgwickRotations::Quaternion::Quaternion() 
	: x(), y(), z(), w(){}

Quaternion Quaternion::conjuguate() {
	return Quaternion(x, -y, -z, -w);
}

double Quaternion::magnitude() {
	return x * x + y * y + z * z + w * w;
}

Quaternion Quaternion::reciprocal() {
	return conjuguate().multiplyByReal(1/magnitude());
}

Quaternion Quaternion::multiplyByReal(double f) {
	return Quaternion(x * f, y * f, z * f, w * f);
}

Quaternion Quaternion::negative() {
	return Quaternion(-x, -y, -z, -w);
}

double Quaternion::getX() const { return x; }
double Quaternion::getY() const { return y; }
double Quaternion::getZ() const { return z; }
double Quaternion::getW() const { return w; }

Quaternion Quaternion::operator+=(const Quaternion& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Quaternion madgwickRotations::operator+(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(
		q1.getX() + q2.getX(),
		q1.getY() + q2.getY(),
		q1.getZ() + q2.getZ(),
		q1.getW() + q2.getW()
	);
}

Quaternion madgwickRotations::operator-(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(
		q1.getX() - q2.getX(),
		q1.getY() - q2.getY(),
		q1.getZ() - q2.getZ(),
		q1.getW() - q2.getW()
	);
}

Quaternion madgwickRotations::operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(
		q1.getX() * q2.getX() - q1.getY() * q2.getY() - q1.getZ() * q2.getZ() - q1.getW() * q2.getW(),
		q1.getY() * q2.getX() + q1.getX() * q2.getY() + q1.getZ() * q2.getW() - q1.getW() * q2.getZ(),
		q1.getX() * q2.getZ() - q1.getY() * q2.getW() + q1.getZ() * q2.getX() + q1.getW() * q2.getY(),
		q1.getX() * q2.getW() + q1.getY() * q2.getZ() - q1.getZ() * q2.getY() + q1.getW() * q2.getX()
	);
}

Quaternion madgwickRotations::operator*(const Quaternion& q, const double num)
{
	return Quaternion(
		q.getX() * num,
		q.getY() * num,
		q.getZ() * num,
		q.getW() * num
	);
}

Quaternion madgwickRotations::operator/(const Quaternion& q, const double num)
{
	return Quaternion(
		q.getX() / num,
		q.getY() / num,
		q.getZ() / num,
		q.getW() / num
	);
}