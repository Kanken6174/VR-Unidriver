<?xml version="1.0"?><doc>
<members>
<member name="T:Quaternion" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\controller_sim.h" line="22">
maths.h functions and definitions
used mainly for mathematic angle conversions

</member>
<member name="M:DoMoDriver.RunFrame" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\controller_sim.h" line="89">
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu

</member>
<member name="M:Controller_simDriverServer.Init(vr.IVRDriverContext*)" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="14">
reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
serveur.

</member>
<member name="M:HmdDriverFactory(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32*)" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="83">
 La fonction qui sera exportée vers OpenVR, il s'agit de
 notre point d'entrée! (void main() en gros)

 Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR

</member>
</members>
</doc>