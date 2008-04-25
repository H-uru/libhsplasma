///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 22 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ExplorerFrm.h"

using namespace std;

BEGIN_EVENT_TABLE(ExplorerFrm,wxFrame)
	EVT_TREE_ITEM_ACTIVATED(ID_TREECTRL, ExplorerFrm::LoadPRC)
END_EVENT_TABLE()


///////////////////////////////////////////////////////////////////////////

ExplorerFrm::ExplorerFrm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
           : wxFrame( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( wxFRAME_EX_METAL );
}

ExplorerFrm::~ExplorerFrm()
{
}

void ExplorerFrm::SetPlasmaPage(const wxString& filename)
{
    try {
		page = rm.ReadPage(filename.ToUTF8());
	} catch (hsException& e) {
        plString msg = plString::Format("%s:%lu: %s", e.File(), e.Line(), e.what());
        wxMessageBox(wxString(msg, wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR, this);
		return;
	} catch (std::exception& e) {
        plString msg = plString::Format("%s", e.what());
        wxMessageBox(wxString(msg, wxConvUTF8), wxT("Error"), wxOK | wxICON_ERROR, this);
		return;
	}

	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
    m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( ExplorerFrm::m_splitterOnIdle ), NULL, this );
	m_panelLeft = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panelLeft, wxID_ANY, wxString::FromUTF8(page->getAge().cstr())), wxVERTICAL );
	
	m_treeCtrl5 = new wxTreeCtrl( m_panelLeft, ID_TREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxFULL_REPAINT_ON_RESIZE|wxRAISED_BORDER );
	sbSizer1->Add( m_treeCtrl5, 1, wxALL|wxEXPAND, 1 );
	
	bSizer5->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_panelLeft->SetSizer( bSizer5 );
	m_panelLeft->Layout();
	bSizer5->Fit( m_panelLeft );
	m_panelRight = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_output = new wxPlasmaTextCtrl( m_panelRight, ID_PRCEDIT);
    m_output->SetSyntaxMode(wxPlasmaTextCtrl::kSynXML);
    m_output->SetReadOnly(true);
	bSizer3->Add( m_output, 1, wxALL|wxEXPAND, 5 );
	
	m_panelRight->SetSizer( bSizer3 );
	m_panelRight->Layout();
	bSizer3->Fit( m_panelRight );
	m_splitter->SplitVertically( m_panelLeft, m_panelRight, 200 );
	bSizer->Add( m_splitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer );
	this->Layout();
	
    this->LoadObjects();
}

void ExplorerFrm::LoadObjects()
{
	wxTreeItemId fRoot = m_treeCtrl5->AddRoot(wxString::FromUTF8(page->getPage().cstr()));
	
	std::vector<short> types = rm.getTypes(page->getLocation());
	
	for(unsigned int f = 0; f < types.size(); f++) {
        plString TypeName = plString::Format("[%04hX] %s", types[f], pdUnifiedTypeMap::ClassName(types[f]));
		wxTreeItemId fType = m_treeCtrl5->AppendItem(fRoot, wxString::FromUTF8(TypeName.cstr()));
		
		std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);
		
		for(unsigned int ks = 0; ks < mykeys.size(); ks++) {
			m_treeCtrl5->AppendItem(fType, wxString::FromUTF8(mykeys[ks]->getName().cstr()), -1, -1, new wxTreeKeyData(mykeys[ks]));
		}
		
		m_treeCtrl5->SortChildren(fType);
	}
	
	m_treeCtrl5->SortChildren(fRoot);
}

void ExplorerFrm::LoadPRC(wxTreeEvent& event)
{
    m_output->SetReadOnly(false);
	wxTreeItemId fID = event.GetItem();
	
	m_output->ClearAll();
	
	wxTreeKeyData* KeyData = (wxTreeKeyData*)m_treeCtrl5->GetItemData(fID);
	wxString name = m_treeCtrl5->GetItemText(fID);

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
            plString s = plString::Format("Class [%04hX]%s is not currently supported",
                                          fKey->getType(), pdUnifiedTypeMap::ClassName(fKey->getType()));
            prc->writeComment(s);
        }

	    hsUint32 size = S->size();
		char* data = new char[size + 1];
    	S->copyTo((void*&)data, size);
        data[size] = 0;
		
    	m_output->SetText(wxString::FromUTF8(data));
        delete[] data;

        delete prc;
        delete S;
	}
    m_output->SetReadOnly(true);
}



wxTreeKeyData::wxTreeKeyData(const plKey& key): wxTreeItemData()
{
	this->fKey = key;
}

wxTreeKeyData::~wxTreeKeyData() { }

plKey& wxTreeKeyData::getKey()
{
	return this->fKey;
}
