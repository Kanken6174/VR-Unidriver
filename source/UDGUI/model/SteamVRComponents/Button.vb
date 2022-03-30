Public Class Button : Inherits _SteamVRComponent
    Public click As DigitalComponent

    Public Sub New()
        Me.type = "button"
    End Sub

    Public Overrides Function to_input_profile() As String
        Dim output As String = ""

        Return output
    End Function

    Public Overrides Function to_UDC() As String
        Dim output As String = ""
        output += ("#component n°" + Me.order + " of type button\n")
        output += click.To_UDC()
        Return output
    End Function
End Class
