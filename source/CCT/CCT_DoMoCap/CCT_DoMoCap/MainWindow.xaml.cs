using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CCT_DoMoCap
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnLoadTrame(object sender, KeyEventArgs e)
        {

            Window footerParentWindow = Window.GetWindow(Footer);
            // Footer.TrameButton.DataContext;


        }


        private void ChangeDeviceName (object sender, RoutedEventArgs e)
        {
            DeviceName.Text = "New Name";
        }

        private void OpenOptionWindow(object sender, RoutedEventArgs e )
        {
            OptionWindow w = new OptionWindow();
            w.Show();
        }


        private void OpenDeviceAddingWindow(object sender, RoutedEventArgs e)
        {
            DeviceAdding w = new DeviceAdding();
            w.Show();
        }
    }


}
