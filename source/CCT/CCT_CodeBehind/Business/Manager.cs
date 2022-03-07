using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Business
{
    public partial class Manager
    {
        public IPersistanceManager Persistance { get; /*private*/ set; }

        public ReadOnlyCollection<DriverDataTemplate> Driver { get; private set; }
        public List<DriverDataTemplate> driver = new List<DriverDataTemplate>();

        public ReadOnlyCollection<Component> Components { get; private set; }
        public List<Component> components = new List<Component>();
        public Manager(IPersistanceManager persistance)
        {
            Persistance = persistance;
            Driver = new ReadOnlyCollection<DriverDataTemplate>(driver);
            Components = new ReadOnlyCollection<Component>(components);
            chargeDonnees();
        }

        public void chargeDonnees()
        {
            var donnees = Persistance.ChargeDonnees();
            foreach(var donne in donnees.driver)
            {
                driver.Add(donne);
            }
            foreach (var j in donnees.components)
            {
                components.Add(j);
            }
        }

        public void SauvegardeDonnees()
        {
            Persistance.SauvegardeDonnees(driver, components);
        }

        

    }
}


   