#include "VRQuaternion.h"

void VRQuaternion::setValue(madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro)
{
    //TODO @eliott
}

string VRQuaternion::to_string()
{
    string toReturn = "";
    toReturn += std::to_string(value.getW()) + "_" + std::to_string(value.getX()) + "_" + std::to_string(value.getY()) + "_" + std::to_string(value.getZ());
    return toReturn;
}

void VRQuaternion::receiveData(string data)
{
    vector<string> splitData = vector<string>();
    splitData = utilities::split(data, '/');
    if (splitData.size() != 9)
        throw new runtime_error(std::string("size mismatch, size was ") += splitData.size());

    vector<double> numbers = vector<double>();

    for (string number : splitData) {
        numbers.push_back(stod(number));
    }

    madgwickRotations::Vector accelerometerData = Vector(numbers[0],numbers[1],numbers[2]);
    madgwickRotations::Vector gyroscopeData = Vector(numbers[4],numbers[5],numbers[6]);
    madgwickRotations::Vector magnetometerData = Vector(numbers[7],numbers[8],numbers[9]);

    this->setValue(accelerometerData, magnetometerData, gyroscopeData);
}