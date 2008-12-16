#ifndef _PYATCANIM_H
#define _PYATCANIM_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plATCAnim* fThis;
    bool fPyOwned;
} pyATCAnim;

typedef struct {
    PyObject_HEAD
    class plEmoteAnim* fThis;
    bool fPyOwned;
} pyEmoteAnim;

typedef struct {
    PyObject_HEAD
    class plAGAnimBink* fThis;
    bool fPyOwned;
} pyAGAnimBink;

extern PyTypeObject pyATCAnim_Type;
PyObject* Init_pyATCAnim_Type();
int pyATCAnim_Check(PyObject* obj);
PyObject* pyATCAnim_FromATCAnim(class plATCAnim* anim);

extern PyTypeObject pyEmoteAnim_Type;
PyObject* Init_pyEmoteAnim_Type();
int pyEmoteAnim_Check(PyObject* obj);
PyObject* pyEmoteAnim_FromEmoteAnim(class plEmoteAnim* anim);

extern PyTypeObject pyAGAnimBink_Type;
PyObject* Init_pyAGAnimBink_Type();
int pyAGAnimBink_Check(PyObject* obj);
PyObject* pyAGAnimBink_FromAGAnimBink(class plAGAnimBink* anim);

}

#endif
