#ifndef _PLVAULTNODEREF_H
#define _PLVAULTNODEREF_H

#include "../Sys/plUnifiedTime.h"

DllClass plVaultNodeRef {
protected:
    unsigned int fSaver, fParent, fChild;
    plUnifiedTime fAutoTime;
    bool fSeen;

public:
    plVaultNodeRef();
    plVaultNodeRef(const plVaultNodeRef& init);
    plVaultNodeRef& operator=(const plVaultNodeRef& init);

    void read(hsStream* S);
    void write(hsStream* S);

public:
    unsigned int getSaver() const { return fSaver; }
    unsigned int getParent() const { return fParent; }
    unsigned int getChild() const { return fChild; }
    plUnifiedTime getAutoTime() const { return fAutoTime; }
    bool getSeen() const { return fSeen; }

    void setSaver(unsigned int id) { fSaver = id; }
    void setParent(unsigned int id) { fParent = id; }
    void setChild(unsigned int id) { fChild = id; }
    void setAutoTime(const plUnifiedTime& time) { fAutoTime = time; }
    void setSeen(bool seen) { fSeen = seen; }
};

#endif
