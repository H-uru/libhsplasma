#ifndef _PLASMATREEITEM_H
#define _PLASMATREEITEM_H

#include <wx/treectrl.h>
#include <PRP/plPageInfo.h>
#include <ResManager/plAgeInfo.h>
#include <PRP/KeyedObject/hsKeyedObject.h>

class PlasmaTreeItem : public wxTreeItemData {
public:
    enum Type { kTypeInvalid, kTypeAge, kTypePage, kTypeObject, kTypeClass };

protected:
    Type fType;
    plAgeInfo* fAge;
    plPageInfo* fPage;
    plKey fObject;
    unsigned int fClass;

public:
    PlasmaTreeItem();
    PlasmaTreeItem(plAgeInfo* age);
    PlasmaTreeItem(plPageInfo* page);
    PlasmaTreeItem(plKey obj);
    PlasmaTreeItem(unsigned int clsIdx);

    plAgeInfo* getAge();
    plPageInfo* getPage();
    plKey getObject();
    unsigned int getClass();
};

#endif
