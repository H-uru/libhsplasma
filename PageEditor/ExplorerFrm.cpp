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
    m_toolBar->AddTool( ID_TB_SAVE, wxT("Save PRP"), wxArtProvider::GetBitmap(wxART_FILE_SAVE), wxNullBitmap, wxITEM_NORMAL, wxT("Commit PRC edits to file"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_OPEN, wxT("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN), wxNullBitmap, wxITEM_NORMAL, wxT("Load .age or .prp files"), wxEmptyString );
    m_toolBar->AddTool( ID_TB_SAVE_FILE, wxT("Save PRC"), wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS), wxNullBitmap, wxITEM_NORMAL, wxT("Save the current PRC to a file"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_BACK, wxT("Back"), wxArtProvider::GetBitmap(wxART_GO_BACK), wxNullBitmap, wxITEM_NORMAL, wxT("Go to the previously viewed object"), wxEmptyString );
    m_toolBar->AddSeparator();
    m_toolBar->AddTool( ID_TB_INDICENAMES, wxT("Show Indices"), wxArtProvider::GetBitmap(wxART_TIP), wxNullBitmap, wxITEM_CHECK, wxT("Show/Hide the Class Indices in the treeview"), wxEmptyString );
    m_toolBar->Realize();
    
    m_toolBar->EnableTool(ID_TB_BACK, false);
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
    this->Connect( ID_TB_INDICENAMES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::RedrawTree ) );
    m_prpTree->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( ExplorerFrm::LoadObjPrc ), NULL, this );
}

ExplorerFrm::~ExplorerFrm()
{
    // Disconnect Events
    this->Disconnect( ID_TB_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePage ) );
    this->Disconnect( ID_TB_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::OpenBrowser ) );
    this->Disconnect( ID_TB_SAVE_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::SavePrcFile ) );
    this->Disconnect( ID_TB_INDICENAMES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ExplorerFrm::RedrawTree ) );
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

    try {
        if (plString(filename.ToUTF8()).afterFirst('.') == "age") {
            plAgeInfo* age = rm.ReadAge(filename.ToUTF8(), true);
            fRoot = m_prpTree->AddRoot(wxString::FromUTF8(age->getAgeName().cstr()), 2, 2);
            fCurrent = fRoot;
            for (unsigned int i=0; i<age->getNumPages(); i++) {
                plPageInfo* page = rm.FindPage(age->getPageLoc(i, rm.getVer()));
                pages.push_back(page);
            }
        }
        else if (plString(filename.ToUTF8()).afterFirst('.') == "prp") {
            plPageInfo* page = rm.ReadPage(filename.ToUTF8());
            pages.push_back(page);
            fRoot = m_prpTree->AddRoot(wxString::FromUTF8(page->getAge().cstr()), 2, 2);
            fCurrent = fRoot;
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
    wxTreeItemId fPageN = m_prpTree->AppendItem(fRoot, wxString::FromUTF8(page->getPage().cstr()), 0, 0);
    std::vector<short> types = rm.getTypes(page->getLocation());

    for(unsigned int f = 0; f < types.size(); f++) {
        plString TypeName;
        if(m_toolBar->GetToolState( ID_TB_INDICENAMES )) {
            TypeName = plString::Format("[%04hX] %s", types[f], pdUnifiedTypeMap::ClassName(types[f]));
        } else {
            plString className = pdUnifiedTypeMap::ClassName(types[f]);
            if(className.startsWith("pl", false)) className = className.mid(2);
            if(className.startsWith("hs", false)) className = className.mid(2);
            if(className.startsWith("pf", false)) className = className.mid(2);
            if(className.startsWith("hsg", false)) className = className.mid(3);
            TypeName = plString::Format("%s", className.cstr());
        }
        wxTreeItemId fType = m_prpTree->AppendItem(fPageN, wxString::FromUTF8(TypeName.cstr()), 0, 0);

        std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);

        for(unsigned int ks = 0; ks < mykeys.size(); ks++) {
            m_prpTree->AppendItem(fType, wxString::FromUTF8(mykeys[ks]->getName().cstr()), 1, 1, new wxTreeKeyData(mykeys[ks]));
        }

        m_prpTree->SortChildren(fType);
    }

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

    m_prcEditor->ClearAll();

    wxTreeKeyData* KeyData = (wxTreeKeyData*)m_prpTree->GetItemData(fID);
    wxString name = m_prpTree->GetItemText(fID);

    if (KeyData) {
        plKey fKey = KeyData->getKey();

        hsKeyedObject* fObj = rm.getObject(fKey);
        hsRAMStream* S = new hsRAMStream(rm.getVer());
        pfPrcHelper* prc = new pfPrcHelper(S);

        if (fObj != NULL) {
            try {
                fObj->prcWrite(prc);
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

        hsUint32 size = S->size();
        char* data = new char[size + 1];
        S->copyTo((void*&)data, size);
        data[size] = 0;

        m_prcEditor->SetText(wxString::FromUTF8(data));
        if (fCurrent != fRoot)
            fBack.push_back(fCurrent);

        fCurrent = fID;
        delete[] data;

        delete prc;
        delete S;
    }
    
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
    wxTreeKeyData* KeyData = (wxTreeKeyData*)m_prpTree->GetItemData(fCurrent);
    if (KeyData == NULL) return;

    plKey fKey = KeyData->getKey();
    pfPrcParser prc;
    wxString wTxt = m_prcEditor->GetText();
    plString txt = plString(wTxt.ToUTF8());
    hsRAMStream* S = new hsRAMStream(rm.getVer());
    S->copyFrom((const void*)txt.cstr(), txt.len());

    prc.read(S);
    const pfPrcTag* root = prc.getRoot();

    KeyData->setKey(plKey());
    rm.DelObject(fKey);
    hsKeyedObject* obj = hsKeyedObject::Convert(rm.prcParseCreatable(root));
    if (obj != NULL) {
        KeyData->setKey(obj->getKey());
        rm.AddObject(obj->getKey()->getLocation(), obj);
        m_prpTree->SetItemText(fCurrent, wxString(obj->getKey()->getName().cstr(), wxConvUTF8));
    } else {
        m_prpTree->Delete(fCurrent);
    }

    for(unsigned int j=0; j<pages.size();j++) {
        plPageInfo* page = pages[j];
        rm.WritePage(fPath + PATHSEP + page->getFilename(rm.getVer()), page);
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
        fCurrent = fRoot;

        fBack.pop_back();

        wxTreeEvent t = wxTreeEvent(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, m_prpTree, fID);
        this->LoadObjPrc(t);
    }
}

void ExplorerFrm::RedrawTree( wxCommandEvent& event )
{
    fBack.clear();
    m_prcEditor->ClearAll();
    if(fRoot && m_prpTree->ItemHasChildren(fRoot))
        m_prpTree->DeleteChildren(fRoot);
    
    m_toolBar->EnableTool(ID_TB_BACK, false);
    m_toolBar->EnableTool(ID_TB_SAVE_FILE, false);
    
    for(unsigned int j=0; j<pages.size();j++) {
        this->LoadObjects(pages[j]);
    }
}

///////////////////////////////////////////////////////////////////////////

wxTreeKeyData::wxTreeKeyData(const plKey& key): wxTreeItemData()
{
    this->fKey = key;
}

wxTreeKeyData::~wxTreeKeyData() { }

plKey& wxTreeKeyData::getKey()
{
    return this->fKey;
}

void wxTreeKeyData::setKey(plKey key)
{
    this->fKey = key;
}
