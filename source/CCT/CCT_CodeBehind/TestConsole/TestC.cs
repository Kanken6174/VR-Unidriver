using Business;
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
        }
    }
}