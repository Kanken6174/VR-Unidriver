Public Class RendermodelPose : Inherits _SteamVRComponent
    Public dataSource As _Component

    Public Sub New()
        Me.type = "pose"
    End Sub

    Public Overrides Function to_input_profile() As String
        Throw New NotImplementedException()
    End Function

    Public Overrides Function to_UDC() As String
        Throw New NotImplementedException()
    End Function
End Class
