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

string GetLastErrorAsString();  //permet d'obtenir la derni�re erreur du syst�me windows comme un string

/*
Cette classe d�signe un tunnel nomm� avec droit d'�criture uniquement pour un agent ext�rieur, ainsi qu'un utilitaire pour se connecter � un autre tunnel nomm� et �crire
dedans.
*/
class PipeServer {
private:
    HANDLE hPipe = nullptr; //le handle du tunnel nomm� local (seulement lu par le possesseur, �crit par les agents ext�rieurs)
    char buffer[1024];      //le buffer qui permet de lire � partir du tunnel nomm� (pas limit� � 1024 caract�res, on lit juste 1024 caract�res � chaque fois)
    std::string pipeName;   //le nom du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"
    DWORD dwRead = 0;       //le nombre de caract�res lus dans le tunnel (utilis� en interne)
    bool connected = false; // si le tunnel est connect�
    bool isExternConnected = false;

public:
    /// <summary>
    /// Le constructeur du PipeServer
    /// </summary>
    /// <param name="pipeName">Le nom syst�me du tunnel, sous le format windows standard "\\.\\\\pipe\\nom_du_tunnel_ici"</param>
    PipeServer(string pipeName);
    /// <summary>
    /// Permet de lire les donn�es qui ont �t� �crites dans le tunnel nomm� local (hPipe)
    /// </summary>
    /// <returns>Le texte lu depuis le tunnel nomm�</returns>
    string ReadPipe();
    /// <summary>
    /// Permet d'�crire vers un tunnel nomm� sp�cifi�
    /// </summary>
    /// <param name="message"> Le message � �crire dans le tunnel nomm� sp�cifi�</param>
    /// <param name="targetPipe"> Le nom syst�me du tunnel nomm� vers lequel �crire</param>
    /// <returns>Le succ�s ou l'�chec de l'�criture</returns>
    bool WriteToPipe(string message, string targetPipe);
    /// <returns>condition si le tunnel nomm� local est fonctionnel (connect�) ou non</returns>
    bool isConnected();
};