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

#ifndef _PLFACTORY_H
#define _PLFACTORY_H

#include "pdUnifiedTypeMap.h"
#include <functional>

class PLASMA_DLL plFactory
{
public:
    static class plCreatable* Create(short typeIdx);
    static class plCreatable* Create(short typeIdx, PlasmaVer ver);
    static class plCreatable* Create(const char* typeName);
    static const char* ClassName(short typeIdx);
    static const char* ClassName(short typeIdx, PlasmaVer ver);
    static short ClassIndex(const char* typeName);
    static short ClassVersion(short typeIdx, PlasmaVer ver);

    typedef std::function<plCreatable* (short)> OverrideFunc;
    static void SetOverride(OverrideFunc over) { fOverride = std::move(over); }
    static void ClearOverride() { fOverride = OverrideFunc(); }

private:
    static OverrideFunc fOverride;
};

#endif
