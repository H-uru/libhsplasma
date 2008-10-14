///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  7 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ExplorerFrm__
#define __ExplorerFrm__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "wxPlasmaTextCtrl.h"
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include <wx/artprov.h>
#include "ResManager/plResManager.h"
#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Debug/hsExceptions.h"
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include "PlasmaDefs.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ExplorerFrm
///////////////////////////////////////////////////////////////////////////////
class ExplorerFrm : public wxFrame
{
    private:
        enum
        {
            ID_TOOLBAR = 1000,
            ID_TB_SAVE,
            ID_TB_OPEN,
            ID_TB_SAVE_FILE,
            ID_TB_BACK,
            ID_TB_FORWARD,
            ID_TREEVIEW,
            ID_EDITOR,
        };

    protected:
        wxToolBar* m_toolBar;
        wxSplitterWindow* m_splitter;
        wxPanel* m_panelLeft;
        wxTreeCtrl* m_prpTree;
        wxPanel* m_panelRight;
        wxNotebook* m_notebook;
        wxPanel* m_panelPRC;
        wxPlasmaTextCtrl* m_prcEditor;
        wxPanel* m_panelHEX;
        plResManager rm;
        std::vector<plPageInfo*> pages;
        wxTreeItemId fRoot;
        plString fPath;
        std::vector<wxTreeItemId> fBack;
        wxTreeItemId fPrev;
        wxTreeItemId fCurrent;

        // Virtual event handlers, overide them in your derived class
        void SavePage( wxCommandEvent& event );
        void OpenBrowser( wxCommandEvent& event );
        void LoadObjects(plPageInfo* page);
        void SavePrcFile( wxCommandEvent& event );
        void LoadObjPrc( wxTreeEvent& event );
        void GoBack( wxCommandEvent& event );


    public:

        ExplorerFrm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PageEditor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, const wxString& name = wxT("PageEditor") );
        ~ExplorerFrm();
        void InitFromFile( const wxString& filename);
        void m_splitterOnIdle( wxIdleEvent& )
        {
        m_splitter->SetSashPosition( 0 );
        m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ExplorerFrm::m_splitterOnIdle ), NULL, this );
        }


};

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class wxTreeKeyData
///////////////////////////////////////////////////////////////////////////////
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
