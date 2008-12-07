/*
* Softerra Hex Editor (c) Softerra, LLC 2005
*
* Port to wxWidgets by Zbyl
*/

#include "CHexEditCtrl.h"

#include <wx/settings.h>
#include <wx/dcbuffer.h>
#include <wx/caret.h>
#include <wx/clipbrd.h>


enum EDIT_MODE {			// m_editMode flags
	EDIT_BYTES = 1,
	EDIT_INSERT = 2,
};

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

DEFINE_EVENT_TYPE(wxEVT_HEXEDIT_CHANGED)

//----------------------------------------------------------------------------
// CHexEditCtrl
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(CHexEditCtrl,wxWindow)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(CHexEditCtrl::OnClose)
	EVT_CHAR(CHexEditCtrl::OnChar)
	EVT_KEY_DOWN(CHexEditCtrl::OnKeyDown)
	EVT_SIZE(CHexEditCtrl::OnSize)
	EVT_SET_FOCUS(CHexEditCtrl::OnSetFocus)
	EVT_KILL_FOCUS(CHexEditCtrl::OnKillFocus)
	EVT_MOTION(CHexEditCtrl::OnMouseMotion)
	EVT_MOUSEWHEEL(CHexEditCtrl::OnMouseWheel)
	EVT_RIGHT_DOWN(CHexEditCtrl::OnContextMenu)
	EVT_LEFT_DOWN(CHexEditCtrl::OnLeftDown)
	EVT_LEFT_UP(CHexEditCtrl::OnLeftUP)
	EVT_LEFT_DCLICK(CHexEditCtrl::OnLeftDclick)
	EVT_PAINT(CHexEditCtrl::OnPaint)
	EVT_TIMER(ID_M_TIMER,CHexEditCtrl::OnTimer)
	EVT_MENU(wxID_COPY , CHexEditCtrl::OnEditCopy)
	EVT_UPDATE_UI(wxID_COPY , CHexEditCtrl::OnUpdateEditCopy)
	EVT_MENU(wxID_CUT , CHexEditCtrl::OnEditCut)
	EVT_UPDATE_UI(wxID_CUT , CHexEditCtrl::OnUpdateEditCut)
	EVT_MENU(wxID_PASTE , CHexEditCtrl::OnEditPaste)
	EVT_UPDATE_UI(wxID_PASTE , CHexEditCtrl::OnUpdateEditPaste)
	EVT_MENU(wxID_SELECTALL , CHexEditCtrl::OnEditSelectAll)
	EVT_UPDATE_UI(wxID_SELECTALL , CHexEditCtrl::OnUpdateEditSelectAll)
	EVT_MOUSE_CAPTURE_LOST(CHexEditCtrl::OnCaptureLost)
	
	EVT_SCROLLWIN(CHexEditCtrl::OnScroll)
END_EVENT_TABLE()
////Event Table End

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Constructing, destructing

//for integral types only
/*template<typename T>
T _ceil_div(const T& dividend, const T& divisor) {
	return (dividend + divisor - (T)1) / divisor;
}*/
size_t _ceil_div(const size_t& dividend, const size_t& divisor) {
	return (dividend + divisor - (size_t)1) / divisor;
}

wxCommandEvent _dummy_command;

CHexEditCtrl::CHexEditCtrl(wxWindow *parent, wxWindowID id, const wxPoint &position, const wxSize& size, long style)
: wxWindow(parent, id, position, size, style)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM); //for wxAutoBufferedPaintDC
	CreateGUIControls();

	//m_data
	m_origDataSize = 0;

	m_selStart = m_selEnd = -1;
	m_editPos = m_viewPos = 0;
	m_editMode = EDIT_BYTES | EDIT_INSERT;
	m_bMouseDown = m_bMouseMove = false;
	m_bTimer = false;
	m_dataModified = false;
	m_dwStartAddr = 0;
	m_nHorzScroll = 0;

	//persistent custom properties
	//TODO: make them persistent
	m_showAddress = true;
	m_showAscii = true;
	m_digitsInData = 2;
	m_digitsInAddress = 4;
	m_columns = 16;
	m_fontHeight = 10; //in points
	m_allowChangeSize = false;

	m_vScrollShown = false;
	m_hScrollShown = false;

	//m_font = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);
	m_font.Create(m_fontHeight, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	//m_myForegroundColour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
	//m_myBackgroundColour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
	//m_mySelectionColour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
	//m_mySelectionTextColour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);
	m_myForegroundColour = *wxBLACK;
	m_myBackgroundColour = *wxWHITE;
	m_myBackgroundColourOdd.Set(237, 243, 254);
	m_mySelectionColour.Set(255, 210, 129);
	m_mySelectionTextColour = m_myForegroundColour;
	m_myOffsetColour = wxTheColourDatabase->Find(wxT("GRAY"));
	m_myCurentColour = wxTheColourDatabase->Find(wxT("YELLOW"));

	//FIXME: dunno if this is required
	wxCaret* caret = new wxCaret(this, 10, 10);
	SetCaret(caret);
}

CHexEditCtrl::~CHexEditCtrl()
{
	m_timer->Stop();
	delete m_timer;
	delete m_popupMenu;
} 

void CHexEditCtrl::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	//SetSize(8,19,316,379);
	//Center();
	

	m_timer = new wxTimer();
	m_timer->SetOwner(this, ID_M_TIMER);

	m_popupMenu = new wxMenu(wxT(""));
	m_popupMenu->Append(wxID_COPY, wxT("Copy"), wxT(""), wxITEM_NORMAL);
	m_popupMenu->Append(wxID_CUT, wxT("Cut"), wxT(""), wxITEM_NORMAL);
	m_popupMenu->Append(wxID_PASTE, wxT("Paste"), wxT(""), wxITEM_NORMAL);
	m_popupMenu->AppendSeparator();
	m_popupMenu->Append(wxID_SELECTALL, wxT("Select All"), wxT(""), wxITEM_NORMAL);

	////GUI Items Creation End
}

