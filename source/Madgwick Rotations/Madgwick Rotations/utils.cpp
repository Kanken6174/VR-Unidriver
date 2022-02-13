#include "utils.h"

void printq(madgwickRotations::Quaternion &q) {
	std::cout << "||Q = " << q.getX() << " + " << q.getY() << "i + " << q.getZ() << "j + " << q.getW() << "k||" << std::endl;
}

void expectedVsResult(madgwickRotations::Quaternion expected, madgwickRotations::Quaternion& result) {
	std::cout << "Expected result : ";
	printq(expected);
	std::cout << "Obtained : ";
	printq(result);
}