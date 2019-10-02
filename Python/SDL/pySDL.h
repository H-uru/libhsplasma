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

#ifndef _PYSDL_H
#define _PYSDL_H

#include "PyPlasma.h"
#include <SDL/plStateDescriptor.h>

PY_WRAP_PLASMA(SDLMgr, class plSDLMgr);

PY_WRAP_PLASMA(VarDescriptor, class plVarDescriptor);
PY_WRAP_PLASMA(StateDescriptor, class plStateDescriptor);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plVarDescriptor::Type value) { return PyInt_FromLong((long)value); }

template <> inline int pyPlasma_check<plVarDescriptor::Type>(PyObject* value) { return PyInt_Check(value); }

template <> inline plVarDescriptor::Type pyPlasma_get(PyObject* value) { return (plVarDescriptor::Type)PyInt_AsLong(value); }

#endif
