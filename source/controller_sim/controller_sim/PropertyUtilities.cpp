/**
* @author Yorick Geoffre
* @brief defines methods related to property setting on the OpenVR side (these are shortened version of the usual methods)
* @version 0.7
* @date 22/12/2021
*/

#include "controller_sim.h"


void DoMoDriver::setStrProperty(vr::ETrackedDeviceProperty SVRproperty, std::string value)
{
	vr::VRProperties()->SetStringProperty(deviceContainer, SVRproperty, value.c_str());
}

void DoMoDriver::setInt32Property(vr::ETrackedDeviceProperty SVRproperty, int32_t value)
{
	vr::VRProperties()->SetInt32Property(deviceContainer, SVRproperty, value);
}

void DoMoDriver::setUInt64Property(vr::ETrackedDeviceProperty SVRproperty, uint64_t value)
{
	vr::VRProperties()->SetUint64Property(deviceContainer, SVRproperty, value);
}

void DoMoDriver::setBoolProperty(vr::ETrackedDeviceProperty SVRproperty, bool value)
{
	vr::VRProperties()->SetBoolProperty(deviceContainer, SVRproperty, value);
}