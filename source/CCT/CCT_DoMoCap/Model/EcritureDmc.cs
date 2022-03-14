
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Model
{
    public class EcritureDmc : IPersistanceManager
    {

        public string FilePath { get; set; } = Path.Combine(Directory.GetCurrentDirectory(), "..//..//..//..//Testw");

        public string FileName { get; set; } = "config.dmc";

        public (IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc) chargeDonnees()
        {
            throw new System.NotImplementedException();
        }

        public void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> Dmc)
        {


            if (!Directory.Exists(FilePath))
            {
                Directory.CreateDirectory(FilePath);
            }

            StreamWriter sw = new StreamWriter(File.OpenWrite(Path.Combine(FilePath, FileName)));


            sw.WriteLine(driver.First());
            foreach (var q in Dmc)
            {
                foreach (var component in q.Components.Values)
                    sw.WriteLine(component);
            }
            sw.Close();
            

        }
    }
}