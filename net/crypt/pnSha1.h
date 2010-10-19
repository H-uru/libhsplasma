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

#include "Util/plString.h"

DllStruct pnSha1Hash {
    unsigned int fData[5];

    void fromString(const plString& src);
    plString toString() const;

    void swapBytes();

    static pnSha1Hash Sha0(const void* src, size_t len);
    static pnSha1Hash Sha1(const void* src, size_t len);
};

DllExport pnSha1Hash NCHashPassword(const plString& userName,
                                    const plString& password);

DllExport pnSha1Hash NCHashLoginInfo(const plString& userName,
                                     const plString& password,
                                     hsUint32 serverChallenge,
                                     hsUint32 clientChallenge);

#endif
