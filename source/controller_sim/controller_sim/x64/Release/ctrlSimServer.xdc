<?xml version="1.0"?><doc>
<members>
<member name="M:DriverLog(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,BTEllipsis)" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\VRComponent.h" line="1">
@author Yorick Geoffre
@brief defines a single component, like a joystick or a button on a device
@version 0.3 - added dataTemplate based constructors
@date 30/11/2021

@author Valve corporation
@brief this file holds the declaration of the driver logging related functions
@version 0.1
@date 16/12/2021

</member>
<member name="M:acos(System.Single)" decl="false" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\dataObjects.h" line="1">
@author Yorick Geoffre
@brief this file holds the declaration of the dataObjects, which contain the info required to create a device driver and some components
@version 0.1
@date 16/12/2021

</member>
<member name="T:Quaternion" decl="false" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\controller_sim.h" line="25">
maths.h functions and definitions
used mainly for mathematic angle conversions

</member>
<member name="M:DoMoDriver.RunFrame" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\controller_sim.h" line="92">
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu

</member>
<member name="M:Controller_simDriverServer.Init(vr.IVRDriverContext*)" decl="false" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="14">
reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
serveur.

</member>
<member name="M:HmdDriverFactory(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32*)" decl="false" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="169">
 La fonction qui sera exportée vers OpenVR, il s'agit de
 notre point d'entrée! (void main() en gros)

 Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR

</member>
</members>
</doc>