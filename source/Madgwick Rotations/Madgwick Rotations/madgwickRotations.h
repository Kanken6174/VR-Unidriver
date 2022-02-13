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

	
	Quaternion rotate(Quaternion q, Vector v);

}