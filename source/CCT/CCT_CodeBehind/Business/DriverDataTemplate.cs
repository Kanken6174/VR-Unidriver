using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.Serialization;
using System.Text;

namespace Business
{
    [Serializable()]
    public class DriverDataTemplate : IEquatable<DriverDataTemplate>
    {

        public string Name { get; set; }  //le nom de l'appareil qui sera ajouté
        public string RenderModel { get; set; }      //le modèle 3d de l'appareil (optionnel)
        public string SerialNumber { get; set; }     //le numéro de série (révision) de l'appareil
        public string Driver { get; set; } // The driver Steam vr will use
        public int Role { get; set; }   //défaut à invalid (0), de 0 à 5 (1 main droite, 2 main gauche)
        public QuaternionCorrection Quaternion { get; set; }


        public DriverDataTemplate(String name, string serialNumber, string renderModel, string driver, int role, string inputPath, int inputType, string flag, double magCorrectionStepSize, double gyroCorrectionStepSize)
        {
            Name = name;
            RenderModel = renderModel;
            SerialNumber = serialNumber;
            Driver = driver;
            Role = role;
            Quaternion = new QuaternionCorrection(inputPath, inputType, flag, magCorrectionStepSize, gyroCorrectionStepSize);

        }

        public override string ToString()
        {
            return $"#on donne le nom du driver, cela en créé un nouveau à chaque $\n" +
                $"${ Name}\n&{RenderModel}\n!{SerialNumber}\n" +
                $"#on donne le modèle 3d à utiliser pour le driver\n" +
                $">{Driver}\n" +
                $"#on définit le rôle du driver (1 = main gauche, " +
                $"2 = droite, 3 = pas applicable,...)\n" +
                $"<{Role}\n" +
                $"#on définit désormais les composants de ce driver\n" +
                $"={Quaternion.InputPath}\n" +
                $":{Quaternion.InputType}\n" +
                $"~{Quaternion.Flag}";

        }

        public bool Equals([AllowNull] DriverDataTemplate other)
        {
            return Name.Equals(other.Name);
        }
        public override bool Equals(object obj)
        {
            if (Equals(obj, null)) return false;
            if (Equals(obj, this)) return true;
            if (GetType() != obj.GetType()) return false;
            return Equals(obj as DriverDataTemplate);
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }

    }
}
