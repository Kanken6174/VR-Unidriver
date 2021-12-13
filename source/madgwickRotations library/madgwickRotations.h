/**
 * @file madgwickRotations.h
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief defines the namespace madgwickRotations that encapsulates the rotation process
 * @version 0.1
 * @date 2021-12-13
 */
#pragma once
#include <ctime>

/**
 * @brief namespace holding the objects used for rotations
 * 
 */
namespace madgwickRotations {
	//for doc see Vector.h
	struct Vector;

	//for doc see Quaternion.h
	struct Quaternion;

	//for doc see MadgwickRotator.h
	class MadgwickRotator;

	/**
	 * @brief Rotate a vector using a quaternion consists of multiplying the quaternion by the vector, and then by the quaternion's reciprocal
	 * 
	 * @param q A quaternion to rotate v
	 * @param v A vector to be rotated by q
	 * @return Quaternion = the resulting rotation
	 */
	Quaternion rotate(Quaternion q, Vector v);

	/**
	 * @brief Multiplies q1 by q2. Caution : q1 * q2 != q2 * q1 => order matters!
	 * 
	 * @param q1 the left quaternion
	 * @param q2 the right quaternion
	 * @return Quaternion = the result of the multiplication
	 */
	Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2);

	/**
	 * @brief Adds q1 and q2
	 * 
	 * @param q1 the left quaternion
	 * @param q2 the right quaternion
	 * @return Quaternion = the result of the addition
	 */
	Quaternion addQuaternions(Quaternion q1, Quaternion q2);
}