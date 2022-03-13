using Business;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Xml;

namespace EcriturefichierDataContract
{
    public class EcritureDmc : IPersistanceManager
    {

        public string FilePath { get; set; } = Path.Combine(Directory.GetCurrentDirectory(), "..//..//..//..//Testw");

        public string FileName { get; set; } = "config.dmc";

        public (IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc) chargeDonnees()
        {
            throw new NotImplementedException();
        }

        public void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc)
        {


            if (!Directory.Exists(FilePath))
            {
                Directory.CreateDirectory(FilePath);
            }

            using (FileStream stream = File.OpenWrite(Path.Combine(FilePath,FileName)))
            {
                
                BinaryFormatter formatter = new BinaryFormatter();

#pragma warning disable SYSLIB0011 // Le type ou le membre est obsolète
                formatter.Serialize(stream, dmc);
#pragma warning restore SYSLIB0011 // Le type ou le membre est obsolète

            }

        }
    }
}