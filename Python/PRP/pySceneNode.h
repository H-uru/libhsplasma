#ifndef _PYSCENENODE_H
#define _PYSCENENODE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSceneNode* fThis;
    bool fPyOwned;
} pySceneNode;

extern PyTypeObject pySceneNode_Type;
PyObject* Init_pySceneNode_Type();
int pySceneNode_Check(PyObject* obj);
PyObject* pySceneNode_FromSceneNode(class plSceneNode* obj);

}

#endif
