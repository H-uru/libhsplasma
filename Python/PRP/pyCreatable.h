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

#ifndef _PYCREATABLE_H
#define _PYCREATABLE_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(Creatable, class plCreatable);
PY_WRAP_PLASMA(CreatableStub, const class plCreatableStub);

PyObject* ICreate(class plCreatable* pCre);

/* Python property helpers */
#define PY_PROPERTY_CREATABLE_READ(myType, name, getter)                \
    PY_GETSET_GETTER_DECL(myType, name)                                 \
    {                                                                   \
        return ICreate(self->fThis->getter());                          \
    }

#define PY_PROPERTY_CREATABLE_WRITE(plType, pyType, myType, name, setter) \
    PY_GETSET_SETTER_DECL(myType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (value == Py_None) {                                         \
            self->fThis->setter(nullptr);                               \
            return 0;                                                   \
        } else if (!py##pyType##_Check(value)) {                        \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #plType); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setter(((py##pyType*)value)->fThis);               \
        ((py##pyType*)value)->fPyOwned = false;                         \
        return 0;                                                       \
    }

#define PY_PROPERTY_CREATABLE(plType, pyType, myType, name, getter, setter) \
    PY_PROPERTY_CREATABLE_READ(myType, name, getter)                    \
    PY_PROPERTY_CREATABLE_WRITE(plType, pyType, myType, name, setter)   \
    PY_PROPERTY_GETSET_DECL(myType, name)

#define PY_PROPERTY_CREATABLE_RO(myType, name, getter)                  \
    PY_PROPERTY_CREATABLE_READ(myType, name, getter)                    \
    PY_PROPERTY_GETSET_RO_DECL(myType, name)

#define PY_PROPERTY_CREATABLE_MEMBER_READ(myType, name, member)         \
    PY_GETSET_GETTER_DECL(myType, name)                                 \
    {                                                                   \
        return ICreate(self->fThis->member);                            \
    }

#define PY_PROPERTY_CREATABLE_MEMBER_WRITE(plType, pyType, myType, name, member) \
    PY_GETSET_SETTER_DECL(myType, name)                                 \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (value == Py_None) {                                         \
            self->fThis->member = nullptr;                              \
            return 0;                                                   \
        } else if (!py##pyType##_Check(value)) {                        \
            PyErr_SetString(PyExc_TypeError, #name " expected type " #plType); \
            return -1;                                                  \
        }                                                               \
        self->fThis->member = ((py##pyType*)value)->fThis;              \
        ((py##pyType*)value)->fPyOwned = false;                         \
        return 0;                                                       \
    }

#define PY_PROPERTY_CREATABLE_MEMBER(plType, pyType, myType, name, member) \
    PY_PROPERTY_CREATABLE_MEMBER_READ(myType, name, member)             \
    PY_PROPERTY_CREATABLE_MEMBER_WRITE(plType, pyType, myType, name, member) \
    PY_PROPERTY_GETSET_DECL(myType, name)

#endif
