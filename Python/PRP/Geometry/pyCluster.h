#ifndef _PYCLUSTER_H
#define _PYCLUSTER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCluster* fThis;
    bool fPyOwned;
} pyCluster;

extern PyTypeObject pyCluster_Type;
PyObject* Init_pyCluster_Type();
int pyCluster_Check(PyObject* obj);
PyObject* pyCluster_FromCluster(class plCluster* cluster);

}

#endif
