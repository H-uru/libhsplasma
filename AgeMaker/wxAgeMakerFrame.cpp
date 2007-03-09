#include "wxAgeMakerFrame.h"
#include "PubUtilLib/plResMgr/plResManager.h"
#include "PubUtilLib/plScene/plSceneNode.h"
#include <GL/gl.h>

wxAgeMakerFrame::wxAgeMakerFrame(wxApp* owner)
               : wxFrame((wxFrame*)NULL, -1, "AgeMaker") {
    wxFlexGridSizer* sz1 = new wxFlexGridSizer(1, 2, 0, 4);
    
    wxFlexGridSizer* sz2 = new wxFlexGridSizer(2, 1, 4, 0);
    objTree = new wxTreeCtrl(this);
    objTree->SetMinSize(wxSize(200, 200));
    sz2->Add(objTree);
    props = new wxPropertyGridManager(this, -1, wxDefaultPosition, wxDefaultSize,
                                      wxPGMAN_DEFAULT_STYLE | wxPG_AUTO_SORT |
                                      wxPG_SPLITTER_AUTO_CENTER | wxPG_TOOLBAR |
                                      wxPG_BOLD_MODIFIED | wxPG_DESCRIPTION);
    props->SetMinSize(wxSize(200, 200));
    sz2->Add(props);
    
    sz1->Add(sz2);
    glc = new wxGLCanvas(this, -1, wxDefaultPosition, wxDefaultSize);
    glc->SetMinSize(wxSize(400, 400));
#if wxCHECK_VERSION(2, 7, 0)
    wxGLContext(glc).SetCurrent(*glc);
#else
    glc->SetCurrent();
#endif
    sz1->Add(glc);
    sz1->AddGrowableCol(1);
    sz1->AddGrowableRow(0);
    sz1->SetFlexibleDirection(wxBOTH);
    
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

