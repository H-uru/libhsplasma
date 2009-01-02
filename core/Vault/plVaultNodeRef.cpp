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

unsigned int plVaultNodeRef::getSaver() const { return fSaver; }
unsigned int plVaultNodeRef::getParent() const { return fParent; }
unsigned int plVaultNodeRef::getChild() const { return fChild; }
plUnifiedTime plVaultNodeRef::getAutoTime() const { return fAutoTime; }
bool plVaultNodeRef::getSeen() const { return fSeen; }

void plVaultNodeRef::setSaver(unsigned int id) { fSaver = id; }
void plVaultNodeRef::setParent(unsigned int id) { fParent = id; }
void plVaultNodeRef::setChild(unsigned int id) { fChild = id; }
void plVaultNodeRef::setAutoTime(const plUnifiedTime& time) { fAutoTime = time; }
void plVaultNodeRef::setSeen(bool seen) { fSeen = seen; }
