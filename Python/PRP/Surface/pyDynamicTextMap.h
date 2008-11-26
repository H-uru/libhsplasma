#ifndef _PYDYNAMICTEXTMAP_H
#define _PYDYNAMICTEXTMAP_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plDynamicTextMap* fThis;
    bool fPyOwned;
} pyDynamicTextMap;

extern PyTypeObject pyDynamicTextMap_Type;
PyObject* Init_pyDynamicTextMap_Type();
int pyDynamicTextMap_Check(PyObject* obj);
PyObject* pyDynamicTextMap_FromDynamicTextMap(class plDynamicTextMap* img);

}

#endif
