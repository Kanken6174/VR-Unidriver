#include "VRQuaternion.h"
#include <iostream>
#include <iostream>

void VRQuaternion::setValue(time_t delay, madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro)
{
    //value = transformator.update(delay, acc, mag, gyro);
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
    cout << data << endl;
    vector<string> delimiters = vector<string>();
    vector<string> splitData = vector<string>();

    delimiters = utilities::split(this->getFlag(), '|');    //on récupère les 9 flages du composant

    if (delimiters.size() != 9) //flags manquants ou en excès
        return;

    vector<double> numbers = vector<double>();

    for (string delimiter : delimiters) {
        string number =  utilities::getDelimitedValueFromRawString(data, delimiter);
        numbers.push_back(stod(number));
    }

    time_t delay = numbers[0];

    madgwickRotations::Vector gyroscopeData = Vector(numbers[1], numbers[2], numbers[3]);
    madgwickRotations::Vector accelerometerData = Vector(numbers[4],numbers[5],numbers[6]);
    madgwickRotations::Vector magnetometerData = Vector(numbers[7],numbers[8],numbers[9]);

    this->setValue(delay, accelerometerData, magnetometerData, gyroscopeData);
}