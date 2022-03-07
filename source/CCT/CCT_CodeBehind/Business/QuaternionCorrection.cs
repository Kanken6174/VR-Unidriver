using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    class QuaternionCorrection : ComponentDataTemplate
    {
        
        public double MagCorrectionStepSize { get; set; }
        public double AccCorrectionStepSize { get; set; }

        public QuaternionCorrection(string inputPath, int inputType,char flag, double magCorrectionStepSize, double accCorrectionStepSize)
            : base(inputPath, inputType, flag)
        {
            MagCorrectionStepSize = magCorrectionStepSize;
            AccCorrectionStepSize = accCorrectionStepSize;
        }
    }
}
