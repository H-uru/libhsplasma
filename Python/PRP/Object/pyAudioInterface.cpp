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

#include "pyObjInterface.h"

#include <PRP/Object/plAudioInterface.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(AudioInterface, plAudioInterface)

PY_PROPERTY(plKey, AudioInterface, audible, getAudible, setAudible)

PyGetSetDef pyAudioInterface_GetSet[] = {
    pyAudioInterface_audible_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AudioInterface, plAudioInterface, "plAudioInterface wrapper")

PY_PLASMA_TYPE_INIT(AudioInterface)
{
    pyAudioInterface_Type.tp_new = pyAudioInterface_new;
    pyAudioInterface_Type.tp_getset = pyAudioInterface_GetSet;
    pyAudioInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyAudioInterface_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAudioInterface_Type);
    return (PyObject*)&pyAudioInterface_Type;
}

PY_PLASMA_IFC_METHODS(AudioInterface, plAudioInterface)
