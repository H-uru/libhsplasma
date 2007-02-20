#include "wxPlasmaProperties.h"

/*
WX_PG_IMPLEMENT_VALUE_TYPE_VOIDP(PageID, wxPageIdProperty, PageID())

class wxPageIdPropertyClass : public wxPGPropertyWithChildren {
    WX_PG_DECLARE_PROPERTY_CLASS()
public:

    wxPageIdPropertyClass(const wxString& label, const wxString& name, const PageID& value);
    virtual ~wxPageIdPropertyClass();

    WX_PG_DECLARE_PARENTAL_TYPE_METHODS()
    WX_PG_DECLARE_PARENTAL_METHODS()

protected:
    PageID m_value;

    void SetValueI(const PageID& value) {
        m_value = value;
        RefreshChildren();
    }
};

WX_PG_IMPLEMENT_PROPERTY_CLASS(wxPageIdProperty, wxBaseParentProperty,
                               PageID, const PageID&, TextCtrl)

wxPageIdPropertyClass::wxPageIdPropertyClass(const wxString& label, const wxString& name,
                       const PageID& value) : wxPGPropertyWithChildren(label, name) {
    wxPG_INIT_REQUIRED_TYPE(PageID)
    SetValueI(value);
    AddChild(wxIntProperty(wxT("Sequence Prefix"), wxPG_LABEL, value.getSeqPrefix()));
    AddChild(wxIntProperty(wxT("Page Number"), wxPG_LABEL, value.getPageNum()));
}

wxPageIdPropertyClass::~wxPageIdPropertyClass() { }

void wxPageIdPropertyClass::DoSetValue(wxPGVariant value) {
    SetValueI(wxPGVariantToPageId(value));
}

wxPGVariant wxPointPropertyClass::DoGetValue() const {
    return wxPGVariantCreator(m_value);
}

void wxPointPropertyClass::RefreshChildren() {
    if (!GetCount()) return;
    Item(0)->DoSetValue(m_value.getSeqPrefix());
    Item(1)->DoSetValue(m_value.getPageNum());
}

void wxPointPropertyClass::ChildChanged(wxPGProperty* p) {
    switch (p->GetIndexInParent()) {
    case 0:
        m_value.setSeqPrefix(p->DoGetValue().GetInt());
        break;
    case 1:
        m_value.setPageNum(p->DoGetValue().GetInt());
        break;
    }
} */

