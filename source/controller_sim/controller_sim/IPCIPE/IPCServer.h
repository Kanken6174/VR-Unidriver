/**
* @author Yorick Geoffre
* @brief this files contains the declaration of the PipeServer type which is used for named pipe communication operations.
* @version 0.1
* @date 16/01/2022
*/

#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <string>

using namespace std;

string GetLastErrorAsString();  //permet d'obtenir la dernière erreur du système windows comme un string

/*
Cette classe désigne un tunnel nommé avec droit d'écriture uniquement pour un agent extérieur, ainsi qu'un utilitaire pour se connecter à un autre tunnel nommé et écrire
dedans.
*/
class PipeServer {
private:
    HANDLE hPipe = nullptr; //le handle du tunnel nommé local (seulement lu par le possesseur, écrit par les agents extérieurs)
    char buffer[1024];      //le buffer qui permet de lire à partir du tunnel nommé (pas limité à 1024 caractères, on lit juste 1024 caractères à chaque fois)
    std::string pipeName;   //le nom du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"
    DWORD dwRead = 0;       //le nombre de caractères lus dans le tunnel (utilisé en interne)
    bool connected = false; // si le tunnel est connecté
    bool isExternConnected = false;

public:
    /// <summary>
    /// Le constructeur du PipeServer
    /// </summary>
    /// <param name="pipeName">Le nom système du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
    PipeServer(string pipeName);
    /// <summary>
    /// Permet de lire les données qui ont été écrites dans le tunnel nommé local (hPipe)
    /// </summary>
    /// <returns>Le texte lu depuis le tunnel nommé</returns>
    string ReadPipe();
    /// <summary>
    /// Permet d'écrire vers un tunnel nommé spécifié
    /// </summary>
    /// <param name="message"> Le message à écrire dans le tunnel nommé spécifié</param>
    /// <param name="targetPipe"> Le nom système du tunnel nommé vers lequel écrire</param>
    /// <returns>Le succès ou l'échec de l'écriture</returns>
    bool WriteToPipe(string message, string targetPipe);
    /// <returns>condition si le tunnel nommé local est fonctionnel (connecté) ou non</returns>
    bool isConnected();
};