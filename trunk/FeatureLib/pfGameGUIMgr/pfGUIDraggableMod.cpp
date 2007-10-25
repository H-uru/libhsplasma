#include "pfGUIDraggableMod.h"

pfGUIDraggableMod::pfGUIDraggableMod() : fDragging(false) { }
pfGUIDraggableMod::~pfGUIDraggableMod() { }

IMPLEMENT_CREATABLE(pfGUIDraggableMod, kGUIDraggableMod, pfGUIControlMod)
