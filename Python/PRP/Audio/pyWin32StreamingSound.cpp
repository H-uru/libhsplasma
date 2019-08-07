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

PY_PLASMA_NEW(Win32StreamingSound, plWin32StreamingSound)

PY_PLASMA_TYPE(Win32StreamingSound, plWin32StreamingSound,
               "plWin32StreamingSound wrapper")

PY_PLASMA_TYPE_INIT(Win32StreamingSound)
{
    pyWin32StreamingSound_Type.tp_new = pyWin32StreamingSound_new;
    pyWin32StreamingSound_Type.tp_base = &pyWin32Sound_Type;
    if (PyType_CheckAndReady(&pyWin32StreamingSound_Type) < 0)
        return nullptr;

    Py_INCREF(&pyWin32StreamingSound_Type);
    return (PyObject*)&pyWin32StreamingSound_Type;
}

PY_PLASMA_IFC_METHODS(Win32StreamingSound, plWin32StreamingSound)
