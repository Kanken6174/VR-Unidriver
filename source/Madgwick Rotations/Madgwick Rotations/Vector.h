/**
 * @file Vector.h
 * @author elliott.le_guehennec@etu.uca.fr
 * @brief Defines struct Vector, which is used as input.
 * @version 0.1
 * @date 2021-12-13
 */
#pragma once

#include "madgwickRotations.h"

/**
 * @brief A three-dimensional vector representing the forces measured by an instrument (e.g. gyroscope).
 * 
 */
struct madgwickRotations::Vector {
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
	Quaternion toQuaternion(); //converts vector to a quaternion

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

public: //getters fpr the coordinates
	double getX();
	double getY();
	double getZ();
};