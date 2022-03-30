Imports Microsoft.VisualBasic

Public MustInherit Class Component
    Protected Path As String
    Protected Type As UInteger
    Protected Flags As List(Of String)

    Public Function To_string() As String
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