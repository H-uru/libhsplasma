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

#ifndef _PLDIRECTIONALLIGHTINFO_H
#define _PLDIRECTIONALLIGHTINFO_H

#include "plLightInfo.h"

class PLASMA_DLL plDirectionalLightInfo : public virtual plLightInfo {
    CREATABLE(plDirectionalLightInfo, kDirectionalLightInfo, plLightInfo)
};


class PLASMA_DLL plLimitedDirLightInfo : public virtual plDirectionalLightInfo {
    CREATABLE(plLimitedDirLightInfo, kLimitedDirLightInfo,
              plDirectionalLightInfo)

protected:
    float fWidth, fHeight, fDepth;

public:
    plLimitedDirLightInfo() : fWidth(0.0f), fHeight(0.0f), fDepth(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getWidth() const { return fWidth; }
    float getHeight() const { return fHeight; }
    float getDepth() const { return fDepth; }

    void setWidth(float width) { fWidth = width; }
    void setHeight(float height) { fHeight = height; }
    void setDepth(float depth) { fDepth = depth; }
};

#endif
