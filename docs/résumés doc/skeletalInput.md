#étude de l'interface Skeletal input (entrée squelette) d'openvr

Cette interface fonctionne en faisant passer un flux d'informations type squelette à l'api IVRDriverInput (vue dans IVRDriverInput.md).

## création d'un squelette:
on utilise la fonction:

`EVRInputError vr::IVRDriverInput::CreateSkeletonComponent( PropertyContainerHandle_t ulContainer, const char *pchName, const char *pchSkeletonPath, const char *pchBasePosePath, EVRSkeletalTrackingLevel eSkeletalTrackingLevel, const VRBoneTransform_t *pGripLimitTransforms, uint32_t unGripLimitTransformCount, VRInputComponentHandle_t *pHandle )`
