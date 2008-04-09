///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 22 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ExplorerFrm.h"


///////////////////////////////////////////////////////////////////////////

ExplorerFrm::ExplorerFrm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxFrame( parent, id, title, pos, size, style, name )
{
	plDebug::InitFile(plDebug::kDLAll);
	
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( wxFRAME_EX_METAL );
}

ExplorerFrm::~ExplorerFrm()
{
}

void ExplorerFrm::SetPlasmaPage(wxString& filename)
{
    try {
		page = rm.ReadPage(filename.ToUTF8());
	} catch (hsException& e) {
		fprintf(stderr, "%s:%lu: %s\n", e.File(), e.Line(), e.what());
		return;
	} catch (std::exception& e) {
		fprintf(stderr, "PrcExtract Exception: %s\n", e.what());
		return;
	} catch (...) {
		fprintf(stderr, "Undefined error!\n");
		return;
	}
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( ExplorerFrm::m_splitterOnIdle ), NULL, this );
	m_panelLeft = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panelLeft, wxID_ANY, wxString::FromUTF8(page->getAge().cstr())), wxVERTICAL );
	
	m_treeCtrl5 = new wxTreeCtrl( m_panelLeft, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTR_DEFAULT_STYLE|wxFULL_REPAINT_ON_RESIZE|wxRAISED_BORDER );
	sbSizer1->Add( m_treeCtrl5, 1, wxALL|wxEXPAND, 1 );
	
	bSizer5->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_panelLeft->SetSizer( bSizer5 );
	m_panelLeft->Layout();
	bSizer5->Fit( m_panelLeft );
	m_panelRight = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl4 = new wxTextCtrl( m_panelRight, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer3->Add( m_textCtrl4, 1, wxALL|wxEXPAND, 5 );
	
	m_panelRight->SetSizer( bSizer3 );
	m_panelRight->Layout();
	bSizer3->Fit( m_panelRight );
	m_splitter->SplitVertically( m_panelLeft, m_panelRight, 0 );
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
		printf("Iteration %d - [%04X] %s", f, types[f], pdUnifiedTypeMap::ClassName(types[f], rm.getVer()));
        plString TypeName = plString::Format("[%04X] %s", types[f], pdUnifiedTypeMap::ClassName(types[f], rm.getVer()));
		wxTreeItemId fType = m_treeCtrl5->AppendItem(fRoot, wxString::FromUTF8(TypeName.cstr()));
		
		std::vector<plKey> mykeys = rm.getKeys(page->getLocation(), types[f]);
		
		for(unsigned int ks = 0; ks < mykeys.size(); ks++) {
			m_treeCtrl5->AppendItem(fType, wxString::FromUTF8(mykeys[ks]->getName().cstr()));
		}
	}
}
