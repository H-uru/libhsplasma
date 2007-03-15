#include "wxAgeMakerFrame.h"
#include "PubUtilLib/plResMgr/plResManager.h"
#include "PubUtilLib/plScene/plSceneNode.h"
#include <GL/gl.h>

wxAgeMakerFrame::wxAgeMakerFrame(wxApp* creator)
    : wxFrame(NULL, -1, "AgeMaker", wxDefaultPosition, wxSize(800, 600)) {
    owner = creator;
    wxFlexGridSizer* sz1 = new wxFlexGridSizer(1, 2, 0, 4);
    //sz1->AddGrowableCol(0);
    sz1->AddGrowableCol(1);
    sz1->AddGrowableRow(0);
    sz1->SetFlexibleDirection(wxBOTH);
    
    wxFlexGridSizer* sz2 = new wxFlexGridSizer(2, 1, 4, 0);
    sz2->AddGrowableCol(0);
    sz2->AddGrowableRow(0);
    sz2->AddGrowableRow(1);
    sz2->SetFlexibleDirection(wxBOTH);

    objTree = new wxTreeCtrl(this);
    objTree->SetMinSize(wxSize(200, 200));
    sz2->Add(objTree, 1, wxEXPAND, 0);
    props = new wxPropertyGridManager(this, -1, wxDefaultPosition, wxSize(200, -1),
                                      wxPGMAN_DEFAULT_STYLE | wxPG_AUTO_SORT |
                                      wxPG_TOOLBAR | wxPG_DESCRIPTION);
    props->SetMinSize(wxSize(200, 200));
    sz2->Add(props, 1, wxEXPAND, 0);
    
    sz1->Add(sz2, 1, wxEXPAND, 0);
    glc = new wxGLCanvas(this, -1, wxDefaultPosition, wxSize(200, -1));
    //glc->SetMinSize(wxSize(400, 400));
#if wxCHECK_VERSION(2, 7, 0)
    wxGLContext(glc).SetCurrent(*glc);
#else
    glc->SetCurrent();
#endif
    sz1->Add(glc, 1, wxEXPAND, 0);
    
    statBar = new wxStatusBar(this, -1, wxST_SIZEGRIP, "statBar");
    SetStatusBar(statBar);
    SetStatusText("Blah");
    
    SetSizerAndFit(sz1);
    
    glc->SwapBuffers();
    if (owner->argc > 1 && wxFileExists(owner->argv[1])) {
        plResManager rm;
        plPageInfo* page = rm.ReadPage(owner->argv[1]);
        wxTreeItemId tidPage = objTree->AppendItem(objTree->AddRoot(page->getAge()), page->getPage());
        plSceneNode* sn = rm.getSceneNode(page->getLocation());
        if (sn != NULL) {
            for (int i=0; i<sn->SceneObjects.getSize(); i++)
                objTree->AppendItem(tidPage, wxT(sn->SceneObjects[i]->getName()));
            for (int j=0; j<sn->OtherObjects.getSize(); j++)
                objTree->AppendItem(tidPage, wxT(sn->OtherObjects[j]->getName()));
        }
    
        props->AddPage("Alphabetical");
        props->Append(wxPropertyCategory("Page Settings"));
        props->Append(wxStringProperty("Page ID", "The PageID", wxT(page->getLocation().toString())));
        props->Append(wxEnumProperty("Page Type", "Flags",
            enPageTypes, evPageTypes, page->getLocation().flags));
        props->Append(wxStringProperty("Age Name", wxPG_LABEL, wxT(page->getAge())));
        props->Append(wxStringProperty("Page Name", wxPG_LABEL, wxT(page->getPage())));
    }
}

