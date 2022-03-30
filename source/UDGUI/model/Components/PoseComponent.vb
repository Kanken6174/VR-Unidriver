Public Class PoseComponent : Inherits _Component
    Protected headTranslation() As Double = New Double() {0, 0, 0}
    Protected worldTranslation() As Double = New Double() {0, 0, 0}
    Protected headRotation() As Double = New Double() {0, 0, 0}
    Protected worldRotation() As Double = New Double() {0, 0, 0}
    Protected rotationOffset() As Double = New Double() {0, 0, 0}

    Protected willDrift As Boolean = False
    Protected shouldShadowRotation As Boolean = False
    Protected shouldShadowPosition As Boolean = False

    Protected shadowHandle As Integer = -1

    Protected dataSource As _Component

    Public Overrides Function To_UDC() As String
        Dim output As String = ""
        output += "#Defining the pose component for this device:"
        output += ("%" + shadowHandle + "\n")
        output += ("|" + shouldShadowRotation.ToString.ToLower + "\n")
        output += ("_" + shouldShadowPosition.ToString.ToLower + "\n")
        output += ("{" + headTranslation(0) + "|" + headTranslation(1) + "|" + headTranslation(2) + "\n")
        output += ("}" + worldTranslation(0) + "|" + worldTranslation(1) + "|" + worldTranslation(2) + "\n")
        output += ("]" + worldRotation(0) + "|" + worldRotation(1) + "|" + worldRotation(2) + "\n")
        output += ("[" + headRotation(0) + "|" + headRotation(1) + "|" + headRotation(2) + "\n")
        output += ("{" + rotationOffset(0) + "|" + rotationOffset(1) + "|" + rotationOffset(2) + "\n")
        output += ("\" + willDrift.ToString.ToLower + "\n")
        Return output
    End Function
End Class