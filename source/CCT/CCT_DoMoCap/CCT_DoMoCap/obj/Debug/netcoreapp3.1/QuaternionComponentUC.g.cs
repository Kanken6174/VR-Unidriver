﻿#pragma checksum "..\..\..\QuaternionComponentUC.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "18039E7528C3296169222C17E9D900C1FD451F87"
//------------------------------------------------------------------------------
// <auto-generated>
//     Ce code a été généré par un outil.
//     Version du runtime :4.0.30319.42000
//
//     Les modifications apportées à ce fichier peuvent provoquer un comportement incorrect et seront perdues si
//     le code est régénéré.
// </auto-generated>
//------------------------------------------------------------------------------

using CCT_DoMoCap;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Controls.Ribbon;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace CCT_DoMoCap {
    
    
    /// <summary>
    /// QuaternionComponentUC
    /// </summary>
    public partial class QuaternionComponentUC : System.Windows.Controls.UserControl, System.Windows.Markup.IComponentConnector {
        
        
        #line 16 "..\..\..\QuaternionComponentUC.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Primitives.ToggleButton LetterBox;
        
        #line default
        #line hidden
        
        
        #line 32 "..\..\..\QuaternionComponentUC.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox LBGen;
        
        #line default
        #line hidden
        
        
        #line 35 "..\..\..\QuaternionComponentUC.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox MagnetoBox;
        
        #line default
        #line hidden
        
        
        #line 38 "..\..\..\QuaternionComponentUC.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox GyroBox;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.14.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/CCT_DoMoCap;component/quaternioncomponentuc.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\..\QuaternionComponentUC.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "5.0.14.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.LetterBox = ((System.Windows.Controls.Primitives.ToggleButton)(target));
            
            #line 16 "..\..\..\QuaternionComponentUC.xaml"
            this.LetterBox.AddHandler(System.Windows.Input.Keyboard.KeyDownEvent, new System.Windows.Input.KeyEventHandler(this.OnKeyDownHandler));
            
            #line default
            #line hidden
            return;
            case 2:
            this.LBGen = ((System.Windows.Controls.ListBox)(target));
            return;
            case 3:
            this.MagnetoBox = ((System.Windows.Controls.TextBox)(target));
            
            #line 35 "..\..\..\QuaternionComponentUC.xaml"
            this.MagnetoBox.AddHandler(System.Windows.Input.Keyboard.KeyDownEvent, new System.Windows.Input.KeyEventHandler(this.OnEnterVerifyFloatMagneto));
            
            #line default
            #line hidden
            return;
            case 4:
            this.GyroBox = ((System.Windows.Controls.TextBox)(target));
            
            #line 38 "..\..\..\QuaternionComponentUC.xaml"
            this.GyroBox.AddHandler(System.Windows.Input.Keyboard.KeyDownEvent, new System.Windows.Input.KeyEventHandler(this.OnEnterVerifyFloatGyro));
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

