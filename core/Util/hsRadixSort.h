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

#ifndef _HSRADIXSORT_H
#define _HSRADIXSORT_H

#include "PlasmaDefs.h"
#include <stdlib.h>

struct PLASMA_DLL hsRadixSortElem
{
    union
    {
        int fSigned;
        unsigned int fUnsigned;
        float fFloat;
    } fKey;

    void* fData;
    hsRadixSortElem* fNext;
};

class PLASMA_DLL hsRadixSort
{
public:
    enum
    {
        kFloat = 0,
        kSigned = 1,
        kUnsigned = 2,
        kReverse = 4
    };

private:
    hsRadixSortElem* fList;
    hsRadixSortElem* fHeads[256];
    hsRadixSortElem* fTails[256];

public:
    hsRadixSort() : fList(), fHeads(), fTails() { }

    hsRadixSortElem* sort(hsRadixSortElem* in, unsigned int flags);

protected:
    void collapse();
    void reverse();
    void unpackSigned();
    void unpackFloat();
};

#endif
