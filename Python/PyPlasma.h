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

#ifndef _PYPLASMA_H
#define _PYPLASMA_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <PlasmaDefs.h>
#include <Sys/Platform.h>
#include <string_theory/string>
#include <type_traits>

PyObject* PyUnicode_FromSTString(const ST::string& str);
ST::string PyAnyString_AsSTString(PyObject* str);
int PyAnyString_PathDecoder(PyObject* obj, void* str);
#define PyAnyString_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))

int PyType_CheckAndReady(PyTypeObject* type);

// The Python API insists that character constants are "char *" without the
// const. Sane compilers complain about this (with good reason). Therefore:
template <size_t size>
inline char* _pycs(const char (&str)[size]) { return const_cast<char*>(str); }

/* Helper object for managing and accessing the reference that is returned by
 * PySequence_Fast() to allow fast access to arbitrary sequence-type objects */
struct pySequenceFastRef
{
    PyObject* fObj;

    pySequenceFastRef(PyObject* o)
        : fObj(PySequence_Fast(o, "Object is not a sequence")) { }
    ~pySequenceFastRef() { Py_XDECREF(fObj); }

    bool isSequence() const { return fObj != nullptr; }

    Py_ssize_t size() { return PySequence_Fast_GET_SIZE(fObj); }

    /** Returns a borrowed reference within the sequence FAST storage */
    PyObject* get(Py_ssize_t idx) { return PySequence_Fast_GET_ITEM(fObj, idx); }
};

#if (PY_MAJOR_VERSION < 3) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION < 2))
    #error Your Python version is too old.  Only 3.2 and later are supported
#endif

// C doesn't have boolean types until C11, which Python doesn't use
#define PyBool_FromBool(b) PyBool_FromLong((b) ? 1 : 0)
#define PyBool_AsBool(b) (PyLong_AsLong((b)) != 0)

