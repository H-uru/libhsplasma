#include "wxPlasmaTextCtrl.h"

/* wxPlasmaTextCtrl */
BEGIN_EVENT_TABLE(wxPlasmaTextCtrl, wxStyledTextCtrl)
    EVT_STC_MARGINCLICK(wxID_ANY, wxPlasmaTextCtrl::OnMarginClick)
    EVT_STC_UPDATEUI(wxID_ANY, wxPlasmaTextCtrl::OnUpdateUI)
    EVT_STC_MODIFIED(wxID_ANY, wxPlasmaTextCtrl::OnModified)
    EVT_STC_ZOOM(wxID_ANY, wxPlasmaTextCtrl::OnZoom)
END_EVENT_TABLE()

wxPlasmaTextCtrl::wxPlasmaTextCtrl(wxWindow* parent, wxWindowID id,
                                   const wxPoint& pos, const wxSize& size,
                                   long style, const wxString& name)
    : wxStyledTextCtrl(parent, id, pos, size, style, name)
{
    SetMarginWidth(kMarginLineNumbers, 0);
    SetMarginType(kMarginLineNumbers, wxSTC_MARGIN_NUMBER);
    SetMarginWidth(kMarginFolders, 12);
    SetMarginType(kMarginFolders, wxSTC_MARGIN_SYMBOL);
    SetMarginMask(kMarginFolders, wxSTC_MASK_FOLDERS);
    SetMarginSensitive(kMarginFolders, true);
    SetFoldFlags(wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

    MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNER, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));
    MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUSCONNECTED, wxColour(0xFF, 0xFF, 0xFF), wxColour(0, 0, 0));

    SetProperty(wxT("fold"), wxT("1"));
    SetProperty(wxT("fold.compact"), wxT("0"));
    SetProperty(wxT("fold.at.else"), wxT("1"));
    SetProperty(wxT("fold.html"), wxT("1"));

    SetIndent(4);
    SetTabWidth(4);
    SetViewWhiteSpace(false);

#if defined(wxSTC_VERSION) && (wxSTC_VERSION >= 175)
    SetScrollWidth(800);
    SetScrollWidthTracking(true);
#endif

#if defined(__WXMSW__)
    fFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
#elif defined(__WXMAC__)
    fFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_NORMAL, false, wxT("Courier"));
#else /* Linux, UNIX, OSX, etc */
    fFont = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_NORMAL, false, wxT("Monospace"));
#endif

    SetSyntaxMode(kSynNone);
}

wxPlasmaTextCtrl::~wxPlasmaTextCtrl()
{ }

void wxPlasmaTextCtrl::ResetSyntax()
{
    StyleResetDefault();
    StyleSetFaceName(wxSTC_STYLE_DEFAULT, fFont.GetFaceName());
    StyleSetSize(wxSTC_STYLE_DEFAULT, fFont.GetPointSize());
    StyleSetForeground(wxSTC_STYLE_BRACEBAD, wxColour(0xFF, 0, 0));
    StyleSetFontAttr(wxSTC_STYLE_BRACEBAD, fFont.GetPointSize(), fFont.GetFaceName(), true, false, false);
    StyleSetForeground(wxSTC_STYLE_BRACELIGHT, wxColour(0, 0, 0xC0));
    StyleSetFontAttr(wxSTC_STYLE_BRACELIGHT, fFont.GetPointSize(), fFont.GetFaceName(), true, false, false);
    UpdateLineNumberWidth();
}

void wxPlasmaTextCtrl::SetSyntaxMode(SyntaxMode mode) {
    switch (mode) {
    case kSynNone:
        ResetSyntax();
        SetLexer(wxSTC_LEX_NULL);
        break;
    case kSynXML:
        ResetSyntax();
        SetLexer(wxSTC_LEX_XML);
        StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour(0, 0x80, 0));
        StyleSetForeground(wxSTC_H_COMMENT, wxColour(0x80, 0x80, 0x80));
        StyleSetFontAttr(wxSTC_H_COMMENT, fFont.GetPointSize(), fFont.GetFaceName(), false, true, false);
        StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour(0x80, 0, 0));
        StyleSetForeground(wxSTC_H_NUMBER, wxColour(0, 0, 0xFF));
        StyleSetForeground(wxSTC_H_SINGLESTRING, wxColour(0x80, 0, 0));
        StyleSetForeground(wxSTC_H_TAG, wxColour(0, 0, 0x80));
        StyleSetFontAttr(wxSTC_H_TAG, fFont.GetPointSize(), fFont.GetFaceName(), true, false, false);
        StyleSetForeground(wxSTC_H_TAGEND, wxColour(0, 0, 0x80));
        StyleSetFontAttr(wxSTC_H_TAGEND, fFont.GetPointSize(), fFont.GetFaceName(), true, false, false);
        StyleSetForeground(wxSTC_H_XMLSTART, wxColour(0x80, 0x80, 0));
        StyleSetForeground(wxSTC_H_XMLEND, wxColour(0x80, 0x80, 0));
        break;
    }

    fSyntaxMode = mode;
}

wxPlasmaTextCtrl::SyntaxMode wxPlasmaTextCtrl::GetSyntaxMode()
{
    return fSyntaxMode;
}

void wxPlasmaTextCtrl::UpdateLineNumberWidth()
{
    wxString lnLast = wxString::Format(wxT(" %d"), GetLineCount());
    int lnWidth = TextWidth(wxSTC_STYLE_LINENUMBER, lnLast);
    SetMarginWidth(kMarginLineNumbers, lnWidth);
}

void wxPlasmaTextCtrl::OnMarginClick(wxStyledTextEvent& evt)
{
    switch (evt.GetMargin()) {
    case kMarginFolders:
        ToggleFold(LineFromPosition(evt.GetPosition()));
        break;
    }
}

void wxPlasmaTextCtrl::OnUpdateUI(wxStyledTextEvent& evt)
{
    int nextCh = GetCharAt(GetCurrentPos());
    int lastCh = GetCharAt(GetCurrentPos() - 1);
    if (strchr("()[]{}", nextCh)) {
        int brace = BraceMatch(GetCurrentPos());
        if (brace >= 0)
            BraceHighlight(brace, GetCurrentPos());
        else
            BraceBadLight(GetCurrentPos());
    } else if (strchr("()[]{}", lastCh)) {
        int brace = BraceMatch(GetCurrentPos() - 1);
        if (brace >= 0)
            BraceHighlight(brace, GetCurrentPos() - 1);
        else
            BraceBadLight(GetCurrentPos() - 1);
    } else {
        BraceHighlight(-1, -1);
    }
}

void wxPlasmaTextCtrl::OnModified(wxStyledTextEvent& evt)
{
    UpdateLineNumberWidth();
}

void wxPlasmaTextCtrl::OnZoom(wxStyledTextEvent& evt)
{
    UpdateLineNumberWidth();
}
