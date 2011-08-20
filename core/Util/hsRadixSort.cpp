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

#include "hsRadixSort.h"

hsRadixSort::hsRadixSort() {
    for (int i = 0; i < 256; i++) {
        fHeads[i] = NULL;
        fTails[i] = NULL;
    }
}

hsRadixSortElem* hsRadixSort::sort(hsRadixSortElem* in, unsigned int flags)
{
    hsRadixSortElem* res = in;

    if (in && in->fNext) {
        fList = in;

        unsigned char key;
        hsRadixSortElem* it;

        for (int i = 0; i < 4; i++) {
            it = fList->fNext;
            while (it != NULL) {
                key = (fList->fKey.fUnsigned >> (8*i)) & 0xFF;
                if (fTails[key])
                    fTails[key]->fNext = fList;
                else
                    fHeads[key] = fList;

                fList->fNext = NULL;
                fTails[key] = fList;
                fList = it;
                it = it->fNext;
            }

            key = (fList->fKey.fUnsigned >> (8*i)) & 0xFF;
            if (fTails[key])
                fTails[key]->fNext = fList;
            else
                fHeads[key] = fList;

            fList->fNext = NULL;
            fTails[key] = fList;
            collapse();
        }

        if (flags & kSigned) {
            unpackSigned();
        } else if (flags & kFloat) {
            unpackFloat();
        }

        if (flags & kReverse) {
            reverse();
        }

        res = fList;
    }

    return res;
}

void hsRadixSort::collapse() {
    hsRadixSortElem* head = NULL;
    hsRadixSortElem* tail = NULL;

    for (int i = 0; i < 256; i++) {
        if (fHeads[i]) {
            if (head) {
                tail->fNext = fHeads[i];
            } else {
                head = fHeads[i];
            }

            tail = fTails[i];
        }

        fTails[i] = NULL;
        fHeads[i] = NULL;
    }

    fList = head;
}

void hsRadixSort::reverse() {
    if (fList && fList->fNext) {
        hsRadixSortElem* next = fList->fNext;

        fList->fNext = NULL;
        hsRadixSortElem* nnext = NULL;
        while ((nnext = next->fNext) != NULL) {
            next->fNext = fList;
            fList = next;
            next = nnext;
        }
    }
}

void hsRadixSort::unpackSigned() {
    hsRadixSortElem* head = NULL;
    hsRadixSortElem* tail = NULL;

    for (int i = 0; i < 128; i++) {
        if (fHeads[i+128]) {
            if (head) {
                tail->fNext = fHeads[i+128];
            } else {
                head = fHeads[i+128];
            }

            tail = fTails[i+128];
        }

        fTails[i+128] = NULL;
        fHeads[i+128] = NULL;
    }

    for (int i = 0; i < 128; i++) {
        if (fHeads[i]) {
            if (head) {
                tail->fNext = fHeads[i];
            } else {
                head = fHeads[i];
            }

            tail = fTails[i];
        }

        fTails[i] = NULL;
        fHeads[i] = NULL;
    }

    fList = head;
}

void hsRadixSort::unpackFloat() {
    hsRadixSortElem* head = NULL;
    hsRadixSortElem* tail = NULL;

    for (int i = 0; i < 128; i++) {
        if (fHeads[i+128]) {
            if (head) {
                tail->fNext = fHeads[i+128];
            } else {
                head = fHeads[i+128];
            }

            tail = fTails[i+128];
        }

        fTails[i+128] = NULL;
        fHeads[i+128] = NULL;
    }

    fList = head;
    reverse();
    tail = head;
    head = fList;

    for (int i = 0; i < 128; i++) {
        if (fHeads[i]) {
            if (head) {
                tail->fNext = fHeads[i];
            } else {
                head = fHeads[i];
            }

            tail = fTails[i];
        }

        fTails[i] = NULL;
        fHeads[i] = NULL;
    }

    fList = head;
}
