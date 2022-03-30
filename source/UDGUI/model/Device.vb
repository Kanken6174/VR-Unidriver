Imports Microsoft.VisualBasic

Public Class Device
    Private serialPort As UInteger = 0
    Private baudrate As UInt16 = 9600

    Private poseComponent As PoseComponent

    Private components As List(Of _SteamVRComponent) = New List(Of _SteamVRComponent)
End Class