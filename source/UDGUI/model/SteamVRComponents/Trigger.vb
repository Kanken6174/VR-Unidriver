Public Class Trigger : Inherits _SteamVRComponent
    Public value As AnalogAbsoluteComponent
    Public click As DigitalComponent
    Public touch As DigitalComponent
    Public force As AnalogAbsoluteComponent

    Public Sub New()
        Me.type = "trigger"
    End Sub

    Public Overrides Function to_input_profile() As String
        Throw New NotImplementedException()
    End Function

    Public Overrides Function to_UDC() As String
        Throw New NotImplementedException()
    End Function
End Class