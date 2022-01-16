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
<member name="D:size_t" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="1">
@author Yorick Geoffre
@brief this files contains the declaration of the PipeServer type which is used for named pipe communication operations.
@version 0.1
@date 16/01/2022

</member>
<member name="M:PipeServer.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="32">
<summary>
Le constructeur du PipeServer
</summary>
<param name="pipeName">Le nom système du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
</member>
<member name="M:PipeServer.ReadPipe" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="37">
<summary>
Permet de lire les données qui ont été écrites dans le tunnel nommé local (hPipe)
</summary>
<returns>Le texte lu depuis le tunnel nommé</returns>
</member>
<member name="M:PipeServer.WriteToPipe(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="42">
<summary>
Permet d'écrire vers un tunnel nommé spécifié
</summary>
<param name="message"> Le message à écrire dans le tunnel nommé spécifié</param>
<param name="targetPipe"> Le nom système du tunnel nommé vers lequel écrire</param>
<returns>Le succès ou l'échec de l'écriture</returns>
</member>
<member name="M:PipeServer.isConnected" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="49">
<returns>condition si le tunnel nommé local est fonctionnel (connecté) ou non</returns>
</member>
<member name="T:dispatchers.DataDispatcher" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="18">
<summary>
La classe DataDispatcher est un wrapper autour de la classe IPCServer et permet d'intéragir avec les tunnels nommés.
</summary>
</member>
<member name="F:dispatchers.DataDispatcher.splitData" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="24">
Un vecteur contenant les données séparées de la trame d'arrivée, produite en interne en appellant <code>Split()</code> sur la trame brute.
</member>
<member name="F:dispatchers.DataDispatcher.pipeName" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="26">
Le nom du tunnel nommé local
</member>
<member name="F:dispatchers.DataDispatcher.targetName" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="28">
Le nom du tunnel nommé distant (de la moulinette dans ce cas)
</member>
<member name="F:dispatchers.DataDispatcher.localServer" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="30">
Le pointeur vers le PipeServer que cette class enrobe
</member>
<member name="M:dispatchers.DataDispatcher.#ctor" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="34">
<summary>
Le constructeur de la classe DataDispatcher, il créé également le tunnel nommé interne
</summary>
</member>
<member name="M:dispatchers.DataDispatcher.Dispose" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="38">
<summary>
Le destructeur de la classe DataDispatcher, il déconnecte également le tunnel nommé interne
</summary>
</member>
<member name="M:dispatchers.DataDispatcher.feedPipeDataToDrivers(std.vector&lt;DoMoDriver**,std.allocator&lt;DoMoDriver**&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="42">
<summary>
permet de faire passer les données reçues par le tunnel nommé aux drivers correspondants (ordre naturel)
</summary>
<param name="drivers"> une collection de drivers (vecteur)</param>
</member>
</members>
</doc>