using System;
using Business;
using Stub;

namespace test
{
    class TestS
    {

        static void Main(String[] args)
        {
            Manager manager = new Manager(new Stub.Stub());
            manager.chargeDonnees();
            manager.Persistance = new EcriturefichierDataContract.EcritureDmc();
            manager.SauvegardeDonnees();
        }
    }
}