<?xml version="1.0"?><doc>
<members>
<member name="M:PipeServer.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="34">
<summary>
Le constructeur du PipeServer
</summary>
<param name="pipeName">Le nom système du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
</member>
<member name="M:PipeServer.ReadPipe" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="39">
<summary>
Permet de lire les données qui ont été écrites dans le tunnel nommé local (hPipe)
</summary>
<returns>Le texte lu depuis le tunnel nommé</returns>
</member>
<member name="M:PipeServer.WriteToPipe(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="44">
<summary>
Permet d'écrire vers un tunnel nommé spécifié
</summary>
<param name="message"> Le message à écrire dans le tunnel nommé spécifié</param>
<param name="targetPipe"> Le nom système du tunnel nommé vers lequel écrire</param>
<returns>Le succès ou l'échec de l'écriture</returns>
</member>
<member name="M:PipeServer.isConnected" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="51">
<returns>condition si le tunnel nommé local est fonctionnel (connecté) ou non</returns>
</member>
<member name="M:ATL.CRegKey.#ctor(ATL.CAtlTransactionManager*)" decl="true" source="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\atlmfc\include\atlbase.h" line="1316">
<summary>
CRegKey constructor</summary>
<param name="pTM">Pointer to CAtlTransactionManager object</param>
</member>
<member name="F:ATL.CRegKey.m_pTM" decl="false" source="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\atlmfc\include\atlbase.h" line="1332">
<summary>
Pointer to CAtlTransactionManager object</summary>
</member>
<member name="M:DriverLog(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,BTEllipsis)" decl="true" source="C:\Users\ASUS\Documents\2A\domocap\source\controller_sim\controller_sim\entry_point.h" line="1">
@author Valve corporation
@brief defines the HMD_DLL_EXPORT/IMPORT types which serve as entry points for the DLL
@version 0.1
@date 16/12/2021

</member>
</members>
</doc>