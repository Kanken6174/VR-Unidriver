using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CCT
{
    /// <summary>
    /// Logique d'interaction pour GenericComponentUC.xaml
    /// </summary>
    public partial class GenericComponentUC : UserControl
    {
        public GenericComponentUC()
        {
            InitializeComponent();
        }

        private void ListeBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void ListeBox_AddItem(object sender, EventArgs e)
        {
            LBGen.Items.Add("Test d'ajout à la listbox");
            LBGen.Items.Add("Et celui ci ?");
            LBGen.Items.Add("Un dernier pour le détour");

        }
    }
}
