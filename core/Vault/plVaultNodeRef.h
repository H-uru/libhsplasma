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

    unsigned int getSaver() const;
    unsigned int getParent() const;
    unsigned int getChild() const;
    plUnifiedTime getAutoTime() const;
    bool getSeen() const;

    void setSaver(unsigned int id);
    void setParent(unsigned int id);
    void setChild(unsigned int id);
    void setAutoTime(const plUnifiedTime& time);
    void setSeen(bool seen);
};

#endif
