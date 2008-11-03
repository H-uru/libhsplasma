#ifndef _PLLEAFCONTROLLER_H
#define _PLLEAFCONTROLLER_H

#include "plController.h"

DllClass plLeafController : public plController {
protected:
    unsigned int fType, fUruUnknown;
    hsTArray<hsKeyFrame*> fKeys;
    hsTArray<class plEaseController*> fEaseControllers;

public:
    plLeafController();
    virtual ~plLeafController();

    DECLARE_CREATABLE(plLeafController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    void AllocKeys(unsigned int numKeys, unsigned int type);
    void DeallocKeys();
    void AllocControllers(unsigned int numControllers);
    void DeallocControllers();

    void IReadUruController(hsStream* S);
    void IWriteUruController(hsStream* S);

public:
    plLeafController* ExpandToKeyController() const;
    plLeafController* CompactToLeafController() const;

    bool hasKeys() const;
    bool hasEaseControllers() const;

    unsigned int getType() const;
    const hsTArray<hsKeyFrame*>& getKeys() const;
    const hsTArray<class plEaseController*>& getEaseControllers() const;

    void setKeys(const hsTArray<hsKeyFrame*>& keys, unsigned int type);
    void setEaseControllers(const hsTArray<class plEaseController*>& controllers);
};

#endif
