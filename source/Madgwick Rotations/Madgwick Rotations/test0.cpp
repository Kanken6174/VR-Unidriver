#include "test0.h"
#include "headers.h"

using namespace std;

void testAllValuesToZero()
{
	cout << "Begin test : all values to Zero" << endl << endl << "Creating values..." << endl;

	//initialise values
	float accCS = 0, magCS = 0;
	time_t delay = 100;
	Vector g = Vector(1, 2, 3);
	Vector a = g, m = g;
	Quaternion quaternion;

	cout << "Values created" << endl << endl << "Initialising rotator..." << endl;

	MadgwickRotator rotator = MadgwickRotator(accCS, magCS);

	cout << "Rotator initialized" << endl << endl << "First update on Quaternion..." << endl;

	quaternion = rotator.update(delay, g, a, m);
	printq(quaternion);
}

void rotationTest() {
	Quaternion entry = Quaternion(1, 2, 3, 4);
	Vector vec = Vector(5, 6, 7);
	cout << "Begin test : rotate" << endl;
	cout << "---" << endl << "Multiply 2 identical quaternions" << endl;

	Quaternion result = entry * entry;
	expectedVsResult(Quaternion(-28, 4, 6, 8), result);

	cout << "---" << endl << "Multiply 2 different quaternions" << endl;

	result = entry * vec.toQuaternion();
	expectedVsResult(Quaternion(-28, -12, 46, 16), result);

	cout << "---" << endl << "Rotate a vector using a quaternion" << endl;
	result = rotate(entry, vec);
	expectedVsResult(entry * vec.toQuaternion() * entry.reciprocal(), result);

	cout << "---" << endl << "Rotate a vector using a value 1 quaternion" << endl;
	result = rotate(Quaternion(1, 0, 0, 0), vec);
	printq(result);

	cout << "---" << endl << "Continue rotating" << endl;
	result = rotate(result, vec);
	printq(result);
	result = rotate(result, Vector(3, 2, 1));
	printq(result);
	result = rotate(result, Vector(10, 0, 20));
	printq(result);
}