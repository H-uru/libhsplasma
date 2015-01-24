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
#include <PRP/Surface/plBitmap.h>
#include "pyBitmap.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyBitmap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plBitmap is abstract");
    return NULL;
}

static PyObject* pyBitmap_setConfig(pyBitmap* self, PyObject* args) {
    int format;
    if (!PyArg_ParseTuple(args, "i", &format)) {
        PyErr_SetString(PyExc_TypeError, "setConfig expects an int");
        return NULL;
    }
    self->fThis->setConfig((plBitmap::ColorFormat)format);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBitmap_getBPP(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getBPP());
}

static PyObject* pyBitmap_getSpace(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getSpace());
}

static PyObject* pyBitmap_getFlags(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pyBitmap_getCType(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getCompressionType());
}

static PyObject* pyBitmap_getDXComp(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getDXCompression());
}

static PyObject* pyBitmap_getDXBlock(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getDXBlockSize());
}

static PyObject* pyBitmap_getARGBType(pyBitmap* self, void*) {
    return PyInt_FromLong(self->fThis->getARGBType());
}

static PyObject* pyBitmap_getModTime(pyBitmap* self, void*) {
    return Py_BuildValue("ii", PyInt_FromLong(self->fThis->getLowModTime()),
                               PyInt_FromLong(self->fThis->getHighModTime()));
}

