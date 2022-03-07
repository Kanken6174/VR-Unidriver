using Business;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Xml;

namespace EcriturefichierDataContract
{
    public class EcritureDmc : IPersistanceManager
    {

        public string FilePath { get; set; } = Path.Combine(Directory.GetCurrentDirectory(), "..//..//..//..//Testw");

        public string FileName { get; set; } = "config.dmc";

        public (IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components) ChargeDonnees()
        {
            throw new NotImplementedException();
        }

        public void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components)
        {
            var serializer = new DataContractSerializer(typeof(IEnumerable<DriverDataTemplate>));

            if(!Directory.Exists(FilePath))
            {
                Directory.CreateDirectory(FilePath);
            }

            var settings = new XmlWriterSettings() { Indent = true };
            using (TextWriter s = File.CreateText(Path.Combine(FilePath, FileName)))
            {
                using (XmlWriter w = XmlWriter.Create(s, settings))
                {
                    serializer.WriteObject(w, driver);
                }
            }
        }

    }
}