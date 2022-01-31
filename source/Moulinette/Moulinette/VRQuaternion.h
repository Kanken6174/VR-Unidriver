

#include "VRComponent.h"
#include "moulinette_components.h"
#include "../../madgwickRotations library/Quaternion.h"

using namespace madgwickRotations;
using namespace moulinette_components;

class VRQuaternion : public VRComponent
{
public:
	Quaternion quaternion;

	std::string to_string() override;
};

