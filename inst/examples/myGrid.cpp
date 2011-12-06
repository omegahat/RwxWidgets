#include "wx/wx.h"
#include "wx/grid.h"
#include "wx/frame.h"

class GridApp : public wxApp
{
public:
    bool OnInit();
};

IMPLEMENT_APP( GridApp )

bool GridApp::OnInit()
{
    wxFrame *frame = new  wxFrame( (wxFrame *)NULL, wxID_ANY, _T("wxWidgets grid class demo"),
                                   wxDefaultPosition,
                                   wxDefaultSize );

    wxGrid *grid = new wxGrid(frame,
                               wxID_ANY,
                               wxPoint( 0, 0 ),
                               wxSize( 400, 300 ) );

    grid->CreateGrid( 100, 80);
//    grid->SetCellValue( 50, 12, _T("Blah") );

    frame->SetAutoLayout(true);
    frame->Show(true);

    return true;
}

