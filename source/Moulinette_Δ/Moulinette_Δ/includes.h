#pragma once

#define BUTTON 0
#define ANALOG 1
#define RELATIVE 2
#define QUATERNION 3

#include<stdexcept>
#include<string>

#include "../utilities/utilities.h"
#include"../../Madgwick Rotations/Madgwick Rotations/Quaternion.h"
#include"../../Madgwick Rotations/Madgwick Rotations/Vector.h"

using namespace std;
using namespace madgwickRotations;
using namespace utilities;