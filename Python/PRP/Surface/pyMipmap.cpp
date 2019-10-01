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

#include <PRP/Surface/plMipmap.h>
#include "PRP/pyCreatable.h"
#include "Stream/pyStream.h"

PY_PLASMA_INIT_DECL(Mipmap)
{
    const char* name = "";
    int width, height, numLevels, compType, format;
    int dxtLevel = plBitmap::kDXTError;
    static char* kwlist[] = { _pycs("name"), _pycs("width"), _pycs("height"),
                              _pycs("numLevels"), _pycs("compType"),
                              _pycs("format"), _pycs("dxtLevel"), nullptr };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "siiiii|i", kwlist,
                                    &name, &width, &height, &numLevels,
                                    &compType, &format, &dxtLevel)) {
        self->fThis->init(name);
        self->fThis->Create(width, height, numLevels, compType,
                            (plBitmap::ColorFormat)format, dxtLevel);
        return 0;
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|s", &name)) {
        self->fThis->init(name);
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "__init__ expects an optional string, or a set of creation parameters");
    return -1;
}

PY_PLASMA_NEW(Mipmap, plMipmap)

PY_METHOD_VA(Mipmap, readData,
    "Params: stream\n"
    "Reads a plMipmap from a stream, exluding the plKey")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readData expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readData expects an hsStream");
        return nullptr;
    }
    self->fThis->readData(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, writeData,
    "Params: stream\n"
    "Writes a plMipmap to a stream, exluding the plKey")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeData expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeData expects an hsStream");
        return nullptr;
    }
    self->fThis->writeData(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, getLevelWidth,
    "Params: level\n"
    "Get the width of a specified mip level")
{
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevelWidth expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getLevelWidth(level));
}

PY_METHOD_VA(Mipmap, getLevelHeight,
    "Params: level\n"
    "Get the height of a specified mip level")
{
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevelHeight expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getLevelHeight(level));
}

PY_METHOD_VA(Mipmap, getLevel,
    "Params: level\n"
    "Get the image data buffer for a specified mip level")
{
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevel expects an int");
        return nullptr;
    }
    PyObject* data = PyBytes_FromStringAndSize((const char*)self->fThis->getLevelData(level),
                                               self->fThis->getLevelSize(level));
    return data;
}

PY_METHOD_VA(Mipmap, setRawImage,
    "Params: data\n"
    "Set the raw full image data (not for JPEG or RLE encoding)")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setRawImage expects a binary string");
        return nullptr;
    }
    self->fThis->setImageData((const void*)data, dataSize);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, setLevel,
    "Params: level, data\n"
    "Set the image data for a specified mip level")
{
    const char* data;
    int dataSize, level;
    if (!PyArg_ParseTuple(args, "is#", &level, &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setLevel expects int, binary string");
        return nullptr;
    }
    try {
        self->fThis->setLevelData(level, (const void*)data, dataSize);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, setImageJPEG,
    "Params: jpegData\n"
    "Set the image data as a JPEG stream")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setImageJPEG expects a binary string");
        return nullptr;
    }
    try {
        self->fThis->setImageJPEG((const void*)data, dataSize);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, setAlphaJPEG,
    "Params: jpegData\n"
    "Set the alpha data as a JPEG stream")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setAlphaJPEG expects a binary string");
        return nullptr;
    }
    try {
        self->fThis->setAlphaJPEG((const void*)data, dataSize);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, setColorData,
    "Params: buffer\n"
    "Set the RGB color data for a JPEG mipmap")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setColorData expects a binary string");
        return nullptr;
    }
    try {
        self->fThis->setColorData((const void*)data, dataSize);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_VA(Mipmap, setAlphaData,
    "Params: buffer\n"
    "Set the alpha data for a JPEG mipmap")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setAlphaData expects a binary string");
        return nullptr;
    }
    try {
        self->fThis->setAlphaData((const void*)data, dataSize);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Mipmap, extractColorData,
    "Extract an RGB color buffer from a JPEG mipmap")
{
    size_t dataSize = self->fThis->getWidth() * self->fThis->getHeight() * 3;
    PyObject* buf = PyBytes_FromStringAndSize(nullptr, dataSize);
    char* data = PyBytes_AS_STRING(buf);
    self->fThis->extractColorData(data, dataSize);
    return buf;
}

PY_METHOD_NOARGS(Mipmap, extractAlphaData,
    "Extract an alpha intensity buffer from a JPEG mipmap")
{
    size_t dataSize = self->fThis->getWidth() * self->fThis->getHeight() * 1;
    PyObject* buf = PyBytes_FromStringAndSize(nullptr, dataSize);
    char* data = PyBytes_AS_STRING(buf);
    self->fThis->extractAlphaData(data, dataSize);
    return buf;
}

