#include "serialPort.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>

SerialPort::SerialPort()
{

}

SerialPort::~SerialPort()
{

}

bool SerialPort::open(const char* portname, int baudrate, char databit)
{

	HANDLE hCom = NULL;


	hCom = CreateFileA(portname,                //port name
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,                            // No Sharing
		NULL,                         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);



	if (hCom == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	//Configurer la taille du tampon 
	if (!SetupComm(hCom, 1024, 1024))
	{
		return false;
	}

	// Paramètre de configuration 
	DCB p;
	memset(&p, 0, sizeof(p));
	p.DCBlength = sizeof(p);
	p.BaudRate = baudrate; // Débit en bauds
	p.ByteSize = databit; // Bit de données


	if (!SetCommState(hCom, &p))
	{
		// Échec de la définition des paramètres
		return false;
	}


	//Traitement du délai d'attente, unité : millisecondes
	//Timeout total = facteur de temps × nombre de caractères lus ou écrits + constante de temps
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1000; //Délai d'expiration de l'intervalle de lecture
	TimeOuts.ReadTotalTimeoutMultiplier = 500; //Facteur de temps de lecture
	TimeOuts.ReadTotalTimeoutConstant = 5000; //Constante de temps de lecture
	TimeOuts.WriteTotalTimeoutMultiplier = 500; // Écrire le facteur temps
	TimeOuts.WriteTotalTimeoutConstant = 2000; //Écrire la constante de temps
	SetCommTimeouts(hCom, &TimeOuts);

	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//Effacer le tampon série

	memcpy(pHandle, &hCom, sizeof(hCom));// Enregistrer la poignée

	return true;
}

void SerialPort::close()
{
	HANDLE hCom = *(HANDLE*)pHandle;
	CloseHandle(hCom);
}

int SerialPort::send(const void* buf, int len)
{
	HANDLE hCom = *(HANDLE*)pHandle;

	DWORD dwBytesWrite = len; //Nombre d'octets de données écrits avec succès
	BOOL bWriteStat = WriteFile(hCom, //Poignée de port série
		buf, //Données de la première adresse
		dwBytesWrite, //Nombre d'octets de données à envoyer
		&dwBytesWrite, //DWORD*, utilisé pour recevoir et renvoyer le nombre d'octets de données envoyés avec succès
		NULL); //NULL signifie envoi synchrone, OVERLAPPED* signifie envoi asynchrone
	if (!bWriteStat)
	{
		return 0;
	}
	return dwBytesWrite;

}

int SerialPort::receive(void* buf, int maxlen)
{
	HANDLE hCom = *(HANDLE*)pHandle;

	DWORD wCount = maxlen; //Nombre d'octets de données lus avec succès
	BOOL bReadStat = ReadFile(hCom, //Poignée de port série
		buf, //Données de la première adresse
		wCount, //Nombre maximum d'octets de données à lire
		&wCount, //DWORD*, utilisé pour recevoir et retourner le nombre d'octets de données lus avec succès
		NULL); //NULL signifie envoi synchrone, OVERLAPPED* signifie envoi asynchrone
	if (!bReadStat)
	{
		return 0;
	}
	return wCount;


}