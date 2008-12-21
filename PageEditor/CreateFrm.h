///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CREATEFRM_H__
#define __CREATEFRM_H__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include "ResManager/plResManager.h"
#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Debug/hsExceptions.h"
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include "PlasmaDefs.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CreateObjDlg
///////////////////////////////////////////////////////////////////////////////
class CreateObjDlg : public wxDialog 
{
	private:
	    enum
        {
            ID_NAME = 2000,
            ID_LOCATION,
            ID_CLASS,
            ID_CREATE
        };
	
	protected:
		wxStaticText* lblObjName;
		wxTextCtrl* txtObjName;
		wxStaticText* lblObjLoc;
		wxChoice* chObjLoc;
		wxStaticText* lblObjType;
		wxChoice* chObjType;
		wxButton* btnOK;
		wxButton* btnCancel;
		
		void Create( wxCommandEvent& event );
	
	public:
		CreateObjDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Object..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,185 ), long style = wxDEFAULT_DIALOG_STYLE, plResManager* mgr = NULL );
		~CreateObjDlg();
		
		plLocation GetLocation();
		wxString GetName();
	    unsigned int GetClassType();
};

#endif //__noname__

