﻿using System;
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
    /// Logique d'interaction pour Footer.xaml
    /// </summary>
    public partial class Footer : UserControl
    {
        Manager Mng => (App.Current as App).Manager;
        public Footer()
        {
            InitializeComponent();
        }


        private void OnLoadTrame(object sender, KeyEventArgs e)
        {



        }

       
    }
}
