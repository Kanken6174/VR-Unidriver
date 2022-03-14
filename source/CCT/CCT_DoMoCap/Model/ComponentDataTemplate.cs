using System;

namespace Model
{
    public class ComponentDataTemplate
    {

        public string InputPath { get; set; } ///Le chemin d'input SVR, exemple /input/a/click
        public int InputType { get; set; } ///0-5 pour choisir un vrai mode (analog, bool, skeleton...), 5+ pour le mode stub qui évalue l'update à partie de la touche de clavier correspondante
        public string Flag { get; set; }

        public ComponentDataTemplate(string inputPath,  int inputType, string flag)
        {

            InputPath = inputPath;
            InputType = inputType;
            Flag = flag;
        }

    }
}
