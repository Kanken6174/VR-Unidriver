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
using System.Windows.Shapes;
using Model;

namespace CCT_DoMoCap
{
    /// <summary>
    /// Logique d'interaction pour DeviceAdding.xaml
    /// </summary>
    public partial class DeviceAdding : Window
    {
        Manager Mng => (App.Current as App).Manager;
        public DeviceAdding()
        {
            InitializeComponent();
        }
    }
}
