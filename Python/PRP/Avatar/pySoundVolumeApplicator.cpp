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
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SoundVolumeApplicator, plSoundVolumeApplicator)

PY_PROPERTY(unsigned int, SoundVolumeApplicator, index, getIndex, setIndex)

static PyGetSetDef pySoundVolumeApplicator_GetSet[] = {
    pySoundVolumeApplicator_index_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SoundVolumeApplicator, plSoundVolumeApplicator,
               "plSoundVolumeApplicator wrapper")

PY_PLASMA_TYPE_INIT(SoundVolumeApplicator)
{
    pySoundVolumeApplicator_Type.tp_new = pySoundVolumeApplicator_new;
    pySoundVolumeApplicator_Type.tp_getset = pySoundVolumeApplicator_GetSet;
    pySoundVolumeApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_CheckAndReady(&pySoundVolumeApplicator_Type) < 0)
        return nullptr;

    Py_INCREF(&pySoundVolumeApplicator_Type);
    return (PyObject*)&pySoundVolumeApplicator_Type;
}

PY_PLASMA_IFC_METHODS(SoundVolumeApplicator, plSoundVolumeApplicator)
