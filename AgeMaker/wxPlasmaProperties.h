/*
#ifndef _WXPLASMAPROPERTIES_H
#define _WXPLASMAPROPERTIES_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/propdev.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>
#include "../Plasma/DynLib/PageID.h"

#define wxPGVariantToPageId(A) *((PageID*)wxPGVariantToVoidPtr(A))

WX_PG_DECLARE_PROPERTY(PageID, const PageID&, PageID())

#endif */

