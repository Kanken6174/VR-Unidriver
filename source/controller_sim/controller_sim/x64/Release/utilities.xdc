<?xml version="1.0"?><doc>
<members>
<member name="M:PipeServer.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="33">
<summary>
Le constructeur du PipeServer
</summary>
<param name="pipeName">Le nom système du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
</member>
<member name="M:PipeServer.ReadPipe" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="38">
<summary>
Permet de lire les données qui ont été écrites dans le tunnel nommé local (hPipe)
</summary>
<returns>Le texte lu depuis le tunnel nommé</returns>
</member>
<member name="M:PipeServer.WriteToPipe(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="43">
<summary>
Permet d'écrire vers un tunnel nommé spécifié
</summary>
<param name="message"> Le message à écrire dans le tunnel nommé spécifié</param>
<param name="targetPipe"> Le nom système du tunnel nommé vers lequel écrire</param>
<returns>Le succès ou l'échec de l'écriture</returns>
</member>
<member name="M:PipeServer.isConnected" decl="true" source="Y:\domocap\source\controller_sim\controller_sim\IPCIPE\IPCServer.h" line="50">
<returns>condition si le tunnel nommé local est fonctionnel (connecté) ou non</returns>
</member>
</members>
</doc>