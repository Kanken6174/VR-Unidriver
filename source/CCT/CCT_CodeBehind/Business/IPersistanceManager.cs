using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public interface IPersistanceManager
    {
        (IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components) ChargeDonnees();
        void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components);
    }

    
}
