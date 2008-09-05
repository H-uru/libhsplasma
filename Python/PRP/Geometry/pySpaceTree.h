#ifndef _PYSPACETREE_H
#define _PYSPACETREE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSpaceTreeNode* fThis;
} pySpaceTreeNode;

typedef struct {
    PyObject_HEAD
    class plSpaceTree* fThis;
    bool fPyOwned;
} pySpaceTree;

extern PyTypeObject pySpaceTreeNode_Type;
PyObject* Init_pySpaceTreeNode_Type();
int pySpaceTreeNode_Check(PyObject* obj);
PyObject* pySpaceTreeNode_FromSpaceTreeNode(const plSpaceTreeNode& node);

extern PyTypeObject pySpaceTree_Type;
PyObject* Init_pySpaceTree_Type();
int pySpaceTree_Check(PyObject* obj);
PyObject* pySpaceTree_FromSpaceTree(class plSpaceTree* obj);

}

#endif
