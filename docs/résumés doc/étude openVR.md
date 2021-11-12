#Etude de l'API OpenVR:

SteamVR Input: la partie qui nous intéresse aka, comment transmettre des données à steamVR via un driver OpenVR, doc trouvée ici: https://github.com/ValveSoftware/openvr/wiki/Driver-Documentation

Les étapes pour un driver OpenVR selon la doc:
- rassembler tous les fichiers pour le driver dans un dossier (exemple: /monDriver)
- ajouter un nouveau dll à /monDriver/bin/win64/friver_monDriver.dll
- implémenter la fonction factory à driver (patron de conception usine, on l'a déjà vu) dans ce dll, voir > https://github.com/ValveSoftware/openvr/wiki/Driver-Factory-Function
- implémenter vr::IServerTrackedDeviceProvider de façon à retourner des implémentations de vr::ITrackedDeviceServerDriver pour chaque appareil de tracking
  \-> voir https://github.com/ValveSoftware/openvr/wiki/IServerTrackedDeviceProvider_Overview et https://github.com/ValveSoftware/openvr/wiki/vr::ITrackedDeviceServerDriver-Overview
- ajouter un manifeste de driver à /monDriver (déclare ce que chaque appareil tracké est, comme son nom, ses conditions d'activation, etc)
  \-> voir https://github.com/ValveSoftware/openvr/wiki/DriverManifest
- lancer la commande vrpathreg adddriver "/monDriver" pour ajouter le driver aux drivers steamVR

|| MAIS ça, c'est QUE pour un driver minimaliste, pour un driver avec des boutons ou joysticks, il faudra utiliser une autre interface! ||

Cette interface est vr::IVRDriverInput vue ici -> https://github.com/ValveSoftware/openvr/wiki/IVRDriverInput-Overview

L'interface pour l'entrée type squelette est encore à part, elle est décrite ici -> https://github.com/ValveSoftware/openvr/wiki/Creating-a-Skeletal-Input-Driver
