/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PyPlasma.h>
#include <PRP/Surface/hsGMatState.h>
#include "pyGMatState.h"

extern "C" {

static PyObject* pyGMatState_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct hsGMatState objects");
    return NULL;
}

static PyObject* pyGMatState_getBlendFlags(pyGMatState* self, void*) {
    return PyInt_FromLong(self->fThis->fBlendFlags);
}

static PyObject* pyGMatState_getClampFlags(pyGMatState* self, void*) {
    return PyInt_FromLong(self->fThis->fClampFlags);
}

static PyObject* pyGMatState_getShadeFlags(pyGMatState* self, void*) {
    return PyInt_FromLong(self->fThis->fShadeFlags);
}

static PyObject* pyGMatState_getZFlags(pyGMatState* self, void*) {
    return PyInt_FromLong(self->fThis->fZFlags);
}

static PyObject* pyGMatState_getMiscFlags(pyGMatState* self, void*) {
    return PyInt_FromLong(self->fThis->fMiscFlags);
}

static int pyGMatState_setBlendFlags(pyGMatState* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "blendFlags should be an int");
        return -1;
    }
    self->fThis->fBlendFlags = PyInt_AsLong(value);
    return 0;
}

static int pyGMatState_setClampFlags(pyGMatState* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "clampFlags should be an int");
        return -1;
    }
    self->fThis->fClampFlags = PyInt_AsLong(value);
    return 0;
}

static int pyGMatState_setShadeFlags(pyGMatState* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "shadeFlags should be an int");
        return -1;
    }
    self->fThis->fShadeFlags = PyInt_AsLong(value);
    return 0;
}

static int pyGMatState_setZFlags(pyGMatState* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ZFlags should be an int");
        return -1;
    }
    self->fThis->fZFlags = PyInt_AsLong(value);
    return 0;
}

static int pyGMatState_setMiscFlags(pyGMatState* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "miscFlags should be an int");
        return -1;
    }
    self->fThis->fMiscFlags = PyInt_AsLong(value);
    return 0;
}

