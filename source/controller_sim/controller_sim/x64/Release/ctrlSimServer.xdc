<?xml version="1.0"?><doc>
<members>
<member name="M:ATL.CRegKey.#ctor(ATL.CAtlTransactionManager*)" decl="true" source="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\atlmfc\include\atlbase.h" line="1316">
<summary>
CRegKey constructor</summary>
<param name="pTM">Pointer to CAtlTransactionManager object</param>
</member>
<member name="F:ATL.CRegKey.m_pTM" decl="false" source="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29910\atlmfc\include\atlbase.h" line="1332">
<summary>
Pointer to CAtlTransactionManager object</summary>
</member>
<member name="M:DriverLog(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,BTEllipsis)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\entry_point.h" line="1">
@author Valve corporation
@brief defines the HMD_DLL_EXPORT/IMPORT types which serve as entry points for the DLL
@version 0.1
@date 16/12/2021

</member>
<member name="T:Quaternion" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="3">
maths.h functions and definitions
used mainly for mathematic angle conversions

</member>
<member name="M:DoMoDriver.RunFrameStub" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="78">
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu

</member>
<member name="M:DoMoDriver.UpdateInternalValuesFromPipedData(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="84">
Cette fonction gère la mise à jour de valeurs par celles reçues du tunnel nommé

</member>
<member name="M:Controller_simDriverServer.Init(vr.IVRDriverContext*)" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="14">
reference: https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview
Il s'agit du serveur qui va contrôler les différents appareils, car il peut y en avoir plusieurs par
serveur.

</member>
<member name="M:HmdDriverFactory(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32*)" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\ctrlSimServer.cpp" line="82">
 La fonction qui sera exportée vers OpenVR, il s'agit de
 notre point d'entrée! (void main() en gros)

 Elle va récupérer des pointeurs vers des classes prédéfinies pour les charger dans SVR

</member>
</members>
</doc>