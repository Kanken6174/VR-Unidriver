using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public class DriverDataTemplate
    {

        public string Name { get; set; }  //le nom de l'appareil qui sera ajouté
        public string RenderModel { get; set; }      //le modèle 3d de l'appareil (optionnel)
        public string SerialNumber { get; set; }     //le numéro de série (révision) de l'appareil
        public string Driver { get; set; } // The driver Steam vr will use
        public int Role { get; set; }   //défaut à invalid (0), de 0 à 5 (1 main droite, 2 main gauche)
        
        
        public List<Component> components = new List<Component>();

        public void display(List<Component> components)
        {
            List<Component> l = components;
            foreach (Component c in l)
            {
                Console.WriteLine(c);
            }
        }
        

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
