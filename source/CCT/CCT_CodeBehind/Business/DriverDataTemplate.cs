using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace Business
{
    [DataContract]
    public class DriverDataTemplate
    {

        [DataMember]
        public string Name { get; set; }  //le nom de l'appareil qui sera ajouté
        [DataMember]
        public string RenderModel { get; set; }      //le modèle 3d de l'appareil (optionnel)
        [DataMember]
        public string SerialNumber { get; set; }     //le numéro de série (révision) de l'appareil
        [DataMember]
        public string Driver { get; set; } // The driver Steam vr will use
        [DataMember]
        public int Role { get; set; }   //défaut à invalid (0), de 0 à 5 (1 main droite, 2 main gauche)
        
        public DriverDataTemplate(String name, string serialNumber, string renderModel, string driver, int role)
        {
            Name = name;
            RenderModel = renderModel;
            SerialNumber = serialNumber;
            Driver = driver;
            Role = role;
        }

        public override string ToString()
        {
            return $"#on donne le nom du driver, cela en créé un nouveau à chaque $\n" +
                $"${ Name}\n&{RenderModel}\n!{SerialNumber}\n" +
                $"#on donne le modèle 3d à utiliser pour le driver\n" +
                $">{Driver}\n" +
                $"#on définit le rôle du driver (1 = main gauche, " +
                $"2 = droite, 3 = pas applicable,...)\n" +
                $"<{Role}";
        }
    }
}
