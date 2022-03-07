using Business;
namespace Stub
{
    public class Stub : IPersistanceManager
    {
        public Stub()
        {
        }

        public (IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components) chargeDonnees()
        {
            List<DriverDataTemplate> driver = ChargeDriver();
            List<Component> components = ChargeComponent();
            return (driver, components);
        }

        private List<DriverDataTemplate> ChargeDriver()
        {
            List<DriverDataTemplate> driver = new List<DriverDataTemplate>();
            driver.Add(new DriverDataTemplate("ApexGlove_Right", "COM8",
                "500000", "oculus_cv1_controller_right", 2));
            return driver;
        }


        private List<Component> ChargeComponent()
        {
            List<Component> components = new List<Component>();
            components.Add(new Component("/input/thumbX/value", 0, 'A'));
            components.Add(new Component("/input/thumbY/value", 0, 'B'));
            components.Add(new Component("/input/finger/index", 0, 'C'));
            components.Add(new Component("/input/finger/middle", 0, 'D'));
            components.Add(new Component("/input/finger/ring", 0, 'E'));
            components.Add(new Component("/input/finger/pinky", 0, 'F'));

            components.Add(new Component("/input/joystick/x", 1, 'G'));
            components.Add(new Component("/input/joystick/y", 1, 'H'));
            components.Add(new Component("/input/joystick/click", 2, 'I'));

            components.Add(new Component("/input/a/click", 2, 'J'));
            components.Add(new Component("/input/b/click", 2, 'K'));
            components.Add(new Component("/input/x/click", 2, 'L'));
            components.Add(new Component("/input/system/click", 2, 'M'));
            return components;
        }

        public void SauvegardeDonnees(IEnumerable<DriverDataTemplate> driver, IEnumerable<Component> components)
        {
            throw new NotImplementedException();
        }

    }
}