#ifndef _PYKEYS_H
#define _PYKEYS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    struct hsKeyFrame* fThis;
    bool fPyOwned;
} pyKeyFrame;

typedef struct {
    PyObject_HEAD
    struct hsPoint3Key* fThis;
    bool fPyOwned;
} pyPoint3Key;

typedef struct {
    PyObject_HEAD
    struct hsScalarKey* fThis;
    bool fPyOwned;
} pyScalarKey;

typedef struct {
    PyObject_HEAD
    struct hsScaleKey* fThis;
    bool fPyOwned;
} pyScaleKey;

typedef struct {
    PyObject_HEAD
    struct hsQuatKey* fThis;
    bool fPyOwned;
} pyQuatKey;

typedef struct {
    PyObject_HEAD
    struct hsCompressedQuatKey32* fThis;
    bool fPyOwned;
} pyCompressedQuatKey32;

typedef struct {
    PyObject_HEAD
    struct hsCompressedQuatKey64* fThis;
    bool fPyOwned;
} pyCompressedQuatKey64;

typedef struct {
    PyObject_HEAD
    struct hsG3DSMaxKeyFrame* fThis;
    bool fPyOwned;
} pyG3DSMaxKeyFrame;

typedef struct {
    PyObject_HEAD
    struct hsMatrix33Key* fThis;
    bool fPyOwned;
} pyMatrix33Key;

typedef struct {
    PyObject_HEAD
    struct hsMatrix44Key* fThis;
    bool fPyOwned;
} pyMatrix44Key;

extern PyTypeObject pyKeyFrame_Type;
PyObject* Init_pyKeyFrame_Type();
int pyKeyFrame_Check(PyObject* obj);
PyObject* pyKeyFrame_FromKeyFrame(struct hsKeyFrame* frame);

extern PyTypeObject pyPoint3Key_Type;
PyObject* Init_pyPoint3Key_Type();
int pyPoint3Key_Check(PyObject* obj);
PyObject* pyPoint3Key_FromPoint3Key(struct hsPoint3Key* frame);

extern PyTypeObject pyScalarKey_Type;
PyObject* Init_pyScalarKey_Type();
int pyScalarKey_Check(PyObject* obj);
PyObject* pyScalarKey_FromScalarKey(struct hsScalarKey* frame);

extern PyTypeObject pyScaleKey_Type;
PyObject* Init_pyScaleKey_Type();
int pyScaleKey_Check(PyObject* obj);
PyObject* pyScaleKey_FromScaleKey(struct hsScaleKey* frame);

extern PyTypeObject pyQuatKey_Type;
PyObject* Init_pyQuatKey_Type();
int pyQuatKey_Check(PyObject* obj);
PyObject* pyQuatKey_FromQuatKey(struct hsQuatKey* frame);

extern PyTypeObject pyCompressedQuatKey32_Type;
PyObject* Init_pyCompressedQuatKey32_Type();
int pyCompressedQuatKey32_Check(PyObject* obj);
PyObject* pyCompressedQuatKey32_FromCompressedQuatKey32(struct hsCompressedQuatKey32* frame);

extern PyTypeObject pyCompressedQuatKey64_Type;
PyObject* Init_pyCompressedQuatKey64_Type();
int pyCompressedQuatKey64_Check(PyObject* obj);
PyObject* pyCompressedQuatKey64_FromCompressedQuatKey64(struct hsCompressedQuatKey64* frame);

extern PyTypeObject pyG3DSMaxKeyFrame_Type;
PyObject* Init_pyG3DSMaxKeyFrame_Type();
int pyG3DSMaxKeyFrame_Check(PyObject* obj);
PyObject* pyG3DSMaxKeyFrame_FromG3DSMaxKeyFrame(struct hsG3DSMaxKeyFrame* frame);

extern PyTypeObject pyMatrix33Key_Type;
PyObject* Init_pyMatrix33Key_Type();
int pyMatrix33Key_Check(PyObject* obj);
PyObject* pyMatrix33Key_FromMatrix33Key(struct hsMatrix33Key* frame);

extern PyTypeObject pyMatrix44Key_Type;
PyObject* Init_pyMatrix44Key_Type();
int pyMatrix44Key_Check(PyObject* obj);
PyObject* pyMatrix44Key_FromMatrix44Key(struct hsMatrix44Key* frame);

}

#endif
