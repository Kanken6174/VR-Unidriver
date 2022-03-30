Public Class Trackpad : Inherits _SteamVRComponent
    Public x As AnalogRelativeComponent
    Public y As AnalogRelativeComponent
    Public click As DigitalComponent
    Public touch As DigitalComponent
    Public force As AnalogAbsoluteComponent

    Public Sub New()
        Me.type = "trackpad"
    End Sub

    Public Overrides Function to_input_profile() As String
        Throw New NotImplementedException()
    End Function

    Public Overrides Function to_UDC() As String
        Throw New NotImplementedException()
    End Function
End Class