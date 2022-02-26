using System;
using Business;
using Stub;

namespace test
{
    class Program
    {

        static void Main(String[] args)
        {
            Manager manager = new Manager(new Stub.Stub());
            manager.chargeDonnees();
            Console.WriteLine(manager.Driver);
            manager.Driver.display(manager.Driver.components);
        }
        

        
    }
}