static int pyBitmap_setBPP(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "BPP should be an int");
        return -1;
    }
    self->fThis->setBPP(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setSpace(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "space should be an int");
        return -1;
    }
    self->fThis->setSpace(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setFlags(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setCType(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "compressionType should be an int");
        return -1;
    }
    self->fThis->setCompressionType(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setDXComp(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "DXCompression should be an int");
        return -1;
    }
    self->fThis->setDXCompression(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setDXBlock(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "DXBlockSize should be an int");
        return -1;
    }
    self->fThis->setDXBlockSize(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setARGBType(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ARGBType should be an int");
        return -1;
    }
    self->fThis->setARGBType(PyInt_AsLong(value));
    return 0;
}

static int pyBitmap_setModTime(pyBitmap* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {
        PyErr_SetString(PyExc_TypeError, "modTime should be a tuple (int, int)");
        return -1;
    }
    PyObject* time[2];
    time[0] = PyTuple_GetItem(value, 0);
    time[1] = PyTuple_GetItem(value, 1);
    if (!PyInt_Check(time[0]) || !PyInt_Check(time[1])) {
        PyErr_SetString(PyExc_TypeError, "modTime should be a tuple (int, int)");
        return -1;
    }
    self->fThis->setModTime(PyInt_AsLong(time[0]), PyInt_AsLong(time[1]));
    return 0;
}

static PyMethodDef pyBitmap_Methods[] = {
    { "setConfig", (PyCFunction)pyBitmap_setConfig, METH_VARARGS,
      "Params: format\n"
      "Set the config format of the image data" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyBitmap_GetSet[] = {
    { _pycs("BPP"), (getter)pyBitmap_getBPP, (setter)pyBitmap_setBPP, NULL, NULL },
    { _pycs("space"), (getter)pyBitmap_getSpace, (setter)pyBitmap_setSpace, NULL, NULL },
    { _pycs("flags"), (getter)pyBitmap_getFlags, (setter)pyBitmap_setFlags, NULL, NULL },
    { _pycs("compressionType"), (getter)pyBitmap_getCType, (setter)pyBitmap_setCType, NULL, NULL },
    { _pycs("DXCompression"), (getter)pyBitmap_getDXComp, (setter)pyBitmap_setDXComp, NULL, NULL },
    { _pycs("DXBlockSize"), (getter)pyBitmap_getDXBlock, (setter)pyBitmap_setDXBlock, NULL, NULL },
    { _pycs("ARGBType"), (getter)pyBitmap_getARGBType, (setter)pyBitmap_setARGBType, NULL, NULL },
    { _pycs("modTime"), (getter)pyBitmap_getModTime, (setter)pyBitmap_setModTime, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBitmap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plBitmap",              /* tp_name */
    sizeof(pyBitmap),                   /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plBitmap wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyBitmap_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyBitmap_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBitmap_new,                       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyBitmap_Type() {
    pyBitmap_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyBitmap_Type) < 0)
        return NULL;

    // Flags
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kAlphaChannelFlag",
                         PyInt_FromLong(plBitmap::kAlphaChannelFlag));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kAlphaBitFlag",
                         PyInt_FromLong(plBitmap::kAlphaBitFlag));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kBumpEnvMap",
                         PyInt_FromLong(plBitmap::kBumpEnvMap));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kForce32Bit",
                         PyInt_FromLong(plBitmap::kForce32Bit));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDontThrowAwayImage",
                         PyInt_FromLong(plBitmap::kDontThrowAwayImage));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kForceOneMipLevel",
                         PyInt_FromLong(plBitmap::kForceOneMipLevel));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kNoMaxSize",
                         PyInt_FromLong(plBitmap::kNoMaxSize));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIntensityMap",
                         PyInt_FromLong(plBitmap::kIntensityMap));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kHalfSize",
                         PyInt_FromLong(plBitmap::kHalfSize));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kUserOwnsBitmap",
                         PyInt_FromLong(plBitmap::kUserOwnsBitmap));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kForceRewrite",
                         PyInt_FromLong(plBitmap::kForceRewrite));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kForceNonCompressed",
                         PyInt_FromLong(plBitmap::kForceNonCompressed));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIsTexture",
                         PyInt_FromLong(plBitmap::kIsTexture));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIsOffscreen",
                         PyInt_FromLong(plBitmap::kIsOffscreen));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIsProjected",
                         PyInt_FromLong(plBitmap::kIsProjected));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIsOrtho",
                         PyInt_FromLong(plBitmap::kIsOrtho));

    // Compression Type
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kUncompressed",
                         PyInt_FromLong(plBitmap::kUncompressed));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDirectXCompression",
                         PyInt_FromLong(plBitmap::kDirectXCompression));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kJPEGCompression",
                         PyInt_FromLong(plBitmap::kJPEGCompression));

    // Space
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kNoSpace",
                         PyInt_FromLong(plBitmap::kNoSpace));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDirectSpace",
                         PyInt_FromLong(plBitmap::kDirectSpace));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kGraySpace",
                         PyInt_FromLong(plBitmap::kGraySpace));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kIndexSpace",
                         PyInt_FromLong(plBitmap::kIndexSpace));

    // DX Type
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDXTError",
                         PyInt_FromLong(plBitmap::kDXTError));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDXT1",
                         PyInt_FromLong(plBitmap::kDXT1));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDXT3",
                         PyInt_FromLong(plBitmap::kDXT3));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kDXT5",
                         PyInt_FromLong(plBitmap::kDXT5));

    // Uncompressed Type
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kRGB8888",
                         PyInt_FromLong(plBitmap::kRGB8888));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kRGB4444",
                         PyInt_FromLong(plBitmap::kRGB4444));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kRGB1555",
                         PyInt_FromLong(plBitmap::kRGB1555));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kInten8",
                         PyInt_FromLong(plBitmap::kInten8));
    PyDict_SetItemString(pyBitmap_Type.tp_dict, "kAInten88",
                         PyInt_FromLong(plBitmap::kAInten88));

    Py_INCREF(&pyBitmap_Type);
    return (PyObject*)&pyBitmap_Type;
}

int pyBitmap_Check(PyObject* obj) {
    if (obj->ob_type == &pyBitmap_Type
        || PyType_IsSubtype(obj->ob_type, &pyBitmap_Type))
        return 1;
    return 0;
}

PyObject* pyBitmap_FromBitmap(class plBitmap* img) {
    if (img == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyBitmap* pybmp = PyObject_New(pyBitmap, &pyBitmap_Type);
    pybmp->fThis = img;
    pybmp->fPyOwned = false;
    return (PyObject*)pybmp;
}

}
