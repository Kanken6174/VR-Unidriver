#pragma once

#define BUTTON 0
#define ANALOG 1
#define RELATIVE 2
#define QUATERNION 3

#include<stdexcept>
#include<string>

#include "../utilities/utilities.h"
#include"../Rotations/Quaternion.h"
#include"../Rotations/Vector.h"

using namespace std;
using namespace madgwickRotations;
using namespace utilities;