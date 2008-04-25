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
    
    if (argc < 2) {
        wxFileDialog* ofd = new wxFileDialog(NULL, wxT("Choose a file"), wxEmptyString, wxEmptyString,
                                wxT("Plasma Registry Pages (*.prp)|*.prp"), wxFD_OPEN, wxDefaultPosition);
        if (ofd->ShowModal() == wxID_CANCEL) {
            delete ofd;
            return false;
        }
        frame->SetPlasmaPage(ofd->GetPath());
        delete ofd;
    } else {
        frame->SetPlasmaPage(argv[1]);
	}
    
    SetTopWindow(frame);
    frame->Show();
    return true;
}

/**
 * Function that is called when the application is exiting.
 */
int PageExplorer::OnExit()
{
    return 0;
}
