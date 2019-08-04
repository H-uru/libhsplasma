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

#include "Util/hsBitVector.h"
#include "Stream/hsStream.h"

class PLASMA_DLL hsG3DDeviceMode
{
private:
    unsigned int fFlags;
    unsigned int fWidth;
    unsigned int fHeight;
    unsigned int fDepth;
    std::vector<unsigned short> fZStencilDepths;
    std::vector<unsigned char> fFSAATypes;
    bool fCanRenderToCubics;

public:
    hsG3DDeviceMode()
        : fFlags(), fWidth(), fHeight(), fDepth(), fCanRenderToCubics() { }
    virtual ~hsG3DDeviceMode() { }

    void read(hsStream* S, int version=11);
    void write(hsStream* S, int version=11);

    unsigned int getFlags() const { return fFlags; }
    unsigned int getWidth() const { return fWidth; }
    unsigned int getHeight() const { return fHeight; }
    unsigned int getDepth() const { return fDepth; }
    std::vector<unsigned short>& getZStencilDepths() { return fZStencilDepths; }
    const std::vector<unsigned short>& getZStencilDepths() const { return fZStencilDepths; }
    std::vector<unsigned char>& getFSAATypes() { return fFSAATypes; }
    const std::vector<unsigned char>& getFSAATypes() const { return fFSAATypes; }
    bool getCanRenderToCubics() const { return fCanRenderToCubics; }

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setWidth(unsigned int width) { fWidth = width; }
    void setHeight(unsigned int height) { fHeight = height; }
    void setDepth(unsigned int depth) { fDepth = depth; }
    void setCanRenderToCubics(bool b) { fCanRenderToCubics = b; }
};

class PLASMA_DLL hsG3DDeviceRecord
{
public:
    struct FogKnee
    {
        float fFogKnee;
        float fFogKneeVal;
    };

    enum
    {
        kNone, kDiscarded, kInvalid
    };

    enum DeviceType
    {
        kUnknown,
        kGlide,
        kDirect3D,
        kOpenGL,
        kDirect3D_TnL
    };

    enum { kMaxFogKnees = 2 };

private:
    unsigned int fRecordVersion;
    unsigned int fFlags;
    unsigned int fDeviceType;
    ST::string fDriverDesc;
    ST::string fDriverName;
    ST::string fDriverVersion;
    ST::string fDeviceDesc;
    hsBitVector fCaps;
    unsigned int fLayersAtOnce;
    unsigned int fMemoryBytes;
    std::vector<hsG3DDeviceMode> fModes;
    float fZBiasRating;
    float fLODBiasRating;
    float fFogExpApproxStart;
    float fFogExp2ApproxStart;
    float fFogEndBias;
    FogKnee fFogKnees[kMaxFogKnees];
    unsigned char fAASetting;
    unsigned char fMaxAnisotropicSamples;

public:
    hsG3DDeviceRecord()
        : fRecordVersion(11), fFlags(kInvalid), fDeviceType(), fLayersAtOnce(),
          fMemoryBytes(), fZBiasRating(), fLODBiasRating(), fFogExpApproxStart(),
          fFogExp2ApproxStart(), fFogEndBias(), fAASetting(),
          fMaxAnisotropicSamples() { }
    virtual ~hsG3DDeviceRecord() { }

    void read(hsStream* S);
    void write(hsStream* S);

    unsigned int getVersion() const { return fRecordVersion; }
    unsigned int getFlags() const { return fFlags; }
    unsigned int getDeviceType() const { return fDeviceType; }
    const ST::string& getDriverDesc() const { return fDriverDesc; }
    const ST::string& getDriverName() const { return fDriverName; }
    const ST::string& getDriverVersion() const { return fDriverVersion; }
    const ST::string& getDeviceDesc() const { return fDeviceDesc; }
    hsBitVector& getCaps() { return fCaps; }
    const hsBitVector& getCaps() const { return fCaps; }
    unsigned int getLayersAtOnce() const { return fLayersAtOnce; }
    unsigned int getMemoryBytes() const { return fMemoryBytes; }
    std::vector<hsG3DDeviceMode>& getModes() { return fModes; }
    const std::vector<hsG3DDeviceMode>& getModes() const { return fModes; }
    float getZBiasRating() const { return fZBiasRating; }
    float getLODBiasRating() const { return fLODBiasRating; }
    float getFogExpApproxStart() const { return fFogExpApproxStart; }
    float getFogExp2ApproxStart() const { return fFogExp2ApproxStart; }
    float getFogEndBias() const { return fFogEndBias; }
    const FogKnee* getFogKnees() const { return fFogKnees; }
    FogKnee* getFogKnees() { return fFogKnees; }
    unsigned char getAASetting() const { return fAASetting; }
    unsigned char getMaxAnisotropicSamples() const { return fMaxAnisotropicSamples; }

    void setVersion(unsigned int version) { fRecordVersion = version; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setDeviceType(unsigned int type) { fDeviceType = type; }
    void setDriverDesc(const ST::string& desc) { fDriverDesc = desc; }
    void setDriverName(const ST::string& name) { fDriverName = name; }
    void setDriverVersion(const ST::string& version) { fDriverVersion = version; }
    void setDeviceDesc(const ST::string& desc) { fDeviceDesc = desc; }
    void setLayersAtOnce(unsigned int layers) { fLayersAtOnce = layers; }
    void setMemoryBytes(unsigned int membytes) { fMemoryBytes = membytes; }
    void setZBiasRating(float bias) { fZBiasRating = bias; }
    void setLODBiasRating(float bias) { fLODBiasRating = bias; }
    void setFogExpApproxStart(float start) { fFogExpApproxStart = start; }
    void setFogExp2ApproxStart(float start) { fFogExp2ApproxStart = start; }
    void setFogEndBias(float bias) { fFogEndBias = bias; }
    void setAASetting(unsigned char aa) { fAASetting = aa; }
    void setMaxAnisotropicSamples(unsigned char aniso) { fMaxAnisotropicSamples = aniso; }
};

class PLASMA_DLL hsG3DDeviceModeRecord
{
private:
    hsG3DDeviceRecord fRecord;
    hsG3DDeviceMode fMode;
    unsigned short fTextureQuality;

public:
    hsG3DDeviceModeRecord() : fTextureQuality() { }
    virtual ~hsG3DDeviceModeRecord() { }

    void read(hsStream* S);
    void write(hsStream* S);

    hsG3DDeviceRecord& getRecord() { return fRecord; }
    const hsG3DDeviceRecord& getRecord() const { return fRecord; }
    hsG3DDeviceMode& getMode() { return fMode; }
    const hsG3DDeviceMode& getMode() const { return fMode; }
    unsigned short getTextureQuality() const { return fTextureQuality; }

    void setTextureQuality(unsigned short quality) { fTextureQuality = quality; }
};

#endif
