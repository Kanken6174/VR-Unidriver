#include "VRQuaternion.h"
#include <iostream>

void VRQuaternion::setValue(time_t delay, madgwickRotations::Vector acc, madgwickRotations::Vector mag, madgwickRotations::Vector gyro)
{
        value = transformator.update(delay, gyro, acc, mag);
    /*
    // Abbreviations for the various angular functions
    double cy = cos((acc.getX() / 20000) * 0.5);
    double sy = sin((acc.getX()/20000) * 0.5);
    double cp = cos((acc.getY()/20000) * 0.5);
    double sp = sin((acc.getY()/20000) * 0.5);
    double cr = cos((acc.getZ()/20000) * 0.5);
    double sr = sin((acc.getZ()/20000) * 0.5);

    Quaternion q = Quaternion(sr * cp * cy - cr * sp * sy,
                              cr * sp * cy + sr * cp * sy, 
                              cr * cp * sy - sr * sp * cy, 
                              cr * cp * cy + sr * sp * sy);
    value = q;
    */
    
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
    vector<string> splitData = vector<string>();
    vector<double> numbers = vector<double>();

    splitData = utilities::split(data, '|');

    for (string data : splitData) {
        double number = utilities::stringToDouble(data);
        if (number == ERROR_STOD || number == ERROR_MAJOR) {
            cout << "STOD return error";
            return;
        }
        numbers.push_back(number);
    }

    if (numbers.size() == 9) {
        time_t delay = numbers[0] * 1000;

        madgwickRotations::Vector accelerometerData = Vector(numbers[1], numbers[2], numbers[3]);
        madgwickRotations::Vector gyroscopeData = Vector(numbers[4], numbers[5], numbers[6]);
        madgwickRotations::Vector magnetometerData = Vector(numbers[7], numbers[8], numbers[9]);

        
    }
    else if (numbers.size() == 5) {
       Quaternion val = Quaternion(numbers[1], numbers[2], numbers[3], numbers[4]);
       value = val;
    }
    
}