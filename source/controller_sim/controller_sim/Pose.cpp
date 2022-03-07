#include "DoMoDriver.h"

/*Cette fonction gère la position (rotation quaternionique et position par vecteur) de l'objet,
* qrotation est responsable de l'angle et Vecposition[3] de la position.
*/
DriverPose_t DoMoDriver::GetPoseProvided() {
	DriverPose_t pose = { 0 };
	pose.poseIsValid = true;
	pose.result = TrackingResult_Running_OK;
	pose.deviceIsConnected = true;

	pose.qWorldFromDriverRotation = ToQuaternion(0, 0, 0);
	pose.qDriverFromHeadRotation = ToQuaternion(0, 0, 0);
	pose.vecDriverFromHeadTranslation[2] = 0;	//on met la manette juste devant la caméra par défaut (la caméra est en -1, car l'axe X est inversé)
	pose.vecDriverFromHeadTranslation[1] = 0;
	pose.vecDriverFromHeadTranslation[0] = 0;
	pose.qRotation = *DeviceRotation;
	pose.vecPosition[2] = 0;
	pose.vecPosition[1] = 0;
	pose.vecPosition[0] = 0;

	return pose;
}

//----------------------------------------------------Modes stub---------------------------------------------------

DriverPose_t DoMoDriver::GetPoseStubmode()
{
	GetKeypresses();	//on le laisse statique dans l'espace pour l'instant, rotation seulement
	DriverPose_t pose = { 0 };
	pose.poseIsValid = true;
	pose.result = TrackingResult_Running_OK;
	pose.deviceIsConnected = true;

	pose.qWorldFromDriverRotation = ToQuaternion(0, 0, 0);
	pose.qDriverFromHeadRotation = ToQuaternion(0, 0, 0);
	pose.vecDriverFromHeadTranslation[2] = -0.5;	//on met la manette juste devant la caméra par défaut (la caméra est en -1, car l'axe X est inversé)
	pose.vecDriverFromHeadTranslation[1] = -0.25;
	pose.vecDriverFromHeadTranslation[0] = 0.25;

	//pose.vecDriverFromHeadTranslation[2] = -this->PosOffsets[2];	//on met la manette juste devant la caméra par défaut (la caméra est en -1, car l'axe X est inversé)
	//pose.vecDriverFromHeadTranslation[1] = this->PosOffsets[1];
	//pose.vecDriverFromHeadTranslation[0] = this->PosOffsets[0];

	pose.qRotation = ToQuaternion(0, yaw, pitch);
	pose.vecPosition[2] = X;
	pose.vecPosition[0] = Y;
	return pose;
}

void DoMoDriver::GetKeypresses() {
	if ((0x8000 & GetAsyncKeyState(VK_NUMPAD1)) != 0) {
			yaw += 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(VK_NUMPAD5)) != 0) {
			pitch += 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(VK_NUMPAD3)) != 0) {
			yaw -= 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(VK_NUMPAD2)) != 0) {
			pitch -= 0.01;
	}
	/*if ((0x8000 & GetAsyncKeyState(70)) != 0) {	//F

		X -= 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(86)) != 0) {	//B
		X += 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(67)) != 0) { //C
		Y -= 0.01;
	}
	if ((0x8000 & GetAsyncKeyState(66)) != 0) {	//V
		Y += 0.01;
	}*/
}