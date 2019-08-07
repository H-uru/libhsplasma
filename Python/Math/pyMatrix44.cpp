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

#include "pyMatrix.h"

#include <Math/hsMatrix44.h>
#include "pyGeometry3.h"
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(Matrix44)

PY_PLASMA_INIT_DECL(Matrix44)
{
    PyObject* init = nullptr;
    if (!PyArg_ParseTuple(args, "|O", &init))
        return -1;

    if (init) {
        if (pyMatrix44_Check(init)) {
            (*self->fThis) = pyPlasma_get<hsMatrix44>(init);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a matrix");
            return -1;
        }
    } else {
        self->fThis->Reset();
    }
    return 0;
}

PY_PLASMA_VALUE_NEW(Matrix44, hsMatrix44)

PY_PLASMA_SUBSCRIPT_DECL(Matrix44)
{
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return nullptr;
    }
    return pyPlasma_convert((*self->fThis)(i, j));
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(Matrix44)
{
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return -1;
    }
    if (!pyPlasma_check<float>(value)) {
        PyErr_SetString(PyExc_TypeError, "Matrix values should be floats");
        return -1;
    }
    (*self->fThis)(i, j) = pyPlasma_get<float>(value);
    return 0;
}

PY_GETSET_GETTER_DECL(Matrix44, mat)
{
    PyObject* t1 = PyTuple_New(4);
    PyObject* t2 = PyTuple_New(4);
    PyObject* t3 = PyTuple_New(4);
    PyObject* t4 = PyTuple_New(4);
    PyTuple_SET_ITEM(t1, 0, pyPlasma_convert((*self->fThis)(0, 0)));
    PyTuple_SET_ITEM(t1, 1, pyPlasma_convert((*self->fThis)(0, 1)));
    PyTuple_SET_ITEM(t1, 2, pyPlasma_convert((*self->fThis)(0, 2)));
    PyTuple_SET_ITEM(t1, 3, pyPlasma_convert((*self->fThis)(0, 3)));
    PyTuple_SET_ITEM(t2, 0, pyPlasma_convert((*self->fThis)(1, 0)));
    PyTuple_SET_ITEM(t2, 1, pyPlasma_convert((*self->fThis)(1, 1)));
    PyTuple_SET_ITEM(t2, 2, pyPlasma_convert((*self->fThis)(1, 2)));
    PyTuple_SET_ITEM(t2, 3, pyPlasma_convert((*self->fThis)(1, 3)));
    PyTuple_SET_ITEM(t3, 0, pyPlasma_convert((*self->fThis)(2, 0)));
    PyTuple_SET_ITEM(t3, 1, pyPlasma_convert((*self->fThis)(2, 1)));
    PyTuple_SET_ITEM(t3, 2, pyPlasma_convert((*self->fThis)(2, 2)));
    PyTuple_SET_ITEM(t3, 3, pyPlasma_convert((*self->fThis)(2, 3)));
    PyTuple_SET_ITEM(t4, 0, pyPlasma_convert((*self->fThis)(3, 0)));
    PyTuple_SET_ITEM(t4, 1, pyPlasma_convert((*self->fThis)(3, 1)));
    PyTuple_SET_ITEM(t4, 2, pyPlasma_convert((*self->fThis)(3, 2)));
    PyTuple_SET_ITEM(t4, 3, pyPlasma_convert((*self->fThis)(3, 3)));

    PyObject* mat = PyTuple_New(4);
    PyTuple_SET_ITEM(mat, 0, t1);
    PyTuple_SET_ITEM(mat, 1, t2);
    PyTuple_SET_ITEM(mat, 2, t3);
    PyTuple_SET_ITEM(mat, 3, t4);
    return mat;
}

PY_PROPERTY_GETSET_RO_DECL(Matrix44, mat)

