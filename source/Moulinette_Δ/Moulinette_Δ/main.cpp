#include "VRDevice.h"	
#include "../IPCPIPE/IPCServer.h"
#include <thread>
#include <mutex>


VRDevice *lectureDMC(string file ) {
    ifstream fichier(file, ios::in);

    VRDevice *device = new VRDevice();
    SerialPort *w = new SerialPort();
    if (fichier)
    {
        string ligne;
        while (getline(fichier, ligne))
        {
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
                
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                int number = stringToInt(ligne);

                switch (number) {                           //Type du component a ajouté dans le vector
                case 0:
                    //"ABSOLUTE_T";
                {VRAnalog* component = new VRAnalog();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                vector<string> flag_char = split(ligne,' ');
                component->setFlag(flag_char);
                device->addComponents(component); }
                    break;
                case 1:
                    //"RELATIVE_T";
                {VRRelative* component = new VRRelative();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                vector<string> flag_char = split(ligne, ' ');
                component->setFlag(flag_char);
                device->addComponents(component); }
                    break;
                case 2:
                    //"DIGITAL";
                {VRBoolean* component = new VRBoolean();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                vector<string> flag_char = split(ligne, ' ');
                component->setFlag(flag_char);
                device->addComponents(component); }
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
                {VRQuaternion* component = new VRQuaternion();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                vector<string> tmp = split(ligne, '|');
                component->setFlag(tmp);                                          //le flag d'un quaternion est de la forme A|B|C|D|E|F|G|H|I (9 tags car 3x3 [gyro[xyz], acc[xyz], mag[xyz]])
                device->addComponents(component);
                }
                    break;
                default:
                    //"DEFAULT"
                    break;
                }
            }            
        }

        try
        {
            w->connect(w);
        }
        catch (const runtime_error& e)
        {
            cout << e.what() << endl;
            getchar();
        }

        device->setSerialport(w);

        return device;
    }
    else {
        cerr << "Erreur lecture fichier DMC" << endl;

    }
}


int main(int argc, char* argv[]) {
    char* usrname = nullptr;
    size_t sz = 0;
    _dupenv_s(&usrname, &sz, "username");
    if (usrname == nullptr)
        return -2333;

    string filePath = "C:\\Users\\" + string(usrname) + "\\AppData\\Roaming\\.DoMoCap\\driverCfg.dmc";	//full path


    VRDevice *devices = lectureDMC("gant.dmc");

    mutex t1Lock;

    thread t1([&t1Lock, devices]() {
        while (true) {
            try {
                devices->requestTram();
            }
            catch (exception e) {
                cout << e.what() << endl;
            }
        }
    });
    
    while (getchar()) {
        
        t1Lock.lock();
        cout << devices->to_string() << endl;
        t1Lock.unlock();
    }


   /*
    string received = "";
    PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");

    while (true) {
        received = ps->ReadPipe();
        //cout << "Received data\n";
        //cout << received;
        if (received == "cleanup") {
            return 0;
        }
        devices->updateValues();
        //cout << " got request!!! Sending data right away...\n";
        string toSend = devices->to_string();
        bool success = ps->WriteToPipe(toSend, "\\\\.\\pipe\\pipeDriver");
    }
    */
}