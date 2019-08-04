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

#ifndef _HSGMATSTATE_H
#define _HSGMATSTATE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

class PLASMA_DLL hsGMatState
{
public:
    enum hsGMatBlendFlags
    {
        kBlendTest = 0x1,
        kBlendAlpha = 0x2,
        kBlendMult = 0x4,
        kBlendAdd = 0x8,
        kBlendAddColorTimesAlpha = 0x10,
        kBlendAntiAlias = 0x20,
        kBlendDetail = 0x40,
        kBlendNoColor = 0x80,
        kBlendMADD = 0x100,
        kBlendDot3 = 0x200,
        kBlendAddSigned = 0x400,
        kBlendAddSigned2X = 0x800,
        kBlendMask = 0xF5E,
        kBlendInvertAlpha = 0x1000,
        kBlendInvertColor = 0x2000,
        kBlendAlphaMult = 0x4000,
        kBlendAlphaAdd = 0x8000,
        kBlendNoVtxAlpha = 0x10000,
        kBlendNoTexColor = 0x20000,
        kBlendNoTexAlpha = 0x40000,
        kBlendInvertVtxAlpha = 0x80000,
        kBlendAlphaAlways = 0x100000,
        kBlendInvertFinalColor = 0x200000,
        kBlendInvertFinalAlpha = 0x400000,
        kBlendEnvBumpNext = 0x800000,
        kBlendSubtract = 0x1000000,
        kBlendRevSubtract = 0x2000000,
        kBlendAlphaTestHigh = 0x4000000
    };

    enum hsGMatClampFlags
    {
        kClampTextureU = 0x1,
        kClampTextureV = 0x2,
        kClampTexture = 0x3
    };

    enum hsGMatShadeFlags
    {
        kShadeSoftShadow = 0x1,
        kShadeNoProjectors = 0x2,
        kShadeEnvironMap = 0x4,
        kShadeVertexShade = 0x20,
        kShadeNoShade = 0x40,
        kShadeBlack = 0x40,
        kShadeSpecular = 0x80,
        kShadeNoFog = 0x100,
        kShadeWhite = 0x200,
        kShadeSpecularAlpha = 0x400,
        kShadeSpecularColor = 0x800,
        kShadeSpecularHighlight = 0x1000,
        kShadeVertColShade = 0x2000,
        kShadeInherit = 0x4000,
        kShadeIgnoreVtxIllum = 0x8000,
        kShadeEmissive = 0x10000,
        kShadeReallyNoFog = 0x20000
    };

    enum hsGMatZFlags
    {
        kZIncLayer = 0x1,
        kZClearZ = 0x4,
        kZNoZRead = 0x8,
        kZNoZWrite = 0x10,
        kZMask = 0x1C,
        kZLODBias = 0x20
    };

    enum hsGMatMiscFlags
    {
        kMiscWireFrame = 0x1,
        kMiscDrawMeshOutlines = 0x2,
        kMiscTwoSided = 0x4,
        kMiscDrawAsSplats = 0x8,
        kMiscAdjustPlane = 0x10,
        kMiscAdjustCylinder = 0x20,
        kMiscAdjustSphere = 0x40,
        kMiscAdjust = 0x70,
        kMiscTroubledLoner = 0x80,
        kMiscBindSkip = 0x100,
        kMiscBindMask = 0x200,
        kMiscBindNext = 0x400,
        kMiscLightMap = 0x800,
        kMiscUseReflectionXform = 0x1000,
        kMiscPerspProjection = 0x2000,
        kMiscOrthoProjection = 0x4000,
        kMiscProjection = 0x6000,
        kMiscRestartPassHere = 0x8000,
        kMiscBumpLayer = 0x10000,
        kMiscBumpDu = 0x20000,
        kMiscBumpDv = 0x40000,
        kMiscBumpDw = 0x80000,
        kMiscBumpChans = 0xE0000,
        kMiscNoShadowAlpha = 0x100000,
        kMiscUseRefractionXform = 0x200000,
        kMiscCam2Screen = 0x400000,
        kAllMiscFlags = 0xFF
    };

public:
    unsigned int fBlendFlags, fClampFlags, fShadeFlags, fZFlags, fMiscFlags;

    hsGMatState(unsigned int blend = 0, unsigned int clamp = 0,
                unsigned int shade = 0, unsigned int Z = 0,
                unsigned int misc = 0);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