PY_METHOD_NOARGS(Mipmap, isImageJPEG,
    "Returns whether the imageData member is a JPEG stream")
{
    return pyPlasma_convert(self->fThis->isImageJPEG());
}

PY_METHOD_NOARGS(Mipmap, isAlphaJPEG,
    "Returns whether the alphaData member is a JPEG stream")
{
    return pyPlasma_convert(self->fThis->isAlphaJPEG());
}

PY_METHOD_VA(Mipmap, DecompressImage,
    "Params: level\n"
    "Decompresses the specified mip level and returns the uncompressed RGBA buffer")
{
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "DecompressImage expects an int");
        return nullptr;
    }
    size_t size = self->fThis->GetUncompressedSize(level);
    PyObject* img = PyBytes_FromStringAndSize(nullptr, size);
    char* buf = PyBytes_AS_STRING(img);
    try {
        self->fThis->DecompressImage(level, buf, size);
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        Py_DECREF(img);
        return nullptr;
    }
    return img;
}

PY_METHOD_VA(Mipmap, CompressImage,
    "Params: level, data\n"
    "Compresses the specified mip level")
{
    int level, dataSize;
    char* data;
    if (!PyArg_ParseTuple(args, "is#", &level, &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "CompressImage expects an int and a binary string");
        return nullptr;
    }
    try {
        self->fThis->CompressImage(level, data, dataSize);
    } catch (hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return nullptr;
    } catch (const hsNotImplementedException& ex) {
        PyErr_SetString(PyExc_NotImplementedError, ex.what());
        return nullptr;
    }
    Py_RETURN_NONE;
}

static PyMethodDef pyMipmap_Methods[] = {
    pyMipmap_readData_method,
    pyMipmap_writeData_method,
    pyMipmap_getLevelWidth_method,
    pyMipmap_getLevelHeight_method,
    pyMipmap_getLevel_method,
    pyMipmap_setRawImage_method,
    pyMipmap_setLevel_method,
    pyMipmap_setImageJPEG_method,
    pyMipmap_setAlphaJPEG_method,
    pyMipmap_setColorData_method,
    pyMipmap_setAlphaData_method,
    pyMipmap_extractColorData_method,
    pyMipmap_extractAlphaData_method,
    pyMipmap_isImageJPEG_method,
    pyMipmap_isAlphaJPEG_method,
    pyMipmap_DecompressImage_method,
    pyMipmap_CompressImage_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(Mipmap, width, getWidth)
PY_PROPERTY_SETTER_MSG(Mipmap, width, "To set the width, you must re-create the mipmap object")
PY_PROPERTY_GETSET_DECL(Mipmap, width)

PY_PROPERTY_READ(Mipmap, height, getHeight)
PY_PROPERTY_SETTER_MSG(Mipmap, height, "To set the height, you must re-create the mipmap object")
PY_PROPERTY_GETSET_DECL(Mipmap, height)

PY_GETSET_GETTER_DECL(Mipmap, imageData)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getImageData(),
                                     self->fThis->getTotalSize());
}

PY_PROPERTY_SETTER_MSG(Mipmap, imageData, "To set the image data, use the mipmap set methods")
PY_PROPERTY_GETSET_DECL(Mipmap, imageData)

PY_PROPERTY_READ(Mipmap, numLevels, getNumLevels)
PY_PROPERTY_SETTER_MSG(Mipmap, numLevels, "To set the number of mip levels, you must re-create the mipmap object")
PY_PROPERTY_GETSET_DECL(Mipmap, numLevels)

static PyGetSetDef pyMipmap_GetSet[] = {
    pyMipmap_width_getset,
    pyMipmap_height_getset,
    pyMipmap_imageData_getset,
    pyMipmap_numLevels_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Mipmap, plMipmap, "plMipmap wrapper")

PY_PLASMA_TYPE_INIT(Mipmap)
{
    pyMipmap_Type.tp_init = pyMipmap___init__;
    pyMipmap_Type.tp_new = pyMipmap_new;
    pyMipmap_Type.tp_methods = pyMipmap_Methods;
    pyMipmap_Type.tp_getset = pyMipmap_GetSet;
    pyMipmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_CheckAndReady(&pyMipmap_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMipmap_Type);
    return (PyObject*)&pyMipmap_Type;
}

PY_PLASMA_IFC_METHODS(Mipmap, plMipmap)
