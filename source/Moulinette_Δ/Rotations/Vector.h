/**
 * @file Vector.h
 * @author elliott.le_guehennec@etu.uca.fr
 * @brief Defines struct Vector, which is used as input.
 * @version 0.2
 * @date 2022-02-13
 */
#pragma once

#include "Quaternion.h"

namespace madgwickRotations {
	/**
	 * @brief A three-dimensional vector representing the forces measured by an instrument (e.g. gyroscope).
	 *
	 */
	struct Vector {
	public: //constructors
		/**
		 * @brief Construct a new Vector object
		 *
		 * @param x Value for x
		 * @param y Value for y
		 * @param z Value for z
		 */
		Vector(double x, double y, double z);

		/**
		 * @brief Default constructor
		 */
		Vector();

	public: //methods defined in Vector.cpp
		/**
		 * @brief Used for quaternion multiplication. A quaternion and a vector cannot just be multiplied, therefore we convert our vector, setting its W value to 0, so that it is compatible for multiplication.
		 *
		 * @return Quaternion version of self
		 */
		Quaternion useAsQuaternion(); //converts vector to a quaternion

	private: //coordinates of a vector
		/**
		 * @brief Value on axis x
		 *
		 */
		double x;

		/**
		 * @brief Value on axis y
		 *
		 */
		double y;

		/**
		 * @brief Value on axis z
		 *
		 */
		double z;

	public: //getters for the coordinates
		double getX();
		double getY();
		double getZ();
	};

	/**
	 * @brief Rotate a vector using a quaternion consists of multiplying the quaternion by the vector, and then by the quaternion's reciprocal
	 *
	 * @param q A quaternion to rotate v
	 * @param v A vector to be rotated by q
	 * @return Quaternion = the resulting rotation
	 */
	Quaternion rotate(Quaternion q, Vector v);
}