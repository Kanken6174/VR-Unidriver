#étude de l'interface Skeletal input (entrée squelette) d'openvr
https://github.com/ValveSoftware/openvr/wiki/Creating-a-Skeletal-Input-Driver

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

`EVRInputError vr::IVRDriverInput::UpdateSkeletonComponent( VRInputComponentHandle_t ulComponent, EVRSkeletalMotionRange eMotionRange, const VRBoneTransform_t *pTransforms, uint32_t unTransformCount )`

arguments:	`ulComponent` -> handle du composant squelette à mettre à jour (`pHandle` de la fonction précédente)
			`eMotionRange` -> définit un comportement du composant squelette, si `VRSkeletalMotionRange_WithController`, on prend en compte la présence de la manette dans la main,
								cela signifie qu'il devient impossible que la main se ferme complètement. `VRSkeletalMotionRange_WithoutController` modifie les valeurs et autorise
								une main entièrement fermée.
			`pTransforms` -> un tableau de "transforms" explication ICI:
												```cpp
												struct VRBoneTransform_t	//un "transform"
												{
													HmdVector4_t position;
													HmdQuaternionf_t orientation;
												};


												struct HmdVector4_t	//un vecteur dans l'espace quaternionique à 4 valeurs donne la position
												{
													float v[4];
												};

												struct HmdQuaternionf_t
												{
													float w, x, y, z; //un quaternion a 4 valeurs donne la rotation
												};
												```
			`unTransformCount` -> le nombre de transforms dans `ptransforms`, il doit être égal au nb d'os de la main choisie, sinon renvoie une erreur.

##notes:

les `pchName` valides pour un composant de type squelette sont:
		```cpp
		/input/skeleton/right
		/input/skeleton/left
		```
