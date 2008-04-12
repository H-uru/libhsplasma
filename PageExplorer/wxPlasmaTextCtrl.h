#ifndef _WXPLASMATEXTCTRL_H
#define _WXPLASMATEXTCTRL_H

/****
 * wxPlasmaTextCtrl
 * (c) 2008 Michael Hansen
 * Insert GPL stuff here...
 ****/

#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/stc/stc.h>

class wxPlasmaTextCtrl : public wxStyledTextCtrl {
public:
    enum SyntaxMode {
        kSynNone, kSynXML
    };

    wxPlasmaTextCtrl(wxWindow* parent, wxWindowID id=wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize, long style = 0,
                     const wxString& name = wxSTCNameStr);
    ~wxPlasmaTextCtrl();

    void SetSyntaxMode(SyntaxMode mode);
    SyntaxMode GetSyntaxMode();

protected:
    enum { kMarginUNUSED, kMarginLineNumbers, kMarginFolders };
    unsigned int fLineNumberWidth;
    SyntaxMode fSyntaxMode;
    wxFont fFont;

    void ResetSyntax();
    void UpdateLineNumberWidth();

protected:
    DECLARE_EVENT_TABLE()

    void OnMarginClick(wxStyledTextEvent& evt);
    void OnUpdateUI(wxStyledTextEvent& evt);
    void OnModified(wxStyledTextEvent& evt);
    void OnZoom(wxStyledTextEvent& evt);
};

#endif
