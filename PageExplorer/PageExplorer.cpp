#include <stdlib.h>

#include "PageExplorer.h"
#include "ExplorerFrm.h"
#include <wx/filename.h>

IMPLEMENT_APP(PageExplorer)

/**
 * Function that is called when the application is started.
 */
bool PageExplorer::OnInit()
{
    wxFileName logPath(wxPathOnly(argv[0]), wxT("Plasma.log"));
    plDebug::InitFile(plDebug::kDLAll, logPath.GetFullPath().mb_str(wxConvFile));

    ExplorerFrm* frame = new ExplorerFrm(NULL);
    
    bool dumpPages = false;
    bool gui = true;
    int curArg = 1;
    wxString filename = wxT("");
    while (curArg < argc) {
		if(!wxString(wxT("-dump")).Cmp(argv[curArg]))
			dumpPages = true;
		else if(!wxString(wxT("-nogui")).Cmp(argv[curArg]))
			gui = false;
		else break;
		curArg++;
	}
	if(curArg < argc)
		filename = argv[curArg];
	else
	{
        wxFileDialog* ofd = new wxFileDialog(NULL, wxT("Choose a file"), wxEmptyString, wxEmptyString,
                                wxT("Plasma Registry Pages (*.prp)|*.prp"), wxFD_OPEN, wxDefaultPosition);
        if (ofd->ShowModal() == wxID_CANCEL) {
            delete ofd;
            return false;
        }
		filename = ofd->GetPath();
        delete ofd;
    }
    frame->SetPlasmaPage(filename);
    if(dumpPages)
		frame->SaveKeys(filename + wxT(".xml"));
	if(gui) {
		SetTopWindow(frame);
		frame->Show();
	}
	else frame->Close();
    return true;
}

/**
 * Function that is called when the application is exiting.
 */
int PageExplorer::OnExit()
{
    return 0;
}
