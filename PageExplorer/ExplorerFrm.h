///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 22 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ExplorerFrm__
#define __ExplorerFrm__

#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include "ResManager/plResManager.h"
#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Debug/hsExceptions.h"
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include "PlasmaDefs.h"
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include "wxPlasmaTextCtrl.h"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class ExplorerFrm
///////////////////////////////////////////////////////////////////////////////
class ExplorerFrm : public wxFrame 
{
	protected:
		wxSplitterWindow* m_splitter;
		wxPanel* m_panelLeft;
		wxTreeCtrl* m_treeCtrl5;
		wxPanel* m_panelRight;
		wxPlasmaTextCtrl* m_output;
		plResManager rm;
        plPageInfo* page;
	
	public:
		ExplorerFrm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PageExplorer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, const wxString& name = wxT("ExplorerFrm") );
		~ExplorerFrm();
		void SetPlasmaPage(const wxString& filename);
		void LoadObjects();
		void SaveKeys(const wxString& filename);
		void m_splitterOnIdle( wxIdleEvent& )
		{
		m_splitter->SetSashPosition( 0 );
		m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ExplorerFrm::m_splitterOnIdle ), NULL, this );
		}
	
	private:
        DECLARE_EVENT_TABLE()
        enum
        {
        	ID_TREECTRL = 1001,
        	ID_PRCEDIT = 1002
		};
		void LoadPRC(wxTreeEvent & event);
		
	
};

/*
 *  Class which is stored in the tree and in the list to keep informations
 *  about the element.
 */
class wxTreeKeyData : public wxTreeItemData
{
   public:
      wxTreeKeyData(const plKey& key = plKey(NULL));
      ~wxTreeKeyData();
      plKey& getKey();

   protected:
      plKey fKey;
};


#endif //__ExplorerFrm__
