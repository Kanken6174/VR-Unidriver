#include "DoMoDriver.h"

/*Cette fonction gère la position (rotation quaternionique et position par vecteur) de l'objet,
* qrotation est responsable de l'angle et Vecposition[3] de la position.
*/
DriverPose_t DoMoDriver::GetPoseProvided() {
	DriverPose_t pose = { 0 };
	pose.poseIsValid = true;
	pose.result = TrackingResult_Running_OK;
	pose.deviceIsConnected = true;

	pose.vecPosition[2] = localData.positionsOffsets[2];
	pose.vecPosition[1] = localData.positionsOffsets[1];
	pose.vecPosition[0] = -localData.positionsOffsets[0];

	pose.qWorldFromDriverRotation = ToQuaternion(localData.qWorldFromDriverRotation[0], localData.qWorldFromDriverRotation[1], localData.qWorldFromDriverRotation[2]);
	pose.qDriverFromHeadRotation = ToQuaternion(localData.qDriverFromHeadRotation[0], localData.qDriverFromHeadRotation[1], localData.qDriverFromHeadRotation[2]);

	pose.qRotation = *DeviceRotation;

	pose.vecDriverFromHeadTranslation[2] = localData.vecDriverFromHeadTranslation[2];
	pose.vecDriverFromHeadTranslation[1] = localData.vecDriverFromHeadTranslation[1];
	pose.vecDriverFromHeadTranslation[0] = localData.vecDriverFromHeadTranslation[0];

	pose.vecWorldFromDriverTranslation[0] = localData.vecWorldFromDriverTranslation[0];
	pose.vecWorldFromDriverTranslation[1] = localData.vecWorldFromDriverTranslation[1];
	pose.vecWorldFromDriverTranslation[2] = localData.vecWorldFromDriverTranslation[2];

	//shadowing de position et de rotation (vont réécrire les valeurs)
	if (localData.handleToShadow >= 0) {
		vr::TrackedDevicePose_t dt = utilities::getPoseFromID(localData.handleToShadow);
		if (!dt.bPoseIsValid) {
			pose.poseIsValid = false;
			return pose;
		}
		HmdMatrix34_t tp = dt.mDeviceToAbsoluteTracking;

		if (localData.shadowPosition) {
			HmdVector3_t posVect = GetPositionMatrixFromRotationPositionMatrix(tp);
			pose.vecPosition[0] = posVect.v[0] + localData.positionsOffsets[0];
			pose.vecPosition[1] = posVect.v[1] + localData.positionsOffsets[1];
			pose.vecPosition[2] = -(posVect.v[2] + localData.positionsOffsets[2]);
		}

		if (localData.shadowRotation) {
			pose.qRotation = GetQuaternionFromMatrix(getRotationMatrixFromRotationPositionMatrix(tp));
		}
	}

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