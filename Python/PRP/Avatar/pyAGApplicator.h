#ifndef _PYAGAPPLICATOR_H
#define _PYAGAPPLICATOR_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAGApplicator* fThis;
    bool fPyOwned;
} pyAGApplicator;

typedef struct {
    PyObject_HEAD
    class plSoundVolumeApplicator* fThis;
    bool fPyOwned;
} pySoundVolumeApplicator;

typedef struct {
    PyObject_HEAD
    class plLightAmbientApplicator* fThis;
    bool fPyOwned;
} pyLightAmbientApplicator;

typedef struct {
    PyObject_HEAD
    class plLightDiffuseApplicator* fThis;
    bool fPyOwned;
} pyLightDiffuseApplicator;

typedef struct {
    PyObject_HEAD
    class plLightSpecularApplicator* fThis;
    bool fPyOwned;
} pyLightSpecularApplicator;

typedef struct {
    PyObject_HEAD
    class plOmniApplicator* fThis;
    bool fPyOwned;
} pyOmniApplicator;

typedef struct {
    PyObject_HEAD
    class plOmniCutoffApplicator* fThis;
    bool fPyOwned;
} pyOmniCutoffApplicator;

typedef struct {
    PyObject_HEAD
    class plOmniSqApplicator* fThis;
    bool fPyOwned;
} pyOmniSqApplicator;

typedef struct {
    PyObject_HEAD
    class plSpotInnerApplicator* fThis;
    bool fPyOwned;
} pySpotInnerApplicator;

typedef struct {
    PyObject_HEAD
    class plSpotOuterApplicator* fThis;
    bool fPyOwned;
} pySpotOuterApplicator;

typedef struct {
    PyObject_HEAD
    class plMatrixChannelApplicator* fThis;
    bool fPyOwned;
} pyMatrixChannelApplicator;

typedef struct {
    PyObject_HEAD
    class plMatrixDelayedCorrectionApplicator* fThis;
    bool fPyOwned;
} pyMatrixDelayedCorrectionApplicator;

typedef struct {
    PyObject_HEAD
    class plMatrixDifferenceApp* fThis;
    bool fPyOwned;
} pyMatrixDifferenceApp;

typedef struct {
    PyObject_HEAD
    class plRelativeMatrixChannelApplicator* fThis;
    bool fPyOwned;
} pyRelativeMatrixChannelApplicator;

typedef struct {
    PyObject_HEAD
    class plPointChannelApplicator* fThis;
    bool fPyOwned;
} pyPointChannelApplicator;

typedef struct {
    PyObject_HEAD
    class plQuatChannelApplicator* fThis;
    bool fPyOwned;
} pyQuatChannelApplicator;

typedef struct {
    PyObject_HEAD
    class plScalarChannelApplicator* fThis;
    bool fPyOwned;
} pyScalarChannelApplicator;

extern PyTypeObject pyAGApplicator_Type;
PyObject* Init_pyAGApplicator_Type();
int pyAGApplicator_Check(PyObject* obj);
PyObject* pyAGApplicator_FromAGApplicator(class plAGApplicator* app);

extern PyTypeObject pySoundVolumeApplicator_Type;
PyObject* Init_pySoundVolumeApplicator_Type();
int pySoundVolumeApplicator_Check(PyObject* obj);
PyObject* pySoundVolumeApplicator_FromSoundVolumeApplicator(class plSoundVolumeApplicator* app);

extern PyTypeObject pyLightAmbientApplicator_Type;
PyObject* Init_pyLightAmbientApplicator_Type();
int pyLightAmbientApplicator_Check(PyObject* obj);
PyObject* pyLightAmbientApplicator_FromLightAmbientApplicator(class plLightAmbientApplicator* app);

extern PyTypeObject pyLightDiffuseApplicator_Type;
PyObject* Init_pyLightDiffuseApplicator_Type();
int pyLightDiffuseApplicator_Check(PyObject* obj);
PyObject* pyLightDiffuseApplicator_FromLightDiffuseApplicator(class plLightDiffuseApplicator* app);

