using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public class Component : ComponentDataTemplate
    {

        public Component(string inputPath, int inputType,  char flag) 
            : base(inputPath, inputType, flag)
        {
        }

        public override string ToString()
        {
            return $"{InputPath} {InputType} {Flag}";
        }
    }
}
