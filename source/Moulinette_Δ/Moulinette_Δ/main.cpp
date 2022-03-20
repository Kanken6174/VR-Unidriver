#include "VRDevice.h"	
#include "../IPCPIPE/IPCServer.h"
#include <thread>


/**
*   Lecture d'un Component dans un fichier pour l'ajouter au VRDevice
*/
void addComponent(ifstream &fichier, VRDevice* device) {
    string ligne = "";

    if (getline(fichier, ligne)) 
    {
        ligne = ligne.erase(0, 1);
        int number = stringToInt(ligne);

        switch (number) {                           //Type du component a ajout� dans le vector
        case 0:
            //"ABSOLUTE_T";
        {
            if (getline(fichier, ligne))
            {
                unique_ptr<VRAnalog> component = make_unique<VRAnalog>();
                ligne = ligne.erase(0, 1);

                if (ligne[0] != '\0')
                {
                    vector<string> flag_char = {ligne};
                    component->setFlag(flag_char);
                    device->addComponents(move(component));
                }
                else {
                    cout << "PAS DE FLAG" << endl;
                }
            }
        }
        break;
        case 1:
            //"RELATIVE_T";
        {
            if (getline(fichier, ligne))
            {
                unique_ptr<VRRelative> component = make_unique<VRRelative>();
                ligne = ligne.erase(0, 1);
                if (ligne[0] != '\0')
                {
                    vector<string> flag_char = { ligne };
                    component->setFlag(flag_char);
                    device->addComponents(move(component));
                }
                else {
                    cout << "PAS DE FLAG" << endl;
                }
            }
        }
        break;
        case 2:
            //"DIGITAL";
        {
            if (getline(fichier, ligne))
            {
                unique_ptr<VRBoolean> component = make_unique<VRBoolean>();
                ligne = ligne.erase(0, 1);
                if (ligne[0] != '\0')
                {
                    vector<string> flag_char = { ligne };
                    component->setFlag(flag_char);
                    device->addComponents(move(component));
                }
                else {
                    cout << "PAS DE FLAG" << endl;
                }
            }
        }
        break;
        case 3:
            //"HAPTIC"
            break;
        case 4:
            //"SKELETAL"
            break;
        case 5:
            //"RESERVED"
            break;
        case 6:
            //"QUATERNIONS"
        {
            if (getline(fichier, ligne))
            {
                unique_ptr<VRQuaternion> component = make_unique<VRQuaternion>();
                ligne = ligne.erase(0, 1);
                vector<string> tmp = split(ligne, '|');
                component->setFlag(tmp);                                          //le flag d'un quaternion est de la forme A|B|C|D|E|F|G|H|I (9 tags car 3x3 [gyro[xyz], acc[xyz], mag[xyz]])
                device->addComponents(move(component));
            }
        }
        break;
        default:
            //"DEFAULT"
            break;
        }
    }
    
}

/**
*   Lecture d'un nouveau VRDevice dans un fichier
*/
VRDevice *lectureDMC(ifstream &fichier ) {

    VRDevice *device = new VRDevice();
    SerialPort *w = new SerialPort();

        string ligne;
        while (getline(fichier, ligne))
        {
            if (ligne == "/.")
                break;

            char id = ligne[0];
            ligne = ligne.erase(0, 1);
            ligne.erase(remove(ligne.begin(), ligne.end(), '\n'), ligne.end()); //on enlve les \n parasites

            switch (id)
            {
            case '$':   // Nom
                device->setName(ligne);
                break;
            case '&':   // Port COM
                w->setPort(stringToChar(ligne));
                break;
            case '!':   // baudrate a terminer
                w->setBaudrate(stringToInt(ligne));
                break;
            case '=':   // nouvel input = nouveau flag 
                addComponent(fichier, device);                
            }            
        }

        try
        {
            w->connect(w);
        }
        catch (const runtime_error& e)
        {
            cout << e.what() << endl;
        }

        device->setSerialport(w);

        return device;
    
}

/**
*   Lecture de tout les VRDevices dans le fichier
*/
vector<VRDevice*> getAllDevice(string file) {
    ifstream fichier(file, ios::in);
    vector<VRDevice*> toto;

    if (fichier.is_open()) {
        while (fichier.good()) {
            VRDevice* devices = lectureDMC(fichier);
            cout << devices->getName() << endl;
            toto.push_back(devices);
        }
        fichier.close();
    }
    else {
        cout << "Erreur lecture file DMC" << endl;
    }

    return toto;
}


 static bool running_ = true;

int main(int argc, char* argv[]) {
    char* usrname = nullptr;
    size_t sz = 0;
    _dupenv_s(&usrname, &sz, "username");
    if (usrname == nullptr)
        return -2333;

    string filePath = "C:\\Users\\" + string(usrname) + "\\AppData\\Roaming\\.DoMoCap\\driverCfg.dmc";	//full path

    /*
    *   Lecture DMC pour lister VRDevice
    */
    vector<VRDevice*> toto = getAllDevice("gant.dmc");

    /*
    *   Demarrage Threads
    */

    vector<thread> readerThreads;
    for (VRDevice* reader : toto)
    {
        readerThreads.push_back(thread([=, &ref = running_]() {
            while (running_) {
                reader->updateValues();
                //cout << reader->to_string() << endl;
            }
        }));
    }

    /*
    *   Partie PIPE Windows pour communiquer avec le Driver
    */
    string received = "";
    PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");

    while (true) {
        received = ps->ReadPipe();

        if (received == "cleanup") {
            running_ = false;
            for (auto& t : readerThreads) t.join();
            return 0;
        }

        string toSend;
        for (VRDevice* test : toto)
        {
            toSend += test->to_string()+";";
        }
        
        toSend.erase(toSend.length()-1,toSend.length());
        bool success = ps->WriteToPipe(toSend, "\\\\.\\pipe\\pipeDriver");
    }
    return 0;
}