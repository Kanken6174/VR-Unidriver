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

namespace CCT_DoMoCap
{
    /// <summary>
    /// Logique d'interaction pour GenericComponentUC.xaml
    /// </summary>
    public partial class GenericComponentUC : UserControl
    {
        public GenericComponentUC()
        {
            InitializeComponent();
            ListeBox_AddItem();

        }


        private void ListeBox_AddItem()
        {
            LBGen.Items.Add("Test d'ajout à la listbox");
            LBGen.Items.Add("Et celui ci ?");
            LBGen.Items.Add("Un dernier pour le détour");
            LBGen.Items.Add("Remplissage");
            LBGen.Items.Add("Remplissage2");
            LBGen.Items.Add("Remplissage3");
            LBGen.Items.Add("Remplissage4");

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

            if (LetterBox.IsPressed == true && LetterBox.IsFocused == true)
            {
                if (Keyboard.IsKeyDown(e.Key))
                {
                    ChangeLetter(e);
                }

            }

        }
    }
}