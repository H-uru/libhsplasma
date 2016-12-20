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

#include <Python.h>
#include <Util/plString.h>
#include <Sys/Platform.h>
#include <type_traits>

PyObject* PlasmaString_To_PyString(const plString& str);
PyObject* PlasmaString_To_PyUnicode(const plString& str);
plString PyString_To_PlasmaString(PyObject* str);

// The Python API insists that character constants are "char *" without the
// const. Sane compilers complain about this (with good reason). Therefore:
template <size_t size>
inline char* _pycs(const char (&str)[size]) { return const_cast<char*>(str); }

// Python 3.x does things differently...  This should help to keep things
// under control with both 2.x and 3.0 somewhat seamlessly.
#if (PY_MAJOR_VERSION >= 3)
    // Int -> Long
    #define PyInt_Check(ob) PyLong_Check(ob)
    #define PyInt_FromLong PyLong_FromLong
    #define PyInt_AsLong PyLong_AsLong

    // String -> Unicode
    #define PyString_FromString(str) PyUnicode_DecodeUTF8((str), strlen((str)), NULL)
    #define PlStr_To_PyStr PlasmaString_To_PyUnicode

    // Py_TPFLAGS_CHECKTYPES is no longer used in Py3k
    #define Py_TPFLAGS_CHECKTYPES 0
#elif (PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION >= 6)
    #undef PyBytes_Check
    #undef PyBytes_FromStringAndSize
    #undef PyBytes_AsStringAndSize
    #undef PyBytes_AsString

    #define PlStr_To_PyStr PlasmaString_To_PyString
    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
    #define PyBytes_AsString PyString_AsString
#else
    #error Your Python version is too old.  Only 2.6 and later are supported
#endif

#if (PY_MAJOR_VERSION >= 3) || ((PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION >= 6))
    #define TP_VERSION_TAG_INIT 0,
#else
    #define TP_VERSION_TAG_INIT
#endif

#if (PY_MAJOR_VERSION >= 4) || ((PY_MAJOR_VERSION == 3) && (PY_MINOR_VERSION >= 4))
    #define TP_FINALIZE_INIT NULL,
#else
    #define TP_FINALIZE_INIT
#endif

// This should work the same for all versions
#define PyStr_To_PlStr PyString_To_PlasmaString
#define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))

// C doesn't have boolean types until C11, which Python doesn't use
#define PyBool_FromBool(b) PyBool_FromLong((b) ? 1 : 0)
#define PyBool_AsBool(b) (PyInt_AsLong((b)) != 0)

/* Use this macro to ensure the layouts of subclass types are consistent */
#define PY_WRAP_PLASMA(pyType, plType)                          \
    extern "C" {                                                \
    struct py##pyType {                                         \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
        bool fPyOwned;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(plType*);               \
    }

#define PY_WRAP_PLASMA_VALUE(pyType, plType)                    \
    extern "C" {                                                \
    struct py##pyType {                                         \
        PyObject_HEAD                                           \
        plType* fThis;                                          \
    };                                                          \
    extern PyTypeObject py##pyType##_Type;                      \
    PyObject* Init_py##pyType##_Type();                         \
    int py##pyType##_Check(PyObject* obj);                      \
    PyObject* py##pyType##_From##pyType(const plType&);         \
    }

#define PY_PLASMA_CHECK_TYPE(pyType)                                    \
    int py##pyType##_Check(PyObject* obj) {                             \
        if (obj->ob_type == &py##pyType##_Type                          \
            || PyType_IsSubtype(obj->ob_type, &py##pyType##_Type))      \
            return 1;                                                   \
        return 0;                                                       \
    }

#define PY_PLASMA_IFC_METHODS(pyType, plType)                           \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(plType* obj) {                  \
        if (!obj) {                                                     \
            Py_INCREF(Py_None);                                         \
            return Py_None;                                             \
        }                                                               \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = obj;                                             \
        pyobj->fPyOwned = false;                                        \
        return (PyObject*)pyobj;                                        \
    }

#define PY_PLASMA_VALUE_IFC_METHODS(pyType, plType)                     \
    PY_PLASMA_CHECK_TYPE(pyType)                                        \
    PyObject* py##pyType##_From##pyType(const plType& obj) {            \
        py##pyType* pyobj = PyObject_New(py##pyType, &py##pyType##_Type); \
        pyobj->fThis = new plType(obj);                                 \
        return (PyObject*)pyobj;                                        \
    }

