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

#include "pyFont.h"

#include "PRP/KeyedObject/pyKeyedObject.h"
#include "Stream/pyStream.h"

/* plFont::plCharacter */
PY_PLASMA_VALUE_DEALLOC(FontCharacter)

PY_PLASMA_INIT_DECL(FontCharacter)
{
    PyObject* init = nullptr;

    if (PyArg_ParseTuple(args, "|O", &init)) {
        if (init == nullptr) {
            return 0;
        } else if (pyFontCharacter_Check(init)) {
            (*self->fThis) = *(((pyFontCharacter*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects an optional plFont::plCharacter");
            return -1;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional plFont::plCharacter");
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(FontCharacter, plFont::plCharacter)

PY_PROPERTY(uint32_t, FontCharacter, offset, getOffset, setOffset)
PY_PROPERTY(uint32_t, FontCharacter, height, getHeight, setHeight)
PY_PROPERTY(int32_t, FontCharacter, baseLine, getBaseline, setBaseline)
PY_PROPERTY(float, FontCharacter, leftKern, getLeftKern, setLeftKern)
PY_PROPERTY(float, FontCharacter, rightKern, getRightKern, setRightKern)

static PyGetSetDef pyFontCharacter_GetSet[] = {
    pyFontCharacter_offset_getset,
    pyFontCharacter_height_getset,
    pyFontCharacter_baseLine_getset,
    pyFontCharacter_leftKern_getset,
    pyFontCharacter_rightKern_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FontCharacter, plFont::plCharacter, "plFont::plCharacter wrapper")

PY_PLASMA_TYPE_INIT(FontCharacter)
{
    pyFontCharacter_Type.tp_dealloc = pyFontCharacter_dealloc;
    pyFontCharacter_Type.tp_init = pyFontCharacter___init__;
    pyFontCharacter_Type.tp_new = pyFontCharacter_new;
    pyFontCharacter_Type.tp_getset = pyFontCharacter_GetSet;
    if (PyType_CheckAndReady(&pyFontCharacter_Type) < 0)
        return nullptr;

    Py_INCREF(&pyFontCharacter_Type);
    return (PyObject*)&pyFontCharacter_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(FontCharacter, plFont::plCharacter)


/* plFont */
PY_PLASMA_NEW(Font, plFont)

PY_PROPERTY(ST::string, Font, name, getName, setName)
PY_PROPERTY(uint8_t, Font, size, getSize, setSize)
PY_PROPERTY(uint8_t, Font, BPP, getBPP, setBPP)
PY_PROPERTY(uint32_t, Font, width, getWidth, setWidth)
PY_PROPERTY(uint32_t, Font, height, getHeight, setHeight)
PY_PROPERTY(uint16_t, Font, firstChar, getFirstChar, setFirstChar)
PY_PROPERTY(int32_t, Font, maxCharHeight, getMaxCharHeight, setMaxCharHeight)
PY_PROPERTY(uint32_t, Font, flags, getFlags, setFlags)
PY_PROPERTY_RO(Font, stride, getStride)

// "Shortcut" properties for flags
PY_PROPERTY(bool, Font, bold, isBold, setBold)
PY_PROPERTY(bool, Font, italic, isItalic, setItalic)

// This will get/set the whole list of characters at once.  Alternatively,
// pyFont also has __getitem__, __setitem__, len() support.
PY_GETSET_GETTER_DECL(Font, characters)
{
    PyObject* chars = PyTuple_New(self->fThis->getNumCharacters());
    for (size_t i = 0; i < self->fThis->getNumCharacters(); ++i)
        PyTuple_SET_ITEM(chars, i, pyFontCharacter_FromFontCharacter(self->fThis->getCharacter(i)));
    return chars;
}

PY_GETSET_SETTER_DECL(Font, characters)
{
    PY_PROPERTY_CHECK_NULL(characters);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "characters should be a sequence of plFont::plCharacter objects");
        return -1;
    }

    // Pre-check the contents of the sequence before writing to the plFont
    size_t numChars = seq.size();
    for (size_t i = 0; i < numChars; ++i) {
        if (!pyFontCharacter_Check(seq.get(i))) {
            PyErr_SetString(PyExc_TypeError, "characters should be a sequence of plFont::plCharacter objects");
            return -1;
        }
    }

    self->fThis->setNumCharacters(numChars);
    for (size_t i = 0; i < numChars; ++i)
        self->fThis->getCharacter(i) = *((pyFontCharacter*)seq.get(i))->fThis;
    return 0;
}

PY_PROPERTY_GETSET_DECL(Font, characters)

static PyGetSetDef pyFont_GetSet [] = {
    pyFont_name_getset,
    pyFont_size_getset,
    pyFont_BPP_getset,
    pyFont_width_getset,
    pyFont_height_getset,
    pyFont_firstChar_getset,
    pyFont_maxCharHeight_getset,
    pyFont_flags_getset,
    pyFont_stride_getset,
    pyFont_bold_getset,
    pyFont_italic_getset,
    pyFont_characters_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_SUBSCRIPT_DECL(Font)
{
    if (!pyPlasma_check<int>(key)) {
        PyErr_SetString(PyExc_TypeError, "plFont subscript expects int index");
        return nullptr;
    }
    const int idx = pyPlasma_get<int>(key);
    if (idx < 0 || size_t(idx) >= self->fThis->getNumCharacters()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    return pyFontCharacter_FromFontCharacter(self->fThis->getCharacter(idx));
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(Font)
{
    if (!pyPlasma_check<int>(key)) {
        PyErr_SetString(PyExc_TypeError, "plFont subscript expects int index");
        return -1;
    }
    const int idx = pyPlasma_get<int>(key);
    if (idx < 0 || size_t(idx) >= self->fThis->getNumCharacters()) {
        PyErr_SetNone(PyExc_IndexError);
        return -1;
    }
    if (!pyFontCharacter_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "plFont subscript values should be plFont::plCharacter objects");
        return -1;
    }
    (*self->fThis).getCharacter(idx) = *((pyFontCharacter*)value)->fThis;
    return 0;
}

PY_PLASMA_LENGTH_DECL(Font)
{
    return self->fThis->getNumCharacters();
}

PY_PLASMA_TYPE_AS_MAPPING(Font)

PY_METHOD_VA(Font, readP2F,
    "Params: stream\n"
    "Read this font from a .p2f stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readP2F expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readP2F expects an hsStream");
        return nullptr;
    }
    self->fThis->readP2F(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Font, writeP2F,
    "Params: stream\n"
    "Write this font to a .p2f stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeP2F expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeP2F expects an hsStream");
        return nullptr;
    }
    self->fThis->writeP2F(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Font, readBitmap,
    "Params: stream\n"
    "Read the font's bitmap data from a .bmp stream.  This Does NOT modify the character table.")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readBitmap expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readBitmap expects an hsStream");
        return nullptr;
    }
    self->fThis->readBitmap(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Font, writeBitmap,
    "Params: stream\n"
    "Write this font's bitmap data to a .bmp stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeBitmap expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeBitmap expects an hsStream");
        return nullptr;
    }
    self->fThis->writeBitmap(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Font, getGlyph,
    "Params: index\n"
    "Return the bitmap data for the specified character")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getGlyph expects an int");
        return nullptr;
    }
    if (idx < 0 || size_t(idx) >= self->fThis->getNumCharacters()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }

    return PyBytes_FromStringAndSize((const char *)self->fThis->getGlyph(idx),
                                     self->fThis->getGlyphSize(idx));
}

static PyMethodDef pyFont_Methods[] = {
    pyFont_readP2F_method,
    pyFont_writeP2F_method,
    pyFont_readBitmap_method,
    pyFont_writeBitmap_method,
    pyFont_getGlyph_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(Font, plFont, "plFont wrapper")

PY_PLASMA_TYPE_INIT(Font)
{
    pyFont_As_Mapping.mp_subscript = pyFont_mp_subscript;
    pyFont_As_Mapping.mp_ass_subscript = pyFont_mp_ass_subscript;
    pyFont_As_Mapping.mp_length = pyFont_length;
    pyFont_Type.tp_new = pyFont_new;
    pyFont_Type.tp_as_mapping = &pyFont_As_Mapping;
    pyFont_Type.tp_methods = pyFont_Methods;
    pyFont_Type.tp_getset = pyFont_GetSet;
    pyFont_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyFont_Type) < 0)
        return nullptr;

    PyDict_SetItemString(pyFont_Type.tp_dict, "plCharacter", Init_pyFontCharacter_Type());

    PY_TYPE_ADD_CONST(Font, "kFontBold", plFont::kFontBold);
    PY_TYPE_ADD_CONST(Font, "kFontItalic", plFont::kFontItalic);

    Py_INCREF(&pyFont_Type);
    return (PyObject*)&pyFont_Type;
}

PY_PLASMA_IFC_METHODS(Font, plFont)