PY_GETSET_GETTER_DECL(Matrix44, glMat)
{
    PyObject* mat = PyTuple_New(16);
    const float* glmat = self->fThis->glMatrix();
    PyTuple_SET_ITEM(mat, 0, pyPlasma_convert(glmat[0]));
    PyTuple_SET_ITEM(mat, 1, pyPlasma_convert(glmat[1]));
    PyTuple_SET_ITEM(mat, 2, pyPlasma_convert(glmat[2]));
    PyTuple_SET_ITEM(mat, 3, pyPlasma_convert(glmat[3]));
    PyTuple_SET_ITEM(mat, 4, pyPlasma_convert(glmat[4]));
    PyTuple_SET_ITEM(mat, 5, pyPlasma_convert(glmat[5]));
    PyTuple_SET_ITEM(mat, 6, pyPlasma_convert(glmat[6]));
    PyTuple_SET_ITEM(mat, 7, pyPlasma_convert(glmat[7]));
    PyTuple_SET_ITEM(mat, 8, pyPlasma_convert(glmat[8]));
    PyTuple_SET_ITEM(mat, 9, pyPlasma_convert(glmat[9]));
    PyTuple_SET_ITEM(mat, 10, pyPlasma_convert(glmat[10]));
    PyTuple_SET_ITEM(mat, 11, pyPlasma_convert(glmat[11]));
    PyTuple_SET_ITEM(mat, 12, pyPlasma_convert(glmat[12]));
    PyTuple_SET_ITEM(mat, 13, pyPlasma_convert(glmat[13]));
    PyTuple_SET_ITEM(mat, 14, pyPlasma_convert(glmat[14]));
    PyTuple_SET_ITEM(mat, 15, pyPlasma_convert(glmat[15]));
    return mat;
}

PY_PROPERTY_GETSET_RO_DECL(Matrix44, glMat)

PyGetSetDef pyMatrix44_GetSet[] = {
    pyMatrix44_mat_getset,
    pyMatrix44_glMat_getset,
    PY_GETSET_TERMINATOR
};

PY_METHOD_STATIC_NOARGS(Matrix44, Identity, "Creates an identity matrix")
{
    return pyPlasma_convert(hsMatrix44::Identity());
}

PY_METHOD_STATIC_VA(Matrix44, TranslateMat,
    "Params: vector\n"
    "Creates a translation matrix")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "TranslateMat expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "TranslateMat expects an hsVector3");
        return nullptr;
    }
    return pyPlasma_convert(hsMatrix44::TranslateMat(*vec->fThis));
}

PY_METHOD_STATIC_VA(Matrix44, RotateMat,
    "Params: axis, angle\n"
    "Creates a rotation matrix")
{
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "RotateMat expects int, float");
        return nullptr;
    }
    return pyPlasma_convert(hsMatrix44::RotateMat(axis, angle));
}

PY_METHOD_STATIC_VA(Matrix44, ScaleMat,
    "Params: vector\n"
    "Creates a scaling matrix")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "ScaleMat expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "ScaleMat expects an hsVector3");
        return nullptr;
    }
    return pyPlasma_convert(hsMatrix44::ScaleMat(*vec->fThis));
}

PY_METHOD_NOARGS(Matrix44, inverse, "Returns the inverse of the matrix")
{
    return pyPlasma_convert(self->fThis->inverse());
}

PY_METHOD_NOARGS(Matrix44, isIdentity,
    "Returns True if the matrix is the identity matrix")
{
    return pyPlasma_convert(self->fThis->IsIdentity());
}

PY_METHOD_VA(Matrix44, translate,
    "Params: vector\n"
    "Translate the matrix by the specified vector")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "translate expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "translate expects an hsVector3");
        return nullptr;
    }
    self->fThis->translate(*vec->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, rotate,
    "Params: axis, angle\n"
    "Rotate the matrix around the specified axis by angle radians")
{
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "rotate expects int, float");
        return nullptr;
    }
    self->fThis->rotate(axis, angle);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, scale,
    "Params: vector\n"
    "Scale the matrix by the specified vector")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "scale expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "scale expects an hsVector3");
        return nullptr;
    }
    self->fThis->scale(*vec->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, setTranslate,
    "Params: vector\n"
    "Set the absolute translation")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "setTranslate expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "setTranslate expects an hsVector3");
        return nullptr;
    }
    self->fThis->setTranslate(*vec->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, setRotate,
    "Params: axis, angle\n"
    "Set the absolute rotation to be along `axis` at `angle` radians")
{
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "setRotate expects int, float");
        return nullptr;
    }
    self->fThis->setRotate(axis, angle);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, setScale,
    "Params: vector\n"
    "Set the absolute scale")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "setScale expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "setScale expects an hsVector3");
        return nullptr;
    }
    self->fThis->setScale(*vec->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, multPoint,
    "Params: vector\n"
    "Multiply a point by the matrix and add displacement")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "multPoint expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "multPoint expects an hsVector3");
        return nullptr;
    }
    hsVector3 result = self->fThis->multPoint(*vec->fThis);
    return pyPlasma_convert(result);
}