static PyGetSetDef pyGMatState_GetSet[] = {
    { "blendFlags", (getter)pyGMatState_getBlendFlags, (setter)pyGMatState_setBlendFlags, NULL, NULL },
    { "clampFlags", (getter)pyGMatState_getClampFlags, (setter)pyGMatState_setClampFlags, NULL, NULL },
    { "shadeFlags", (getter)pyGMatState_getShadeFlags, (setter)pyGMatState_setShadeFlags, NULL, NULL },
    { "ZFlags", (getter)pyGMatState_getZFlags, (setter)pyGMatState_setZFlags, NULL, NULL },
    { "miscFlags", (getter)pyGMatState_getMiscFlags, (setter)pyGMatState_setMiscFlags, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGMatState_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsGMatState",             /* tp_name */
    sizeof(pyGMatState),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "hsGMatState wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyGMatState_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGMatState_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyGMatState_Type() {
    if (PyType_Ready(&pyGMatState_Type) < 0)
        return NULL;

    /* Blend Flags */
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendTest",
                         PyInt_FromLong(hsGMatState::kBlendTest));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAlpha",
                         PyInt_FromLong(hsGMatState::kBlendAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendMult",
                         PyInt_FromLong(hsGMatState::kBlendMult));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAdd",
                         PyInt_FromLong(hsGMatState::kBlendAdd));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAddColorTimesAlpha",
                         PyInt_FromLong(hsGMatState::kBlendAddColorTimesAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAntiAlias",
                         PyInt_FromLong(hsGMatState::kBlendAntiAlias));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendDetail",
                         PyInt_FromLong(hsGMatState::kBlendDetail));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendNoColor",
                         PyInt_FromLong(hsGMatState::kBlendNoColor));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendMADD",
                         PyInt_FromLong(hsGMatState::kBlendMADD));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendDot3",
                         PyInt_FromLong(hsGMatState::kBlendDot3));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAddSigned",
                         PyInt_FromLong(hsGMatState::kBlendAddSigned));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAddSigned2X",
                         PyInt_FromLong(hsGMatState::kBlendAddSigned2X));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendMask",
                         PyInt_FromLong(hsGMatState::kBlendMask));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendInvertAlpha",
                         PyInt_FromLong(hsGMatState::kBlendInvertAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendInvertColor",
                         PyInt_FromLong(hsGMatState::kBlendInvertColor));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAlphaMult",
                         PyInt_FromLong(hsGMatState::kBlendAlphaMult));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAlphaAdd",
                         PyInt_FromLong(hsGMatState::kBlendAlphaAdd));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendNoVtxAlpha",
                         PyInt_FromLong(hsGMatState::kBlendNoVtxAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendNoTexColor",
                         PyInt_FromLong(hsGMatState::kBlendNoTexColor));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendNoTexAlpha",
                         PyInt_FromLong(hsGMatState::kBlendNoTexAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendInvertVtxAlpha",
                         PyInt_FromLong(hsGMatState::kBlendInvertVtxAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAlphaAlways",
                         PyInt_FromLong(hsGMatState::kBlendAlphaAlways));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendInvertFinalColor",
                         PyInt_FromLong(hsGMatState::kBlendInvertFinalColor));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendInvertFinalAlpha",
                         PyInt_FromLong(hsGMatState::kBlendInvertFinalAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendEnvBumpNext",
                         PyInt_FromLong(hsGMatState::kBlendEnvBumpNext));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendSubtract",
                         PyInt_FromLong(hsGMatState::kBlendSubtract));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendRevSubtract",
                         PyInt_FromLong(hsGMatState::kBlendRevSubtract));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kBlendAlphaTestHigh",
                         PyInt_FromLong(hsGMatState::kBlendAlphaTestHigh));

    /* Clamp Flags */
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kClampTextureU",
                         PyInt_FromLong(hsGMatState::kClampTextureU));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kClampTextureV",
                         PyInt_FromLong(hsGMatState::kClampTextureV));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kClampTexture",
                         PyInt_FromLong(hsGMatState::kClampTexture));

    /* Shade Flags */
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeSoftShadow",
                         PyInt_FromLong(hsGMatState::kShadeSoftShadow));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeNoProjectors",
                         PyInt_FromLong(hsGMatState::kShadeNoProjectors));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeEnvironMap",
                         PyInt_FromLong(hsGMatState::kShadeEnvironMap));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeVertexShade",
                         PyInt_FromLong(hsGMatState::kShadeVertexShade));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeNoShade",
                         PyInt_FromLong(hsGMatState::kShadeNoShade));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeBlack",
                         PyInt_FromLong(hsGMatState::kShadeBlack));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeSpecular",
                         PyInt_FromLong(hsGMatState::kShadeSpecular));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeNoFog",
                         PyInt_FromLong(hsGMatState::kShadeNoFog));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeWhite",
                         PyInt_FromLong(hsGMatState::kShadeWhite));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeSpecularAlpha",
                         PyInt_FromLong(hsGMatState::kShadeSpecularAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeSpecularColor",
                         PyInt_FromLong(hsGMatState::kShadeSpecularColor));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeSpecularHighlight",
                         PyInt_FromLong(hsGMatState::kShadeSpecularHighlight));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeVertColShade",
                         PyInt_FromLong(hsGMatState::kShadeVertColShade));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeInherit",
                         PyInt_FromLong(hsGMatState::kShadeInherit));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeIgnoreVtxIllum",
                         PyInt_FromLong(hsGMatState::kShadeIgnoreVtxIllum));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeEmissive",
                         PyInt_FromLong(hsGMatState::kShadeEmissive));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kShadeReallyNoFog",
                         PyInt_FromLong(hsGMatState::kShadeReallyNoFog));

    /* Z Flags */
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZIncLayer",
                         PyInt_FromLong(hsGMatState::kZIncLayer));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZClearZ",
                         PyInt_FromLong(hsGMatState::kZClearZ));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZNoZRead",
                         PyInt_FromLong(hsGMatState::kZNoZRead));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZNoZWrite",
                         PyInt_FromLong(hsGMatState::kZNoZWrite));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZMask",
                         PyInt_FromLong(hsGMatState::kZMask));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kZLODBias",
                         PyInt_FromLong(hsGMatState::kZLODBias));

    /* Misc Flags */
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscWireFrame",
                         PyInt_FromLong(hsGMatState::kMiscWireFrame));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscDrawMeshOutlines",
                         PyInt_FromLong(hsGMatState::kMiscDrawMeshOutlines));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscTwoSided",
                         PyInt_FromLong(hsGMatState::kMiscTwoSided));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscDrawAsSplats",
                         PyInt_FromLong(hsGMatState::kMiscDrawAsSplats));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscAdjustPlane",
                         PyInt_FromLong(hsGMatState::kMiscAdjustPlane));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscAdjustCylinder",
                         PyInt_FromLong(hsGMatState::kMiscAdjustCylinder));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscAdjustSphere",
                         PyInt_FromLong(hsGMatState::kMiscAdjustSphere));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscAdjust",
                         PyInt_FromLong(hsGMatState::kMiscAdjust));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscTroubledLoner",
                         PyInt_FromLong(hsGMatState::kMiscTroubledLoner));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBindSkip",
                         PyInt_FromLong(hsGMatState::kMiscBindSkip));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBindMask",
                         PyInt_FromLong(hsGMatState::kMiscBindMask));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBindNext",
                         PyInt_FromLong(hsGMatState::kMiscBindNext));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscLightMap",
                         PyInt_FromLong(hsGMatState::kMiscLightMap));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscUseReflectionXform",
                         PyInt_FromLong(hsGMatState::kMiscUseReflectionXform));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscPerspProjection",
                         PyInt_FromLong(hsGMatState::kMiscPerspProjection));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscOrthoProjection",
                         PyInt_FromLong(hsGMatState::kMiscOrthoProjection));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscProjection",
                         PyInt_FromLong(hsGMatState::kMiscProjection));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscRestartPassHere",
                         PyInt_FromLong(hsGMatState::kMiscRestartPassHere));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBumpLayer",
                         PyInt_FromLong(hsGMatState::kMiscBumpLayer));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBumpDu",
                         PyInt_FromLong(hsGMatState::kMiscBumpDu));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBumpDv",
                         PyInt_FromLong(hsGMatState::kMiscBumpDv));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBumpDw",
                         PyInt_FromLong(hsGMatState::kMiscBumpDw));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscBumpChans",
                         PyInt_FromLong(hsGMatState::kMiscBumpChans));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscNoShadowAlpha",
                         PyInt_FromLong(hsGMatState::kMiscNoShadowAlpha));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscUseRefractionXform",
                         PyInt_FromLong(hsGMatState::kMiscUseRefractionXform));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kMiscCam2Screen",
                         PyInt_FromLong(hsGMatState::kMiscCam2Screen));
    PyDict_SetItemString(pyGMatState_Type.tp_dict, "kAllMiscFlags",
                         PyInt_FromLong(hsGMatState::kAllMiscFlags));

    Py_INCREF(&pyGMatState_Type);
    return (PyObject*)&pyGMatState_Type;
}

PyObject* pyGMatState_FromGMatState(hsGMatState& state) {
    pyGMatState* pystate = PyObject_New(pyGMatState, &pyGMatState_Type);
    pystate->fThis = &state;
    return (PyObject*)pystate;
}

}
