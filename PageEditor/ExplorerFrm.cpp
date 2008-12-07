///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  7 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ExplorerFrm.h"
#include <wx/imaglist.h>

///////////////////////////////////////////////////////////////////////////

ExplorerFrm::ExplorerFrm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxFrame( parent, id, title, pos, size, style, name )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    this->SetExtraStyle( wxFRAME_EX_METAL );
    wxInitAllImageHandlers();

    m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL|wxTB_TEXT, ID_TOOLBAR );
    m_toolBar->AddTool( ID_TB_SAVE, wxT("Save"), wxArtProvider::GetBitmap(wxART_FILE_SAVE), wxNullBitmap, wxITEM_NORMAL, wxT("Commit PRC edits to file"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_OPEN, wxT("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), wxNullBitmap, wxITEM_NORMAL, wxT("Load .age or .prp files"), wxEmptyString );
    m_toolBar->AddTool( ID_TB_SAVE_FILE, wxT("Save PRC"), wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS), wxNullBitmap, wxITEM_NORMAL, wxT("Save the current PRC to a file"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_NEW, wxT("New"), wxArtProvider::GetBitmap(wxART_NEW), wxNullBitmap, wxITEM_NORMAL, wxT("Add a new object"), wxEmptyString );
    m_toolBar->AddTool( ID_TB_BACK, wxT("Back"), wxArtProvider::GetBitmap(wxART_GO_BACK), wxNullBitmap, wxITEM_NORMAL, wxT("Go to the previously viewed object"), wxEmptyString );
    m_toolBar->AddTool( ID_TB_FORWARD, wxT("Forward"), wxArtProvider::GetBitmap(wxART_GO_FORWARD), wxNullBitmap, wxITEM_NORMAL, wxT("Go to the next viewed object"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_INDEXNAMES, wxT("Show Indices"), wxArtProvider::GetBitmap(wxART_TIP, wxART_OTHER, wxSize(16, 16)), wxNullBitmap, wxITEM_CHECK, wxT("Show/Hide the Class Indices in the treeview"), wxEmptyString );
    m_toolBar->Realize();
    
    m_toolBar->EnableTool(ID_TB_BACK, false);
    m_toolBar->EnableTool(ID_TB_FORWARD, false);
    m_toolBar->EnableTool(ID_TB_NEW, false);
    m_toolBar->EnableTool(ID_TB_SAVE_FILE, false);
    m_toolBar->EnableTool(ID_TB_SAVE, false);

    wxBoxSizer* bSizer;
    bSizer = new wxBoxSizer( wxVERTICAL );

    m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE );
    m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( ExplorerFrm::m_splitterOnIdle ), NULL, this );
    m_panelLeft = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* panelLeft_Sizer;
    panelLeft_Sizer = new wxBoxSizer( wxVERTICAL );

    m_prpTree = new wxTreeCtrl( m_panelLeft, ID_TREEVIEW, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_SINGLE|wxFULL_REPAINT_ON_RESIZE|wxRAISED_BORDER );
    panelLeft_Sizer->Add( m_prpTree, 1, wxALL|wxEXPAND, 3 );

    wxImageList* iml_prpTree = new wxImageList(16, 16);
    iml_prpTree->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
    iml_prpTree->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));
    iml_prpTree->Add(wxArtProvider::GetBitmap(wxART_GO_HOME, wxART_OTHER, wxSize(16, 16)));
    m_prpTree->SetImageList(iml_prpTree);

    m_panelLeft->SetSizer( panelLeft_Sizer );
    m_panelLeft->Layout();
    panelLeft_Sizer->Fit( m_panelLeft );
    m_panelRight = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* panelRight_Sizer;
    panelRight_Sizer = new wxBoxSizer( wxVERTICAL );

    m_notebook = new wxNotebook( m_panelRight, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
    m_panelPRC = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* panelPRC_Sizer;
    panelPRC_Sizer = new wxBoxSizer( wxVERTICAL );

    m_prcEditor = new wxPlasmaTextCtrl( m_panelPRC, ID_EDITOR);
    m_prcEditor->SetSyntaxMode(wxPlasmaTextCtrl::kSynXML);
    m_prcEditor->SetReadOnly(true);
    panelPRC_Sizer->Add( m_prcEditor, 1, wxALL|wxEXPAND, 1 );

    m_panelPRC->SetSizer( panelPRC_Sizer );
    m_panelPRC->Layout();
    panelPRC_Sizer->Fit( m_panelPRC );
    m_notebook->AddPage( m_panelPRC, wxT("PRC"), true );
    
    m_panelHEX = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* panelHEX_Sizer;
    panelHEX_Sizer = new wxBoxSizer( wxVERTICAL );
    
    m_hexCtrl = new CHexEditCtrl(m_panelHEX, ID_HEXVIEW);
    m_hexCtrl->SetReadOnly(true);
    panelHEX_Sizer->Add( m_hexCtrl, 1, wxALL|wxEXPAND, 1 );

    m_panelHEX->SetSizer( panelHEX_Sizer );
    m_panelHEX->Layout();
    panelHEX_Sizer->Fit( m_panelHEX );
    m_notebook->AddPage( m_panelHEX, wxT("HEX"), false );

    panelRight_Sizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );

    m_panelRight->SetSizer( panelRight_Sizer );
    m_panelRight->Layout();
    panelRight_Sizer->Fit( m_panelRight );
    m_splitter->SplitVertically( m_panelLeft, m_panelRight, 0 );
    bSizer->Add( m_splitter, 1, wxEXPAND, 5 );

    this->SetSizer( bSizer );
    this->Layout();

    // Connect Events
    this->Connect( ID_TB_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePage ) );
    this->Connect( ID_TB_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::OpenBrowser ) );
    this->Connect( ID_TB_SAVE_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePrcFile ) );
    this->Connect( ID_TB_BACK, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::GoBack ) );
    this->Connect( ID_TB_INDEXNAMES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::RedrawTree ) );
    m_prpTree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( ExplorerFrm::LoadObjPrc ), NULL, this );
}

