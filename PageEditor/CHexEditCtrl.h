/*
* Softerra Hex Editor (c) Softerra, LLC 2005
*
* Port to wxWidgets by Zbyl
*/

#ifndef __HEXEDITCTRL_h__
#define __HEXEDITCTRL_h__

#include <wx/wx.h>
#include <wx/dialog.h>

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/timer.h>
#include <wx/menu.h>  
////Header Include End

#include <vector>

////Dialog Style Start
#undef CHexEditCtrl_STYLE
#define CHexEditCtrl_STYLE wxWANTS_CHARS | wxVSCROLL | wxHSCROLL /*| wxALWAYS_SHOW_SB | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTHICK_FRAME | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX*/
////Dialog Style End

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_HEXEDIT_CHANGED, 7777)
END_DECLARE_EVENT_TYPES()

class CHexEditCtrl : public wxWindow
{
private:
	DECLARE_EVENT_TABLE();
	
public:
	CHexEditCtrl(wxWindow *parent, wxWindowID id = 1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = CHexEditCtrl_STYLE);
	virtual ~CHexEditCtrl();

	void OnKillFocus(wxFocusEvent& event);
	void OnSetFocus(wxFocusEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnContextMenu(wxMouseEvent& _event);
	void OnLeftDown(wxMouseEvent& event);
	void OnLeftDclick(wxMouseEvent& event);
	void OnLeftUP(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnScroll(wxScrollWinEvent& event);
	void OnHScroll(wxScrollWinEvent& event);
	void OnVScroll(wxScrollWinEvent& event);
	void OnEditCopy(wxCommandEvent& event);
	void OnUpdateEditCopy(wxUpdateUIEvent& event);
	void OnEditCut(wxCommandEvent& event);
	void OnUpdateEditCut(wxUpdateUIEvent& event);
	void OnEditPaste(wxCommandEvent& event);
	void OnUpdateEditPaste(wxUpdateUIEvent& event);
	void OnEditSelectAll(wxCommandEvent& event);
	void OnUpdateEditSelectAll(wxUpdateUIEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnCaptureLost(wxMouseCaptureLostEvent& event);

private:
	//Do not add custom control declarations between 
	//GUI Control Declaration Start and GUI Control Declaration End.
	//wxDev-C++ will remove them. Add custom code after the block.
	////GUI Control Declaration Start
		wxTimer *m_timer;
		wxMenu *m_popupMenu;
	////GUI Control Declaration End
	
private:
	//Note: if you receive any error with these enum IDs, then you need to
	//change your old form code that are based on the #define control IDs.
	//#defines may replace a numeric value for the enum names.
	//Try copy and pasting the below block in your old form header files.
	enum
	{
		////GUI Enum Control ID Start
			ID_M_TIMER = 1008,
		////GUI Enum Control ID End
		ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
	};

private:
	void CreateGUIControls();


// Implementation
protected:
	// Properties

	/*! Data displayed.*/
	std::vector<wxByte> m_data;
	size_t m_origDataSize; //m_data is padded with zeros when is not aligned to m_digitsInData

	/*! Number of hex digits shown in address field (4 or 8).*/
	short m_digitsInAddress;

	/*! Number of hex digits in one number
	- 2 - BYTE view
	- 4 - WORD view
	- 8 - DWORD view
	*/
	short m_digitsInData;

	/*! Number of columns.*/
	short m_columns;

	/*! Font height.*/
	short m_fontHeight;

	/*! Starting address to display.*/
	wxUint32 m_dwStartAddr;

	/*! True if data are modified.*/
	bool m_bDataModified;

	// Other data

	/*! This value equals the following expression: (m_showAscii && m_digitsInData == 2).*/
	//bool m_bRealShowAscii;

	/*! Current horizontal scroll shift in chars.*/
	int m_nHorzScroll;

	/*! True after WM_LBUTTONDOWN, false after WM_LBUTTONUP.*/
	bool m_bMouseDown;

	/*! True after WM_MOUSEMOVE, false after WM_LBUTTONUP.*/
	bool m_bMouseMove;

	/*! Address of number under mouse cursor in WM_LBUTTONDOWN.*/
	int m_posMouseDown;

	/*! Window size in chars.*/
	wxSize m_charCountWindow;

	/*! Total view size in chars.*/
	wxSize m_charCountView;

	/*! Char size in device points.*/
	wxSize m_cellSize;

	/* !!! IMPORTANT
	m_selStart, m_selEnd and other addresses of numbers are counts of numbers (NOT NESESSARY BYTES!),
	depending on m_digitsInData.*/

	/*! Selection start (in numbers).*/
	long m_selStart;

	/*! Selection end (in numbers).*/
	long m_selEnd;

	/*! Address of number being edited.*/
	long m_editPos;

	/*! Address of the first visible number.*/
	long m_viewPos;

	/*! Digit being edited (0 - leftmost).*/
	int m_nEditDigit;

	/*! Right margin of address field in chars.*/
	int m_addrMargin;

	/*! Left margin of ASCII field in chars.*/
	int m_asciiMargin;

	/*! This value is a combination of following flags:
	- EDIT_BYTES - edit hex data mode (if not set - edit ASCII data)
	- EDIT_INSERT - insert mode (if not set - overwrite mode)
	*/
	int m_editMode;

	/*! Control client rect.*/
	wxRect m_rcClient;

	/*! True if timer is active.*/
	bool m_bTimer;

	/*! Coordinates of last point in OnMouseMove.*/
	wxPoint m_prevMousePoint;

	bool m_vScrollShown;
	bool m_hScrollShown;
	wxColour m_myForegroundColour; //CAUTION: wxWindowBase has m_foregroundColour member
	wxColour m_myBackgroundColour; //CAUTION: wxWindowBase has m_backgroundColour member
	wxColour m_myBackgroundColourOdd; //use it for odd columns
	wxColour m_mySelectionColour;
	wxColour m_mySelectionTextColour;
	wxColour m_myOffsetColour;
	wxColour m_myCurentColour;
	wxFont m_font;

	bool m_readOnly;

	bool m_showAddress;
	bool m_showAscii;
	bool m_allowChangeSize;
	bool m_dataModified;

public:
	void SetStartAddr(wxUint32 startAddr);
	wxUint32 GetStartAddr() { return m_dwStartAddr; }

	void SetReadOnly(bool readOnly);
	bool GetReadOnly() { return m_readOnly; }
	void SetShowAddress(bool showAddress);
	bool GetShowAddress() { return m_showAddress; }
	void SetShowAscii(bool showAscii);
	bool getShowAscii() { return m_showAscii; }
	void SetAllowChangeSize(bool allowChangeSize);
	bool GetAllowChangeSize() { return m_allowChangeSize; }

	bool GetDataModified() { return m_dataModified; }

	short GetDigitsInAddress();
	void SetDigitsInAddress(short nNewValue);
	short GetDigitsInData();
	void SetDigitsInData(short nNewValue);
	short GetColumns();
	void SetColumns(short nNewValue);
	short GetFontHeight();
	void SetFontHeight(short nNewValue);
	void SetData(const wxByte* data, int len, wxUint32 startAddr = 0);
	const std::vector<wxByte>& GetData();
	wxUint32 GetOffset(bool absolute = false);
	wxUint32 GetSelectionOffset();
	wxUint32 GetValue();
	std::vector<wxByte> GetSelectedData();
	std::vector<wxByte> GetDataRange(wxUint32 start, wxUint32 len, bool zeroPad = true, bool stopOnZero = false);

protected:
	void SendChangedEvent();
	void SafeReleaseMouse();
	void ShowCaret();
	void HideCaret();

	wxUint32 getAddressFromPos(int pos);
	int getPosFromAddress(wxUint32 address);
	int getRowFromAddress(wxUint32 address);
	int getColFromAddress(wxUint32 address);
	wxUint32 getAddressFromRowCol(int row, int col);
	bool isPosValid(int pos);
	bool isAddressValid(wxUint32 address, bool onlyOneByte = false);

	/*! This function calls pdc->TextOut ( x, y, strText ) function if text overlaps with rcInvalid.*/
	void TextOutWithCheck(wxDC& dc, const wxRect& rcInvalid, int x, int y, const wxString& strText);

	/*! This function calls pdc->TextOut ( x, y, eChar ) function if char overlaps with rcInvalid.*/
	void CharOutWithCheck(wxDC& dc, const wxRect &rcInvalid, int x, int y, wxChar wChar);

	/*! This function called before entering a new number or ascii byte.
	* It does InsertBytes, scrolling, repainting if nesessary.
	* @return false, if it's impossible to insert number because of
	* m_allowChangeSize == false, otherwise - true.
	*/
	bool EnterNumber();

	/*! Clear selection.*/
	void ClearSelection();

	/*! Delete currently selected data.*/
	void DeleteSelection();

	/*! Update selection margins when mouse is moving.
	* @param point mouse coordinates.
	*/
	void RecalcSelection(wxPoint point);

	/*! Returns true, if nothing is selected, and false otherwise.*/
	bool IsSelectionEmpty();

	/*! Recalculate scroll ranges and positions of scrollbars,
	* show or hide scroll bars if nesessary.
	*/
	bool UpdateScrollBars();

	/*! Invalidate rect occupied by number with address nEditPos.*/
	void InvalidateEditRect(long nEditPos);

	/*! Delete dwCount numbers (not bytes!) from m_data, starting from dwPos.*/
	void DeleteData ( wxUint32 dwPos, wxUint32 dwCount = 1 );

	/*! Insert dwCount numbers (not bytes!) in m_data, starting from dwPos.*/
	void InsertData ( wxUint32 dwPos, wxUint32 dwCount = 1 );

	/*! Update caret position and scroll bars when m_editPos is changed.*/
	bool NormalizeEditPos();

	/*! Set new edit position after mouse click.
	* @param pt - mouse coordinates.
	*/
	void ChangeEditPos ( wxPoint pt );


	/*! Set new edit position after moving caret.
	* @param dx - horizontal shift of cursor (in numbers), positive - left, negative - right direction
	* @param dx - vertical shift of cursor (in numbers), positive - down, negative - upward direction
	* @param bRepaint = true - repaint the control always,	false - only if scrolling is nesessary
	*/
	void ChangeEditPos ( long dx, long dy, bool bRepaint = false);

	/*! Calculate coordinates and show caret.*/
	void PlaceCaret();

	/*! Compute m_editPos, m_viewPos, margins etc. after changing properties of the control.*/
	void RecalcLayout();

};

#endif //__HEXEDITCTRL_h__
