#include "PageExplorer.h"
#include "ExplorerFrm.h"

IMPLEMENT_APP(PageExplorer)

/**
 * Function that is called when the application is started.
 */
bool PageExplorer::OnInit()
{
    ExplorerFrm* frame = new ExplorerFrm(NULL);
    
    wxFileDialog* ofd = new wxFileDialog(NULL, wxT("Choose a file"), wxT(""), wxT(""), wxT("Plasma Registry Pages (*.prp)|*.prp"), wxOPEN, wxDefaultPosition);
    
    if(ofd->ShowModal() == wxID_CANCEL) {
    	return 0;
	}
	
	wxString fPath = ofd->GetPath();
	
	frame->SetPlasmaPage(fPath);
    
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
