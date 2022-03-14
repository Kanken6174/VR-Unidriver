using System;
using System.Collections.Generic;
using System.Text;

namespace Model
{
    public class Component : ComponentDataTemplate
    {

        public DriverDataTemplate Driver { get; set; }

        public Component(DriverDataTemplate driver,string inputPath, int inputType,  string flag) 
            : base(inputPath, inputType, flag)
        {
            Driver = driver;
        }

        public override string ToString()
        {
            return $"={InputPath}\n" +
                $":{InputType}\n" +
                $"~{Flag}";
        }

        
    }
}
