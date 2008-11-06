#ifndef _PYLAYERANIMATION_H
#define _PYLAYERANIMATION_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLayerAnimationBase* fThis;
    bool fPyOwned;
} pyLayerAnimationBase;

typedef struct {
    PyObject_HEAD
    class plLayerAnimation* fThis;
    bool fPyOwned;
} pyLayerAnimation;

typedef struct {
    PyObject_HEAD
    class plLayerLinkAnimation* fThis;
    bool fPyOwned;
} pyLayerLinkAnimation;

typedef struct {
    PyObject_HEAD
    class plLayerSDLAnimation* fThis;
    bool fPyOwned;
} pyLayerSDLAnimation;

extern PyTypeObject pyLayerAnimationBase_Type;
PyObject* Init_pyLayerAnimationBase_Type();
int pyLayerAnimationBase_Check(PyObject* obj);
PyObject* pyLayerAnimationBase_FromLayerAnimationBase(class plLayerAnimationBase* layer);

extern PyTypeObject pyLayerAnimation_Type;
PyObject* Init_pyLayerAnimation_Type();
int pyLayerAnimation_Check(PyObject* obj);
PyObject* pyLayerAnimation_FromLayerAnimation(class plLayerAnimation* layer);

extern PyTypeObject pyLayerLinkAnimation_Type;
PyObject* Init_pyLayerLinkAnimation_Type();
int pyLayerLinkAnimation_Check(PyObject* obj);
PyObject* pyLayerLinkAnimation_FromLayerLinkAnimation(class plLayerLinkAnimation* layer);

extern PyTypeObject pyLayerSDLAnimation_Type;
PyObject* Init_pyLayerSDLAnimation_Type();
int pyLayerSDLAnimation_Check(PyObject* obj);
PyObject* pyLayerSDLAnimation_FromLayerSDLAnimation(class plLayerSDLAnimation* layer);

}

#endif
