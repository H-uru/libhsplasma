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

#ifndef _PYSHADER_H
#define _PYSHADER_H

#include "PyPlasma.h"
#include <PRP/Surface/plShader.h>

PY_WRAP_PLASMA_VALUE(ShaderConst, class plShaderConst);
PY_WRAP_PLASMA(Shader, class plShader);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plShader::plShaderID value)
{
    return PyInt_FromLong((long)value);
}

template <>
inline int pyPlasma_check<plShader::plShaderID>(PyObject* value)
{
    return PyInt_Check(value);
}

template <>
inline plShader::plShaderID pyPlasma_get(PyObject* value)
{
    return (plShader::plShaderID)PyInt_AsLong(value);
}

#endif