ExplorerFrm::~ExplorerFrm()
{
    // Disconnect Events
    this->Disconnect( ID_TB_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePage ) );
    this->Disconnect( ID_TB_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::OpenBrowser ) );
    this->Disconnect( ID_TB_SAVE_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePrcFile ) );
    this->Disconnect( ID_TB_INDEXNAMES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::RedrawTree ) );
    m_prpTree->Disconnect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( ExplorerFrm::LoadObjPrc ), NULL, this );

    delete m_prpTree->GetImageList();
    m_prpTree->SetImageList(NULL);
}

void ExplorerFrm::InitFromFile( const wxString& filename)
{
    pages.clear();
    fBack.clear();
    m_prcEditor->ClearAll();
    m_prpTree->DeleteAllItems();
    m_prcEditor->SetReadOnly(true);
    fCurrent = NULL;

    try {
        if (plString(filename.ToUTF8()).afterFirst('.') == "age") {
            plAgeInfo* age = rm.ReadAge(filename.ToUTF8(), true);
            fRoot = m_prpTree->AddRoot(wxString::FromUTF8(age->getAgeName().cstr()), 2, 2, new PlasmaTreeItem(age));
            for (unsigned int i=0; i<age->getNumPages(); i++) {
                plPageInfo* page = rm.FindPage(age->getPageLoc(i, rm.getVer()));
                pages.push_back(page);
            }
            for (unsigned int j=0; j<age->getNumCommonPages(rm.getVer()); j++) {
                plPageInfo* page = rm.FindPage(age->getCommonPageLoc(j, rm.getVer()));
                pages.push_back(page);
            }
        }
        else if (plString(filename.ToUTF8()).afterFirst('.') == "prp") {
            plPageInfo* page = rm.ReadPage(filename.ToUTF8());
            pages.push_back(page);
            plAgeInfo* age = rm.FindAge(page->getAge());
            if(age)
                fRoot = m_prpTree->AddRoot(wxString::FromUTF8(age->getAgeName().cstr()), 2, 2, new PlasmaTreeItem(age));
            else
                fRoot = m_prpTree->AddRoot(wxString::FromUTF8(page->getAge().cstr()), 2, 2);
        }
    } catch (const hsException& e) {
        plDebug::Error("%s:%lu: %s", e.File(), e.Line(), e.what());
        return;
    } catch (const std::exception& e) {
        plDebug::Error("%s", e.what());
        return;
    } catch (...) {
        plDebug::Error("Undefined error!");
        return;
    }
    
    m_toolBar->EnableTool(ID_TB_SAVE, true);

    fPath = plString(wxPathOnly(filename).ToUTF8());
    plDebug::Error("Path is %s", fPath.cstr());

    for(unsigned int j=0; j<pages.size();j++) {
        this->LoadObjects(pages[j]);
    }
}

