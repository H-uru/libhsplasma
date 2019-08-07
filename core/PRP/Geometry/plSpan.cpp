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

#include "plSpan.h"

uint32_t plSpan::deswizzleGeoFlags(uint32_t flags)
{
    uint32_t props = (flags & plGeometrySpan::kPropRunTimeLight) << 5;

    if (flags & plGeometrySpan::kPropNoShadowCast)
        props |= kPropNoShadowCast;
    if (flags & plGeometrySpan::kPropNoShadow)
        props |= kPropNoShadow;
    if (flags & plGeometrySpan::kPropForceShadow)
        props |= kPropForceShadow;
    if (flags & plGeometrySpan::kPropReverseSort)
        props |= kPropReverseSort;
    if (flags & plGeometrySpan::kPartialSort)
        props |= kPartialSort;
    if (flags & plGeometrySpan::kLiteVtxPreshaded)
        props |= kLiteVtxPreshaded;
    if (flags & plGeometrySpan::kLiteVtxNonPreshaded)
        props |= kLiteVtxNonPreshaded;
    if (flags & plGeometrySpan::kWaterHeight)
        props |= kWaterHeight;
    if (flags & plGeometrySpan::kVisLOS)
        props |= kVisLOS;

    return props;
}

uint32_t plSpan::swizzleGeoFlags(uint32_t flags)
{
    uint32_t props = (flags & kPropRunTimeLight) >> 5;

    if (flags & kPropNoShadowCast)
        props |= plGeometrySpan::kPropNoShadowCast;
    if (flags & kPropNoShadow)
        props |= plGeometrySpan::kPropNoShadow;
    if (flags & kPropForceShadow)
        props |= plGeometrySpan::kPropForceShadow;
    if (flags & kPropReverseSort)
        props |= plGeometrySpan::kPropReverseSort;
    if (flags & kPartialSort)
        props |= plGeometrySpan::kPartialSort;
    if (flags & kLiteVtxPreshaded)
        props |= plGeometrySpan::kLiteVtxPreshaded;
    if (flags & kLiteVtxNonPreshaded)
        props |= plGeometrySpan::kLiteVtxNonPreshaded;
    if (flags & kWaterHeight)
        props |= plGeometrySpan::kWaterHeight;
    if (flags & kVisLOS)
        props |= plGeometrySpan::kVisLOS;

    return props;
}

void plSpan::read(hsStream* S)
{
    fSubType = S->readInt();
    fMaterialIdx = S->readInt();
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fProps = S->readInt();
    fLocalBounds.read(S);
    fWorldBounds.read(S);
    fNumMatrices = S->readInt();
    fBaseMatrix = S->readInt();
    fLocalUVWChans = S->readShort();
    fMaxBoneIdx = S->readShort();
    fPenBoneIdx = S->readShort();
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
    if (fProps & kWaterHeight)
        fWaterHeight = S->readFloat();
}

void plSpan::write(hsStream* S)
{
    S->writeInt(fSubType);
    S->writeInt(fMaterialIdx);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    S->writeInt(fProps);
    fLocalBounds.write(S);
    fWorldBounds.write(S);
    S->writeInt(fNumMatrices);
    S->writeInt(fBaseMatrix);
    S->writeShort(fLocalUVWChans);
    S->writeShort(fMaxBoneIdx);
    S->writeShort(fPenBoneIdx);
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
    if (fProps & kWaterHeight)
        S->writeFloat(fWaterHeight);
}

void plSpan::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag(ClassName());
    IPrcWrite(prc);
    prc->closeTag();
}

void plSpan::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        IPrcParse(child);
        child = child->getNextSibling();
    }
}

void plSpan::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("SpanInfo");
      prc->writeParam("SubType", fSubType);
      prc->writeParam("Material", fMaterialIdx);
      prc->writeParamHex("Properties", fProps);
    prc->endTag(true);
    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalBounds");
      fLocalBounds.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldBounds");
      fWorldBounds.prcWrite(prc);
    prc->closeTag();
    prc->startTag("MatrixInfo");
      prc->writeParam("NumMatrices", fNumMatrices);
      prc->writeParam("BaseMatrix", fBaseMatrix);
      prc->writeParam("UVWChans", fLocalUVWChans);
    prc->endTag(true);
    prc->startTag("BoneIndices");
      prc->writeParam("Max", fMaxBoneIdx);
      prc->writeParam("Pen", fPenBoneIdx);
    prc->endTag(true);
    prc->startTag("Dists");
      prc->writeParam("Min", fMinDist);
      prc->writeParam("Max", fMaxDist);
    prc->endTag(true);
    if (fProps & kWaterHeight) {
        prc->startTag("WaterHeight");
        prc->writeParam("value", fWaterHeight);
        prc->endTag(true);
    }
}

void plSpan::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "SpanInfo") {
        fSubType = tag->getParam("SubType", "0").to_uint();
        fMaterialIdx = tag->getParam("Material", "0").to_uint();
        fProps = tag->getParam("Properties", "0").to_uint();
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "MatrixInfo") {
        fNumMatrices = tag->getParam("NumMatrices", "0").to_uint();
        fBaseMatrix = tag->getParam("BaseMatrix", "0").to_uint();
        fLocalUVWChans = tag->getParam("UVWChans", "0").to_uint();
    } else if (tag->getName() == "BoneIndices") {
        fMaxBoneIdx = tag->getParam("Max", "0").to_uint();
        fPenBoneIdx = tag->getParam("Pen", "0").to_uint();
    } else if (tag->getName() == "Dists") {
        fMinDist = tag->getParam("Min", "0").to_float();
        fMaxDist = tag->getParam("Max", "0").to_float();
    } else if (tag->getName() == "WaterHeight") {
        fWaterHeight = tag->getParam("value", "0").to_float();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}
