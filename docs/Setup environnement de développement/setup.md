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