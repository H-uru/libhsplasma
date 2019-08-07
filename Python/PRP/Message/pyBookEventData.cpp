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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>

PY_PLASMA_NEW(BookEventData, proBookEventData)

PY_PROPERTY(unsigned int, BookEventData, event, getEvent, setEvent)
PY_PROPERTY(unsigned int, BookEventData, linkID, getLinkID, setLinkID)

static PyGetSetDef pyBookEventData_GetSet[] = {
    pyBookEventData_event_getset,
    pyBookEventData_linkID_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(BookEventData, proBookEventData, "proBookEventData wrapper")

PY_PLASMA_TYPE_INIT(BookEventData)
{
    pyBookEventData_Type.tp_new = pyBookEventData_new;
    pyBookEventData_Type.tp_getset = pyBookEventData_GetSet;
    pyBookEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyBookEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyBookEventData_Type);
    return (PyObject*)&pyBookEventData_Type;
}

PY_PLASMA_IFC_METHODS(BookEventData, proBookEventData)
