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

#ifndef _PLCUBICENVIRONMAP_H
#define _PLCUBICENVIRONMAP_H

#include "plMipmap.h"

class PLASMA_DLL plCubicEnvironmap : public plBitmap
{
    CREATABLE(plCubicEnvironmap, kCubicEnvironmap, plBitmap)

public:
    enum Faces
    {
        kLeftFace, kRightFace, kFrontFace, kBackFace,
        kTopFace, kBottomFace, kNumFaces
    };

    static const char* kFaceNames[kNumFaces];

protected:
    plMipmap fFaces[kNumFaces];

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plMipmap* getFace(size_t idx) { return &fFaces[idx]; }
    void setFace(size_t idx, plMipmap* newMap) { fFaces[idx].CopyFrom(newMap); }
};

#endif
