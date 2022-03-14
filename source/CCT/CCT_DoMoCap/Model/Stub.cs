
using System.Collections.Generic;

namespace Model
{
    public class Stub : IPersistanceManager
    {
        public Stub()
        {
        }

        public (IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc) chargeDonnees()
        {
            List<DriverDataTemplate> driver = ChargeDriver();
            List<DriverDmc> dmc = ChargeDmc(driver);
            return (driver, dmc);
        }

        private List<DriverDataTemplate> ChargeDriver()
        {
            List<DriverDataTemplate> driver = new List<DriverDataTemplate>();
            driver.Add(new DriverDataTemplate("ApexGlove_Right", "COM8",
                "500000", "oculus_cv1_controller_right", 2, "/pose/imu", 6, "N|O|P|Q|R|S|T|U|V", 5, 2));
            return driver;
        }


        private List<DriverDmc> ChargeDmc(List<DriverDataTemplate> drivers)
        {
            List<DriverDmc> dmc = new List<DriverDmc>();
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/thumbX/value", 0, "A")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/thumbY/value", 0, "B")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/finger/index", 0, "C")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/finger/middle", 0, "D")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/finger/ring", 0, "E")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/finger/pinky", 0, "F")));

            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/joystick/x", 1, "G")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/joystick/y", 1, "H")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/joystick/click", 2, "I")));

            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/a/click", 2, "J")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/b/click", 2, "K")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/x/click", 2, "L")));
            dmc.Add(new DriverDmc(new Component(drivers[0], "/input/system/click", 2, "M")));
            return dmc;
        }




        public void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<DriverDmc> dmc)
        {
            throw new System.NotImplementedException();
        }
    }
}