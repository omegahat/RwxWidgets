#include <wx/filedlg.h>


class wxTestFileDialog : public wxFileDialog
{

public:

    wxTestFileDialog(wxWindow *parent)
	:    wxFileDialog(parent,
			  wxString("", wxConvUTF8),
			  wxString("", wxConvUTF8),
			  wxString("", wxConvUTF8),
			  wxString("*.*", wxConvUTF8),
			  9, wxDefaultPosition)
    {

    }

    void OnOK(wxCommandEvent &ev);
private:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxTestFileDialog, wxFileDialog)
   EVT_BUTTON(wxID_OK, wxTestFileDialog::OnOK)
END_EVENT_TABLE()
