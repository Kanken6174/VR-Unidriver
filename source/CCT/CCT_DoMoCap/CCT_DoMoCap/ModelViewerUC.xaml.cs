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
    /// Logique d'interaction pour ModelViewerUC.xaml
    /// </summary>
    public partial class ModelViewerUC : UserControl
    {
        public ModelViewerUC()
        {
            InitializeComponent();
            FillListView();
        }


        public void FillListView()
        {
            

            listModel.Items.Add("Lorem Ipsum");
            listModel.Items.Add("Lorem Ipsum");
            listModel.Items.Add("Lorem Ipsum");
            listModel.Items.Add("Lorem Ipsum");
            listModel.Items.Add("Lorem Ipsum");
            listModel.Items.Add("Lorem Ipsum");
            listModel.SelectedItem = listModel.Items[0];
        }

    }
}
