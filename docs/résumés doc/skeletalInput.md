#étude de l'interface Skeletal input (entrée squelette) d'openvr

Cette interface fonctionne en faisant passer un flux d'informations type squelette à l'api IVRDriverInput (vue dans IVRDriverInput.md).

## création d'un squelette:
on utilise la fonction:

`EVRInputError vr::IVRDriverInput::CreateSkeletonComponent( PropertyContainerHandle_t ulContainer, const char *pchName, const char *pchSkeletonPath, const char *pchBasePosePath, EVRSkeletalTrackingLevel eSkeletalTrackingLevel, const VRBoneTransform_t *pGripLimitTransforms, uint32_t unGripLimitTransformCount, VRInputComponentHandle_t *pHandle )`

arguments: 	`ulContainer` -> la propriété handle de l'appareil parent de ce composant (ce sera celle de la manette à laquelle le bouton est raccroché par exemple)
			`pchName` -> le NOM du composant, il doit commencer par la forme "/input//"
			`pchSkeletonPath` -> le chemin du squelette à utiliser (seuls mains droite et main gauche existent ici: `/skeleton/hand/right` et `/input/skeleton/left`)
			`pchBasePosePath` -> chemin vers le controleur que le squelette va utiliser comme position de référence (le shadowing peut se faire ici)
			`eSkeletalTrackingLevel` -> permet aux applications VR de comprendre les capactiés du tracker, voir https://github.com/ValveSoftware/openvr/wiki/SteamVR-Skeletal-Input#evrskeletaltrackinglevel
			`pGripLimitTransforms` -> un tableau de `vr::VRBoneTransform_t` qui est sensé contenir des "espaces" de limite de mouvement, le nombre d'éléments du tableau
										est égal au nombre d'éléments du squelette (os) [à revoir]
			`unGripLimitTransformCount` -> le nombre d'éléments dans le tableau `pGripLimitTransforms`
			`pHandle` -> pointeur vers le handle de destination pour le nouveau composant (ici le squelette, qui est un composant d'entrée squelette [~même statut qu'un bouton ou jostick])
			


## mise à jour d'un squelette:
on utilise la fonction:
	
`EVRInputError vr::IVRDriverInput::UpdateSkeletonComponent( VRInputComponentHandle_t ulComponent, EVRSkeletalMotionRange eMotionRange, const VRBoneTransform_t *pTransforms, uint32_t unTransformCount )

arguments:	