PY_METHOD_VA(Matrix44, multVector,
    "Params: vector\n"
    "Multiply a vector by the matrix and do not add displacement")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "multVector expects an hsVector3");
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "multVector expects an hsVector3");
        return nullptr;
    }
    hsVector3 result = self->fThis->multVector(*vec->fThis);
    return pyPlasma_convert(result);
}

PY_METHOD_VA(Matrix44, read,
    "Params: stream\n"
    "Reads this matrix from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix44, write,
    "Params: stream\n"
    "Writes this matrix to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PyMethodDef pyMatrix44_Methods[] = {
    pyMatrix44_Identity_method,
    pyMatrix44_TranslateMat_method,
    pyMatrix44_RotateMat_method,
    pyMatrix44_ScaleMat_method,
    pyMatrix44_inverse_method,
    pyMatrix44_isIdentity_method,
    pyMatrix44_translate_method,
    pyMatrix44_rotate_method,
    pyMatrix44_scale_method,
    pyMatrix44_setTranslate_method,
    pyMatrix44_setRotate_method,
    pyMatrix44_setScale_method,
    pyMatrix44_multPoint_method,
    pyMatrix44_multVector_method,
    pyMatrix44_read_method,
    pyMatrix44_write_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_NB_BINARYFUNC_DECL(Matrix44, multiply)
{
    if (!pyPlasma_check<hsMatrix44>(left) || !pyPlasma_check<hsMatrix44>(right)) {
        PyErr_SetString(PyExc_TypeError, "Multiplication operand is not another matrix");
        return nullptr;
    }
    return pyPlasma_convert(pyPlasma_get<hsMatrix44>(left) * pyPlasma_get<hsMatrix44>(right));
}

PY_PLASMA_TYPE(Matrix44, hsMatrix44, "hsMatrix44 wrapper")
PY_PLASMA_TYPE_AS_NUMBER(Matrix44)
PY_PLASMA_TYPE_AS_MAPPING(Matrix44)

PY_PLASMA_TYPE_INIT(Matrix44)
{
    pyMatrix44_As_Number.nb_multiply = pyMatrix44_nb_multiply;
    pyMatrix44_As_Mapping.mp_subscript = pyMatrix44_mp_subscript;
    pyMatrix44_As_Mapping.mp_ass_subscript = pyMatrix44_mp_ass_subscript;
    pyMatrix44_Type.tp_dealloc = pyMatrix44_dealloc;
    pyMatrix44_Type.tp_init = pyMatrix44___init__;
    pyMatrix44_Type.tp_new = pyMatrix44_new;
    pyMatrix44_Type.tp_as_number = &pyMatrix44_As_Number;
    pyMatrix44_Type.tp_as_mapping = &pyMatrix44_As_Mapping;
    pyMatrix44_Type.tp_methods = pyMatrix44_Methods;
    pyMatrix44_Type.tp_getset = pyMatrix44_GetSet;
    pyMatrix44_Type.tp_flags |= Py_TPFLAGS_CHECKTYPES;
    if (PyType_CheckAndReady(&pyMatrix44_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Matrix44, "kRight", hsMatrix44::kRight);
    PY_TYPE_ADD_CONST(Matrix44, "kUp", hsMatrix44::kUp);
    PY_TYPE_ADD_CONST(Matrix44, "kView", hsMatrix44::kView);

    Py_INCREF(&pyMatrix44_Type);
    return (PyObject*)&pyMatrix44_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Matrix44, hsMatrix44)
