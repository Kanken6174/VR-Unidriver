/**
* @author Yorick Geoffre
* @brief this file holds the declaration of the euler to quaternion conversions. It does suffer from the gimble lock issue so it shouldn't be used in final prod
* @version 0.1
* @date 16/12/2021
*/

#include "MathOps.h"

vr::HmdQuaternion_t ToQuaternion(double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
{

    // Abbreviations for the various angular functions
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    vr::HmdQuaternion_t q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

vr::HmdVector3_t GetPositionMatrixFromRotationPositionMatrix(const vr::HmdMatrix34_t& inputMatrix) {
    vr::HmdVector3_t result{};

    result.v[0] = inputMatrix.m[0][3];
    result.v[1] = inputMatrix.m[1][3];
    result.v[2] = inputMatrix.m[2][3];

    return result;
}

vr::HmdMatrix33_t getRotationMatrixFromRotationPositionMatrix(const vr::HmdMatrix34_t& inputMatrix) {
    const vr::HmdMatrix33_t result = {
        {{inputMatrix.m[0][0], inputMatrix.m[0][1], inputMatrix.m[0][2]},
         {inputMatrix.m[1][0], inputMatrix.m[1][1], inputMatrix.m[1][2]},
         {inputMatrix.m[2][0], inputMatrix.m[2][1], inputMatrix.m[2][2]}} };

    return result;
}

vr::HmdQuaternion_t GetQuaternionFromMatrix(const vr::HmdMatrix33_t& inputMatrix) {
    vr::HmdQuaternion_t q{};

    q.w = sqrt(fmax(0, 1 + inputMatrix.m[0][0] + inputMatrix.m[1][1] + inputMatrix.m[2][2])) / 2;
    q.x = sqrt(fmax(0, 1 + inputMatrix.m[0][0] - inputMatrix.m[1][1] - inputMatrix.m[2][2])) / 2;
    q.y = sqrt(fmax(0, 1 - inputMatrix.m[0][0] + inputMatrix.m[1][1] - inputMatrix.m[2][2])) / 2;
    q.z = sqrt(fmax(0, 1 - inputMatrix.m[0][0] - inputMatrix.m[1][1] + inputMatrix.m[2][2])) / 2;

    q.x = copysign(q.x, inputMatrix.m[2][1] - inputMatrix.m[1][2]);
    q.y = copysign(q.y, inputMatrix.m[0][2] - inputMatrix.m[2][0]);
    q.z = copysign(q.z, inputMatrix.m[1][0] - inputMatrix.m[0][1]);

    return q;
}