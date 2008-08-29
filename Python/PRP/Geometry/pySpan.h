#ifndef _PYSPAN_H
#define _PYSPAN_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSpan* fThis;
    bool fPyOwned;
} pySpan;

typedef struct {
    PyObject_HEAD
    class plVertexSpan* fThis;
    bool fPyOwned;
} pyVertexSpan;

typedef struct {
    PyObject_HEAD
    class plIcicle* fThis;
    bool fPyOwned;
} pyIcicle;

typedef struct {
    PyObject_HEAD
    class plParticleSpan* fThis;
    bool fPyOwned;
} pyParticleSpan;

extern PyTypeObject pySpan_Type;
PyObject* Init_pySpan_Type();
int pySpan_Check(PyObject* obj);
PyObject* pySpan_FromSpan(class plSpan* span);

extern PyTypeObject pyVertexSpan_Type;
PyObject* Init_pyVertexSpan_Type();
int pyVertexSpan_Check(PyObject* obj);
PyObject* pyVertexSpan_FromVertexSpan(class plVertexSpan* span);

extern PyTypeObject pyIcicle_Type;
PyObject* Init_pyIcicle_Type();
int pyIcicle_Check(PyObject* obj);
PyObject* pyIcicle_FromIcicle(class plIcicle* span);

extern PyTypeObject pyParticleSpan_Type;
PyObject* Init_pyParticleSpan_Type();
int pyParticleSpan_Check(PyObject* obj);
PyObject* pyParticleSpan_FromParticleSpan(class plParticleSpan* span);

}

#endif
