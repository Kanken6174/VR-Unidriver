#include "ComponentTyper.h"


void ComponentTyper::provideDataToComponent(VRComponent* component, string data)
{
	switch (component->gettype())
	{
	case BUTTON:
		dynamic_cast<VRBoolean*>(component)->receiveData(data);
		break;
	case ANALOG:
		dynamic_cast<VRAnalog*>(component)->receiveData(data);
		break;
	case RELATIVE:
		dynamic_cast<VRRelative*>(component)->receiveData(data);
		break;
	case QUATERNION:
		dynamic_cast<VRQuaternion*>(component)->receiveData(data);
		break;
	default:
		break;
	}
}

string ComponentTyper::requestDataFromComponent(VRComponent* component)
{
	switch (component->gettype())
	{
	case BUTTON:
		return dynamic_cast<VRBoolean*>(component)->to_string();
		break;
	case ANALOG:
		return dynamic_cast<VRAnalog*>(component)->to_string();
		break;
	case RELATIVE:
		return dynamic_cast<VRRelative*>(component)->to_string();
		break;
	case QUATERNION:
		return dynamic_cast<VRQuaternion*>(component)->to_string();
		break;
	default:
		break;
	}
}
