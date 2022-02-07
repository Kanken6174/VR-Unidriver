#include "VRQuaternion.h"
#include <iostream>

void VRQuaternion::setValue(time_t delay, madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro)
{
    value = transformator.update(delay, acc, mag, gyro);
}

VRQuaternion::VRQuaternion(float accCorrectionStrength, float magCorrectionStrength) : transformator(accCorrectionStrength, magCorrectionStrength)
{
}

VRQuaternion::VRQuaternion()
{
    //Version sans offsets (par défaut)
}

string VRQuaternion::to_string()
{
    string toReturn = "";
    toReturn += std::to_string(value.getW()) + "_" + std::to_string(value.getX()) + "_" + std::to_string(value.getY()) + "_" + std::to_string(value.getZ());
    return toReturn;
}

void VRQuaternion::receiveData(string data) // TODO: modifier la trame en amont. delay doit être **au début** du string
{
    //cout << data << endl;
    vector<string> splitData = vector<string>();
    vector<double> numbers = vector<double>();

    splitData = utilities::split(data, '|');

    for (string data : splitData) {
        numbers.push_back(utilities::stringToDouble(data));
    }

    time_t delay = numbers[0]*1000;

    madgwickRotations::Vector gyroscopeData = Vector(numbers[1], numbers[2], numbers[3]);
    madgwickRotations::Vector accelerometerData = Vector(numbers[4],numbers[5],numbers[6]);
    madgwickRotations::Vector magnetometerData = Vector(numbers[7],numbers[8],numbers[9]);

    this->setValue(delay, accelerometerData, magnetometerData, gyroscopeData);
}