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

#include "pyWin32StaticSound.h"

#include <PRP/Audio/plWin32StaticSound.h>
#include "pyWin32Sound.h"

PY_PLASMA_NEW(Win32StaticSound, plWin32StaticSound)

PY_PLASMA_TYPE(Win32StaticSound, plWin32StaticSound, "plWin32StaticSound wrapper")

PY_PLASMA_TYPE_INIT(Win32StaticSound)
{
    pyWin32StaticSound_Type.tp_new = pyWin32StaticSound_new;
    pyWin32StaticSound_Type.tp_base = &pyWin32Sound_Type;
    if (PyType_CheckAndReady(&pyWin32StaticSound_Type) < 0)
        return nullptr;

    Py_INCREF(&pyWin32StaticSound_Type);
    return (PyObject*)&pyWin32StaticSound_Type;
}

PY_PLASMA_IFC_METHODS(Win32StaticSound, plWin32StaticSound)
