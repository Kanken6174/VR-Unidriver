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
using Model;

namespace CCT_DoMoCap
{
    /// <summary>
    /// Logique d'interaction pour GenericComponentUC.xaml
    /// </summary>
    public partial class GenericComponentUC : UserControl
    {
        Manager Mng => (App.Current as App).Manager;
        public GenericComponentUC()
        {
            InitializeComponent();
            ListeBox_AddItem();

        }


        private void ListeBox_AddItem()
        {
            LBGen.Items.Add("Boolean");
            LBGen.Items.Add("Relatif");
            LBGen.Items.Add("Absolu");


        }


        private void ChangeLetter( KeyEventArgs e)
        {
           if (e.Key >= Key.A || e.Key <= Key.Z)
            {
                LetterBox.Content = e.Key.ToString();
            }
        }



        private void OnKeyDownHandler(object sender, KeyEventArgs e)
        {

            if (LetterBox.IsChecked == true && LetterBox.IsFocused == true)
            {

               ChangeLetter(e);
               

            }

        }
    }
}
