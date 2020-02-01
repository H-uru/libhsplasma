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

#include "pyLinkToAgeMsg.h"

#include <PRP/Message/plLinkToAgeMsg.h>
#include "pyMessage.h"
#include "PRP/Misc/pyAgeLinkInfo.h"

PY_PLASMA_NEW(LinkToAgeMsg, plLinkToAgeMsg)

PY_GETSET_GETTER_DECL(LinkToAgeMsg, ageLink)
{
    // This cannot be a subclass, since it's an inline member
    return pyAgeLinkStruct_FromAgeLinkStruct(&self->fThis->getAgeLink());
}

PY_GETSET_SETTER_DECL(LinkToAgeMsg, ageLink)
{
    PY_PROPERTY_CHECK_NULL(ageLink)

    plAgeLinkStruct& als = self->fThis->getAgeLink();
    if (pyAgeLinkStruct_Check(value)) {
        als = *((pyAgeLinkStruct*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "ageLink expected type plAgeLinkStruct");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(LinkToAgeMsg, ageLink)

PY_GETSET_GETTER_DECL(LinkToAgeMsg, linkEffects)
{
    // This cannot be a subclass, since it's an inline member
    return pyAgeLinkEffects_FromAgeLinkEffects(&self->fThis->getLinkEffects());
}

PY_GETSET_SETTER_DECL(LinkToAgeMsg, linkEffects)
{
    PY_PROPERTY_CHECK_NULL(linkEffects)

    plAgeLinkEffects& effects = self->fThis->getLinkEffects();
    if (pyAgeLinkEffects_Check(value)) {
        effects = *((pyAgeLinkEffects*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "linkEffects expected type plAgeLinkEffects");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(LinkToAgeMsg, linkEffects)

static PyGetSetDef pyLinkToAgeMsg_GetSet[] = {
    pyLinkToAgeMsg_ageLink_getset,
    pyLinkToAgeMsg_linkEffects_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LinkToAgeMsg, plLinkToAgeMsg, "plLinkToAgeMsg wrapper")

PY_PLASMA_TYPE_INIT(LinkToAgeMsg)
{
    pyLinkToAgeMsg_Type.tp_new = pyLinkToAgeMsg_new;
    pyLinkToAgeMsg_Type.tp_getset = pyLinkToAgeMsg_GetSet;
    pyLinkToAgeMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyLinkToAgeMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLinkToAgeMsg_Type);
    return (PyObject*)&pyLinkToAgeMsg_Type;
}

PY_PLASMA_IFC_METHODS(LinkToAgeMsg, plLinkToAgeMsg)
