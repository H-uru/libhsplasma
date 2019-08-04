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

#ifndef _PNSHA1_H
#define _PNSHA1_H

#include "PlasmaDefs.h"
#include <string_theory/string>

struct PLASMANET_DLL pnSha1Hash
{
    unsigned int fData[5];

    void fromString(const ST::string& src);
    ST::string toString() const;

    void swapBytes();

    static pnSha1Hash Sha0(const void* src, size_t len);
    static pnSha1Hash Sha1(const void* src, size_t len);
};

PLASMANET_DLL pnSha1Hash NCHashPassword(const ST::string& userName,
                                        const ST::string& password);

PLASMANET_DLL pnSha1Hash NCHashLoginInfo(const ST::string& userName,
                                         const ST::string& password,
                                         uint32_t serverChallenge,
                                         uint32_t clientChallenge);

#endif
