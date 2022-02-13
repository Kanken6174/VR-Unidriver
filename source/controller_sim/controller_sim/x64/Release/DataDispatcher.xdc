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
<member name="M:utilities.split(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,System.Boolean)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\utilities.h" line="14">
<summary>
permet de séparer un string selon un délilimteur précisé
</summary>
<param name="input"> le string à séparer</param>
<param name="splitter"> le caractère de séparation</param>
<param name="remove"> (optionnel à false), si on enlève le caractère de séparation ou pas</param>
<returns>un vecteur contenant les différentes parties du string d'origine</returns>
</member>
<member name="M:utilities.getFirstAndRemoveFromVector(std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\utilities.h" line="22">
<summary>
Va prendre le premier string d'un vecteur de string, le retirer de ce vecteur, et le retourner
</summary>
<param name="source">le vecteur de strings à traiter</param>
<returns>le premier string du vecteur</returns>
</member>
<member name="T:VRcomponent" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\VRComponent.h" line="19">
Redéfinitions de noms de méthodes de SteamVR (pour raccourcir)
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
<member name="M:DoMoDriver.#ctor(DriverDataTemplate)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="42">
Constructeurs et destructeurs
<summary>
Le constructeur d'une classe DoMoDriver (version moderne, désactive le mode obsolète si il est appellé)
</summary>
<param name="driverDataTemplate">La data Template de ce driver, qui décrit l'appareil que ce driver représente</param>
</member>
<member name="M:DoMoDriver.Dispose" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="56">
<summary>
Le destructeur de ce driver
</summary>
</member>
<member name="M:DoMoDriver.ModernActivation(System.UInt32)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="69">
Fonctions d'activation du driver SteamVR
<summary>
Cette fonction va activer et enregistrer le driver auprès de SteamVR, à partir des DataTemplates enregistrées en interne
</summary>
<param name="unObjectId"></param>
<returns></returns>
</member>
<member name="M:DoMoDriver.Activate(System.UInt32)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="82">
fonctions requises par l'interface ITrackedDeviceServerDriver, commes données dans le sample, elles ne sont pas utilisées
</member>
<member name="M:DoMoDriver.GetKeypresses" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="90">
Ces fonctions gèrent la position (rotation quaternionique et position par vecteur) de l'objet,qrotation est responsable de l'angle et Vecposition[3] de la position.
<summary>
récupère les touches de clavier, utilisé par la versions stub de GetPose uniquement
</summary>
</member>
<member name="M:DoMoDriver.GetPoseStubmode" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="95">
<summary>
appelle GetKeypresses() et récupère les informations d'angle d'euler et de position puis en fait une pose.
</summary>
<returns> Une pose Steamvr DriverPose_t</returns>
</member>
<member name="M:DoMoDriver.GetPoseProvided" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="100">
<summary>
recupère les informations locales de quaternion et de position (obtenus via le tunnel nommé normalement) et en fait une pose
</summary>
<returns> Une pose Steamvr DriverPose_t</returns>
</member>
<member name="M:DoMoDriver.GetPose" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="106">
<summary>
version forcée par SteamVR et pas utilisée (décrite dans interfaceRequires.cpp), ne devrait pas être utilisée
</summary>
<returns> Une pose Steamvr DriverPose_t</returns>
</member>
<member name="M:DoMoDriver.RunFrameStub" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="112">
Les fonctions ici gèrent la mise à jour des données à chaque frame-----------------------------------------------------------------
<summary>
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu (version stub)
</summary>
</member>
<member name="M:DoMoDriver.RunFrameRaw(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="117">
<summary>
Cette fonction gère la mise à jour des valeurs d'entrée à chaque frame du jeu
</summary>
<param name="raw">Un string contenant toutes les valeurs relatives à cet appareil (trame de driver standard)</param>
</member>
<member name="M:DoMoDriver.GetSerialNumber" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="122">
fonctions requises par l'interface de SteamVR (peut être non-utilisé)---------------------------------------------------------------
<summary>
Requis par SteamVR, renvoie l'identifiant unique de l'appareil (décrit dans InterfaceRequires.h)
</summary>
<returns>L'identifiant de l'appareil</returns>
</member>
<member name="M:DoMoDriver.UpdateInternalValuesFromPipedData(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DoMoDriver.h" line="128">
fonction de mise à jour des valeurs internes
<summary>
Cette fonction gère la mise à jour de valeurs par celles reçues du tunnel nommé (appellée par RunFrameRaw())
</summary>
<param name="pipeData">la trame contenant toutes les valeurs relatives à cet appareil</param>
<returns>les valeurs de chaque composant, avec les valeurs relatives à l'appareil (latence, orientation) retirées car déjà appliquées</returns>
</member>
<member name="D:size_t" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="1">
@author Yorick Geoffre
@brief this files contains the declaration of the PipeServer type which is used for named pipe communication operations.
@version 0.1
@date 16/01/2022

</member>
<member name="M:PipeServer.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="34">
<summary>
Le constructeur du PipeServer
</summary>
<param name="pipeName">Le nom système du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
</member>
<member name="M:PipeServer.ReadPipe" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="39">
<summary>
Permet de lire les données qui ont été écrites dans le tunnel nommé local (hPipe)
</summary>
<returns>Le texte lu depuis le tunnel nommé</returns>
</member>
<member name="M:PipeServer.WriteToPipe(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="44">
<summary>
Permet d'écrire vers un tunnel nommé spécifié
</summary>
<param name="message"> Le message à écrire dans le tunnel nommé spécifié</param>
<param name="targetPipe"> Le nom système du tunnel nommé vers lequel écrire</param>
<returns>Le succès ou l'échec de l'écriture</returns>
</member>
<member name="M:PipeServer.isConnected" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="51">
<returns>condition si le tunnel nommé local est fonctionnel (connecté) ou non</returns>
</member>
<member name="T:DataDispatcher" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="14">
<summary>
La classe DataDispatcher est un wrapper autour de la classe IPCServer et permet d'intéragir avec les tunnels nommés.
</summary>
</member>
<member name="F:DataDispatcher.splitData" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="21">
Un vecteur contenant les données séparées de la trame d'arrivée, produite en interne en appellant <code>Split()</code> sur la trame brute.
</member>
<member name="F:DataDispatcher.pipeName" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="23">
Le nom du tunnel nommé local
</member>
<member name="F:DataDispatcher.targetName" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="25">
Le nom du tunnel nommé distant (de la moulinette dans ce cas)
</member>
<member name="F:DataDispatcher.localServer" decl="false" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="27">
Le pointeur vers le PipeServer que cette class enrobe
</member>
<member name="M:DataDispatcher.#ctor" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="35">
<summary>
Le constructeur de la classe DataDispatcher, il créé également le tunnel nommé interne
</summary>
</member>
<member name="M:DataDispatcher.Dispose" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="39">
<summary>
Le destructeur de la classe DataDispatcher, il déconnecte également le tunnel nommé interne
</summary>
</member>
<member name="M:DataDispatcher.feedPipeDataToDrivers(std.vector&lt;DoMoDriver**,std.allocator&lt;DoMoDriver**&gt;&gt;*)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\DataDispatcher.h" line="43">
<summary>
permet de faire passer les données reçues par le tunnel nommé aux drivers correspondants (ordre naturel)
</summary>
<param name="drivers"> une collection de drivers (vecteur)</param>
</member>
</members>
</doc>