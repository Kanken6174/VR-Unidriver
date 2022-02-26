using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public interface IPersistanceManager
    {
        (DriverDataTemplate driver, List<Component> components) chargeDonnees();
    }
}
