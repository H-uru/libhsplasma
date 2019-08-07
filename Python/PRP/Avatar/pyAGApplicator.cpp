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

#include "pyAGApplicator.h"

#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(AGApplicator, "plAGApplicator is abstract")

PY_PROPERTY_CREATABLE(plAGChannel, AGChannel, AGApplicator, channel,
                      getChannel, setChannel)
PY_PROPERTY(bool, AGApplicator, enabled, isEnabled, setEnabled)
PY_PROPERTY(ST::string, AGApplicator, channelName, getChannelName, setChannelName)

static PyGetSetDef pyAGApplicator_GetSet[] = {
    pyAGApplicator_channel_getset,
    pyAGApplicator_enabled_getset,
    pyAGApplicator_channelName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGApplicator, plAGApplicator, "plAGApplicator wrapper")

PY_PLASMA_TYPE_INIT(AGApplicator)
{
    pyAGApplicator_Type.tp_new = pyAGApplicator_new;
    pyAGApplicator_Type.tp_getset = pyAGApplicator_GetSet;
    pyAGApplicator_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAGApplicator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAGApplicator_Type);
    return (PyObject*)&pyAGApplicator_Type;
}

PY_PLASMA_IFC_METHODS(AGApplicator, plAGApplicator)
