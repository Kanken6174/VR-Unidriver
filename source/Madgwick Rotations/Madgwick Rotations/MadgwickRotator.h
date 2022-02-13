/**
 * @file MadgwickRotator.h
 * @author Elliott Le Guéhennec (elliott.le_guehennec@etu.uca.fr)
 * @brief The main class for this library. One MadgwickRotator will handle the tracking of your equipment's orientation. Important method to utilise this class is update. More details below.
 * @version 0.2
 * @date 2022-02-13
 */
#pragma once
#include <ctime>
#include "Vector.h"
#include "Quaternion.h"

namespace madgwickRotations {

	/**
	 * @brief A MadgwickRotator tracks the orientation of an object through the measurements of a gyroscope, an accelerometer, and a magnetometer. 
	 * To do so it calculates the difference between the most recent measure and the last estimated orientation. 
	 * Also uses a reference frame to correct deviations.
	 * Usage : call constructor to build the object, specifying your correction strength (aStepSize and mStepSize)
	 */
	class MadgwickRotator
	{
	private://attributes

		/**
		 * @brief LEO stands for Last Estimated Orientation.
		 * Needed to calculate current estimated orientation.
		 * Automatically updated.
		 */
		Quaternion leo;

		/**
		 * @brief Reference vector for gyroscope measures.
		 *
		 */
		Vector zGyro;

		/**
		 * @brief Reference vector for accelerometer measures.
		 *
		 */
		Vector zAccel;

		/**
		 * @brief Reference vector for magnetometer measures.
		 *
		 */
		Vector zMagneto;

		/**
		 * @brief Defines with which strength correction function using accelerometer is applied.
		 * 0 : not applied at all.
		 * 1 : applied full-scale.
		 * 0.5 : applied half-scale.
		 * This value cannot be negative.
		 */
		float aStepSize;

		/**
		 * @brief Defines with which strength correction function using magnetometer is applied.
		 * 0 : not applied at all.
		 * 1 : applied full-scale.
		 * 0.5 : applied half-scale.
		 * This value cannot be negative.
		 */
		float mStepSize;

		/**
		 * @brief False as long as init method has never been called
		 *
		 */
		bool inited = false;

	public://constructor
		/**
		 * @brief Construct a new Madgwick Rotator object
		 *
		 * @param aStepSize fills field aStepSize. Default value : 1.
		 * @param mStepSize fills field mStepSize. Default value : 1.
		 */
		MadgwickRotator(float aStepSize = 1, float mStepSize = 1) : aStepSize(aStepSize), mStepSize(mStepSize) {}

	public://methods defined in MadgwickRotator.cpp
		/**
		 * @brief Update the orientation of your VR equipment. This is the method you need to use
		 *
		 * @param delay Time passed since last update.
		 * @param g Gyroscope measurement
		 * @param a Accelerometer measurement
		 * @param m Magnetometer measurement
		 * @return Quaternion = Current Orientation
		 */
		Quaternion update(time_t delay, Vector g, Vector a, Vector m);

		/**
		 * @brief Load the reference frame, that shall be considered as 0 space.
		 *
		 * @param zGyro Gyroscope reference
		 * @param zAccel Accelerometer reference
		 * @param zMagneto Magnetometer reference
		 */
		void init(Vector zGyro, Vector zAccel, Vector zMagneto);

		/**
		 * @brief Sets field aStepSize to value of parameter
		 *
		 * @param value Cannot be negative
		 */
		void setAStepSize(float value);

		/**
		 * @brief Sets field mStepSize to value of parameter
		 *
		 * @param value Cannot be negative
		 */
		void setMStepSize(float value);

	private://methods defined in MadgwickRotator.cpp
		/**
		 * @brief Submethod for update(). Calculate the change between LEO and CEO, with help from correction functions.
		 *
		 * @param g Gyroscope measurement
		 * @param aCorrection result from correctionFunction() with accelerometer, before aStepSize application
		 * @param mCorrection result from correctionFunction() with accelerometer, before mStepSize application
		 * @return Quaternion = change (update() local variable)
		 */
		Quaternion changeSincePrevious(Vector g, Quaternion aCorrection, Quaternion mCorrection);

		/**
		 * @brief Submethod for update(). Correct the estimated orientation with help of reference measurements. Two calls in update : (a, zGyro) and (m, zMagneto)
		 *
		 * @param currentMeasure the measurement from your equipment
		 * @param reference a reference vector
		 * @return Quaternion = correction/magnitude
		 */
		Quaternion correctionFunction(Vector currentMeasure, Vector reference);
	};
}