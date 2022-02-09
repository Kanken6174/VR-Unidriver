#include "VRDevice.h"	
#include "../IPCPIPE/IPCServer.h"



VRDevice lectureDMC(string file ) {
    ifstream fichier(file, ios::in);

    VRDevice device;
    SerialPort w;

    if (fichier)
    {
        string ligne;
        while (getline(fichier, ligne))
        {
            char id = ligne[0];
            ligne = ligne.erase(0, 1);
            ligne.erase(remove(ligne.begin(), ligne.end(), '\n'), ligne.end()); //on enlve les \n parasites
            //cout << ligne << endl;
            switch (id)
            {
            case '$':   // Nom
                device.setName(ligne);
                break;
            case '&':   // Port COM
                w.setPort(stringToChar(ligne));
                break;
            case '!':   // baudrate a terminer
                w.setBaudrate(stringToInt(ligne));
                break;
            case '=':   // nouvel input = nouveau flag 

                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                istringstream iss(ligne);
                int number;
                iss >> number;

                if (iss.fail()) {
                    cerr << "ERROR! conversion\n";
                }

                string type;
                switch (number) {                           //Type du component a ajouté dans le vector
                case 0:
                    //"ABSOLUTE_T";
                {VRAnalog* component = new VRAnalog();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                ligne.erase(remove(ligne.begin(), ligne.end(), ' '), ligne.end());
                vector<char> flag_string;
                flag_string.push_back(ligne[0]);
                component->setFlag(flag_string);
                component->setMin(ligne[1]);
                component->setMax(ligne[2]);
                device.addComponents(component); }
                    break;
                case 1:
                    //"RELATIVE_T";
                {VRRelative* component = new VRRelative();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                ligne.erase(remove(ligne.begin(), ligne.end(), ' '), ligne.end());
                vector<char> flag_string;
                flag_string.push_back(ligne[0]);
                component->setFlag(flag_string);
                component->setMin(ligne[1]);
                component->setMax(ligne[2]);
                device.addComponents(component); }
                    break;
                case 2:
                    //"DIGITAL";
                {VRBoolean* component = new VRBoolean();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                vector<char> flag_string;
                flag_string.push_back(ligne[0]);
                component->setFlag(flag_string);
                device.addComponents(component); }
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
                vector<char> tmp = utilities::splitChar(ligne, '|');
                component->setFlag(tmp);      //le flag d'un quaternion est de la forme A|B|C|D|E|F|G|H|I (9 tags car 3x3 [gyro[xyz], acc[xyz], mag[xyz]])
                device.addComponents(component); 
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
            w = w.connect();
        }
        catch (const runtime_error& e)
        {
            cout << e.what() << endl;
            getchar();
        }

        device.setSerialport(w);

        return device;
    }
    else {
        cerr << "Erreur lecture fichier DMC" << endl;

    }
}

int main(int argc, char* argv[]) {
    

    VRDevice devices = lectureDMC("gant.dmc");
    devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues(); devices.updateValues();

    cout << devices.to_string() << endl;
    cout << "---------------------------" << endl;

    /*
    string received = "";
    PipeServer* ps = new PipeServer("\\\\.\\pipe\\pipeMoulinette");

    while (true) {
        received = ps->ReadPipe();
        //cout << "Received data\n";
        //cout << received;
        devices.updateValues();
        //cout << " got request!!! Sending data right away...\n";
        string toSend = devices.to_string();
        cout << toSend + "\n";
        Sleep(20);
        bool success = ps->WriteToPipe(toSend, "\\\\.\\pipe\\pipeDriver");
    }
    */
}

