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

#include "pyBitmap.h"

#include <PRP/Surface/plBitmap.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW_MSG(Bitmap, "plBitmap is abstract")

PY_METHOD_VA(Bitmap, setConfig,
    "Params: format\n"
    "Set the config format of the image data")
{
    int format;
    if (!PyArg_ParseTuple(args, "i", &format)) {
        PyErr_SetString(PyExc_TypeError, "setConfig expects an int");
        return NULL;
    }
    self->fThis->setConfig((plBitmap::ColorFormat)format);
    Py_RETURN_NONE;
}

static PyMethodDef pyBitmap_Methods[] = {
    pyBitmap_setConfig_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned char, Bitmap, BPP, getBPP, setBPP)
PY_PROPERTY(unsigned char, Bitmap, space, getSpace, setSpace)
PY_PROPERTY(unsigned short, Bitmap, flags, getFlags, setFlags)
PY_PROPERTY(unsigned char, Bitmap, compressionType, getCompressionType, setCompressionType)
PY_PROPERTY(unsigned char, Bitmap, DXCompression, getDXCompression, setDXCompression)
PY_PROPERTY(unsigned char, Bitmap, DXBlockSize, getDXBlockSize, setDXBlockSize)
PY_PROPERTY(unsigned char, Bitmap, ARGBType, getARGBType, setARGBType)

PY_GETSET_GETTER_DECL(Bitmap, modTime) {
    return Py_BuildValue("ii", pyPlasma_convert(self->fThis->getLowModTime()),
                               pyPlasma_convert(self->fThis->getHighModTime()));
}

PY_GETSET_SETTER_DECL(Bitmap, modTime) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "modTime cannot be deleted");
        return -1;
    } else if (!PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {
        PyErr_SetString(PyExc_TypeError, "modTime should be a tuple (int, int)");
        return -1;
    }
    PyObject* time[2];
    time[0] = PyTuple_GetItem(value, 0);
    time[1] = PyTuple_GetItem(value, 1);
    if (!pyPlasma_check<unsigned int>(time[0]) || !pyPlasma_check<unsigned int>(time[1])) {
        PyErr_SetString(PyExc_TypeError, "modTime should be a tuple (int, int)");
        return -1;
    }
    self->fThis->setModTime(pyPlasma_get<unsigned int>(time[0]),
                            pyPlasma_get<unsigned int>(time[1]));
    return 0;
}

PY_PROPERTY_GETSET_DECL(Bitmap, modTime)

static PyGetSetDef pyBitmap_GetSet[] = {
    pyBitmap_BPP_getset,
    pyBitmap_space_getset,
    pyBitmap_flags_getset,
    pyBitmap_compressionType_getset,
    pyBitmap_DXCompression_getset,
    pyBitmap_DXBlockSize_getset,
    pyBitmap_ARGBType_getset,
    pyBitmap_modTime_getset,
    PY_GETSET_TERMINATOR
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
    PY_TYPE_ADD_CONST(Bitmap, "kAlphaChannelFlag", plBitmap::kAlphaChannelFlag);
    PY_TYPE_ADD_CONST(Bitmap, "kAlphaBitFlag", plBitmap::kAlphaBitFlag);
    PY_TYPE_ADD_CONST(Bitmap, "kBumpEnvMap", plBitmap::kBumpEnvMap);
    PY_TYPE_ADD_CONST(Bitmap, "kForce32Bit", plBitmap::kForce32Bit);
    PY_TYPE_ADD_CONST(Bitmap, "kDontThrowAwayImage", plBitmap::kDontThrowAwayImage);
    PY_TYPE_ADD_CONST(Bitmap, "kForceOneMipLevel", plBitmap::kForceOneMipLevel);
    PY_TYPE_ADD_CONST(Bitmap, "kNoMaxSize", plBitmap::kNoMaxSize);
    PY_TYPE_ADD_CONST(Bitmap, "kIntensityMap", plBitmap::kIntensityMap);
    PY_TYPE_ADD_CONST(Bitmap, "kHalfSize", plBitmap::kHalfSize);
    PY_TYPE_ADD_CONST(Bitmap, "kUserOwnsBitmap", plBitmap::kUserOwnsBitmap);
    PY_TYPE_ADD_CONST(Bitmap, "kForceRewrite", plBitmap::kForceRewrite);
    PY_TYPE_ADD_CONST(Bitmap, "kForceNonCompressed", plBitmap::kForceNonCompressed);
    PY_TYPE_ADD_CONST(Bitmap, "kIsTexture", plBitmap::kIsTexture);
    PY_TYPE_ADD_CONST(Bitmap, "kIsOffscreen", plBitmap::kIsOffscreen);
    PY_TYPE_ADD_CONST(Bitmap, "kIsProjected", plBitmap::kIsProjected);
    PY_TYPE_ADD_CONST(Bitmap, "kIsOrtho", plBitmap::kIsOrtho);

    // Compression Type
    PY_TYPE_ADD_CONST(Bitmap, "kUncompressed", plBitmap::kUncompressed);
    PY_TYPE_ADD_CONST(Bitmap, "kDirectXCompression", plBitmap::kDirectXCompression);
    PY_TYPE_ADD_CONST(Bitmap, "kJPEGCompression", plBitmap::kJPEGCompression);

    // Space
    PY_TYPE_ADD_CONST(Bitmap, "kNoSpace", plBitmap::kNoSpace);
    PY_TYPE_ADD_CONST(Bitmap, "kDirectSpace", plBitmap::kDirectSpace);
    PY_TYPE_ADD_CONST(Bitmap, "kGraySpace", plBitmap::kGraySpace);
    PY_TYPE_ADD_CONST(Bitmap, "kIndexSpace", plBitmap::kIndexSpace);

    // DX Type
    PY_TYPE_ADD_CONST(Bitmap, "kDXTError", plBitmap::kDXTError);
    PY_TYPE_ADD_CONST(Bitmap, "kDXT1", plBitmap::kDXT1);
    PY_TYPE_ADD_CONST(Bitmap, "kDXT3", plBitmap::kDXT3);
    PY_TYPE_ADD_CONST(Bitmap, "kDXT5", plBitmap::kDXT5);

    // Uncompressed Type
    PY_TYPE_ADD_CONST(Bitmap, "kRGB8888", plBitmap::kRGB8888);
    PY_TYPE_ADD_CONST(Bitmap, "kRGB4444", plBitmap::kRGB4444);
    PY_TYPE_ADD_CONST(Bitmap, "kRGB1555", plBitmap::kRGB1555);
    PY_TYPE_ADD_CONST(Bitmap, "kInten8", plBitmap::kInten8);
    PY_TYPE_ADD_CONST(Bitmap, "kAInten88", plBitmap::kAInten88);

    Py_INCREF(&pyBitmap_Type);
    return (PyObject*)&pyBitmap_Type;
}

PY_PLASMA_IFC_METHODS(Bitmap, plBitmap)

}
