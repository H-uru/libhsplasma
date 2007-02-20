#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxAgeMakerFrame.h"

class wxAgeMakerApp : public wxApp {
public:
    virtual bool OnInit() {
        wxAgeMakerFrame* frame = new wxAgeMakerFrame(this);
        frame->Show(true);
        SetTopWindow(frame);
        return true;
    }
};

IMPLEMENT_APP(wxAgeMakerApp)

