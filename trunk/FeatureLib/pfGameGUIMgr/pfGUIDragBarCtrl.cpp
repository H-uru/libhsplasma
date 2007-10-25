#include "pfGUIDragBarCtrl.h"

pfGUIDragBarCtrl::pfGUIDragBarCtrl() : fDragging(false), fAnchored(false) { }
pfGUIDragBarCtrl::~pfGUIDragBarCtrl() { }

IMPLEMENT_CREATABLE(pfGUIDragBarCtrl, kGUIDragBarCtrl, pfGUIControlMod)
