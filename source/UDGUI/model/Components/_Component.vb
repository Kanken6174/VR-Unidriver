Imports Microsoft.VisualBasic

Public MustInherit Class _Component
    Public Path As String
    Public Type As UInteger
    Public Flags As List(Of String)

    'To_UDC will convert a UD component to its UDC representation (UniDriver Config file)
    Public Overridable Function To_UDC() As String
        Dim output As String = ""
        output += ("=" + Path + "\n")
        output += (":" + Type + "\n")
        output += "~"
        For Each flag As String In Flags
            output += (flag + "|")
        Next
        output = output.Remove(output.Length) 'we remove the last | which is unwanted to build the config file
        output += "\n"

        Return output
    End Function
End Class