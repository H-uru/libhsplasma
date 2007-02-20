#ifndef _WXAGEMAKERFRAME_H
#define _WXAGEMAKERFRAME_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/propdev.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>
#include <wx/glcanvas.h>
#include <wx/treectrl.h>

static const wxChar* enPageTypes[] = {
    "Normal", "Global", "AgeGlobal", NULL
};
static const long evPageTypes[] = {
    0, 4, 8
};

class wxAgeMakerFrame : public wxFrame {
private:
    wxStatusBar* statBar;
    wxGLCanvas* glc;
    wxPropertyGridManager* props;
    wxTreeCtrl* objTree;
    
public:
    wxAgeMakerFrame(wxApp* owner);
};

#endif
