#Setup de l'IDE VS 2019 pour le développement openVR:

##1) installer vcpkg

	dans une invité de commandes élevé admin:

	cd <le dossier où vous voulez cloner vcpkg>
	git clone https://github.com/Microsoft/vcpkg.git
	cd <le dossier où vcpkg a été cloné>
	bootstrap-vcpkg.bat
	vcpkg.exe integrate installer
	
	mettez à jour votre variable d'environnement HOME pour inclure le dossier où le .exe de vcpkg est situé
	redémarrez tous vos IDE et lignes de commandes (voire pc)
	
	vous pouvez d"sormais utiliser vcpkg
	
##2) installer le paquet openVR

	démarrez une ligne de commande, élevée ou pas
	vcpkg install openvr
	vous pouvez ajouter le suffixe :x64-windows pour être sûr de la plateforme: vcpkg install openvr:x64-windows
	
	vous avez désormais les ressources de développement openVR dans le dossier `vcpkg\installed\x64-windows\`
	
##3) ajouter les ressources openVR au chemin d'ajout VS 2019

	ouvrez le projet VS
	project > nom_projet Properties
	C/C++ > all options > Look for options or switches
	recherchez le terme "include"
	vous devriez trouver le champ "Additionnal Include Directories"
	dans ce champ, ajoutez les chemins ABSOLUS vers les ressources openVR:
	perso : `Y:\vcpkg\installed\; Y:\vcpkg\installed\x64-windows\include\`
	les chemins sont séparés pas un ;
	les fichiers .h qu'il nous faudra inclure sont dans le \include\ (openvr.h), d'où l'inclusion
	
##4)Setup des évènements de post-build dans VS 2019

- Ouvrez steam
- Localisez le chemin des fichiers locaux de SteamVR
- copiez ce chemin quelque part

- Dans VS:
- Aller dans Project -> <nom_du_projet> properties (en bas)
- Aller dans Build-Events -> Post-Build Event
- dans les barres en haut mettre:
	- Configuration -> Une config de votre choix (pas toutes ce serait chiant d'ouvrir steamVR à chaque build...)
	- Platform -> All Platforms (windows mais bon, c'est pas important)
- Dans la cellule Command Line mettre:
```
F:\steam\steamapps\common\SteamVR\bin\win64\vrpathreg.exe removedriver "F:\steam\steamapps\common\SteamVR\drivers\$(TargetName)"
rmdir "F:\steam\steamapps\common\SteamVR\drivers\$(TargetName)" /S /Q
xcopy Y:\DoMoCap\EXAMPLE1\sample F:\steam\steamapps\common\SteamVR\drivers\sample\ /E /H /C /I
md "F:\steam\steamapps\common\SteamVR\drivers\$(TargetName)\bin\win64"
copy /Y "$(TargetDir)$(TargetName).dll"  "F:\steam\steamapps\common\SteamVR\drivers\$(TargetName)\bin\win64\driver_$(TargetName).dll"
F:\steam\steamapps\common\SteamVR\bin\win64\vrpathreg.exe adddriver "F:\steam\steamapps\common\SteamVR\drivers\$(TargetName)"
F:\steam\steamapps\common\SteamVR\bin\win64\vrmonitor.exe
F:\steam\steamapps\common\SteamVR\bin\win64\vrserver.exe
```
[C'est juste une commande batch windows]
Cette commande nettoie les vieux fichiers et copie les nouveaux. Tous les chemins sont absolus car il n'est pas simple d'utiliser
des variables d'utilisateur dans les events post-build de VS (il faudrait les définir dans le fichier XML de le solution...)

Il faudra changer les chemins à ce qu'ils sont sur votre disque personnel.

Normalement build avec la configuration que vous avez choisie devrait automatiquement remplacer les fichiers du driver et mettre à
jour le VRPATHREG, puis lancer SteamVR.
Cela permet une débogage **rapide** via les logs SteamVR, le terminal de développeur steamVR, ou l'appli steamVR directement! (si le driver est fonctionnel)