/* Helpers for getters and setters */
inline PyObject* pyPlasma_convert(uint8_t value) { return PyInt_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(uint16_t value) { return PyInt_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(uint32_t value) { return PyInt_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(uint64_t value) { return PyInt_FromLong((long)(unsigned long)value); }
inline PyObject* pyPlasma_convert(int8_t value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(int16_t value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(int32_t value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(int64_t value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(float value) { return PyFloat_FromDouble((double)value); }
inline PyObject* pyPlasma_convert(double value) { return PyFloat_FromDouble(value); }
inline PyObject* pyPlasma_convert(bool value) { return PyBool_FromBool(value); }
inline PyObject* pyPlasma_convert(const plString& value) { return PlStr_To_PyStr(value); }
inline PyObject* pyPlasma_convert(CallbackEvent value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(ControlEventCode value) { return PyInt_FromLong((long)value); }
inline PyObject* pyPlasma_convert(plKeyDef value) { return PyInt_FromLong((long)value); }

// Force compilers to throw an error for pointers without a specialization,
// rather than converting them to an integral type and accepting it silently
PyObject* pyPlasma_convert(void* value) = delete;

template <typename T>
inline int pyPlasma_check(PyObject* value)
{
    return T::unimplemented_specialization_for_pyPlasma_check();
}

template <> inline int pyPlasma_check<uint8_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<uint16_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<uint32_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<uint64_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<int8_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<int16_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<int32_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<int64_t>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<float>(PyObject* value) { return PyFloat_Check(value); }
template <> inline int pyPlasma_check<double>(PyObject* value) { return PyFloat_Check(value); }
template <> inline int pyPlasma_check<bool>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<plString>(PyObject* value) { return PyAnyStr_Check(value); }
template <> inline int pyPlasma_check<CallbackEvent>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<ControlEventCode>(PyObject* value) { return PyInt_Check(value); }
template <> inline int pyPlasma_check<plKeyDef>(PyObject* value) { return PyInt_Check(value); }

template <typename T>
inline T pyPlasma_get(PyObject* value) {
    return T::unimplemented_specialization_for_pyPlasma_get();
}

template <> inline uint8_t pyPlasma_get(PyObject* value) { return (uint8_t)(unsigned long)PyInt_AsLong(value); }
template <> inline uint16_t pyPlasma_get(PyObject* value) { return (uint16_t)(unsigned long)PyInt_AsLong(value); }
template <> inline uint32_t pyPlasma_get(PyObject* value) { return (uint32_t)(unsigned long)PyInt_AsLong(value); }
template <> inline uint64_t pyPlasma_get(PyObject* value) { return (uint64_t)(unsigned long)PyInt_AsLong(value); }
template <> inline int8_t pyPlasma_get(PyObject* value) { return (int8_t)PyInt_AsLong(value); }
template <> inline int16_t pyPlasma_get(PyObject* value) { return (int16_t)PyInt_AsLong(value); }
template <> inline int32_t pyPlasma_get(PyObject* value) { return (int32_t)PyInt_AsLong(value); }
template <> inline int64_t pyPlasma_get(PyObject* value) { return (int64_t)PyInt_AsLong(value); }
template <> inline float pyPlasma_get(PyObject* value) { return (float)PyFloat_AsDouble(value); }
template <> inline double pyPlasma_get(PyObject* value) { return PyFloat_AsDouble(value); }
template <> inline bool pyPlasma_get(PyObject* value) { return PyInt_AsLong(value) != 0; }
template <> inline plString pyPlasma_get(PyObject* value) { return PyString_To_PlasmaString(value); }
template <> inline CallbackEvent pyPlasma_get(PyObject* value) { return (CallbackEvent)PyInt_AsLong(value); }
template <> inline ControlEventCode pyPlasma_get(PyObject* value) { return (ControlEventCode)PyInt_AsLong(value); }
template <> inline plKeyDef pyPlasma_get(PyObject* value) { return (plKeyDef)PyInt_AsLong(value); }

#define PY_GETSET_GETTER_DECL(pyType, name)                             \
    static PyObject* py##pyType##_get_##name(py##pyType* self, void*)

#define PY_GETSET_SETTER_DECL(pyType, name)                             \
    static int py##pyType##_set_##name(py##pyType* self, PyObject* value, void*)

#define PY_PROPERTY_GETSET_DECL(pyType, name)                           \
    static PyGetSetDef py##pyType##_##name##_getset = {                 \
        _pycs(#name), (getter)py##pyType##_get_##name,                  \
        (setter)py##pyType##_set_##name, NULL, NULL                     \
    };

#define PY_PROPERTY_GETSET_RO_DECL(pyType, name)                        \
    static PyGetSetDef py##pyType##_##name##_getset = {                 \
        _pycs(#name), (getter)py##pyType##_get_##name,                  \
        NULL, NULL, NULL                                                \
    };

#define PY_GETSET_TERMINATOR { NULL, NULL, NULL, NULL, NULL }

#define PY_PROPERTY_READ(pyType, name, getter)                          \
    PY_GETSET_GETTER_DECL(pyType, name) {                               \
        return pyPlasma_convert(self->fThis->getter());                 \
    }

#define PY_PROPERTY_WRITE(type, pyType, name, setter)                   \
    PY_GETSET_SETTER_DECL(pyType, name) {                               \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #name " cannot be deleted"); \
            return -1;                                                  \
        } else if (!pyPlasma_check<type>(value)) {                      \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #type); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setter(pyPlasma_get<type>(value));                 \
        return 0;                                                       \
    }

#define PY_PROPERTY_SETTER_MSG(pyType, name, message)                   \
    PY_GETSET_SETTER_DECL(pyType, name) {                               \
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


#define PY_PROPERTY_MEMBER_READ(pyType, name, member)                   \
    PY_GETSET_GETTER_DECL(pyType, name) {                               \
        return pyPlasma_convert(self->fThis->member);                   \
    }

#define PY_PROPERTY_MEMBER_WRITE(type, pyType, name, member)            \
    PY_GETSET_SETTER_DECL(pyType, name) {                               \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #name " cannot be deleted"); \
            return -1;                                                  \
        } else if (!pyPlasma_check<type>(value)) {                      \
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

#define PY_PROPERTY_PROXY_READ(pyType, name, getter)                    \
    PY_GETSET_GETTER_DECL(pyType, name) {                               \
        return pyPlasma_convert(&self->fThis->getter());                \
    }

#define PY_PROPERTY_PROXY_WRITE(type, pyType, name, getter)             \
    PY_GETSET_SETTER_DECL(pyType, name) {                               \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #name " cannot be deleted"); \
            return -1;                                                  \
        } else if (!pyPlasma_check<type>(value)) {                      \
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

#endif