/* Use this macro to ensure the layouts of subclass types are consistent */
#define PY_WRAP_PLASMA(pyType, plType)                          \
    struct py##pyType                                           \
    {                                                           \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
        bool fPyOwned;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(plType*);

/* Defines a value-type wrapped class (i.e. those which are copied instead of
 * sharing references) */
#define PY_WRAP_PLASMA_VALUE(pyType, plType)                    \
    struct py##pyType                                           \
    {                                                           \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(const plType&);

#define PY_PLASMA_CHECK_TYPE(pyType)                                    \
    int py##pyType##_Check(PyObject* obj)                               \
    {                                                                   \
        if (obj->ob_type == &py##pyType##_Type                          \
            || PyType_IsSubtype(obj->ob_type, &py##pyType##_Type))      \
            return 1;                                                   \
        return 0;                                                       \
    }

#define PY_PLASMA_IFC_METHODS(pyType, plType)                           \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(plType* obj)                    \
    {                                                                   \
        if (!obj)                                                       \
            Py_RETURN_NONE;                                             \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = obj;                                             \
        pyobj->fPyOwned = false;                                        \
        return (PyObject*)pyobj;                                        \
    }

#define PY_PLASMA_VALUE_IFC_METHODS(pyType, plType)                     \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(const plType& obj)              \
    {                                                                   \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = new plType(obj);                                 \
        return (PyObject*)pyobj;                                        \
    }

template <class pyType, class plType, typename... ArgsT>
PyObject* PyPlasma_new(PyTypeObject* type, ArgsT&&... args)
{
    pyType* self = (pyType*)type->tp_alloc(type, 0);
    if (self) {
        self->fThis = new plType(std::forward<ArgsT&&>(args)...);
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

template <class pyType, class plType, typename... ArgsT>
PyObject* PyPlasmaValue_new(PyTypeObject* type, ArgsT&&... args)
{
    pyType* self = (pyType*)type->tp_alloc(type, 0);
    if (self)
        self->fThis = new plType(std::forward<ArgsT&&>(args)...);
    return (PyObject*)self;
}

#define PY_PLASMA_NEW_DECL(pyType)                                      \
    static PyObject* py##pyType##_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)

/* The default tp_new implementation */
#define PY_PLASMA_NEW(pyType, plType)                                   \
    PY_PLASMA_NEW_DECL(pyType)                                          \
    {                                                                   \
        (void)args;                                                     \
        (void)kwargs;                                                   \
        return PyPlasma_new<py##pyType, plType>(type);                  \
    }

/* The default tp_new implementation with one or more static arguments */
#define PY_PLASMA_NEW_VA(pyType, plType, ...)                           \
    PY_PLASMA_NEW_DECL(pyType)                                          \
    {                                                                   \
        (void)args;                                                     \
        (void)kwargs;                                                   \
        return PyPlasma_new<py##pyType, plType>(type, __VA_ARGS__);     \
    }

/* The default tp_new implementation for value-type objects */
#define PY_PLASMA_VALUE_NEW(pyType, plType)                             \
    PY_PLASMA_NEW_DECL(pyType)                                          \
    {                                                                   \
        (void)args;                                                     \
        (void)kwargs;                                                   \
        return PyPlasmaValue_new<py##pyType, plType>(type);             \
    }

/* A tp_new implementation that raises a RuntimeError instead of constructing
 * an object */
#define PY_PLASMA_NEW_MSG(pyType, message)                              \
    PY_PLASMA_NEW_DECL(pyType)                                          \
    {                                                                   \
        (void)args;                                                     \
        (void)kwargs;                                                   \
        PyErr_SetString(PyExc_RuntimeError, message);                   \
        return nullptr;                                                 \
    }

#define PY_PLASMA_INIT_DECL(pyType)                                     \
    static int py##pyType##___init__impl(py##pyType*, PyObject*, PyObject*); \
    static int (*py##pyType##___init__)(PyObject*, PyObject*, PyObject*) = (initproc)&py##pyType##___init__impl; \
    int py##pyType##___init__impl(py##pyType* self, PyObject* args, PyObject* kwds)

/* The default tp_init implementation for objects which have no need for
 * custom __init__() behavior or additional arguments */
#define PY_PLASMA_EMPTY_INIT(pyType)                                    \
    PY_PLASMA_INIT_DECL(pyType)                                         \
    {                                                                   \
        if (!PyArg_ParseTuple(args, ""))                                \
            return -1;                                                  \
        return 0;                                                       \
    }

#define PY_PLASMA_DEALLOC_DECL(pyType)                                  \
    static void py##pyType##_dealloc(PyObject* self)

/* The default tp_dealloc implementation */
#define PY_PLASMA_DEALLOC(pyType)                                       \
    PY_PLASMA_DEALLOC_DECL(pyType)                                      \
    {                                                                   \
        if (((py##pyType*)self)->fPyOwned)                              \
            delete ((py##pyType*)self)->fThis;                          \
        Py_TYPE(self)->tp_free(self);                                   \
    }

/* The default tp_dealloc implementation for value-type objects */
#define PY_PLASMA_VALUE_DEALLOC(pyType)                                 \
    PY_PLASMA_DEALLOC_DECL(pyType)                                      \
    {                                                                   \
        delete ((py##pyType*)self)->fThis;                              \
        Py_TYPE(self)->tp_free(self);                                   \
    }

/* Helpers for other types of special functions */
#define PY_PLASMA_REPR_DECL(pyType)                                     \
    static PyObject* py##pyType##_repr_impl(py##pyType*);               \
    static PyObject* (*py##pyType##_repr)(PyObject*) = (reprfunc)py##pyType##_repr_impl; \
    PyObject* py##pyType##_repr_impl(py##pyType* self)

#define PY_PLASMA_STR_DECL(pyType)                                      \
    static PyObject* py##pyType##_str_impl(py##pyType*);                \
    static PyObject* (*py##pyType##_str)(PyObject*) = (reprfunc)py##pyType##_str_impl; \
    PyObject* py##pyType##_str_impl(py##pyType* self)

#define PY_PLASMA_HASH_DECL(pyType)                                     \
    static Py_hash_t py##pyType##_hash_impl(py##pyType*);                    \
    static Py_hash_t (*py##pyType##_hash)(PyObject*) = (hashfunc)py##pyType##_hash_impl; \
    Py_hash_t py##pyType##_hash_impl(py##pyType* self)

#define PY_PLASMA_LENGTH_DECL(pyType)                                   \
    static Py_ssize_t py##pyType##_length_impl(py##pyType*);            \
    static Py_ssize_t (*py##pyType##_length)(PyObject*) = (lenfunc)py##pyType##_length_impl; \
    Py_ssize_t py##pyType##_length_impl(py##pyType* self)

#define PY_PLASMA_RICHCOMPARE_DECL(pyType)                              \
    static PyObject* py##pyType##_richcompare_impl(py##pyType*, py##pyType*, int); \
    static PyObject* (*py##pyType##_richcompare)(PyObject*, PyObject*, int) = \
                (richcmpfunc)&py##pyType##_richcompare_impl;            \
    PyObject* py##pyType##_richcompare_impl(py##pyType* left, py##pyType* right, int op)

#define PY_PLASMA_SUBSCRIPT_DECL(pyType)                                \
    static PyObject* py##pyType##_mp_subscript_impl(py##pyType*, PyObject*); \
    static PyObject* (*py##pyType##_mp_subscript)(PyObject*, PyObject*) = \
                (binaryfunc)&py##pyType##_mp_subscript_impl;            \
    PyObject* py##pyType##_mp_subscript_impl(py##pyType* self, PyObject* key)

#define PY_PLASMA_ASS_SUBSCRIPT_DECL(pyType)                            \
    static int py##pyType##_mp_ass_subscript_impl(py##pyType*, PyObject*, PyObject*); \
    static int (*py##pyType##_mp_ass_subscript)(PyObject*, PyObject*, PyObject*) = \
                (objobjargproc)&py##pyType##_mp_ass_subscript_impl;     \
    int py##pyType##_mp_ass_subscript_impl(py##pyType* self, PyObject* key, PyObject* value)

#define PY_PLASMA_NB_BINARYFUNC_DECL(pyType, name)                      \
    static PyObject* py##pyType##_nb_##name(PyObject* left, PyObject* right)

#define PY_PLASMA_NB_UNARYFUNC_DECL(pyType, name)                       \
    static PyObject* py##pyType##_nb_##name##_impl(py##pyType*);        \
    static PyObject* (*py##pyType##_nb_##name)(PyObject*) = (unaryfunc)&py##pyType##_nb_##name##_impl; \
    PyObject* py##pyType##_nb_##name##_impl(py##pyType* self)

#define PY_PLASMA_NB_INQUIRY_DECL(pyType, name)                        \
    static int py##pyType##_nb_##name##_impl(py##pyType*);              \
    static int (*py##pyType##_nb_##name)(PyObject*) = (inquiry)&py##pyType##_nb_##name##_impl; \
    int py##pyType##_nb_##name##_impl(py##pyType* self)

/* Helpers for getters and setters */
inline PyObject* pyPlasma_convert(char value) { return PyLong_FromLong(std::is_signed<char>::value ? (long)value : (long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(unsigned char value) { return PyLong_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(unsigned short value) { return PyLong_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(unsigned int value) { return PyLong_FromUnsignedLong((unsigned long)value); }
inline PyObject* pyPlasma_convert(unsigned long value) { return PyLong_FromUnsignedLong(value); }
inline PyObject* pyPlasma_convert(unsigned long long value) { return PyLong_FromUnsignedLongLong(value); }
inline PyObject* pyPlasma_convert(signed char value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(short value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(int value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(long value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(long long value) { return PyLong_FromLongLong(value); }
inline PyObject* pyPlasma_convert(float value) { return PyFloat_FromDouble((double)value); }
inline PyObject* pyPlasma_convert(double value) { return PyFloat_FromDouble(value); }
inline PyObject* pyPlasma_convert(bool value) { return PyBool_FromBool(value); }
inline PyObject* pyPlasma_convert(const ST::string& value) { return PyUnicode_FromSTString(value); }
inline PyObject* pyPlasma_convert(const char* value) { return PyUnicode_DecodeUTF8(value, strlen(value), nullptr); }
inline PyObject* pyPlasma_convert(CallbackEvent value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(ControlEventCode value) { return PyLong_FromLong((long)value); }
inline PyObject* pyPlasma_convert(plKeyDef value) { return PyLong_FromLong((long)value); }

// Force compilers to throw an error for pointers without a specialization,
// rather than converting them to an integral type and accepting it silently
PyObject* pyPlasma_convert(void* value) = delete;

template <typename T>
inline int pyPlasma_check(PyObject* value)
{
    return T::unimplemented_specialization_for_pyPlasma_check();
}

template <> inline int pyPlasma_check<char>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<unsigned char>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<unsigned short>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<unsigned int>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<unsigned long>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<unsigned long long>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<signed char>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<short>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<int>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<long>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<long long>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<float>(PyObject* value) { return PyFloat_Check(value); }
template <> inline int pyPlasma_check<double>(PyObject* value) { return PyFloat_Check(value); }
template <> inline int pyPlasma_check<bool>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<ST::string>(PyObject* value) { return PyAnyString_Check(value); }
template <> inline int pyPlasma_check<CallbackEvent>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<ControlEventCode>(PyObject* value) { return PyLong_Check(value); }
template <> inline int pyPlasma_check<plKeyDef>(PyObject* value) { return PyLong_Check(value); }

template <typename T>
inline T pyPlasma_get(PyObject* value)
{
    return T::unimplemented_specialization_for_pyPlasma_get();
}

// Python 2.x note:  PyLong_As*Long() will correctly return the value of a
// PyInt object if passed, as well as a PyLong.  Unfortunately, this is not
// also true of PyLong_As*LongLong(), so we must check that explicitly :(

template <> inline char pyPlasma_get(PyObject* value)
{
    return std::is_signed<char>::value ? (char)PyLong_AsLong(value)
                                       : (char)PyLong_AsUnsignedLong(value);
}

template <> inline unsigned char pyPlasma_get(PyObject* value) { return (unsigned char)PyLong_AsUnsignedLong(value); }
template <> inline unsigned short pyPlasma_get(PyObject* value) { return (unsigned short)PyLong_AsUnsignedLong(value); }
template <> inline unsigned int pyPlasma_get(PyObject* value) { return (unsigned int)PyLong_AsUnsignedLong(value); }
template <> inline unsigned long pyPlasma_get(PyObject* value) { return PyLong_AsUnsignedLong(value); }
template <> inline unsigned long long pyPlasma_get(PyObject* value) { return PyLong_AsUnsignedLongLong(value); }
template <> inline signed char pyPlasma_get(PyObject* value) { return (signed char)PyLong_AsLong(value); }
template <> inline short pyPlasma_get(PyObject* value) { return (short)PyLong_AsLong(value); }
template <> inline int pyPlasma_get(PyObject* value) { return (int)PyLong_AsLong(value); }
template <> inline long pyPlasma_get(PyObject* value) { return PyLong_AsLong(value); }
template <> inline long long pyPlasma_get(PyObject* value) { return PyLong_AsLongLong(value); }
template <> inline float pyPlasma_get(PyObject* value) { return (float)PyFloat_AsDouble(value); }
template <> inline double pyPlasma_get(PyObject* value) { return PyFloat_AsDouble(value); }
template <> inline bool pyPlasma_get(PyObject* value) { return PyLong_AsLong(value) != 0; }
template <> inline ST::string pyPlasma_get(PyObject* value) { return PyAnyString_AsSTString(value); }
template <> inline CallbackEvent pyPlasma_get(PyObject* value) { return (CallbackEvent)PyLong_AsLong(value); }
template <> inline ControlEventCode pyPlasma_get(PyObject* value) { return (ControlEventCode)PyLong_AsLong(value); }
template <> inline plKeyDef pyPlasma_get(PyObject* value) { return (plKeyDef)PyLong_AsLong(value); }

/* Helpers for properties (GetSet objects in the Python/C API) */
#define PY_GETSET_GETTER_DECL(pyType, name)                             \
    static PyObject* py##pyType##_get_##name(py##pyType* self, void*)

#define PY_GETSET_SETTER_DECL(pyType, name)                             \
    static int py##pyType##_set_##name(py##pyType* self, PyObject* value, void*)

#define PY_PROPERTY_GETSET_DECL(pyType, name)                           \
    static PyGetSetDef py##pyType##_##name##_getset = {                 \
        _pycs(#name), (getter)py##pyType##_get_##name,                  \
        (setter)py##pyType##_set_##name, nullptr, nullptr               \
    };

#define PY_PROPERTY_GETSET_RO_DECL(pyType, name)                        \
    static PyGetSetDef py##pyType##_##name##_getset = {                 \
        _pycs(#name), (getter)py##pyType##_get_##name,                  \
        nullptr, nullptr, nullptr                                       \
    };

#define PY_GETSET_TERMINATOR { nullptr, nullptr, nullptr, nullptr, nullptr }

#define PY_PROPERTY_READ(pyType, name, getter)                          \
    PY_GETSET_GETTER_DECL(pyType, name)                                 \
    {                                                                   \
        return pyPlasma_convert(self->fThis->getter());                 \
    }

/* Place this at the beginning of a property SETTER to ensure the value
 * is not NULL (i.e. that the caller didn't try to delete the property) */
#define PY_PROPERTY_CHECK_NULL(name)                                    \
    if (value == nullptr) {                                             \
        PyErr_SetString(PyExc_RuntimeError, #name " cannot be deleted"); \
        return -1;                                                      \
    }

#define PY_PROPERTY_WRITE(type, pyType, name, setter)                   \
    PY_GETSET_SETTER_DECL(pyType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (!pyPlasma_check<type>(value)) {                             \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #type); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setter(pyPlasma_get<type>(value));                 \
        return 0;                                                       \
    }

#define PY_PROPERTY_WRITE_PATHLIKE(pyType, name, setter)                \
    PY_GETSET_SETTER_DECL(pyType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        ST::string path;                                                \
        if (!PyAnyString_PathDecoder(value, &path)) {                   \
            PyErr_SetString(PyExc_TypeError, #name " expected type string or os.PathLike object"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setter(path);                                      \
        return 0;                                                       \
    }

#define PY_PROPERTY_SETTER_MSG(pyType, name, message)                   \
    PY_GETSET_SETTER_DECL(pyType, name)                                 \
    {                                                                   \
        (void)self;                                                     \
        (void)value;                                                    \
        PyErr_SetString(PyExc_RuntimeError, message);                   \
        return -1;                                                      \
    }

#define PY_PROPERTY(type, pyType, name, getter, setter)                 \
    PY_PROPERTY_READ(pyType, name, getter)                              \
    PY_PROPERTY_WRITE(type, pyType, name, setter)                       \
    PY_PROPERTY_GETSET_DECL(pyType, name)

#define PY_PROPERTY_RO(pyType, name, getter)                            \
    PY_PROPERTY_READ(pyType, name, getter)                              \
    PY_PROPERTY_GETSET_RO_DECL(pyType, name)

#define PY_PROPERTY_PATHLIKE(pyType, name, getter, setter)              \
    PY_PROPERTY_READ(pyType, name, getter)                              \
    PY_PROPERTY_WRITE_PATHLIKE(pyType, name, setter)                    \
    PY_PROPERTY_GETSET_DECL(pyType, name)

/* Helpers for properties that have direct-access to a member, rather than
 * using getter/setter functions */
#define PY_PROPERTY_MEMBER_READ(pyType, name, member)                   \
    PY_GETSET_GETTER_DECL(pyType, name)                                 \
    {                                                                   \
        return pyPlasma_convert(self->fThis->member);                   \
    }

#define PY_PROPERTY_MEMBER_WRITE(type, pyType, name, member)            \
    PY_GETSET_SETTER_DECL(pyType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (!pyPlasma_check<type>(value)) {                             \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #type); \
            return -1;                                                  \
        }                                                               \
        self->fThis->member = pyPlasma_get<type>(value);                \
        return 0;                                                       \
    }

#define PY_PROPERTY_MEMBER(type, pyType, name, member)                  \
    PY_PROPERTY_MEMBER_READ(pyType, name, member)                       \
    PY_PROPERTY_MEMBER_WRITE(type, pyType, name, member)                \
    PY_PROPERTY_GETSET_DECL(pyType, name)

/* Helpers for properties that proxy an object through a reference, rather
 * than taking a pointer or value and constructing a new object */
#define PY_PROPERTY_PROXY_READ(pyType, name, getter)                    \
    PY_GETSET_GETTER_DECL(pyType, name)                                 \
    {                                                                   \
        return pyPlasma_convert(&self->fThis->getter());                \
    }

#define PY_PROPERTY_PROXY_WRITE(type, pyType, name, getter)             \
    PY_GETSET_SETTER_DECL(pyType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (!pyPlasma_check<type>(value)) {                             \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #type); \
            return -1;                                                  \
        }                                                               \
        self->fThis->getter() = *pyPlasma_get<type*>(value);            \
        return 0;                                                       \
    }

#define PY_PROPERTY_PROXY(type, pyType, name, getter)                   \
    PY_PROPERTY_PROXY_READ(pyType, name, getter)                        \
    PY_PROPERTY_PROXY_WRITE(type, pyType, name, getter)                 \
    PY_PROPERTY_GETSET_DECL(pyType, name)

#define PY_PROPERTY_PROXY_RO(type, pyType, name, getter)                \
    PY_PROPERTY_PROXY_READ(pyType, name, getter)                        \
    PY_PROPERTY_GETSET_RO_DECL(pyType, name)

/* Helpers for setting up the structures and function declarations for
 * bound methods */
#define PY_METHOD_NOARGS(pyType, name, doctext)                         \
    static PyObject* py##pyType##_##name(py##pyType*);                  \
    static PyMethodDef py##pyType##_##name##_method = {                 \
        #name, (PyCFunction)py##pyType##_##name,                        \
        METH_NOARGS,                                                    \
        doctext                                                         \
    };                                                                  \
    PyObject* py##pyType##_##name(py##pyType* self)

#define PY_METHOD_VA(pyType, name, doctext)                             \
    static PyObject* py##pyType##_##name(py##pyType*, PyObject*);       \
    static PyMethodDef py##pyType##_##name##_method = {                 \
        #name, (PyCFunction)py##pyType##_##name,                        \
        METH_VARARGS,                                                   \
        doctext                                                         \
    };                                                                  \
    PyObject* py##pyType##_##name(py##pyType* self, PyObject* args)

#define PY_METHOD_KWARGS(pyType, name, doctext)                         \
    static PyObject* py##pyType##_##name(py##pyType*, PyObject*, PyObject*); \
    static PyMethodDef py##pyType##_##name##_method = {                 \
        #name, (PyCFunction)py##pyType##_##name,                        \
        METH_VARARGS | METH_KEYWORDS,                                   \
        doctext                                                         \
    };                                                                  \
    PyObject* py##pyType##_##name(py##pyType* self, PyObject* args, PyObject* kwds)

#define PY_METHOD_STATIC_NOARGS(pyType, name, doctext)                  \
    static PyObject* py##pyType##_##name(PyObject*);                    \
    static PyMethodDef py##pyType##_##name##_method = {                 \
        #name, (PyCFunction)py##pyType##_##name,                        \
        METH_STATIC | METH_NOARGS,                                      \
        doctext                                                         \
    };                                                                  \
    PyObject* py##pyType##_##name(PyObject*)

#define PY_METHOD_STATIC_VA(pyType, name, doctext)                      \
    static PyObject* py##pyType##_##name(PyObject*, PyObject*);         \
    static PyMethodDef py##pyType##_##name##_method = {                 \
        #name, (PyCFunction)py##pyType##_##name,                        \
        METH_STATIC | METH_VARARGS,                                     \
        doctext                                                         \
    };                                                                  \
    PyObject* py##pyType##_##name(PyObject*, PyObject* args)

#define PY_METHOD_GLOBAL_NOARGS(module, name, doctext)                  \
    static PyObject* module##_##name(PyObject*);                        \
    static PyMethodDef module##_##name##_method = {                     \
        #name, (PyCFunction)module##_##name,                            \
        METH_NOARGS,                                                    \
        doctext                                                         \
    };                                                                  \
    PyObject* module##_##name(PyObject*)

#define PY_METHOD_GLOBAL_VA(module, name, doctext)                      \
    static PyObject* module##_##name(PyObject*, PyObject*);             \
    static PyMethodDef module##_##name##_method = {                     \
        #name, (PyCFunction)module##_##name,                            \
        METH_VARARGS,                                                   \
        doctext                                                         \
    };                                                                  \
    PyObject* module##_##name(PyObject*, PyObject* args)

#define PY_METHOD_TERMINATOR { nullptr, nullptr, 0, nullptr }

/* Helpers for declaring and populating the master PyTypeObject structure */
#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 4))
    #define _TP_FINALIZE_INIT nullptr,
#else
    #define _TP_FINALIZE_INIT
#endif

// tp_print moved to the end, and two new vectorcall fields inserted in Python 3.8...
// tp_print removed entirely from Python 3.9...
#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 8))
    #define _TP_PRINT_OR_VECTORCALL_OFFSET 0
#if (PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION == 8)
    #define _TP_VECTORCALL_PRINT nullptr, nullptr,
#else
    #define _TP_VECTORCALL_PRINT nullptr,
#endif
#else
    #define _TP_PRINT_OR_VECTORCALL_OFFSET nullptr
    #define _TP_VECTORCALL_PRINT
#endif

#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 12))
    #define _TP_WATCHED_INIT 0,
#else
    #define _TP_WATCHED_INIT
#endif

#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 13))
    #define _TP_VERSIONS_USED 0,
#else
    #define _TP_VERSIONS_USED
#endif

#define PY_PLASMA_TYPE(pyType, classname, doctext)                      \
    PyTypeObject py##pyType##_Type = {                                  \
        PyVarObject_HEAD_INIT(nullptr, 0)                               \
        "PyHSPlasma." #classname,                                       \
        sizeof(py##pyType), 0,                                          \
        nullptr, _TP_PRINT_OR_VECTORCALL_OFFSET,                        \
        nullptr, nullptr, nullptr, nullptr,                             \
        nullptr, nullptr, nullptr,                                      \
        nullptr, nullptr, nullptr, nullptr, nullptr,                    \
        nullptr,                                                        \
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                       \
        doctext,                                                        \
        nullptr, nullptr, nullptr, 0, nullptr, nullptr,                 \
        nullptr, nullptr, nullptr, nullptr, nullptr,                    \
        nullptr, nullptr, 0,                                            \
        nullptr, nullptr, nullptr, nullptr, nullptr,                    \
        nullptr, nullptr, nullptr, nullptr, nullptr,                    \
        nullptr, 0,                                                     \
        _TP_FINALIZE_INIT                                               \
        _TP_VECTORCALL_PRINT                                            \
        _TP_WATCHED_INIT                                                \
        _TP_VERSIONS_USED                                               \
    };

#if ((PY_MAJOR_VERSION > 3) || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 5))
    #define _NB_MATRIX_MULTIPLY_INIT nullptr, nullptr,
#else
    #define _NB_MATRIX_MULTIPLY_INIT
#endif

#define PY_PLASMA_TYPE_AS_NUMBER(pyType)                                \
    static PyNumberMethods py##pyType##_As_Number = {                   \
        nullptr, nullptr, nullptr,                                      \
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  \
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,           \
        nullptr, nullptr, nullptr,                                      \
        nullptr, nullptr, nullptr,                                      \
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  \
        nullptr, nullptr, nullptr, nullptr,                             \
        nullptr,                                                        \
        _NB_MATRIX_MULTIPLY_INIT                                        \
    };

#define PY_PLASMA_TYPE_AS_MAPPING(pyType)                               \
    static PyMappingMethods py##pyType##_As_Mapping = {                 \
        nullptr, nullptr, nullptr,                                      \
    };

#define PY_PLASMA_TYPE_INIT(pyType)                                     \
    PyObject* Init_py##pyType##_Type()

#define PY_TYPE_ADD_CONST(pyType, name, value)                          \
    PyDict_SetItemString(py##pyType##_Type.tp_dict, name,               \
                         pyPlasma_convert(value))

#ifndef Py_SET_TYPE
    #define Py_SET_TYPE(ob, type)  Py_TYPE(ob) = type
#endif

#endif
