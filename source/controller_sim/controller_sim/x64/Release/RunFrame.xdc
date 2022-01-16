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
<member name="M:ToQuaternion(System.Double,System.Double,System.Double)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\MathOps.h" line="1">
@author Yorick Geoffre
@brief this file holds the declaration of maths-related functions
@version 0.1
@date 16/12/2021

<summary>
Une fonction qui va convertir trois angles d'euler en un quaternion SteamVR
</summary>
<param name="yaw">Le lacet en degrés</param>
<param name="pitch">Le tangage en degrés</param>
<param name="roll">Le roulis en degrés</param>
<returns>HmdQuaternion_t un quaternion SteamVR</returns>
</member>
<member name="T:DoMoDriver" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="13">
<summary>
Cette classe représente un appareil tracké (implémente ITrackedDeviceServerDriver), il a une position et une rotation, et peut
</summary>
</member>
<member name="M:DoMoDriver.#ctor(DriverDataTemplate)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="41">
<summary>
Le constructeur d'une classe DoMoDriver (version moderne, désactive le mode obsolète si il est appellé)
</summary>
<param name="driverDataTemplate">La data Template de ce driver, qui décrit l'appareil que ce driver représente</param>
</member>
<member name="M:DoMoDriver.Dispose" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="54">
<summary>
Le destructeur de ce driver
</summary>
</member>
<member name="M:DoMoDriver.RunFrameStub" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="88">
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu

</member>
<member name="M:DoMoDriver.UpdateInternalValuesFromPipedData(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="94">
Cette fonction gère la mise à jour de valeurs par celles reçues du tunnel nommé

</member>
<member name="M:DoMoDriver.RunFrameStub" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\RunFrame.cpp" line="3">
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu

</member>
</members>
</doc>