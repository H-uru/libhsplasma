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

#ifndef _PLLAYERINTERFACE_H
#define _PLLAYERINTERFACE_H

#include "PRP/Object/plSynchedObject.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "plBitmap.h"
#include "hsGMatState.h"

class PLASMA_DLL plLayerInterface : public plSynchedObject
{
    CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

public:
    enum plLayerDirtyBits
    {
        kTransform = 0x1,
        kPreshadeColor = 0x2,
        kAmbientColor = 0x4,
        kOpacity = 0x8,
        kTexture = 0x10,
        kState = 0x20,
        kUVWSrc = 0x40,
        kLODBias = 0x80,
        kSpecularColor = 0x100,
        kSpecularPower = 0x200,
        kRuntimeColor = 0x400,
        kVertexShader = 0x800,
        kPixelShader = 0x1000,
        kBumpEnvXfm = 0x2000,
        kAllDirty = 0xFFFFFFFF
    };

    enum plUVWSrcModifiers
    {
        kUVWPassThru = 0,
        kUVWIdxMask = 0xFFFF,
        kUVWNormal = 0x10000,
        kUVWPosition = 0x20000,
        kUVWReflect = 0x30000
    };

protected:
    plKey fUnderLay;
    hsMatrix44 fTransform;
    hsColorRGBA fPreshade, fRuntime, fAmbient, fSpecular;
    float fOpacity;
    unsigned int fUVWSrc;
    float fLODBias;
    float fSpecularPower;
    plKey fTexture, fVertexShader, fPixelShader;
    hsMatrix44 fBumpEnvXfm;
    hsGMatState fState;

public:
    plLayerInterface()
        : fOpacity(1.0f), fUVWSrc(), fLODBias(), fSpecularPower() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getUnderLay() const { return fUnderLay; }
    plKey getTexture() const { return fTexture; }
    plKey getVertexShader() const { return fVertexShader; }
    plKey getPixelShader() const { return fPixelShader; }
    void setUnderLay(plKey layer) { fUnderLay = std::move(layer); }
    void setTexture(plKey tex) { fTexture = std::move(tex); }
    void setVertexShader(plKey shader) { fVertexShader = std::move(shader); }
    void setPixelShader(plKey shader) { fPixelShader = std::move(shader); }

    hsMatrix44 getTransform() const { return fTransform; }
    hsMatrix44 getBumpEnvTransform() const { return fBumpEnvXfm; }
    void setTransform(const hsMatrix44& xform) { fTransform = xform; }
    void setBumpEnvTransform(const hsMatrix44& xform) { fBumpEnvXfm =  xform; }

    hsColorRGBA getPreshade() const { return fPreshade; }
    hsColorRGBA getRuntime() const { return fRuntime; }
    hsColorRGBA getAmbient() const { return fAmbient; }
    hsColorRGBA getSpecular() const { return fSpecular; }
    void setPreshade(const hsColorRGBA& color) { fPreshade = color; }
    void setRuntime(const hsColorRGBA& color) { fRuntime = color; }
    void setAmbient(const hsColorRGBA& color) { fAmbient = color; }
    void setSpecular(const hsColorRGBA& color) { fSpecular = color; }

    float getOpacity() const { return fOpacity; }
    unsigned int getUVWSrc() const { return fUVWSrc; }
    float getLODBias() const { return fLODBias; }
    float getSpecularPower() const { return fSpecularPower; }
    void setOpacity(float opac) { fOpacity = opac; }
    void setUVWSrc(unsigned int src) { fUVWSrc = src; }
    void setLODBias(float bias) { fLODBias = bias; }
    void setSpecularPower(float power) { fSpecularPower = power; }

    const hsGMatState& getState() const { return fState; }
    hsGMatState& getState() { return fState; }
};

#endif
