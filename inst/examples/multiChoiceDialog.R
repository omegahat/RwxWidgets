wxCANCEL =  0x00000010
wxOK =  0x00000004
wxSYSTEM_MENU = 0x0800
wxCLOSE_BOX = 0x1000

wxDEFAULT_DIALOG_STYLE = bitlist(wxCAPTION, wxSYSTEM_MENU, wxCLOSE_BOX)
wxCHOICEDLG_STYLE = bitlist(wxDEFAULT_DIALOG_STYLE, wxOK , wxCANCEL , wxCENTRE)

dlg = wxMultiChoiceDialog(NULL, "Select an item", "my caption", LETTERS)
status = dlg$ShowModal()

print(dlg$GetSelections())

    
