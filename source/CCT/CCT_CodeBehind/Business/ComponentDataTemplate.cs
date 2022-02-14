using System;

namespace Business
{
    public class ComponentDataTemplate
    {

        public ComponentDataTemplate(int inputType, string inputPath, char flag)
        {

            InputPath = inputPath;
            InputType = inputType;
            Flag = flag;
        }

        public string InputPath ///Le chemin d'input SVR, exemple /input/a/click
        {
            get
            {
                return inputPath;
            }
            private set
            {
                inputPath = value;
            }
        }
        private string inputPath;



        public int InputType        ///0-5 pour choisir un vrai mode (analog, bool, skeleton...), 5+ pour le mode stub qui évalue l'update à partie de la touche de clavier correspondante
        {
            get
            {
                return inputType;
            }
            private set
            {
                inputType = value;
            }
        }
        private int inputType;

        public char Flag
        {
            get
            {
                return flag;
            }
            private set
            {
                flag = value;
            }
        }
        private char flag;




    }
}
