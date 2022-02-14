using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    class QuaternionCorrection : ComponentDataTemplate
    {
        public QuaternionCorrection(int inputType, string inputPath, char flag, double magCorrectionStepSize, double gyroCorrectionStepSize) 
            : base(inputType, inputPath, flag)
        {
            MagCorrectionStepSize = magCorrectionStepSize;
            GyroCorrectionStepSize = gyroCorrectionStepSize;
        }

        public double MagCorrectionStepSize
        {
            get
            {
                return magCorrectionStepSize;
            }
            private set
            {
                magCorrectionStepSize = value;
            }
        }
        private double magCorrectionStepSize;

        public double GyroCorrectionStepSize
        {
            get
            {
                return gyroCorrectionStepSize;
            }
            private set
            {
                gyroCorrectionStepSize = value;
            }
        }
        private double gyroCorrectionStepSize;
    }
}
