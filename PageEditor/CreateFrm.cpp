///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CreateFrm.h"

///////////////////////////////////////////////////////////////////////////

CreateObjDlg::CreateObjDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, plResManager* mgr ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( wxDIALOG_EX_METAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 2, 5, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	lblObjName = new wxStaticText( this, wxID_ANY, wxT("Object Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjName->Wrap( -1 );
	fgSizer1->Add( lblObjName, 0, wxALIGN_CENTRE_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	txtObjName = new wxTextCtrl( this, ID_NAME, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( txtObjName, 0, wxALIGN_CENTRE_VERTICAL|wxEXPAND|wxALL, 5 );
	
	lblObjLoc = new wxStaticText( this, wxID_ANY, wxT("Object Location:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjLoc->Wrap( -1 );
	fgSizer1->Add( lblObjLoc, 0, wxALIGN_RIGHT|wxALL|wxALIGN_CENTRE_VERTICAL, 5 );
	
	std::vector<plLocation> fLocations = mgr->getLocations();
	chObjLoc = new wxChoice( this, ID_LOCATION, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	for (size_t i=0; i<fLocations.size(); i++) {
        plPageInfo* page = mgr->FindPage(fLocations[i]);
        chObjLoc->Append(wxString::FromUTF8(page->getAge().cstr()) + wxT("::") + wxString::FromUTF8(page->getPage().cstr()), (void*)page->getLocation().unparse());
    }
	chObjLoc->SetSelection( 0 );
	fgSizer1->Add( chObjLoc, 0, wxALIGN_CENTRE_VERTICAL|wxEXPAND|wxALL, 5 );
	
	lblObjType = new wxStaticText( this, wxID_ANY, wxT("Object Class:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblObjType->Wrap( -1 );
	fgSizer1->Add( lblObjType, 0, wxALIGN_CENTRE_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	chObjType = new wxChoice( this, ID_CLASS, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	for(size_t i = 0; i < 0x200; i++) {
	    if(pdUnifiedTypeMap::ClassName(i, mgr->getVer())) {
	        chObjType->Append(wxString::FromUTF8(pdUnifiedTypeMap::ClassName(i, mgr->getVer())), (void*)i);
	    }
	}
	chObjType->SetSelection( 0 );
	fgSizer1->Add( chObjType, 0, wxALIGN_CENTRE_VERTICAL|wxEXPAND|wxALL, 5 );
	
	btnOK = new wxButton( this, wxID_OK, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnOK, 0, wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL|wxALL, 5 );
	
	btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnCancel, 0, wxALIGN_CENTRE_VERTICAL|wxALL, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

CreateObjDlg::~CreateObjDlg()
{
}

plLocation CreateObjDlg::GetLocation()
{
    int sel = chObjLoc->GetSelection();
    int toparse = (long)chObjLoc->GetClientData(sel);
    
    plLocation loc;
    loc.parse(toparse);
    
    if(!loc.isValid())
        loc.invalidate();
    
    return loc;
}

wxString CreateObjDlg::GetName()
{
    return txtObjName->GetValue();
}

unsigned int CreateObjDlg::GetClassType()
{
    int sel = chObjType->GetSelection();
    unsigned int type = (unsigned long)chObjType->GetClientData(sel);
    
    return type;
}
