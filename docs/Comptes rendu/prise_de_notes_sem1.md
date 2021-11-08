# Lundi 8/11/2021

## Organisation

* 4h tous les lundis, on fait la pause en même temps.
* On peut commencer plus tôt pour finir plus tôt.

* 14 semaines officielles + 2 soutenances.
* Soutenance de Janvier (SJ) : 5m par personne + 45m de questions. 
    * C'est court 5 minutes.
    * On peut répéter (et prof est membre du jury)
    * Date : ??? (en même temps que les exams)
* Démo en décembre, début des répèt courant Janvier
* Soutenance finale : fin mars/début avril
* Rapport à faire aussi
    * On commence à faire des rapports après la SJ.

* On devrait bosser sous GitLab
    * Peut être migré sur GitHub, mais on ne verra que la fin
    * Choisir dans la matinée

On a choisi GitHub.

## Le sujet : DoMoCap

### Objectifs de fin de projet 
* Faciliter la création d'un périphérique d'entrée de VR utilisable avec SteamVR
* Avoir un exemple avec un gant avec des entrées avec des valeurs discrètes ou continues
* Combiner avec d'autres périphériques existants
* Démo Unity
* Upscale plus tard selon le temps

### Démo en janvier
* Gant fonctionnel avec de la VR => gère les modules analogiques et discrets
* Re map possible
* Un périphérique, pas un jeu

**Question à anticiper** : qu'est-ce qu'il faut faire pour refaire avec un autre périphérique?

* Outil universel qui à partir d'un capteur, en reçoit les données brutes, les map et nous permet de les utiliser avec un jeu

### Parties du projet

#### La base
* Mapping pour un gant déjà existant
* Flux SteamVR
* Vérification console et SVR

*TOUT DÉPEND DE ÇA*

Technos à maîtriser :
- SteamVR
- Flux
- Vérificateur SVR
- Trame brute -> Trame SVR
- Port série

#### Démo simple
* Démo Unity de merde avec des assets un peu pourris et une logique

#### Skeleton
* Fusion en squelette
* Nouvelle démo

#### Outil de configuration simple

#### GUI pour l'outil de personnalisation

#### Nouveaux pérphériques

## Random infos cool
- Vérif SVR existe déjà
- Il faut savoir ce qui a existe déjà : Steam VR, flux brut, vérificateur brut WPF

## Répartition des tâches
* Recherches SteamVR : Mattéo et Yorick
* Recherches trames et flux : Jordan et Erwan
* Repo GitHub sur une machine de l'IUT : Elliott