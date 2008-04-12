#include "PageExplorer.h"
#include "ExplorerFrm.h"

IMPLEMENT_APP(PageExplorer)

/**
 * Function that is called when the application is started.
 */
bool PageExplorer::OnInit()
{
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
