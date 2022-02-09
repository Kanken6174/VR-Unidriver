/**
* @author Yorick Geoffre
* @brief this files contains the declaration of the DataDispatcher type, used to wrap around the IPCServer type for named pipe communication
* @version 0.1
* @date 16/01/2022
*/

#include "DoMoDriver.h"
#include "IPCIPE/IPCServer.h"

using namespace std;
using namespace vr;

	/// <summary>
	/// La classe DataDispatcher est un wrapper autour de la classe IPCServer et permet d'intéragir avec les tunnels nommés.
	/// </summary>
class DataDispatcher
{
	private:
		string lastFrame = "";
		/// Un vecteur contenant les données séparées de la trame d'arrivée, produite en interne en appellant <code>Split()</code> sur la trame brute.
		vector<string> splitData;
		/// Le nom du tunnel nommé local
		string pipeName = "\\\\.\\pipe\\pipeDriver";
		/// Le nom du tunnel nommé distant (de la moulinette dans ce cas)
		string targetName = "\\\\.\\pipe\\pipeMoulinette";
		/// Le pointeur vers le PipeServer que cette class enrobe
		PipeServer* localServer;

		int cyclesToIgnore = 200;

		bool dispatcherRunning = false;

	public:
		/// <summary>
		/// Le constructeur de la classe DataDispatcher, il créé également le tunnel nommé interne
		/// </summary>
		DataDispatcher();
		/// <summary>
		/// Le destructeur de la classe DataDispatcher, il déconnecte également le tunnel nommé interne
		/// </summary>
		~DataDispatcher();
		/// <summary>
		/// permet de faire passer les données reçues par le tunnel nommé aux drivers correspondants (ordre naturel)
		/// </summary>
		/// <param name="drivers"> une collection de drivers (vecteur)</param>
		virtual void feedPipeDataToDrivers(vector<DoMoDriver*>* drivers);

		virtual void doPipeAction();
};