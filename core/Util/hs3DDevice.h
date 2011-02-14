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

#ifndef _HS3DDEVICE_H
#define _HS3DDEVICE_H

#include "Util/hsTArray.hpp"
#include "Util/hsBitVector.h"
#include "Stream/hsStream.h"

class PLASMA_DLL hsG3DDeviceMode {
private:
    unsigned int fFlags;
    unsigned int fWidth;
    unsigned int fHeight;
    unsigned int fDepth;
    hsTArray<unsigned short> fZStencilDepths;
    hsTArray<unsigned char> fFSAATypes;
    bool fCanRenderToCubics;

public:
    hsG3DDeviceMode();
    virtual ~hsG3DDeviceMode();

    void read(hsStream* S, int version=11);
    void write(hsStream* S, int version=11);

    unsigned int getWidth() const { return fWidth; }
    unsigned int getHeight() const { return fHeight; }
    unsigned int getDepth() const { return fDepth; }
    bool getCanRenderToCubics() const { return fCanRenderToCubics; }

    void setWidth(unsigned int width) { fWidth = width; }
    void setHeight(unsigned int height) { fHeight = height; }
    void setDepth(unsigned int depth) { fDepth = depth; }
    void setCanRenderToCubics(bool b) { fCanRenderToCubics = b; }
};

class PLASMA_DLL hsG3DDeviceRecord {
public:
    struct FogKnee {
        float fFogKnee;
        float fFogKneeVal;
    };

    enum {
        kNone, kDiscarded, kInvalid
    };

    enum DeviceType {
        kUnknown,
        kGlide,
        kDirect3D,
        kOpenGL,
        kDirect3D_TnL
    };

private:
    unsigned int fRecordVersion;
    unsigned int fFlags;
    unsigned int fDeviceType;
    plString fDriverDesc;
    plString fDriverName;
    plString fDriverVersion;
    plString fDeviceDesc;
    hsBitVector fCaps;
    unsigned int fLayersAtOnce;
    unsigned int fMemoryBytes;
    hsTArray<hsG3DDeviceMode> fModes;
    float fZBiasRating;
    float fLODBiasRating;
    float fFogExpApproxStart;
    float fFogExp2ApproxStart;
    float fFogEndBias;
    FogKnee fFogKnees[2];
    unsigned char fAASetting;
    unsigned char fMaxAnisotropicSamples;

public:
    hsG3DDeviceRecord();
    virtual ~hsG3DDeviceRecord();

    void read(hsStream* S);
    void write(hsStream* S);

    unsigned int getVersion() const { return fRecordVersion; }
    unsigned int getFlags() const { return fFlags; }
    unsigned int getDeviceType() const { return fDeviceType; }
    const plString& getDriverDesc() const { return fDriverDesc; }
    const plString& getDriverName() const { return fDriverName; }
    const plString& getDriverVersion() const { return fDriverVersion; }
    const plString& getDeviceDesc() const { return fDeviceDesc; }
    const hsBitVector getCaps() { return fCaps; }
    unsigned int getLayersAtOnce() const { return fLayersAtOnce; }
    unsigned int getMemoryBytes() const { return fMemoryBytes; }
    size_t getNumModes() const { return fModes.getSize(); }
    const hsG3DDeviceMode& getMode(size_t idx) { return fModes[idx]; }
    float getZBiasRating() const { return fZBiasRating; }
    float getLODBIasRating() const { return fLODBiasRating; }
    float getFogExpApproxStart() const { return fFogExpApproxStart; }
    float getFogExp2ApproxStart() const { return fFogExp2ApproxStart; }
    float getFogEndBias() const { return fFogEndBias; }

    void setVersion(unsigned int version) { fRecordVersion = version; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setDeviceType(unsigned int type) { fDeviceType = type; }
    void setDriverDesc(const plString& desc) { fDriverDesc = desc; }
    void setDriverName(const plString& name) { fDriverName = name; }
    void setDriverVersion(const plString& version) { fDriverVersion = version; }
    void setDeviceDesc(const plString& desc) { fDeviceDesc = desc; }
};

class PLASMA_DLL hsG3DDeviceModeRecord {
private:
    hsG3DDeviceRecord fRecord;
    hsG3DDeviceMode fMode;
    unsigned short fTextureQuality;

public:
    hsG3DDeviceModeRecord();
    virtual ~hsG3DDeviceModeRecord();

    void read(hsStream* S);
    void write(hsStream* S);
};

#endif
