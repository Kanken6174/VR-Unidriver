using Business;
using System;
using System.Linq;

namespace TestConsole
{
    public class TestC
    {
        static void Main(String[] args)
        {
            Manager manager = new Manager(new Stub.Stub());
            Console.WriteLine(manager.driver.First());
        }
    }
}