#include "test0.h"
#include "headers.h"

using namespace std;

void testAllValuesToZero()
{
	cout << "Begin test : all values to Zero" << endl << endl << "Creating values..." << endl;

	//initialise values
	float accCS = 0, magCS = 0;
	time_t delay = 100;
	Vector g = Vector(0, 0, 0);
	Vector a = g, m = g;
	Quaternion quaternion;

	cout << "Values created" << endl << endl << "Initialising rotator..." << endl;

	MadgwickRotator rotator = MadgwickRotator(accCS, magCS);

	cout << "Rotator initialized" << endl << endl << "First update on Quaternion..." << endl;

	quaternion = rotator.update(delay, g, a, m);
	printq(quaternion);
}