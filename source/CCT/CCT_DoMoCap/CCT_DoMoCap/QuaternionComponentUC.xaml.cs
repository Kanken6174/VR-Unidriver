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

namespace CCT_DoMoCap
{
    /// <summary>
    /// Logique d'interaction pour QuaternionComponentUC.xaml
    /// </summary>
    public partial class QuaternionComponentUC : UserControl
    {
        public QuaternionComponentUC()
        {
            InitializeComponent();
            ListeBox_AddItem();
        }

        private void ListeBox_AddItem()
        {
            LBGen.Items.Add("Quaternion");

        }

        private void ChangeLetter(KeyEventArgs e)
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

        private void OnEnterVerifyFloatMagneto(object sender, KeyEventArgs e)
        {

            if (e.Key == Key.Return)
            {
                try {
                    float mag = float.Parse(MagnetoBox.Text);
                    
                }
                catch  (Exception ex)
                {
                    string err = ex.ToString();

                    Console.WriteLine(err);
                   
                }
               

            }
   

        }

        private void OnEnterVerifyFloatGyro(object sender, KeyEventArgs e)
        {

            if (e.Key == Key.Return)
            {

            }

        }


    }
}
