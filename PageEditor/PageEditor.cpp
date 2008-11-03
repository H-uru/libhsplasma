#include <stdlib.h>

#include "PageEditor.h"
#include "ExplorerFrm.h"
#include <wx/filename.h>

IMPLEMENT_APP(PageEditor)

/**
 * Function that is called when the application is started.
 */
bool PageEditor::OnInit()
{
    plDebug::InitFile(plDebug::kDLAll);

    ExplorerFrm* frame = new ExplorerFrm(NULL);

    if(1 < argc) {
        wxString filename = argv[1];
        frame->InitFromFile(filename);
    }

    SetTopWindow(frame);
    frame->Show();
    return true;
}

/**
 * Function that is called when the application is exiting.
 */
int PageEditor::OnExit()
{
    return 0;
}