void ExplorerFrm::LoadObjects(plPageInfo* page)
{
    plString PageName;
    if(m_toolBar->GetToolState( ID_TB_INDEXNAMES )) {
        PageName = plString::Format("%s %s", page->getLocation().toString().cstr(), page->getPage().cstr());
    } else {
        PageName = page->getPage();
    }
    wxTreeItemId fPageN = m_prpTree->AppendItem(fRoot, wxString::FromUTF8(PageName.cstr()), 0, 0, new PlasmaTreeItem(page));
    std::vector<short> types = rm.getTypes(page->getLocation());

    for(unsigned int f = 0; f < types.size(); f++) {
        plString TypeName;
        if(m_toolBar->GetToolState( ID_TB_INDEXNAMES )) {
            TypeName = plString::Format("<%04hX> %s", types[f], pdUnifiedTypeMap::ClassName(types[f]));
        } else {
            plString className = pdUnifiedTypeMap::ClassName(types[f]);
            if(className.startsWith("hsg", true)) className = className.mid(3);
            if(className.startsWith("hsG", true)) className = className.mid(3);
            if(className.startsWith("plg", false)) className = className.mid(3);
            if(className.startsWith("pl", false)) className = className.mid(2);
            if(className.startsWith("hs", false)) className = className.mid(2);
            if(className.startsWith("pf", false)) className = className.mid(2);
            TypeName = plString::Format("%s", className.cstr());
        }
        wxTreeItemId fType = m_prpTree->AppendItem(fPageN, wxString::FromUTF8(TypeName.cstr()), 0, 0, new PlasmaTreeItem(types[f]));

        std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);

        for(unsigned int ks = 0; ks < mykeys.size(); ks++) {
            wxTreeItemId keykey = m_prpTree->AppendItem(fType, wxString::FromUTF8(mykeys[ks]->getName().cstr()), 1, 1, new PlasmaTreeItem(mykeys[ks]));
        }

        m_prpTree->SortChildren(fType);
    }
    
    m_prpTree->SortChildren(fPageN);

    m_prpTree->SortChildren(fRoot);
}

void ExplorerFrm::OpenBrowser( wxCommandEvent& event )
{
    wxFileDialog* ofd = new wxFileDialog(NULL, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("Plasma Age and Page files (*.age, *.prp)|*.age;*.prp"), wxFD_OPEN, wxDefaultPosition);
    if (ofd->ShowModal() == wxID_CANCEL) {
        delete ofd;
        return;
    }
    wxString filename = ofd->GetPath();
    delete ofd;

    this->InitFromFile(filename);
}

