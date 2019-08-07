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

PY_PLASMA_NEW_MSG(Bitmap, "plBitmap is abstract")

PY_METHOD_VA(Bitmap, setConfig,
    "Params: format\n"
    "Set the config format of the image data")
{
    int format;
    if (!PyArg_ParseTuple(args, "i", &format)) {
        PyErr_SetString(PyExc_TypeError, "setConfig expects an int");
        return nullptr;
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

PY_GETSET_GETTER_DECL(Bitmap, modTime)
{
    return Py_BuildValue("ii", pyPlasma_convert(self->fThis->getLowModTime()),
                               pyPlasma_convert(self->fThis->getHighModTime()));
}

PY_GETSET_SETTER_DECL(Bitmap, modTime)
{
    PY_PROPERTY_CHECK_NULL(modTime)
    if (!PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {
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

PY_PLASMA_TYPE(Bitmap, plBitmap, "plBitmap wrapper")

PY_PLASMA_TYPE_INIT(Bitmap)
{
    pyBitmap_Type.tp_new = pyBitmap_new;
    pyBitmap_Type.tp_methods = pyBitmap_Methods;
    pyBitmap_Type.tp_getset = pyBitmap_GetSet;
    pyBitmap_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyBitmap_Type) < 0)
        return nullptr;

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
    PY_TYPE_ADD_CONST(Bitmap, "kPNGCompression", plBitmap::kPNGCompression);

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
