using Business;
using EcriturefichierDataContract;
using System.Linq;

namespace TestConsole
{
    public class TestC
    {
        static void Main(String[] args)
        {
            Manager manager = new Manager(new Stub.Stub());
            manager.chargeDonnees();

            Console.WriteLine(manager.driver.First());
            foreach (var q in manager.Dmc)
            {
                foreach( var component in q.Components.Values)
                    Console.WriteLine(component);
            }
            

        }

        public void testConsole()
        {
            Manager manager = new Manager(new Stub.Stub());
            manager.chargeDonnees();
            foreach (var q in manager.driver)
            {
                if (q.Name != null)
                    Console.WriteLine(q);
            }
            foreach (var q in manager.dmc)
            {
                    Console.WriteLine(q);
            }
        }
    }
}