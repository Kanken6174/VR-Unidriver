using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Business
{
    public partial class Manager
    {
        public IPersistanceManager Persistance { get; /*private*/ set; }

        public void chargeDonnees()
        {
            var donnees = Persistance.chargeDonnees();
            foreach(var donne in donnees.driver)
            {
                driver.Add(donne);
            }
            foreach (var j in donnees.dmc)
            {
                dmc.Add(j);
            }
        }

        public void SauvegardeDonnees()
        {
            Persistance.SauvegardeDonnees(driver, dmc);
        }

        public ReadOnlyCollection<DriverDataTemplate> Driver { get; private set; }
        public List<DriverDataTemplate> driver = new List<DriverDataTemplate>();

        public ReadOnlyCollection<DriverDmc> Dmc { get; private set; }
        public List<DriverDmc> dmc = new List<DriverDmc>();
        public Manager(IPersistanceManager persistance)
        {
            Persistance = persistance;
            Driver = new ReadOnlyCollection<DriverDataTemplate>(driver);
            Dmc = new ReadOnlyCollection<DriverDmc>(dmc);
        }

    }
}


   