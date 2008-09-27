#ifndef __PAGEEXPLORER_h__
#define __PAGEEXPLORER_h__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#else
    #include <wx/wxprec.h>
#endif

#include <wx/filedlg.h>

class PageEditor : public wxApp
{
    public:
        bool OnInit();
        int OnExit();
};

#endif
