using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public class Component : ComponentDataTemplate
    {
        public Component(int inputType, string inputPath, char flag) 
            : base(inputType, inputPath, flag)
        {
        }

    }
}
