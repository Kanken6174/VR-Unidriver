#include "utils.h"

void printq(madgwickRotations::Quaternion &q) {
	std::cout << "||Q = " << q.getX() << " + " << q.getY() << "i + " << q.getZ() << "j + " << q.getW() << "k||" << std::endl;
}