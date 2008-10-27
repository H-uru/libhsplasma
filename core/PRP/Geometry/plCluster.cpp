#include "plCluster.h"
#include "plClusterGroup.h"

plCluster::plCluster() { }

plCluster::~plCluster() {
    for (size_t i=0; i<fInstances.getSize(); i++)
        delete fInstances[i];
}

void plCluster::read(hsStream* S, plClusterGroup* group) {
    fEncoding.read(S);
    fGroup = group;
    unsigned int numVerts = fGroup->getTemplate().getNumVerts();
    fInstances.setSizeNull(S->readInt());
    for (size_t i=0; i<fInstances.getSize(); i++) {
        fInstances[i] = new plSpanInstance();
        fInstances[i]->read(S, fEncoding, numVerts);
    }
}

void plCluster::write(hsStream* S) {
    fEncoding.write(S);
    S->writeInt(fInstances.getSize());
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->write(S);
}

void plCluster::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plCluster");

    prc->writeSimpleTag("Encoding");
    fEncoding.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Instances");
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}

void plCluster::prcParse(const pfPrcTag* tag, plClusterGroup* group) {
    if (tag->getName() != "plCluster")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fGroup = group;
    unsigned int numVerts = fGroup->getTemplate().getNumVerts();
    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Encoding") {
            if (child->hasChildren())
                fEncoding.prcParse(child->getFirstChild());
        } else if (child->getName() == "Instances") {
            fInstances.setSizeNull(child->countChildren());
            const pfPrcTag* inst = child->getFirstChild();
            for (size_t i=0; i<fInstances.getSize(); i++) {
                fInstances[i] = new plSpanInstance();
                fInstances[i]->prcParse(inst, fEncoding, numVerts);
                inst = inst->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

plSpanEncoding& plCluster::getEncoding() { return fEncoding; }
plClusterGroup* plCluster::getGroup() const { return fGroup; }
void plCluster::setGroup(plClusterGroup* group) { fGroup = group; }

size_t plCluster::getNumInstances() const { return fInstances.getSize(); }
plSpanInstance* plCluster::getInstance(size_t idx) const { return fInstances[idx]; }
void plCluster::addInstance(plSpanInstance* inst) { fInstances.append(inst); }

void plCluster::delInstance(size_t idx) {
    delete fInstances[idx];
    fInstances.remove(idx);
}

void plCluster::clearInstances() {
    for (size_t i=0; i<fInstances.getSize(); i++)
        delete fInstances[i];
    fInstances.clear();
}
