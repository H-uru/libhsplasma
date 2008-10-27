#ifndef _PYCLUSTERGROUP_H
#define _PYCLUSTERGROUP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLODDist* fThis;
} pyLODDist;

typedef struct {
    PyObject_HEAD
    class plClusterGroup* fThis;
    bool fPyOwned;
} pyClusterGroup;

extern PyTypeObject pyLODDist_Type;
PyObject* Init_pyLODDist_Type();
PyObject* pyLODDist_FromLODDist(class plLODDist& dist);

extern PyTypeObject pyClusterGroup_Type;
PyObject* Init_pyClusterGroup_Type();
int pyClusterGroup_Check(PyObject* obj);
PyObject* pyClusterGroup_FromClusterGroup(class plClusterGroup* group);

}

#endif
