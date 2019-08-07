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

#include "pyWin32Sound.h"

#include <PRP/Audio/plWin32Sound.h>
#include "pySound.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(Win32Sound, "plWin32Sound is abstract")

PY_PROPERTY(unsigned char, Win32Sound, channel, getChannel, setChannel)

static PyGetSetDef pyWin32Sound_GetSet[] = {
    pyWin32Sound_channel_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Win32Sound, plWin32Sound, "plWin32Sound wrapper")

PY_PLASMA_TYPE_INIT(Win32Sound)
{
    pyWin32Sound_Type.tp_new = pyWin32Sound_new;
    pyWin32Sound_Type.tp_getset = pyWin32Sound_GetSet;
    pyWin32Sound_Type.tp_base = &pySound_Type;
    if (PyType_CheckAndReady(&pyWin32Sound_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Win32Sound, "kLeftChannel", plWin32Sound::kLeftChannel);
    PY_TYPE_ADD_CONST(Win32Sound, "kRightChannel", plWin32Sound::kRightChannel);

    Py_INCREF(&pyWin32Sound_Type);
    return (PyObject*)&pyWin32Sound_Type;
}

PY_PLASMA_IFC_METHODS(Win32Sound, plWin32Sound)
