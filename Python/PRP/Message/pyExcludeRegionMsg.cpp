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

#include "pyExcludeRegionMsg.h"

#include <PRP/Message/plExcludeRegionMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(ExcludeRegionMsg, plExcludeRegionMsg)

PY_PROPERTY(unsigned char, ExcludeRegionMsg, cmd, getCmd, setCmd)
PY_PROPERTY(unsigned int, ExcludeRegionMsg, synchFlags, getSynchFlags, setSynchFlags)

static PyGetSetDef pyExcludeRegionMsg_GetSet[] = {
    pyExcludeRegionMsg_cmd_getset,
    pyExcludeRegionMsg_synchFlags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ExcludeRegionMsg, plExcludeRegionMsg, "plExcludeRegionMsg wrapper")

PY_PLASMA_TYPE_INIT(ExcludeRegionMsg)
{
    pyExcludeRegionMsg_Type.tp_new = pyExcludeRegionMsg_new;
    pyExcludeRegionMsg_Type.tp_getset = pyExcludeRegionMsg_GetSet;
    pyExcludeRegionMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyExcludeRegionMsg_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ExcludeRegionMsg, "kClear", plExcludeRegionMsg::kClear);
    PY_TYPE_ADD_CONST(ExcludeRegionMsg, "kRelease", plExcludeRegionMsg::kRelease);

    Py_INCREF(&pyExcludeRegionMsg_Type);
    return (PyObject*)&pyExcludeRegionMsg_Type;
}

PY_PLASMA_IFC_METHODS(ExcludeRegionMsg, plExcludeRegionMsg)
