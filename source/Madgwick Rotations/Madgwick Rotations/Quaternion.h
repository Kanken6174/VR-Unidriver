/**
 * @file Quaternion.h
 * @author Elliott Le Guéhennec(elliott.le_guehennec@etu.uca.fr)
 * @brief Definition of struct Quaternion, which represents a manipulatable Quaternion
 * @version 0.2
 * @date 2022-02-13
 */
#pragma once

namespace madgwickRotations {
	/**
	 * @brief Quaternion used to represent a rotation.
	 * A quaternion is a hyper complex number, containing 1 real dimension and 3 imaginary ones (i, j, k)
	 *
	 */
	struct Quaternion {
	public: //constructors
		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param x Value for x
		 * @param y Value for y
		 * @param z Value for z
		 * @param w Value for w
		 */
		Quaternion(double x, double y, double z, double w);

		/**
		 * @brief Default constructor
		 */
		Quaternion();

	public: //methods defined in Quaternion.cpp
		/**
		 * @brief Returns self's conjugate.
		 * If a quaternion can be expressed as RE + IM, its conjugate is RE - IM
		 *
		 * @return Quaternion conjugate
		 */
		Quaternion conjuguate();

		/**
		 * @brief Returns self's magnitude.
		 * The magnitude of a quaternion defined as Q = a + bi + cj + dk is a² + b² + c² + d²
		 *
		 * @return double magnitude
		 */
		double magnitude();
		Quaternion reciprocal();

		/**
		 * @brief Multiply self by a real number
		 *
		 * @param value factor for the multiplication
		 * @return Quaternion result of the multiplication
		 */
		Quaternion multiplyByReal(double value);

		/**
		 * @brief returns - Quaternion
		 *
		 * @return Quaternion negative
		 */
		Quaternion negative();

	private: //coordinates of a quaternion
		/**
		 * @brief the real part
		 *
		 */
		double x;

		/**
		 * @brief imaginary value: i
		 *
		 */
		double y;

		/**
		 * @brief imaginary value: j
		 *
		 */
		double z;

		/**
		 * @brief imaginary value: k
		 *
		 */
		double w;

	public: //getters for the coordinates
		double getX() const;
		double getY() const;
		double getZ() const;
		double getW() const;

		//redefinition of += operator
		Quaternion operator+=(const Quaternion& other);


	};

	//redefinition of operators: quaternion calculations

	//q1 + q2
	Quaternion operator+(const Quaternion& q1, const Quaternion& q2);

	//q1 - q2
	Quaternion operator-(const Quaternion& q1, const Quaternion& q2);

	//q1 * q2
	Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

	//q1 * num
	Quaternion operator*(const Quaternion& q, const double num);

	//q1 / num
	Quaternion operator/(const Quaternion& q, const double num);
}