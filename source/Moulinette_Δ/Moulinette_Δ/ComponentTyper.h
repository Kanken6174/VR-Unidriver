#pragma once
#include"VRAnalog.h"
#include"VRComponent.h"
#include"VRRelative.h"
#include "VRBoolean.h"
#include "VRQuaternion.h"

static class ComponentTyper {
private:
public:
	static void provideDataToComponent(VRComponent* component, string data);
	static string requestDataFromComponent(VRComponent* component);
};