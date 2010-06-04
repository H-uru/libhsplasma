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

#ifndef _HSGLOBALS_H
#define _HSGLOBALS_H

#include "Util/PlasmaVersions.h"
#include "ResManager/plResManager.h"
#include "SDL/plSDLMgr.h"

DllClass hsGlobals {
private:
    static PlasmaVer gVersion;

public:
    static PlasmaVer getVersion() { return gVersion; }
    static void setVersion(PlasmaVersion ver) { gVersion = ver; }

    static plResManager* getResManager();
    static plSDLMgr* getSDLManager();
};

#endif
