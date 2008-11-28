#include "PlasmaTreeItem.h"

/* PlasmaTreeItem */
PlasmaTreeItem::PlasmaTreeItem()
              : fType(kTypeInvalid)
{ }

PlasmaTreeItem::PlasmaTreeItem(plAgeInfo* age)
              : fType(kTypeAge), fAge(age)
{ }

PlasmaTreeItem::PlasmaTreeItem(plPageInfo* page)
              : fType(kTypePage), fPage(page)
{ }

PlasmaTreeItem::PlasmaTreeItem(plKey obj)
              : fType(kTypeObject), fObject(obj)
{ }

PlasmaTreeItem::PlasmaTreeItem(unsigned int clsIdx)
              : fType(kTypeClass), fClass(clsIdx)
{ }

plAgeInfo* PlasmaTreeItem::getAge()
{ return (fType == kTypeAge) ? fAge : NULL; }

plPageInfo* PlasmaTreeItem::getPage()
{ return (fType == kTypePage) ? fPage : NULL; }

plKey PlasmaTreeItem::getObject()
{ return (fType == kTypeObject) ? fObject : plKey(); }

unsigned int PlasmaTreeItem::getClass()
{ return (fType == kTypeClass) ? fClass : 0xFFFF; }
