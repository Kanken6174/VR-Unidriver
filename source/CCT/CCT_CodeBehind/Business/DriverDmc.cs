using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Business
{
    public class DriverDmc
    {
        public IReadOnlyDictionary<DriverDataTemplate, Component> Components => components;
        private Dictionary<DriverDataTemplate, Component> components = new Dictionary<DriverDataTemplate, Component>();

        public DriverDmc(params Component[] components)
        {
            AddComponents(components);
        }
        
        
        public void AddComponent(Component components)
        {
            this.components[components.Driver] = components;
        }

        public void AddComponents(params Component[] components)
        {
            foreach (Component component in components)
                this.components[component.Driver] = component;
        }

        public void DeleteAComponent(DriverDataTemplate driver)
        {
            components.Remove(driver);
        }

        public void DeleteAllComponents()
        {
            components.Clear();
        }


    }
}
