#pragma once
#include <iostream>
#include"Quaternion.h"

void printq(madgwickRotations::Quaternion &q);
void expectedVsResult(madgwickRotations::Quaternion expected, madgwickRotations::Quaternion& result);