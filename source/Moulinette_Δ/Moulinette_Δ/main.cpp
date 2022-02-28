#include "VRDevice.h"	
#include "../IPCPIPE/IPCServer.h"
#include <thread>

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
                VRAnalog* component = new VRAnalog();
                ligne = ligne.erase(0, 1);

                if (ligne[0] != '\0')
                {
                    cout << ligne[0] << endl;
                    vector<string> flag_char = {ligne};
                    component->setFlag(flag_char);
                    device->addComponents(component);
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
                VRRelative* component = new VRRelative();
                ligne = ligne.erase(0, 1);
                if (ligne[0] != '\0')
                {
                    vector<string> flag_char = { ligne };
                    component->setFlag(flag_char);
                    device->addComponents(component);
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
                VRBoolean* component = new VRBoolean();
                ligne = ligne.erase(0, 1);
                if (ligne[0] != '\0')
                {
                    vector<string> flag_char = { ligne };
                    component->setFlag(flag_char);
                    device->addComponents(component);
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
                VRQuaternion* component = new VRQuaternion();
                ligne = ligne.erase(0, 1);
                vector<string> tmp = split(ligne, '|');
                component->setFlag(tmp);                                          //le flag d'un quaternion est de la forme A|B|C|D|E|F|G|H|I (9 tags car 3x3 [gyro[xyz], acc[xyz], mag[xyz]])
                device->addComponents(component);
            }
        }
        break;
        default:
            //"DEFAULT"
            break;
        }
    }
    
}

VRDevice *lectureDMC(ifstream &fichier ) {

    VRDevice *device = new VRDevice();
    SerialPort *w = new SerialPort();

        string ligne;
        while (getline(fichier, ligne))
        {
            if (ligne == "/.")
                return device;
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
            //getchar();
        }

        device->setSerialport(w);

        return device;
    
}

vector<VRDevice*> getAllDevice(string file) {
    ifstream fichier(file, ios::in);
    vector<VRDevice*> toto;

    if (fichier.is_open()) {
        while (fichier.good()) {
            VRDevice* devices = lectureDMC(fichier);
            cout << devices->to_string() << endl;
            toto.push_back(devices);
        }
        fichier.close();
    }
    else {
        cout << "Erreur lecture file DMC" << endl;
    }

    return toto;
}

void start(VRDevice* device) {

    while (true) {
        device->updateValues();
        //cout << device->to_string() << endl;
        //cout << " got request!!! Sending data right away...\n";
    }
}

int main(int argc, char* argv[]) {
    char* usrname = nullptr;
    size_t sz = 0;
    _dupenv_s(&usrname, &sz, "username");
    if (usrname == nullptr)
        return -2333;

    string filePath = "C:\\Users\\" + string(usrname) + "\\AppData\\Roaming\\.DoMoCap\\driverCfg.dmc";	//full path

    vector<VRDevice*> toto = getAllDevice("gant.dmc");

    /*
    vector<thread> readerThreads;

    for (VRDevice* reader : toto)
    {
        readerThreads.push_back(thread(&start,reader));
    }
    

    string received = "";
    PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");

    while (true) {
        received = ps->ReadPipe();
        //cout << "Received data\n";
        //cout << received;
        if (received == "cleanup") {
            for (auto& t : readerThreads) t.join();
            return 0;
        }

        string toSend;
        for (VRDevice* test : toto)
        {
            toSend += test->to_string()+";";
        }
        
        //string toSend = devices->to_string();
        toSend.erase(toSend.length()-1,toSend.length());
        bool success = ps->WriteToPipe(toSend, "\\\\.\\pipe\\pipeDriver");
    }
    
    */
    return 0;
}