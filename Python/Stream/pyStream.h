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

#ifndef _PYSTREAM_H
#define _PYSTREAM_H

#include "PyPlasma.h"
#include <Util/PlasmaVersions.h>

PY_WRAP_PLASMA(Stream, class hsStream);
PY_WRAP_PLASMA(FileStream, class hsFileStream);
PY_WRAP_PLASMA(EncryptedStream, class plEncryptedStream);
PY_WRAP_PLASMA(RAMStream, class hsRAMStream);

#ifdef _WIN32
PY_WRAP_PLASMA(WindowsStream, class hsWindowsStream);
#endif

/* Python property helpers */
inline PyObject* pyPlasma_convert(const PlasmaVer& value)
{
    return PyLong_FromLong((long)(int)value);
}

template <>
inline int pyPlasma_check<PlasmaVer>(PyObject* value)
{
    return PyLong_Check(value);
}

template <>
inline PlasmaVer pyPlasma_get(PyObject* value)
{
    return PlasmaVer((int)PyLong_AsLong(value));
}

#endif
