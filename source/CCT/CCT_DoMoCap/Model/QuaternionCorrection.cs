using System;
using System.Collections.Generic;
using System.Text;

namespace Model
{
    public class QuaternionCorrection : ComponentDataTemplate
    {
        
        public double MagCorrectionStepSize { get; set; }
        public double GyroCorrectionStepSize { get; set; }

        public QuaternionCorrection(string inputPath, int inputType,string flag, double magCorrectionStepSize, double gyroCorrectionStepSize)
            : base(inputPath, inputType, flag)
        {
            MagCorrectionStepSize = magCorrectionStepSize;
            GyroCorrectionStepSize = gyroCorrectionStepSize;
        }
    }
}
