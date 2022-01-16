/**
* @author Yorick Geoffre
* @brief this file holds the declaration of maths-related functions
* @version 0.1
* @date 16/12/2021
*/

#pragma once
#include "includes.hpp"

///<summary>
/// Une fonction qui va convertir trois angles d'euler en un quaternion SteamVR
///</summary>
///<param name="yaw">Le lacet en degrés</param>
///<param name="pitch">Le tangage en degrés</param>
///<param name="roll">Le roulis en degrés</param>
///<returns>HmdQuaternion_t un quaternion SteamVR</returns>
vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll);