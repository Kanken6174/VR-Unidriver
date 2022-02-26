using System;
using System.Collections.Generic;
using System.Text;

namespace Business
{
    public partial class Manager
    {
        public IPersistanceManager Persistance { get; private set; }

        public void chargeDonnees()
        {
            var donnees = Persistance.chargeDonnees();
            Driver = donnees.driver;
            foreach (var j in Driver.components)
            {
                Driver.components.Add(j);
            }
        }
       public DriverDataTemplate Driver { get; private set; }
        public Manager(IPersistanceManager persistance)
        {
            Persistance = persistance;
        }

    }
}


   