extern PyTypeObject pyLightSpecularApplicator_Type;
PyObject* Init_pyLightSpecularApplicator_Type();
int pyLightSpecularApplicator_Check(PyObject* obj);
PyObject* pyLightSpecularApplicator_FromLightSpecularApplicator(class plLightSpecularApplicator* app);

extern PyTypeObject pyOmniApplicator_Type;
PyObject* Init_pyOmniApplicator_Type();
int pyOmniApplicator_Check(PyObject* obj);
PyObject* pyOmniApplicator_FromOmniApplicator(class plOmniApplicator* app);

extern PyTypeObject pyOmniCutoffApplicator_Type;
PyObject* Init_pyOmniCutoffApplicator_Type();
int pyOmniCutoffApplicator_Check(PyObject* obj);
PyObject* pyOmniCutoffApplicator_FromOmniCutoffApplicator(class plOmniCutoffApplicator* app);

extern PyTypeObject pyOmniSqApplicator_Type;
PyObject* Init_pyOmniSqApplicator_Type();
int pyOmniSqApplicator_Check(PyObject* obj);
PyObject* pyOmniSqApplicator_FromOmniSqApplicator(class plOmniSqApplicator* app);

extern PyTypeObject pySpotInnerApplicator_Type;
PyObject* Init_pySpotInnerApplicator_Type();
int pySpotInnerApplicator_Check(PyObject* obj);
PyObject* pySpotInnerApplicator_FromSpotInnerApplicator(class plSpotInnerApplicator* app);

extern PyTypeObject pySpotOuterApplicator_Type;
PyObject* Init_pySpotOuterApplicator_Type();
int pySpotOuterApplicator_Check(PyObject* obj);
PyObject* pySpotOuterApplicator_FromSpotOuterApplicator(class plSpotOuterApplicator* app);

extern PyTypeObject pyMatrixChannelApplicator_Type;
PyObject* Init_pyMatrixChannelApplicator_Type();
int pyMatrixChannelApplicator_Check(PyObject* obj);
PyObject* pyMatrixChannelApplicator_FromMatrixChannelApplicator(class plMatrixChannelApplicator* app);

extern PyTypeObject pyMatrixDelayedCorrectionApplicator_Type;
PyObject* Init_pyMatrixDelayedCorrectionApplicator_Type();
int pyMatrixDelayedCorrectionApplicator_Check(PyObject* obj);
PyObject* pyMatrixDelayedCorrectionApplicator_FromMatrixDelayedCorrectionApplicator(class plMatrixDelayedCorrectionApplicator* app);

extern PyTypeObject pyMatrixDifferenceApp_Type;
PyObject* Init_pyMatrixDifferenceApp_Type();
int pyMatrixDifferenceApp_Check(PyObject* obj);
PyObject* pyMatrixDifferenceApp_FromMatrixDifferenceApp(class plMatrixDifferenceApp* app);

extern PyTypeObject pyRelativeMatrixChannelApplicator_Type;
PyObject* Init_pyRelativeMatrixChannelApplicator_Type();
int pyRelativeMatrixChannelApplicator_Check(PyObject* obj);
PyObject* pyRelativeMatrixChannelApplicator_FromRelativeMatrixChannelApplicator(class plRelativeMatrixChannelApplicator* app);

extern PyTypeObject pyPointChannelApplicator_Type;
PyObject* Init_pyPointChannelApplicator_Type();
int pyPointChannelApplicator_Check(PyObject* obj);
PyObject* pyPointChannelApplicator_FromPointChannelApplicator(class plPointChannelApplicator* app);

extern PyTypeObject pyQuatChannelApplicator_Type;
PyObject* Init_pyQuatChannelApplicator_Type();
int pyQuatChannelApplicator_Check(PyObject* obj);
PyObject* pyQuatChannelApplicator_FromQuatChannelApplicator(class plQuatChannelApplicator* app);

extern PyTypeObject pyScalarChannelApplicator_Type;
PyObject* Init_pyScalarChannelApplicator_Type();
int pyScalarChannelApplicator_Check(PyObject* obj);
PyObject* pyScalarChannelApplicator_FromScalarChannelApplicator(class plScalarChannelApplicator* app);

}

#endif
