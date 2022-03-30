Public MustInherit Class _SteamVRComponent

    Public binding_image_point() As Integer = New Integer() {0, 0}
    Protected type As String = "invalid"
    Public order As UInteger = 0

    MustOverride Function to_input_profile() As String

    MustOverride Function to_UDC() As String

End Class
