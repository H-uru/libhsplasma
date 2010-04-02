#include "plVaultNodeRef.h"

plVaultNodeRef::plVaultNodeRef()
              : fSaver(0), fParent(0), fChild(0), fSeen(false) { }

plVaultNodeRef::plVaultNodeRef(const plVaultNodeRef& init)
              : fSaver(init.fSaver), fParent(init.fParent), fChild(init.fChild),
                fAutoTime(init.fAutoTime), fSeen(init.fSeen) { }

plVaultNodeRef& plVaultNodeRef::operator=(const plVaultNodeRef& init) {
    fSaver = init.fSaver;
    fParent = init.fParent;
    fChild = init.fChild;
    fAutoTime = init.fAutoTime;
    fSeen = init.fSeen;
    return *this;
}

void plVaultNodeRef::read(hsStream* S) {
    fSaver = S->readInt();
    fParent = S->readInt();
    fChild = S->readInt();
    fAutoTime.read(S);
    fSeen = S->readBool();
}

void plVaultNodeRef::write(hsStream* S) {
    S->writeInt(fSaver);
    S->writeInt(fParent);
    S->writeInt(fChild);
    fAutoTime.write(S);
    S->writeBool(fSeen);
}