void ExplorerFrm::LoadObjPrc(wxTreeEvent& event)
{
    m_prcEditor->SetReadOnly(false);
    wxTreeItemId fID = event.GetItem();

    PlasmaTreeItem* data = (PlasmaTreeItem*)m_prpTree->GetItemData(fID);
    if (data == NULL)
        return;
        
    hsRAMStream* S = new hsRAMStream(rm.getVer());
    pfPrcHelper* prc = new pfPrcHelper(S);
    
    if (data->getObject()) {
        plKey fKey = data->getObject();
        
        hsRAMStream* HS = new hsRAMStream(rm.getVer());
        
        hsKeyedObject* fObj = rm.getObject(fKey);

        if (fObj != NULL) {
            try {
                fObj->prcWrite(prc);
                fObj->write(HS, &rm);
                
                hsUint32 size = HS->size();
                wxByte* dat = new wxByte[size + 1];
                HS->copyTo((void*&)dat, size);
                dat[size] = 0;
                
                m_hexCtrl->SetData(dat, size);
            } catch (hsException& e) {
                plString msg = plString::Format("%s:%lu: %s", e.File(), e.Line(), e.what());
                wxMessageBox(wxString(msg, wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR, this);
            } catch (std::exception& e) {
                plString msg = plString::Format("%s", e.what());
                wxMessageBox(wxString(msg, wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR, this);
            }
        } else {
            plString s = plString::Format("An error occurred reading [%04hX]%s.  Check the logs for details.",
                                          fKey->getType(), fKey->getName().cstr());
            prc->writeComment(s);
        }

    } else if (data->getAge() != NULL) {
        plAgeInfo* age = data->getAge();

        if(age != NULL) {
            rm.WriteAgePrc(prc, age);
        } else {
            plString s = plString::Format("An error occurred reading %s.  Check the logs for details.",
                                          age->getAgeName().cstr());
            prc->writeComment(s);
        }
    } else if (data->getClass() != 0xFFFF) {
        m_prpTree->SelectItem(fCurrent, true);
        return;
    } else {
        plString s = plString::Format("An error occurred reading your selection.  Check the logs for details.");
        prc->writeComment(s);
    }
    
    m_prcEditor->ClearAll();
    
    hsUint32 size = S->size();
    char* junk = new char[size + 1];
    S->copyTo((void*&)junk, size);
    junk[size] = 0;

    m_prcEditor->SetText(wxString::FromUTF8(junk));
    fBack.push_back(fCurrent);

    fCurrent = fID;
    delete[] junk;

    delete prc;
    delete S;
    
    if(fBack.size() >= 1)
        m_toolBar->EnableTool(ID_TB_BACK, true);
    m_toolBar->EnableTool(ID_TB_SAVE_FILE, true);
}

void ExplorerFrm::SavePrcFile( wxCommandEvent& event )
{
    if(m_prcEditor->GetLineCount()) {
        wxFileDialog* sfd = new wxFileDialog(NULL, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("Plasma Resource file (*.prc)|*.prc"), wxFD_SAVE, wxDefaultPosition);
        if (sfd->ShowModal() == wxID_CANCEL) {
            delete sfd;
            return;
        }
        wxString filename = sfd->GetPath();
        delete sfd;

        m_prcEditor->SaveFile(filename);
    }
}

void ExplorerFrm::SavePage( wxCommandEvent& event )
{
    PlasmaTreeItem* data = (PlasmaTreeItem*)m_prpTree->GetItemData(fCurrent);
    if(data == NULL) return;
    
    if(m_prcEditor->GetText().IsEmpty()) return;
    
    wxString wTxt = m_prcEditor->GetText();
    plString txt = plString(wTxt.ToUTF8());
    hsRAMStream* S = new hsRAMStream(rm.getVer());
    S->copyFrom((const void*)txt.cstr(), txt.len());
    
    pfPrcParser prc;
    prc.read(S);
    const pfPrcTag* root = prc.getRoot();
    
    if (data->getObject()) {
        plKey fKey = data->getObject();
        
        data = new PlasmaTreeItem(plKey());
        rm.DelObject(fKey);
        hsKeyedObject* obj = hsKeyedObject::Convert(rm.prcParseCreatable(root));
        if (obj != NULL) {
            plPageInfo* page = rm.FindPage(obj->getKey()->getLocation());
            if(page) {
                data = new PlasmaTreeItem(obj->getKey());
                rm.AddObject(obj->getKey()->getLocation(), obj);
                m_prpTree->SetItemText(fCurrent, wxString(obj->getKey()->getName().cstr(), wxConvUTF8));
                
                rm.WritePage(fPath + PATHSEP + page->getFilename(rm.getVer()), page);
            } else {
                m_prpTree->Delete(fCurrent);
                //Invalid Location specified (page not loaded)
            }
        } else {
            m_prpTree->Delete(fCurrent);
        }
    } else if (data->getAge() != NULL) {
        plAgeInfo* age = data->getAge();
        
        if(age != NULL) {
            age->prcParse(root);
            rm.WriteAge(fPath + PATHSEP + plString::Format("%s.age", age->getAgeName().cstr()), age);
        }
    } else {
        return;
    }
    
    wxTreeEvent treeEvt;
    treeEvt.SetItem(fCurrent);
    LoadObjPrc(treeEvt);
}

void ExplorerFrm::GoBack( wxCommandEvent& event )
{
    if(fBack.size() <= 0)
       return;

    wxTreeItemId fID = fBack.back();

    if(fID) {
        fBack.pop_back();
        
        fCurrent = NULL;

        wxTreeEvent t = wxTreeEvent(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, m_prpTree, fID);
        this->LoadObjPrc(t);
    }
}

void ExplorerFrm::RedrawTree( wxCommandEvent& event )
{
    if(fRoot && m_prpTree->ItemHasChildren(fRoot))
    {
        //Handle the pages
        wxTreeItemIdValue Pages;
        
        wxTreeItemId item = m_prpTree->GetFirstChild(fRoot, Pages);
        
        while( item.IsOk() )
        {
            PlasmaTreeItem* pti = (PlasmaTreeItem*)m_prpTree->GetItemData(item);
            
            if (pti->getPage() == NULL) {
                //Something blew up...
                item = m_prpTree->GetNextChild(fRoot, Pages);
                continue;
            }
            
            plString PageName;
            if(m_toolBar->GetToolState( ID_TB_INDEXNAMES )) {
                PageName = plString::Format("%s %s", pti->getPage()->getLocation().toString().cstr(), pti->getPage()->getPage().cstr());
            } else {
                PageName = pti->getPage()->getPage();
            }
            
            m_prpTree->SetItemText(item, wxString::FromUTF8(PageName.cstr()));
            wxTreeItemIdValue Types;
            
            wxTreeItemId child = m_prpTree->GetFirstChild(item, Types);
            
            while( child.IsOk() )
            {
                PlasmaTreeItem* cti = (PlasmaTreeItem*)m_prpTree->GetItemData(child);
                
                if (cti->getClass() == 0xFFFF) {
                    child = m_prpTree->GetNextChild(item, Types);
                    continue;
                }
                
                plString TypeName;
                if(m_toolBar->GetToolState( ID_TB_INDEXNAMES )) {
                    TypeName = plString::Format("<%04hX> %s", cti->getClass(), pdUnifiedTypeMap::ClassName(cti->getClass()));
                } else {
                    plString className = pdUnifiedTypeMap::ClassName(cti->getClass());
                    if(className.startsWith("hsg", true)) className = className.mid(3);
                    if(className.startsWith("plg", false)) className = className.mid(3);
                    if(className.startsWith("pl", false)) className = className.mid(2);
                    if(className.startsWith("hs", false)) className = className.mid(2);
                    if(className.startsWith("pf", false)) className = className.mid(2);
                    TypeName = plString::Format("%s", className.cstr());
                }
                
                m_prpTree->SetItemText(child, wxString::FromUTF8(TypeName.cstr()));
                
                child = m_prpTree->GetNextChild(item, Types);
            }
            
            m_prpTree->SortChildren(item);
            
            item = m_prpTree->GetNextChild(fRoot, Pages);
        }
    }
    
    m_prpTree->SortChildren(fRoot);
}
