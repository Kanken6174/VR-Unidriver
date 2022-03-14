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
    /// Logique d'interaction pour QuaternionComponentUC.xaml
    /// </summary>
    public partial class QuaternionComponentUC : UserControl
    {
        Manager Mng => (App.Current as App).Manager;
        public QuaternionComponentUC()
        {
            InitializeComponent();
            
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
                try
                {
                    float mag = float.Parse(AccelBox.Text);

                }
                catch (Exception ex)
                {
                    string err = ex.ToString();

                    Console.WriteLine(err);

                }
            }

        }


    }
}
