using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public interface IPersistanceManager
    {
        (IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc) chargeDonnees();
        void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc);
    }

    
}
