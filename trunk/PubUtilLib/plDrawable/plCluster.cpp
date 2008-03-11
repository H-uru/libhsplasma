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
    unsigned int numVerts = fGroup->getTemplate()->getNumVerts();
    fInstances.setSizeNull(S->readInt());
    for (size_t i=0; i<fInstances.getSize(); i++) {
        fInstances[i] = new plSpanInstance();
        fInstances[i]->read(S, fEncoding, numVerts);
    }
}

void plCluster::write(hsStream* S) {
    fEncoding.write(S);
    unsigned int numVerts = fGroup->getTemplate()->getNumVerts();
    S->writeInt(fInstances.getSize());
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->write(S, fEncoding, numVerts);
}

void plCluster::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plCluster");

    prc->writeSimpleTag("Encoding");
    fEncoding.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Instances");
    unsigned int numVerts = fGroup->getTemplate()->getNumVerts();
    for (size_t i=0; i<fInstances.getSize(); i++)
        fInstances[i]->prcWrite(prc, fEncoding, numVerts);
    prc->closeTag();

    prc->closeTag();
}
