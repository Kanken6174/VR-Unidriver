using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public class DriverDataTemplate
    {

        public DriverDataTemplate( String name, string renderModel, string serialNumber, int role)
        {
            Name = name;
            RenderModel = renderModel;
            SerialNumber = serialNumber;
            Role = role;
        }

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }
        private string name;    //le nom de l'appareil qui sera ajouté


        public string RenderModel
        {
            get
            {
                return renderModel;
            }
            set
            {
                renderModel = value;
            }
        }
        private string renderModel;        //le modèle 3d de l'appareil (optionnel)

        public string SerialNumber
        {
            get
            {
                return serialNumber;
            }
            set
            {
                serialNumber = value;
            }
        }
        private string serialNumber;        //le numéro de série (révision) de l'appareil

        public int Role
        {
            get
            {
                return role;
            }
            set
            {
                role = value;
            }
        }
        private int role;    //défaut à invalid (0), de 0 à 5 (1 main droite, 2 main gauche)
        
        
        ///vector<ComponentDataTemplate*> components;    //les divers composants du driver (boutons, joysticks, entrées squelette...)
    };
}