void CHexEditCtrl::OnClose(wxCloseEvent& /*_event*/)
{
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Calculations

wxUint32 CHexEditCtrl::getAddressFromPos(int pos) {
	return pos * (m_digitsInData/2);
}

int CHexEditCtrl::getPosFromAddress(wxUint32 address) {
	return address / (m_digitsInData/2);
}

// return address aligned to (m_digitsInData/2)
wxUint32 CHexEditCtrl::getAddressFromRowCol(int row, int col) {
	return (row * m_columns + col) * (m_digitsInData/2);
}

// address does not include m_dwStartAddr, doesn't have to be aligned to (m_digitsInData/2)
int CHexEditCtrl::getRowFromAddress(wxUint32 address) {
	return address / (m_columns * (m_digitsInData/2));
}

// address does not include m_dwStartAddr, doesn't have to be aligned to (m_digitsInData/2)
int CHexEditCtrl::getColFromAddress(wxUint32 address) {
	return (address / (m_digitsInData/2)) % m_columns;
}

//is pos safe to read from
bool CHexEditCtrl::isPosValid(int pos) {
	wxUint32 offs = getAddressFromPos(pos);
	return (offs >= 0 && offs + (m_digitsInData/2) <= (wxUint32)m_data.size());
}

bool CHexEditCtrl::isAddressValid(wxUint32 address, bool onlyOneByte /*= false*/) {
	return (address >= 0 && address + (onlyOneByte ? 1 : (m_digitsInData/2)) <= (wxUint32)m_data.size());
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Painting

void CHexEditCtrl::TextOutWithCheck(wxDC& dc, const wxRect& rcInvalid, int x, int y, const wxString& strText) {
	wxRect rcText(x, y, (int)strText.Length() * m_cellSize.GetWidth(), m_cellSize.GetHeight());
	if(rcText.Intersects(rcInvalid))
		dc.DrawText(strText, x, y);
}

void CHexEditCtrl::CharOutWithCheck(wxDC& dc, const wxRect &rcInvalid, int x, int y, wxChar wChar) {
	wxString str(wChar);
	TextOutWithCheck(dc, rcInvalid, x, y, str);
}

void CHexEditCtrl::OnPaint(wxPaintEvent& _event)
{
    wxRegion region = GetUpdateRegion();
	if (region.IsEmpty())
		return;

	wxAutoBufferedPaintDC dc(this);
	dc.SetBackgroundMode(wxSOLID); //draw text's background

	wxBrush brush(m_myBackgroundColour, wxSOLID);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(brush);

	// FIXME: is this needed???
	dc.DestroyClippingRegion();
	dc.SetClippingRegion(region);

	wxRect rcInvalid = region.GetBox();
	// Paint the background using the BackColor property when no data set
	if (m_data.size() == 0) {
		dc.DrawRectangle(rcInvalid);
		return;
	}

	// paint half-letter-wide rect at the left of the text
	wxRect rc1(0, rcInvalid.GetTop(), m_cellSize.GetWidth() / 2, rcInvalid.GetBottom() );
	dc.DrawRectangle(rc1);

	dc.SetFont(m_font);

	dc.SetPen(*wxLIGHT_GREY_PEN);

	wxString space(wxT(" "));
	wxString strText;
	int nAddr = m_viewPos * (m_digitsInData / 2);

	for (int i = 0; i < m_charCountWindow.GetHeight() + 1; i++) { //+1 here to draw the cut line
		// draw one line of text

		if (m_showAddress) {
			// draw address field
			if (wxUint32(nAddr) <= m_data.size() /*+ m_columns*(m_digitsInData/2)*/)
				strText.Printf(wxT("%0*X  "), m_digitsInAddress, nAddr + m_dwStartAddr);
			else
				strText.Printf(wxT("%*c  "), m_digitsInAddress, wxT(' '));

			dc.SetTextForeground(m_myOffsetColour);
			dc.SetTextBackground(m_myBackgroundColour);
			TextOutWithCheck(dc, rcInvalid, - m_nHorzScroll * m_cellSize.GetWidth() + m_cellSize.GetWidth()/2,
				i * m_cellSize.GetHeight(), strText);
		}

		int dwRowPos = i * m_columns + m_viewPos;
		/*bool full_line = wxUint32((dwRowPos + m_columns) * (m_digitsInData / 2) - 1) <
			m_data.size();*/
		bool partial_line = wxUint32(dwRowPos * (m_digitsInData / 2)) <
			m_data.size();

		wxColour curBackground;
		for (int j = 0; j < m_columns; j++) {
			// draw hex data

			int dwPos = j + dwRowPos;
			bool pos_ok = wxUint32(dwPos * (m_digitsInData / 2)) < m_data.size();

			curBackground = (getRowFromAddress(dwPos) & 1) ? m_myBackgroundColour
															: m_myBackgroundColourOdd;

			//draw a space after hex number
			if ( dwPos >= m_selStart && dwPos < m_selEnd && j != (m_columns-1)) {
				// selected text colors
				dc.SetTextBackground(m_mySelectionColour);
				dc.SetTextForeground(m_mySelectionTextColour);
			} else {
				// normal text colors
				dc.SetTextBackground(curBackground);
				dc.SetTextForeground(m_myForegroundColour);
			}
			TextOutWithCheck(dc, rcInvalid,
				(m_addrMargin + j * (m_digitsInData + 1) + m_digitsInData - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2, 
				i * m_cellSize.GetHeight(), space);

			if (dwPos == m_editPos) {
				// caret text colors
				dc.SetTextBackground(m_myCurentColour);
				dc.SetTextForeground(m_myForegroundColour);
			} else if (dwPos >= m_selStart && dwPos <= m_selEnd) {
				// selected text colors
				dc.SetTextBackground(m_mySelectionColour);
				dc.SetTextForeground(m_mySelectionTextColour);
			}

			if (pos_ok) {
				std::vector<wxByte>::pointer ptr;
				// we are in the data
				switch (m_digitsInData)
				{
				case 2:
					ptr = &m_data[dwPos];
					strText.Printf(wxT("%02X"), *ptr);
					break;
				case 4:
					ptr = &m_data[dwPos * 2];
					strText.Printf(wxT("%04X"), *(wxUint16*)ptr);
					break;
				case 8:
					ptr = &m_data[dwPos * 4];
					strText.Printf(wxT("%08X"), *(wxUint32*)ptr);
					break;
				default:
					assert(0);
				}

				TextOutWithCheck(dc, rcInvalid,
					(m_addrMargin + j * (m_digitsInData + 1) - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2, 
					i * m_cellSize.GetHeight(), strText);

				//if (m_bRealShowAscii)
				{
					// draw ascii data
					//ASSERT(m_digitsInData == 2);

					for (int k = 0; k < m_digitsInData/2; ++k) {
						char cChar = m_data[dwPos * (m_digitsInData/2) + k];
						//if (wxIsprint())
						if (cChar >= 0 && cChar < 32) cChar = '.';
						char str[2];
						str[0] = cChar;
						str[1] = '\0';
						strText = wxString(wxConvCurrent->cMB2WX(str));

						TextOutWithCheck(dc, rcInvalid,
							(m_asciiMargin + (j * (m_digitsInData/2)) + k - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2,
							i * m_cellSize.GetHeight(), strText);
					}
				}

			} else {
				// if the last line has less than m_columns numbers, fill it with spaces
				dc.SetTextForeground(m_myForegroundColour);
				dc.SetTextBackground(partial_line ? curBackground : m_myBackgroundColour);
				strText.Printf(wxT("%*c "), m_digitsInData, wxT(' '));
				TextOutWithCheck(dc, rcInvalid,
					(m_addrMargin + j * (m_digitsInData + 1) - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2,
					i * m_cellSize.GetHeight(), strText);
				//if ( m_bRealShowAscii )
				{
					//ASSERT(m_digitsInData == 2);
					for (int k = 0; k < m_digitsInData/2; ++k) {
						strText = wxT(' ');
						TextOutWithCheck(dc, rcInvalid,
							(m_asciiMargin + (j * (m_digitsInData/2)) + k - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2,
							i * m_cellSize.GetHeight(), strText);
					}
				}
			}

			if (partial_line && m_digitsInData < 8 && j > 0 && j * (m_digitsInData/2) % 4 == 0) {
				int x = (m_addrMargin + j * (m_digitsInData + 1) - m_nHorzScroll) * m_cellSize.GetWidth();
				int y = i * m_cellSize.GetHeight();
				dc.DrawLine(x, y, x, y + m_cellSize.GetHeight());
			}
		}

		dc.SetTextForeground(m_myForegroundColour);
		dc.SetTextBackground(partial_line ? curBackground : m_myBackgroundColour);

		//if ( m_bRealShowAscii )
		{
			// draw space between hex and ascii
			strText = wxT(' ');
			TextOutWithCheck(dc, rcInvalid,
				(m_asciiMargin - m_nHorzScroll - 1) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2,
				i * m_cellSize.GetHeight(), strText);
		}		

		dc.SetTextBackground(m_myBackgroundColour);

		// draw extra spaces at the end of line
		if (m_charCountView.GetWidth() < m_charCountWindow.GetWidth())
			strText.Printf(wxT("%*c  "), m_charCountWindow.GetWidth() - m_charCountView.GetWidth() + 1, wxT(' '));
		else
			strText = wxT("  ");
		TextOutWithCheck(dc, rcInvalid,
			(m_asciiMargin + (/*m_bRealShowAscii*/true ? m_columns * (m_digitsInData/2) : 0) - m_nHorzScroll) * m_cellSize.GetWidth() + m_cellSize.GetWidth() / 2,
			i * m_cellSize.GetHeight(), strText);
		nAddr += m_columns * (m_digitsInData / 2);
	}

	// fill the rest of the window with spaces
	/*strText.Printf(wxT("%*c "), m_charCountWindow.GetWidth(), wxT(' '));
	TextOutWithCheck(dc, rcInvalid,
		m_cellSize.GetWidth() / 2, m_charCountWindow.GetHeight() * m_cellSize.GetHeight(), strText);*/
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CHexEditCtrl properties and methods

void CHexEditCtrl::SetReadOnly(bool readOnly) 
{
	SetAllowChangeSize(false);
	m_readOnly = readOnly;

	//m_nHorzScroll = 0;
	//RecalcLayout();
	ChangeEditPos(0,0); //not really needed, I think
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

void CHexEditCtrl::SetShowAddress(bool showAddress) 
{
	m_showAddress = showAddress;

	m_nHorzScroll = 0;
	RecalcLayout();
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

void CHexEditCtrl::SetShowAscii(bool showAscii) 
{
	m_showAscii = showAscii;

	if(m_digitsInData == 2) {
		m_nEditDigit = 0;
		if (!m_showAscii)
			m_editMode |= EDIT_BYTES;
	
		m_nHorzScroll = 0;
		RecalcLayout();
		ChangeEditPos(0,0);
		Refresh(false);

		//SetModifiedFlag(); - mark that persistent properties changed
	}
}

void CHexEditCtrl::SetAllowChangeSize(bool alowChangeSize) 
{
	m_allowChangeSize = alowChangeSize;
	//SetModifiedFlag(); - mark that persistent properties changed
}

short CHexEditCtrl::GetColumns() 
{
	return m_columns;
}

void CHexEditCtrl::SetColumns(short nNewValue) 
{
	if (nNewValue < 0)
		return;

	m_columns = nNewValue;

	m_nHorzScroll = 0;
	RecalcLayout();
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

void CHexEditCtrl::SetStartAddr(wxUint32 startAddr) 
{
	m_dwStartAddr = startAddr;

	RecalcLayout();
	Refresh(false);

	SendChangedEvent();
	//SetModifiedFlag(); - mark that persistent properties changed
}

void CHexEditCtrl::SetData(const wxByte* data, int len, wxUint32 startAddr /*= 0*/) {
	m_origDataSize = (size_t)len;
	m_data.reserve(len);
	m_data.assign(data, data + len);

	m_dwStartAddr = startAddr;
	m_nEditDigit = 0;
	m_selStart = m_selEnd = -1;
	m_editPos = m_viewPos = m_nHorzScroll = 0;
	m_editMode |= EDIT_BYTES;
	m_dataModified = false;

	RecalcLayout();
	Refresh(false);
	SendChangedEvent();
}

const std::vector<wxByte>& CHexEditCtrl::GetData() 
{
	return m_data;
}

short CHexEditCtrl::GetFontHeight() 
{
	return m_fontHeight;
}

void CHexEditCtrl::SetFontHeight(short nNewValue) 
{
	if (nNewValue < 8)
		return;

	m_fontHeight = nNewValue;
	m_font.SetPointSize(m_fontHeight);

	m_nHorzScroll = 0;
	RecalcLayout();
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

short CHexEditCtrl::GetDigitsInAddress() 
{
	return m_digitsInAddress;
}

void CHexEditCtrl::SetDigitsInAddress(short nNewValue) 
{
	if (nNewValue != 4 && nNewValue != 8)
		return;

	m_digitsInAddress = nNewValue;

	m_nHorzScroll = 0;
	RecalcLayout();
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

short CHexEditCtrl::GetDigitsInData() 
{
	return m_digitsInData;
}

void CHexEditCtrl::SetDigitsInData(short nNewValue) 
{
	if (nNewValue != 2 && nNewValue != 4 && nNewValue != 8)
		return;

	//we want the same line to stay on top
	int editOffs = m_editPos * (m_digitsInData/2);
	int lineOffs = (m_viewPos - m_viewPos % m_columns) * (m_digitsInData/2);

	m_digitsInData = nNewValue;
	m_nEditDigit = 0;
	m_selStart = m_selEnd = -1;
	m_editMode |= EDIT_BYTES;
	m_editPos = editOffs / (m_digitsInData/2);
	m_viewPos = lineOffs / (m_columns * (m_digitsInData/2));

	m_nHorzScroll = 0;
	RecalcLayout();
	Refresh(false);

	//SetModifiedFlag(); - mark that persistent properties changed
}

wxUint32 CHexEditCtrl::GetOffset(bool absolute /*= false*/) {
	return (absolute ? m_dwStartAddr : 0) + getAddressFromPos(m_editPos);
}

wxUint32 CHexEditCtrl::GetSelectionOffset() {
	wxUint32 start = getAddressFromPos(m_selStart);
	if (m_selStart < 0 || m_selEnd < 0) {
		if (m_editPos < 0)
			return 0;
		start = getAddressFromPos(m_editPos);
	}
	return start;
}

wxUint32 CHexEditCtrl::GetValue() {
	wxUint32 offs = getAddressFromPos(m_editPos);
	if (offs >= (wxUint32)m_data.size())
		return 0;
	wxASSERT(isAddressValid(offs));
	switch (m_digitsInData) {
		case 2: return m_data[offs];
		case 4: return *(wxUint16*)&m_data[offs];
		case 8: return *(wxUint32*)&m_data[offs];
		default: break;
	}
	return 0;
}

std::vector<wxByte> CHexEditCtrl::GetSelectedData() {
	wxUint32 start = getAddressFromPos(m_selStart);
	wxUint32 end = getAddressFromPos(m_selEnd + 1);
	if (m_selStart < 0 || m_selEnd < 0) {
		if (m_editPos < 0)
			return std::vector<wxByte>();
		start = getAddressFromPos(m_editPos);
		end = getAddressFromPos(m_editPos + 1);
	}

	return GetDataRange(start, end - start, true, false);
}

std::vector<wxByte> CHexEditCtrl::GetDataRange(wxUint32 start, wxUint32 len, bool zeroPad /*= true*/, bool stopOnZero /*= false*/) {
	std::vector<wxByte> data;
	if (len > 512)
		len = 512;
	wxUint32 end = start + len;

	wxUint32 i;
	for (i = start; i < end; ++i)
		if (!isAddressValid(i, true) || i >= m_origDataSize) {
			if (!stopOnZero && zeroPad)
				data.push_back(0);
			else
				break;
		} else {
			if (stopOnZero && m_data[i] == 0)
				break;
			data.push_back(m_data[i]);
		}

	if (stopOnZero && zeroPad && (data.size() == 0 || data.back() != 0) )
		data.push_back(0);

	return data;
}

void CHexEditCtrl::SendChangedEvent()
{
	wxCommandEvent event(wxEVT_HEXEDIT_CHANGED, GetId());
	event.SetEventObject( this );
	// Give it some contents
	event.SetExtraLong( GetOffset() );
	event.SetInt( GetValue() );
	// Send it
	GetEventHandler()->ProcessEvent( event );
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CHexEditCtrl message handlers

void CHexEditCtrl::OnKillFocus(wxFocusEvent& _event) 
{
	if (m_bMouseDown)
	{
		SafeReleaseMouse();
		m_bMouseDown = false;
		m_bMouseMove = false;
		if ( m_bTimer )
		{
			m_timer->Stop();
			m_bTimer = false;
		}

		// place caret just after the selection
		if ( !IsSelectionEmpty() )
		{
			if ( m_editPos == m_selEnd )
				m_editPos++;
			m_nEditDigit = 0;
		}
	}

	PlaceCaret();
	HideCaret();
}

void CHexEditCtrl::OnSetFocus(wxFocusEvent& _event) 
{
	wxCaret* caret = this->GetCaret();
	caret->SetSize( (m_editMode & EDIT_INSERT) ? 1 : m_cellSize.GetWidth(),
					m_cellSize.GetHeight());
	PlaceCaret();
	if (!m_bMouseDown)
		ShowCaret();
}

void CHexEditCtrl::ShowCaret() {
	wxCaret* caret = this->GetCaret();
	if (!caret->IsVisible())
		caret->Show(true);
}

void CHexEditCtrl::HideCaret() {
	wxCaret* caret = this->GetCaret();
	if (caret->IsVisible())
		caret->Show(false);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnKeyDown(wxKeyEvent& _event)
//void CHexEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	bool bShift = _event.ShiftDown();
	bool bControl = _event.ControlDown();;
	int nChar = _event.GetKeyCode();

	if (nChar == WXK_TAB && !bControl) { 
		wxNavigationKeyEvent navEvent;
		navEvent.SetEventObject(this);
		navEvent.SetId(this->GetId());
		navEvent.SetCurrentFocus(this);
		navEvent.SetFromTab(true);
		if (bShift)
			navEvent.SetDirection(false);
		else
			navEvent.SetDirection(true);
		GetParent()->ProcessEvent(navEvent);
		//_event.Skip();
		return;
	}

	if (m_bMouseDown) return;

	if (bShift && !bControl)
	{
		int prevEditPos = m_editPos;
		switch ( nChar )
			// SHIFT+arrows - modify selection
		{
		case WXK_LEFT:
			ChangeEditPos ( -1,  0 );
			break;
		case WXK_RIGHT:
			ChangeEditPos ( 1, 0 );
			break;
		case WXK_UP:
			ChangeEditPos ( 0, -1 );
			break;
		case WXK_DOWN:
			ChangeEditPos ( 0, 1 );
			break;
		case WXK_PRIOR:
			ChangeEditPos ( 0, -m_charCountWindow.GetHeight() );
			break;
		case WXK_NEXT:
			ChangeEditPos ( 0, m_charCountWindow.GetHeight() );
			break;
		case WXK_HOME:
			if ( m_editMode & EDIT_BYTES )
				m_nHorzScroll = 0;
			if ( bControl )
				// select to the start of data
			{
				m_editPos = 0;
				ChangeEditPos ( 0, 0 );
			}
			else	// select to the beginning of the line
				ChangeEditPos ( -(m_editPos % m_columns),  0 );
			break;
		case WXK_END:
			if ( bControl )
				// select to the end of data
			{
				m_editPos = (long)m_data.size()/(m_digitsInData/2);
				ChangeEditPos ( 0, 0 );
			}
			else	// select to the end of the line
				ChangeEditPos ( m_columns-(m_editPos % m_columns),  0 );
			break;
		case WXK_INSERT:
			OnEditPaste(_dummy_command);
			return;
		case WXK_DELETE:
			OnEditCut(_dummy_command);
			return;
		default:
			_event.Skip();
			return;
		}

		// recalc selection margins
		if ( IsSelectionEmpty() )
		{
			if ( m_editPos < prevEditPos )
			{
				m_selStart = m_editPos;
				m_selEnd = prevEditPos-1;
			}
			else if ( m_editPos > prevEditPos )
			{
				m_selStart = prevEditPos;
				m_selEnd = m_editPos-1;
			}
		}
		else
		{
			if ( prevEditPos-1 == m_selEnd )
				m_selEnd = m_editPos-1;
			else
				m_selStart = m_editPos;
			if ( m_selStart == m_selEnd+1 )
				ClearSelection();
		}
		
		Refresh(false);
	}
	else
	{
		if ( bControl && !bShift)
		{
			switch ( nChar )
			{
			case WXK_HOME:
				m_editPos = 0;
				ChangeEditPos ( 0, 0 );
				break;
			case WXK_END:
				m_editPos = (long)m_data.size();
				ChangeEditPos ( 0, 0 );
				break;
			case WXK_INSERT:
				OnEditCopy(_dummy_command);
				break;
			case 'A':
				OnEditSelectAll(_dummy_command);
				break;
			case WXK_TAB:	
				if ( m_digitsInData == 2 /*&& m_bRealShowAscii*/ )
				{	// switch hex/ascii
					m_editMode ^= EDIT_BYTES;
					ChangeEditPos(0,0);		// update scrollbars and caret pos
				}
				break;
			default:
				_event.Skip();
				break;
			}
		}
		else if ( !bControl && !bShift )
		{
			switch ( nChar )
			{
			case WXK_LEFT:
				ChangeEditPos ( -1,  0 );
				break;
			case WXK_RIGHT:
				ChangeEditPos ( 1, 0 );
				break;
			case WXK_UP:
				ChangeEditPos ( 0, -1 );
				break;
			case WXK_DOWN:
				ChangeEditPos ( 0, 1 );
				break;
			case WXK_PRIOR:
				ChangeEditPos ( 0, -m_charCountWindow.GetHeight() );
				break;
			case WXK_NEXT:
				ChangeEditPos ( 0, m_charCountWindow.GetHeight() );
				break;
			case WXK_HOME:
				if ( m_editMode & EDIT_BYTES )
					m_nHorzScroll = 0;
				ChangeEditPos ( -(m_editPos % m_columns),  0 );
				break;
			case WXK_END:	// todo???: place caret at the end
				ChangeEditPos ( m_columns-(m_editPos % m_columns)-1,  0 );
				break;
			case WXK_BACK:
				if (m_readOnly) break;
				if ( (m_editMode & EDIT_INSERT) || m_allowChangeSize )
				{
					if ( IsSelectionEmpty() )
					{
						if ( m_editPos > 0 )
						{
							ChangeEditPos ( -1,  0, true );
							DeleteData ( m_editPos );
							m_dataModified = true;
						}
					}
					else
						DeleteSelection();
					Refresh(false);
					PlaceCaret();
				}
				break;
			case WXK_DELETE:
				if (m_readOnly) break;
				if ( (m_editMode & EDIT_INSERT) || m_allowChangeSize )
				{
					if ( IsSelectionEmpty() )
					{
						if ( (wxUint32)m_editPos < m_origDataSize )
						{
							DeleteData ( m_editPos );
							ChangeEditPos ( 0,  0, true );
							m_dataModified = true;
						}
					}
					else
					{
						DeleteSelection();
						Refresh(false);
						PlaceCaret();
					}
				}
				else // if !EDIT_INSERT
				{
					if ( !IsSelectionEmpty() )
					{
						// zero selected bytes
						std::vector<wxByte>::pointer ptr = &m_data[0];
						memset(ptr + m_selStart*(m_digitsInData/2), 0, (m_selEnd-m_selStart+1)*(m_digitsInData/2));
						ClearSelection();
					}
				}
				break;
			case WXK_INSERT:
				m_editMode ^= EDIT_INSERT;
				GetCaret()->SetSize( (m_editMode & EDIT_INSERT) ? 1 : m_cellSize.GetWidth(), 
					m_cellSize.GetHeight() );
				ShowCaret();
				PlaceCaret();
				break;
			default:
				_event.Skip();
				return;
			}

			if ( !IsSelectionEmpty() )
			{
				ClearSelection();
				Refresh(false);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnChar(wxKeyEvent& _event)
//void CHexEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (m_bMouseDown) return;
	if (m_readOnly) return;

	int nChar = _event.GetKeyCode();

	if ( m_editMode & EDIT_BYTES )
	{
		if((nChar >= '0' && nChar <= '9') || (nChar >= 'a' && nChar <= 'f') || (nChar >= 'A' && nChar <= 'F'))
		{
			wxUint32 b = nChar - '0';
			if(b > 9)
			{
				if (b <= 'F' - '0')
					b = 10 + nChar - 'A';
				else
					b = 10 + nChar - 'a';
			}
			wxUint32 mask = 0xFUL << (( m_digitsInData - m_nEditDigit - 1 )*4);

			if ( !EnterNumber())
				return;

			wxUint32 bufAddr = m_editPos * (m_digitsInData / 2);
			m_data[bufAddr] = ((m_data[bufAddr] & ~mask) | (b << (( m_digitsInData - m_nEditDigit - 1 )*4)));

			m_nEditDigit++;
			if (NormalizeEditPos())		
				Refresh(false);			// cursor was outside visible area
			InvalidateEditRect ( m_editPos );
			if ( m_nEditDigit == m_digitsInData )
				ChangeEditPos(1, 0, false);
			else
			{
				//				NormalizeEditPos();
				//				Refresh(false);
				UpdateScrollBars();
				PlaceCaret();
			}
		}	
		else
			_event.Skip();
	}
	else	// EDIT_ASCII
	{
		if ( nChar >= ' ' )
		{
			if ( !EnterNumber())
				return;

#if wxUSE_UNICODE
			//wxChar wChar = _event.GetUnicodeKey();
			m_data[m_editPos] = wxByte(nChar);
#else
			m_data[m_editPos] = _event.GetKeyCode();
#endif

			if (NormalizeEditPos())
				Refresh(false);			// cursor was outside visible area
			else
				InvalidateEditRect ( m_editPos );
			ChangeEditPos(1, 0, false);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnCaptureLost(wxMouseCaptureLostEvent& event) {
	m_bMouseMove = false;
	wxMouseEvent dummy;
	OnLeftUP(dummy);
}

void CHexEditCtrl::OnLeftDown(wxMouseEvent& _event)
//void CHexEditCtrl::OnLButtonDown(UINT nFlags, wxPoint point) 
{
	m_bMouseDown = true;

	if ( !IsSelectionEmpty() )
		ClearSelection();

	if (_event.ShiftDown())
	{
		if ( wxUint32(m_editPos*(m_digitsInData/2)) == m_data.size())
			m_posMouseDown = m_editPos - 1;
		else
			m_posMouseDown = m_editPos;
		RecalcSelection(_event.GetPosition());
		m_bMouseMove = true;
	}
	else
	{
		ChangeEditPos(_event.GetPosition());
		if ( wxUint32(m_editPos*(m_digitsInData/2)) == m_data.size())
			m_posMouseDown = m_editPos - 1;
		else
			m_posMouseDown = m_editPos;
	}
	CaptureMouse();
	HideCaret();
	
	_event.Skip();
}

void CHexEditCtrl::SafeReleaseMouse() {
	if (HasCapture())
		ReleaseMouse();
}


void CHexEditCtrl::OnLeftDclick(wxMouseEvent& _event)
//void CHexEditCtrl::OnLButtonDblClk(UINT nFlags, wxPoint point) 
{
	wxPoint point = _event.GetPosition();
	ChangeEditPos(point);

	// select the number under cursor if it isn't at the end of data
	if ( wxUint32(m_editPos*(m_digitsInData/2)) != m_data.size())
	{
		m_selStart = m_selEnd = m_editPos;
		m_nEditDigit = 0;
		InvalidateEditRect(m_editPos);
		m_editPos++;
	}

	PlaceCaret();
	m_bMouseDown = false;
	SafeReleaseMouse();

	_event.Skip();
}

void CHexEditCtrl::OnLeftUP(wxMouseEvent& _event)
//void CHexEditCtrl::OnLButtonUp(UINT nFlags, wxPoint point) 
{
	wxPoint point = _event.GetPosition();
	if ( m_bMouseDown )
	{
		if ( m_bMouseMove )
			RecalcSelection(point);
		SafeReleaseMouse();
		m_bMouseDown = false;
		m_bMouseMove = false;
		if ( m_bTimer )
		{
			m_timer->Stop();
			m_bTimer = false;
		}

		// place caret just after the selection
		if ( !IsSelectionEmpty() )
		{
			/*if ( m_editPos == m_selEnd )
				m_editPos++;*/
			m_nEditDigit = 0;
		}
	}
	PlaceCaret();
	ShowCaret();
	
	_event.Skip();
}

void CHexEditCtrl::OnMouseMotion(wxMouseEvent& _event)
//void CHexEditCtrl::OnMouseMove(UINT nFlags, wxPoint point) 
{
	if ( m_bMouseDown )
	{
		wxPoint point = _event.GetPosition();

		m_bMouseMove = true;
		if ( !m_bTimer && !m_rcClient.Contains(point))
		{
			// mouse went outside the window, so we need to scroll even if mouse doesn't 
			// moving
			m_timer->Start(200);
			m_bTimer = true;
		}
		else if ( m_bTimer && m_rcClient.Contains(point))
		{
			// mouse is inside window, so we don't need the timer
			m_timer->Stop();
			m_bTimer = false;
		}
		m_prevMousePoint = point;
		RecalcSelection(point);
	}

	_event.Skip();
}

void CHexEditCtrl::OnMouseWheel(wxMouseEvent& _event) {
	int lines = _event.GetWheelRotation() / _event.GetWheelDelta() * _event.GetLinesPerAction();

	int nPrevViewPos = m_viewPos;
	m_viewPos -= lines * m_columns;

	if ( m_viewPos < 0 )
		m_viewPos = 0;
	size_t dwDataLen = m_data.size()/(m_digitsInData/2)/m_columns * m_columns;
	if ( m_viewPos > (long)dwDataLen - m_columns*(m_charCountWindow.GetHeight()-1) )
		m_viewPos = (long)dwDataLen - m_columns*(m_charCountWindow.GetHeight()-1);

	if ( m_viewPos != nPrevViewPos )
	{
		Refresh(false);
		SetScrollbar(wxVERTICAL, m_viewPos / m_columns, m_charCountWindow.GetHeight(), m_charCountView.GetHeight());
		PlaceCaret();
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnScroll(wxScrollWinEvent& _event) {
	if (_event.GetOrientation() == wxVERTICAL)
		OnVScroll(_event);
	else
		OnHScroll(_event);
}

void CHexEditCtrl::OnVScroll(wxScrollWinEvent& _event)
//void CHexEditCtrl::OnVScroll(UINT nSBCode, UINT /*nPos*/, CScrollBar* /*pScrollBar*/) 
{
	int nPrevViewPos = m_viewPos;

	wxEventType ev = _event.GetEventType();
	
	if (ev == wxEVT_SCROLLWIN_LINEDOWN)
		m_viewPos += m_columns;
	else
	if (ev == wxEVT_SCROLLWIN_LINEUP)
		m_viewPos -= m_columns;
	else
	if (ev == wxEVT_SCROLLWIN_PAGEDOWN)
		m_viewPos += m_columns*m_charCountWindow.GetHeight();
	else
	if (ev == wxEVT_SCROLLWIN_PAGEUP)
		m_viewPos -= m_columns*m_charCountWindow.GetHeight();
	else
	if (ev == wxEVT_SCROLLWIN_THUMBTRACK ||
	    ev == wxEVT_SCROLLWIN_THUMBRELEASE)
		m_viewPos = _event.GetPosition() * m_columns;

	if ( m_viewPos < 0 )
		m_viewPos = 0;
	size_t dwDataLen = m_data.size()/(m_digitsInData/2)/m_columns * m_columns;
	if ( m_viewPos > (long)dwDataLen - m_columns*(m_charCountWindow.GetHeight()-1) )
		m_viewPos = (long)dwDataLen - m_columns*(m_charCountWindow.GetHeight()-1);

	if ( m_viewPos != nPrevViewPos )
	{
		Refresh(false);
		SetScrollbar(wxVERTICAL, m_viewPos / m_columns, m_charCountWindow.GetHeight(), m_charCountView.GetHeight());
		PlaceCaret();
	}
}

void CHexEditCtrl::OnHScroll(wxScrollWinEvent& _event)
//void CHexEditCtrl::OnHScroll(UINT nSBCode, UINT /*nPos*/, CScrollBar* /*pScrollBar*/) 
{
	int nPrevHorzScroll = m_nHorzScroll;

	wxEventType ev = _event.GetEventType();

	if (ev == wxEVT_SCROLLWIN_LINEUP)
		m_nHorzScroll--;
	else
	if (ev == wxEVT_SCROLLWIN_PAGEUP)
		m_nHorzScroll -= m_charCountWindow.GetWidth();
	else
	if (ev == wxEVT_SCROLLWIN_LINEDOWN)
		m_nHorzScroll++;
	else
	if (ev == wxEVT_SCROLLWIN_PAGEDOWN)
		m_nHorzScroll += m_charCountWindow.GetWidth();
	else
	if (ev == wxEVT_SCROLLWIN_THUMBTRACK ||
	    ev == wxEVT_SCROLLWIN_THUMBRELEASE)
		m_nHorzScroll = _event.GetPosition();
		

	if ( m_nHorzScroll < 0 )
		m_nHorzScroll = 0;
	else if ( m_nHorzScroll > m_charCountView.GetWidth() - m_charCountWindow.GetWidth() )
		m_nHorzScroll = m_charCountView.GetWidth() - m_charCountWindow.GetWidth();

	if ( nPrevHorzScroll != m_nHorzScroll )
	{
		Refresh(false);
		SetScrollbar(wxHORIZONTAL, m_nHorzScroll, m_charCountWindow.GetWidth(), m_charCountView.GetWidth());
		PlaceCaret();
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnEditCut(wxCommandEvent& _event)
//void CHexEditCtrl::OnEditCut()
{
	if (m_readOnly) return;

	if ( (m_editMode & EDIT_INSERT) || m_allowChangeSize )
	{
		if ( !IsSelectionEmpty() ) 
		{
			OnEditCopy(_dummy_command);
			DeleteSelection();
			Refresh(false);
		}
	}
}

void CHexEditCtrl::OnEditCopy(wxCommandEvent& _event)
//void CHexEditCtrl::OnEditCopy()
{
	if ( IsSelectionEmpty() ) return;

	if ( !wxTheClipboard->Open() )
		return;
	//VERIFY(::EmptyClipboard());

	// size of selection in bytes
	int	dwLen = (m_selEnd-m_selStart+1)*(m_digitsInData/2);

	//m_data.push_back(0); //so that string gets terminated
	std::vector<wxByte>::pointer ptr = &m_data[m_selStart*(m_digitsInData/2)];

	/*wxDataObjectSimple* binaryData = new wxDataObjectSimple();
	binaryData->SetData(dwLen, ptr);
	binaryData->SetFormat(wxDataFormat(wxT("application/octet-stream")));*/

	char* str = new char[dwLen + 1];
	for (int i = 0; i < dwLen; ++i) //FIXME: slow
		str[i] = *(ptr + i);
	str[dwLen] = '\0';
	wxString textData(wxConvCurrent->cMB2WX(str));
	delete [] str;

	wxTheClipboard->SetData(new wxTextDataObject(textData));
	//wxTheClipboard->AddData(binaryData);

	//m_data.pop_back(); //pop the string terminator
	wxTheClipboard->Close();
}

void CHexEditCtrl::OnEditPaste(wxCommandEvent& _event)
//void CHexEditCtrl::OnEditPaste()
{
	return; //FIXME: because of inconsistent interface of wxMBConv across ANSI and UNICODE
			//builds the code below needs some workaround. But it's not needed now anyway.
	/*
	if (m_readOnly) return;
	
	if (!wxTheClipboard->Open())
		return;

	wxCustomDataObject binaryData;
	wxTextDataObject textData;

	bool bIsBinaryData = false;
	bool ok = false;
	if (wxTheClipboard->IsSupported(wxDataFormat(wxT("application/octet-stream")))) {
		bIsBinaryData = true;
		ok = wxTheClipboard->GetData(binaryData);
	} else if (wxTheClipboard->IsSupported(wxDF_TEXT) || wxTheClipboard->IsSupported(wxDF_UNICODETEXT)) { //FIXME: is this the right way?
		ok = wxTheClipboard->GetData(textData);
	}
	
	if (!ok) {
		wxTheClipboard->Close();
		return;
	}

	const wxWX2MBbuf buffer;
	wxByte* data;
	size_t cbData = 0;
	if (bIsBinaryData) {
		data = (wxByte*)binaryData.GetData();
		cbData = binaryData.GetSize();
	} else {
		buffer = wxConvCurrent->cWX2MB(textData.GetText().c_str());
		data = (wxByte*)static_cast<const char*>(buffer);
		cbData = textData.GetTextLength();
	}

	if (cbData <= 0) {
		wxTheClipboard->Close();
		return;
	}

	if ( m_editMode & EDIT_INSERT )
	{
		DeleteSelection();
		InsertData ( m_editPos, ((long)cbData+m_digitsInData/2-1)/(m_digitsInData/2) ); //FIXME: insterts trash when not aligned to (m_digitsInData/2)
	}
	else 
	{
		if ( !IsSelectionEmpty() )
		{
			m_editPos = m_selStart;
			if ( (long)cbData > (m_selEnd - m_selStart + 1) )
				cbData = m_selEnd - m_selStart + 1;
			ClearSelection();
		}

		size_t dwDataLen = m_origDataSize;
		if ( m_editPos*(m_digitsInData/2)+(long)cbData > (long)dwDataLen )
		{
			// need to add bytes at the end
			if (m_allowChangeSize)
				InsertData ( (long)dwDataLen/(m_digitsInData/2), (long)(cbData - (dwDataLen-m_editPos*(m_digitsInData/2))+(m_digitsInData/2)-1)/(m_digitsInData/2) );
			else
				cbData = dwDataLen - m_editPos*(m_digitsInData/2);
		}
	}

	if ( cbData > 0 )
	{
		std::vector<wxByte>::pointer ptr = &m_data[m_editPos*(m_digitsInData/2)];
		memcpy(ptr, data, cbData);

		m_dataModified = true;
		Refresh(false);
	}

	wxTheClipboard->Close();
	*/
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnTimer(wxTimerEvent& _event)
//void CHexEditCtrl::OnTimer(UINT nIDEvent) 
{
	// called when mouse went outside window during selection
	assert ( m_bTimer );

	if (_event.GetId() == ID_M_TIMER)
	{
		RecalcSelection ( m_prevMousePoint );
	}
	else
		_event.Skip();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnContextMenu(wxMouseEvent& _event)
//void CHexEditCtrl::OnContextMenu(CWnd*, wxPoint point)
{
	/*wxPoint point = _event.GetPosition();
	if (point == wxDefaultPosition){
		//keystroke invocation
		point = ClientToScreen(wxPoint(5, 5));
	}*/

	PopupMenu(m_popupMenu); //let wxWidgets choose the location
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnEditSelectAll(wxCommandEvent& _event)
//void CHexEditCtrl::OnEditSelectAll()
{
	if ( m_data.size() == 0 ) 
		return;
	m_editPos = m_selStart = 0;
	m_selEnd = (long)m_data.size()/(m_digitsInData/2)-1;
	ChangeEditPos (0, 0, true );	// place caret & repaint
}

void CHexEditCtrl::OnUpdateEditSelectAll(wxUpdateUIEvent& _event)
//void CHexEditCtrl::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	_event.Enable(m_data.size() != 0);
}

void CHexEditCtrl::OnUpdateEditCopy(wxUpdateUIEvent& _event)
//void CHexEditCtrl::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	_event.Enable(!IsSelectionEmpty());
}

void CHexEditCtrl::OnUpdateEditCut(wxUpdateUIEvent& _event)
//void CHexEditCtrl::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	_event.Enable(!m_readOnly && !IsSelectionEmpty() && ((m_editMode & EDIT_INSERT) || m_allowChangeSize));
}

void CHexEditCtrl::OnUpdateEditPaste(wxUpdateUIEvent& _event)
//void CHexEditCtrl::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	if (m_readOnly) {
		_event.Enable(false);
		return;
	}

	if (!wxTheClipboard->Open())
		return;

	bool ok = false;
	if (wxTheClipboard->IsSupported(wxDataFormat(wxT("application/octet-stream")))) {
		ok = true;
	} else if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
		ok = true;
	}

	wxTheClipboard->Close();
		
	_event.Enable(ok);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::OnSize(wxSizeEvent& _event)
//void CHexEditCtrl::OnSize(UINT nType, int cx, int cy) 
{
	//COleControl::OnSize(nType, cx, cy);

	RecalcLayout();
	Refresh(false);
	_event.Skip();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Edit methods

void CHexEditCtrl::InvalidateEditRect(long nEditPos)
{
	wxRect rcInvalid;
	long nPos = nEditPos - m_viewPos;
	//wxASSERT( nPos >= 0 && nPos < m_columns*m_charCountWindow.GetHeight() );
	if ( nPos < 0 && nPos >= m_columns*m_charCountWindow.GetHeight() )
		return;

	// invalidate rect of the number
	rcInvalid.x = (nPos % m_columns * (m_digitsInData+1) + m_addrMargin - m_nHorzScroll)*m_cellSize.GetWidth()+m_cellSize.GetWidth()/2;
	rcInvalid.y = nPos / m_columns * m_cellSize.GetHeight();
	rcInvalid.width = (m_digitsInData+1)*m_cellSize.GetWidth();
	rcInvalid.height = m_cellSize.GetHeight();
	Refresh(false, &rcInvalid);

	//if ( m_bRealShowAscii )
	{
		// invalidate rect of corresponding ASCII char
		rcInvalid.x = (nPos % m_columns * (m_digitsInData/2) + m_asciiMargin - m_nHorzScroll)*m_cellSize.GetWidth()+m_cellSize.GetWidth()/2;
		rcInvalid.y = nPos / m_columns * m_cellSize.GetHeight();
		rcInvalid.width = (m_digitsInData/2)*m_cellSize.GetWidth();
		rcInvalid.height = m_cellSize.GetHeight();
		Refresh(false, &rcInvalid);
		//Refresh(false);
	}
}

void CHexEditCtrl::DeleteSelection()
{
	if ( !IsSelectionEmpty())
	{
		DeleteData ( m_selStart, m_selEnd-m_selStart+1 );
		m_editPos = m_selStart;
		m_dataModified = true;
		//		m_viewPos = m_editPos/m_columns * m_columns;
		ClearSelection();
		NormalizeEditPos();
		PlaceCaret();
	}
}

void CHexEditCtrl::RecalcLayout()
{
	//if ( m_hWnd == 0 ) return;		// invisible window

	if ( m_data.size()+m_dwStartAddr > 0x10000 )
		m_digitsInAddress = 8;
	else
		m_digitsInAddress = 4;

	int nColumns = m_columns;

	wxClientDC dc(this);
	dc.SetFont(m_font);

	// determine char size
	m_cellSize = dc.GetTextExtent(wxT("0"));
	//pdc->LPtoDP ( &m_cellSize );

	m_rcClient = wxRect(GetClientSize());

	// compute entire rect of the control, including scroll bars
	if (m_vScrollShown)
		m_rcClient.width += wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
	if (m_hScrollShown) //FIXME: is this correct?
		m_rcClient.height += wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y);

	// before calculations
	bool bShowSbVert = false;	// need to show vertical scroll bar?
	bool bShowSbHorz = false;	// need to show horizontal scroll bar?

	// after calculations
	bool bShowSbVert2 = false;	
	bool bShowSbHorz2 = false;	

	//m_bRealShowAscii = (m_digitsInData == 2 && m_showAscii);

	do
	{
		bShowSbVert = bShowSbVert2;
		bShowSbHorz = bShowSbHorz2;

		// first pass - compute params when scrollbars are hidden
		// next passes (0, 1, or 2) - recalculate params if client rect was shrunk after showing scrollbars
		// we draw a half-cell margin on either side of the window
		m_charCountWindow.SetWidth( m_rcClient.GetWidth() / m_cellSize.GetWidth() );
		m_charCountWindow.SetHeight( m_rcClient.GetHeight() / m_cellSize.GetHeight() );

		//		if ( m_digitsInData != 2 )
		//			m_bRealShowAscii = false;
		if ( m_showAddress )
			m_addrMargin = m_digitsInAddress+2;
		else
			m_addrMargin = 0;

		if ( nColumns == 0 )
		{
			// auto columns
			int charsLeft = m_charCountWindow.GetWidth() - m_addrMargin - 1; //we subtract 1 for half-cell margins on either side of the window
			charsLeft -= 1; //space between hex and ascii
			int colWidth = (m_digitsInData + 1) + (m_digitsInData/2); //(hex size + space) + chars size
			m_columns = charsLeft/colWidth;

			if ( m_columns <= 0 )
				m_columns = 1;
		}

		m_asciiMargin = m_addrMargin + (m_digitsInData+1) * m_columns + 1;
		m_charCountView.SetWidth(m_asciiMargin + m_columns * (m_digitsInData/2) + 1); //we add 1 for half-cell margins on either side of the window
		m_charCountView.SetHeight( (int)_ceil_div(m_origDataSize, m_columns*(m_digitsInData/2)) );

		if ( m_charCountView.GetWidth() > m_charCountWindow.GetWidth() && !bShowSbHorz )
		{
			m_rcClient.height -= wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y);
			bShowSbHorz2 = true;
		}
		if ( m_charCountView.GetHeight() > m_charCountWindow.GetHeight() && !bShowSbVert )
		{
			m_rcClient.width -= wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
			bShowSbVert2 = true;
		}
	} while ( bShowSbHorz != bShowSbHorz2 || bShowSbVert != bShowSbVert2 );

	// rounding data length to (m_digitsInData/2)
	size_t dataSize = _ceil_div(m_origDataSize, m_digitsInData/2) * (m_digitsInData/2);
	m_data.resize(dataSize);

	//	m_nHorzScroll = 0;
	m_viewPos = m_viewPos / m_columns * m_columns;
	NormalizeEditPos();
	UpdateScrollBars();

	if (!m_vScrollShown)
		m_viewPos = 0;
}

void CHexEditCtrl::PlaceCaret()
{
	if (wxWindow::FindFocus() != this)
		return;

	wxPoint pt;

	if ( !IsSelectionEmpty() && m_editPos == m_selEnd+1 )
	{
		// place caret just after the selection
		if ( m_editMode & EDIT_BYTES )
		{
			pt.x = m_selEnd % m_columns * (m_digitsInData+1) + m_digitsInData + 1;
			if ( m_showAddress )
				pt.x += m_addrMargin;
		}
		else
			pt.x = m_asciiMargin + m_selEnd % m_columns + 1;

		pt.y = (m_selEnd - m_viewPos)/m_columns;
	}
	else
	{
		if ( m_editMode & EDIT_BYTES )
		{
			pt.x = m_editPos % m_columns * (m_digitsInData+1) + m_nEditDigit;
			if ( m_showAddress )
				pt.x += m_addrMargin;
		}
		else
			pt.x = m_asciiMargin + m_editPos % m_columns;

		pt.y = (m_editPos - m_viewPos)/m_columns;
	}
	pt.x = (pt.x - m_nHorzScroll)*m_cellSize.GetWidth()+m_cellSize.GetWidth()/2-1;

	pt.y *= m_cellSize.GetHeight();

	wxCaret* caret = this->GetCaret();
	caret->Move(pt);

	InvalidateEditRect(m_editPos);
	SendChangedEvent();
}

void CHexEditCtrl::ChangeEditPos(long dx, long dy, bool bRepaint /* = false */)
{
	InvalidateEditRect(m_editPos);

	m_nEditDigit = 0;
	m_editPos += dy*m_columns + dx;
	if ( NormalizeEditPos())
		bRepaint = true;

	if ( UpdateScrollBars ())
		bRepaint = true;

	if ( bRepaint )
		Refresh(false);
	PlaceCaret();
}

void CHexEditCtrl::ChangeEditPos(wxPoint pt)
{
	InvalidateEditRect(m_editPos);

	pt.x = (pt.x - m_cellSize.GetWidth()/2) / m_cellSize.GetWidth();
	pt.y /= m_cellSize.GetHeight();

	pt.x += m_nHorzScroll;

	if ( (pt.x >= m_asciiMargin /*&& m_bRealShowAscii*/ && !m_bMouseMove) || 
		(m_bMouseMove && !(m_editMode & EDIT_BYTES)))	
		// click in the ascii field or extending selection in ascii field

		/* if selection was started in ascii, we never shouldn't switch 
		to hex field until selection is finished
		The same, when selection started in hex field
		*/
	{
		if ( pt.x < m_asciiMargin )
			pt.x = m_asciiMargin;
		else
			if ( pt.x >= m_asciiMargin + m_columns*m_digitsInData/2 )
				pt.x = m_asciiMargin + m_columns*m_digitsInData/2 - 1;
		m_editPos = m_viewPos + (pt.x-m_asciiMargin) / (m_digitsInData/2) + pt.y * m_columns;
		m_editMode &= ~EDIT_BYTES;
	}
	else
	{
		m_editMode |= EDIT_BYTES;
		if ( pt.x >= m_asciiMargin )
			pt.x = m_asciiMargin - 1;
		pt.x -= m_addrMargin;
		if ( pt.x < 0 )	// clicked in address area
			pt.x = 0;
		if ( pt.x >= m_columns*(m_digitsInData+1))
			pt.x = (m_columns-1)*(m_digitsInData+1);

		m_nEditDigit = pt.x % (m_digitsInData+1);
		if ( m_nEditDigit == m_digitsInData )
		{
			m_nEditDigit = m_digitsInData-1;
		}
		m_editPos = m_viewPos + pt.x / (m_digitsInData+1) + pt.y * m_columns;
	}

	NormalizeEditPos();
	UpdateScrollBars();
}

bool CHexEditCtrl::NormalizeEditPos()
{
	bool bRepaint = false;
	size_t dwDataSize = m_data.size()/(m_digitsInData/2);

	if ( m_editPos < 0 )
		m_editPos = 0;
	else if ( m_editPos >= (long)dwDataSize )
	{
		m_editPos = (long)dwDataSize;
		m_nEditDigit = 0;
	}

	// change m_viewPos if m_editPos is moved out of the visible area
	if (m_viewPos > m_editPos)
	{
		m_viewPos = m_editPos / m_columns * m_columns;
		bRepaint = true;
	}
	else if (m_viewPos + m_columns * m_charCountWindow.GetHeight() <= m_editPos)
	{
		m_viewPos = (m_editPos / m_columns - m_charCountWindow.GetHeight() + 1) * m_columns;
		bRepaint = true;
	}

	// if m_viewPos is too near to the end of data, decrease m_viewPos so entire page is displayed
	// (this may happen after deleting large selection or changing properties)
	if ( wxUint32(m_viewPos) > m_data.size() / (m_digitsInData/2) - m_columns*(m_charCountWindow.GetHeight()-1))
	{
		m_viewPos = (long)m_data.size() / (m_digitsInData/2) / m_columns * m_columns - m_columns*(m_charCountWindow.GetHeight()-1);
		if ( m_viewPos < 0 ) m_viewPos = 0;
	}

	int nPosX;		// x coordinate of caret in view
	if ( m_editMode & EDIT_BYTES )
		nPosX = m_addrMargin + m_editPos % m_columns * (m_digitsInData+1);
	else	// EDIT_ASCII
		nPosX = m_asciiMargin + m_editPos % m_columns;

	if ( nPosX < m_nHorzScroll ) //m_nHorzScroll is half-cell misaligned (margins)
	{
		m_nHorzScroll = nPosX;
		bRepaint = true;
	}
	else
	{
		if ( m_editMode & EDIT_BYTES ) 
			nPosX += m_digitsInData;	// to make entire number visible
		else
			nPosX++;
		if ( nPosX+1 - m_nHorzScroll >= m_charCountWindow.GetWidth() ) //m_nHorzScroll is half-cell misaligned (margins)
		{
			m_nHorzScroll = nPosX+1 - m_charCountWindow.GetWidth();
			bRepaint = true;
		}
	}
	return bRepaint;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CHexEditCtrl::InsertData(wxUint32 dwPos, wxUint32 dwCount/*=1*/)
{
	// convert to bytes
	dwPos *= (m_digitsInData/2);
	dwCount *= (m_digitsInData/2);

	size_t dwArrSize = m_origDataSize;
	assert ( dwCount > 0 );
	assert ( dwPos <= dwArrSize );

	if ( dwArrSize+dwCount <= dwArrSize || dwArrSize+dwCount >= 0x80000000 )
	{
		// overflow
		wxFAIL_MSG(wxT("Out of memory."));
		return;
	}

	m_data.resize( dwArrSize + dwCount );
	m_origDataSize = m_data.size();

	if ( dwPos != dwArrSize )
	{
		std::vector<wxByte>::pointer ptrPos = &m_data[dwPos];
		std::vector<wxByte>::pointer ptrPosC = ptrPos + dwCount; //&m_data[dwPos + dwCount]; -- out of range error, when trying to get past the vector
		memmove(ptrPosC, ptrPos, dwArrSize-dwPos);
		memset(ptrPos, 0, dwCount);
	}
	RecalcLayout();
}

void CHexEditCtrl::DeleteData(wxUint32 dwPos, wxUint32 dwCount /*=1*/)
{
	// convert to bytes
	dwPos *= (m_digitsInData/2);
	dwCount *= (m_digitsInData/2);

	size_t dwArrSize = m_origDataSize;
	assert ( dwCount > 0 );
	assert ( dwPos < dwArrSize );

	if ( dwPos != dwArrSize-1 )
	{
		std::vector<wxByte>::pointer ptrPos = &m_data[dwPos];
		std::vector<wxByte>::pointer ptrPosC = ptrPos + dwCount; //&m_data[dwPos + dwCount]; -- out of range error, when trying to get past the vector
		memmove(ptrPos, ptrPosC, dwArrSize-dwPos-dwCount);
	}

	m_data.resize(dwArrSize - dwCount);
	m_origDataSize = m_data.size();
	RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CHexEditCtrl::UpdateScrollBars()
{
	bool bRepaint = false;

	{ //wxVERTICAL
	int oldMax = GetScrollRange(wxVERTICAL);
	int oldPage = GetScrollThumb(wxVERTICAL);
	int oldPos = GetScrollPos(wxVERTICAL);

	int newMax = m_charCountView.GetHeight();
	int newPage = m_charCountWindow.GetHeight();
	int newPos = (int)_ceil_div(m_viewPos, m_columns);

	if (newPos != oldPos || newMax != oldMax || newPage != oldPage)
		bRepaint = true;

	if(newMax > newPage) {
		m_vScrollShown = true;
		SetScrollbar(wxVERTICAL, newPos, newPage, newMax);
	} else {
		m_vScrollShown = false;
		SetScrollbar(wxVERTICAL, 0, 0, 0);
	}
	}

	{ //wxHORIZONTAL
	int oldMax = GetScrollRange(wxHORIZONTAL);
	int oldPage = GetScrollThumb(wxHORIZONTAL);
	int oldPos = GetScrollPos(wxHORIZONTAL);

	int newMax = m_charCountView.GetWidth();
	int newPage = m_charCountWindow.GetWidth();
	int newPos = m_nHorzScroll;

	if ( (newMax > newPage) && (newPos + newPage > newMax) )
		newPos = m_nHorzScroll = newMax - newPage;
	if (newMax <= newPage)
		newPos = m_nHorzScroll = 0;
	if (newPos != oldPos || newMax != oldMax || newPage != oldPage)
		bRepaint = true;

	if(newMax > newPage ) {
		if (!m_hScrollShown)
			m_nHorzScroll = 0; //FIXME: this is ugly workaround - it shouldn't be here
		m_hScrollShown = true;
		SetScrollbar(wxHORIZONTAL, newPos, newPage, newMax);
	} else {
		m_hScrollShown = false;
		SetScrollbar(wxHORIZONTAL, 0, 0, 0);
	}
	}

	return bRepaint;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

inline void CHexEditCtrl::ClearSelection()
{
	m_selStart = m_selEnd = -1;
	Refresh(false);
}

inline bool CHexEditCtrl::IsSelectionEmpty()
{
	return ( m_selStart == -1 );
}

void CHexEditCtrl::RecalcSelection(wxPoint point)
{
	if ( m_data.size() == 0 )
		return;
	if ( m_bMouseDown )
	{
		int nPrevSelStart = m_selStart, nPrevSelEnd = m_selEnd;

		ChangeEditPos ( point );
		if ( m_posMouseDown < m_editPos )
		{
			if ( wxUint32(m_editPos*(m_digitsInData/2)) == m_data.size())
				m_editPos--;
			m_selStart = m_posMouseDown; 
			m_selEnd = m_editPos;
			m_editPos = m_selEnd;
			m_nEditDigit = 0;
		}
		else
		{
			m_selStart = m_editPos;
			m_selEnd = m_posMouseDown; 
			m_editPos = m_selStart;
			m_nEditDigit = 0;
		}
		if ( nPrevSelStart != m_selStart || nPrevSelEnd != m_selEnd )
			Refresh(false);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CHexEditCtrl::EnterNumber()
{
	if ( !IsSelectionEmpty())
	{
		if ( (m_editMode & EDIT_INSERT) || m_allowChangeSize )
		{
			// delete current selection and insert 1 number
			m_editPos = m_selStart;
			DeleteSelection();
			InsertData ( m_editPos );
			Refresh(false);
		}
		else
		{
			ClearSelection();
		}
	}
	else	// is m_editPos at the end?
		if ( wxUint32(m_editPos)*(m_digitsInData/2) == m_origDataSize)
		{
			if ( (m_editMode & EDIT_INSERT) || m_allowChangeSize )
			{
				InsertData ( m_editPos );
				if ( m_editPos % m_columns != m_columns-1)
					InvalidateEditRect (m_editPos);
				else
					Refresh(false);	// we need to add new line
			}
			else
				return false;
		}
		else if	((m_editMode & EDIT_INSERT) && m_nEditDigit == 0 )
			// insert 1 number
		{
			InsertData ( m_editPos );
			Refresh(false);
		}
		m_dataModified = true;
		return true;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

