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

#include "hsBounds.h"

/* hsBounds */
void hsBounds::read(hsStream* S)
{
    fType = S->readInt();
}

void hsBounds::write(hsStream* S)
{
    S->writeInt(fType);
}

void hsBounds::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag(ClassName());
    IPrcWrite(prc);
    prc->closeTag();
}

void hsBounds::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("BoundsInfo");
    prc->writeParam("Type", fType);
    prc->endTag(true);
}

void hsBounds::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        IPrcParse(child);
        child = child->getNextSibling();
    }
}

void hsBounds::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "BoundsInfo") {
        fType = tag->getParam("Type", "0").to_int();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}


/* hsBounds3 */
void hsBounds3::init(const hsVector3& right)
{
    fMins = right;
    fMaxs = right;
    fCenter = right;
}

hsBounds3 hsBounds3::operator+(const hsBounds3& right) const
{
    hsBounds3 result = *this;
    result += right;
    return result;
}

hsBounds3& hsBounds3::operator+=(const hsBounds3& right)
{
    if (right.fMins.X < fMins.X)
        fMins.X = right.fMins.X;
    if (right.fMaxs.X > fMaxs.X)
        fMaxs.X = right.fMaxs.X;
    if (right.fMins.Y < fMins.Y)
        fMins.Y = right.fMins.Y;
    if (right.fMaxs.Y > fMaxs.Y)
        fMaxs.Y = right.fMaxs.Y;
    if (right.fMins.Z < fMins.Z)
        fMins.Z = right.fMins.Z;
    if (right.fMaxs.Z > fMaxs.Z)
        fMaxs.Z = right.fMaxs.Z;
    return *this;
}

hsBounds3& hsBounds3::operator+=(const hsVector3& point)
{
    if (point.X < fMins.X)
        fMins.X = point.X;
    if (point.X > fMaxs.X)
        fMaxs.X = point.X;
    if (point.Y < fMins.Y)
        fMins.Y = point.Y;
    if (point.Y > fMaxs.Y)
        fMaxs.Y = point.Y;
    if (point.Z < fMins.Z)
        fMins.Z = point.Z;
    if (point.Z > fMaxs.Z)
        fMaxs.Z = point.Z;
    return *this;
}

void hsBounds3::read(hsStream* S)
{
    hsBounds::read(S);
    fMins.read(S);
    fMaxs.read(S);
}

void hsBounds3::write(hsStream* S)
{
    hsBounds::write(S);
    fMins.write(S);
    fMaxs.write(S);
}

void hsBounds3::IPrcWrite(pfPrcHelper* prc)
{
    hsBounds::IPrcWrite(prc);
    prc->writeSimpleTag("Mins");
    fMins.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Maxs");
    fMaxs.prcWrite(prc);
    prc->closeTag();
}

void hsBounds3::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "Mins") {
        if (tag->hasChildren())
            fMins.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Maxs") {
        if (tag->hasChildren())
            fMaxs.prcParse(tag->getFirstChild());
    } else {
        hsBounds::IPrcParse(tag);
    }
}

hsBounds3Corners hsBounds3::getCorners() const
{
    hsBounds3Corners corners;
    for (size_t i = 0; i < corners.max_size(); ++i) {
        corners[i].X = (i & 0x01) ? fMins.X : fMaxs.X;
        corners[i].Y = (i & 0x02) ? fMins.Y : fMaxs.Y;
        corners[i].Z = (i & 0x04) ? fMins.Z : fMaxs.Z;
    }
    return corners;
}

const hsVector3& hsBounds3::updateCenter()
{
    fCenter.X = (fMins.X + fMaxs.X) / 2.0f;
    fCenter.Y = (fMins.Y + fMaxs.Y) / 2.0f;
    fCenter.Z = (fMins.Z + fMaxs.Z) / 2.0f;
    return fCenter;
}


/* hsBounds3Ext */
hsBounds3Ext hsBounds3Ext::operator+(const hsBounds3Ext& right) const
{
    hsBounds3Ext result = *this;
    result += right;
    return result;
}

void hsBounds3Ext::read(hsStream* S)
{
    fExtFlags = S->readInt();
    hsBounds3::read(S);
    if (!(fExtFlags & kAxisAligned)) {
        fCorner.read(S);
        for (int i=0; i<3; i++) {
            fAxes[i].read(S);
            fDists[i].X = S->readFloat();
            fDists[i].Y = S->readFloat();
        }
    }
}

void hsBounds3Ext::write(hsStream* S)
{
    S->writeInt(fExtFlags);
    hsBounds3::write(S);
    if (!(fExtFlags & kAxisAligned)) {
        fCorner.write(S);
        for (int i=0; i<3; i++) {
            fAxes[i].write(S);
            S->writeFloat(fDists[i].X);
            S->writeFloat(fDists[i].Y);
        }
    }
}

void hsBounds3Ext::IPrcWrite(pfPrcHelper* prc)
{
    hsBounds3::IPrcWrite(prc);
    prc->startTag("ExtFlags");
    prc->writeParamHex("value", fExtFlags);
    prc->endTag(true);
    if (!(fExtFlags & kAxisAligned)) {
        prc->writeSimpleTag("Corner");
        fCorner.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Axes");
        for (int i=0; i<3; i++) {
            prc->startTag("Axis");
            prc->writeParam("DistX", fDists[i].X);
            prc->writeParam("DistY", fDists[i].Y);
            prc->endTag();
            fAxes[i].prcWrite(prc);
            prc->closeTag();
        }
        prc->closeTag();
    }
}

void hsBounds3Ext::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "ExtFlags") {
        fExtFlags = tag->getParam("value", "0").to_uint();
    } else if (tag->getName() == "Corner") {
        if (tag->hasChildren())
            fCorner.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Axes") {
        const pfPrcTag* child = tag->getFirstChild();
        for (int i=0; i<3 && child != nullptr; i++) {
            if (child->getName() != "Axis")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            fDists[i].X = child->getParam("DistX", "0").to_float();
            fDists[i].Y = child->getParam("DistY", "0").to_float();
            if (child->hasChildren())
                fAxes[i].prcParse(child->getFirstChild());

            child = child->getNextSibling();
        }
    } else {
        hsBounds3::IPrcParse(tag);
    }
}

hsBounds3Corners hsBounds3Ext::getCorners() const
{
    if (fExtFlags & kAxisAligned) {
        return hsBounds3::getCorners();
    } else {
        hsBounds3Corners corners;
        for (size_t i = 0; i < corners.max_size(); ++i) {
            corners[i] = fCorner;
            if (!(i & 0x01) && !(fExtFlags & kAxisZeroZero))
                corners[i] += fAxes[0];
            if (!(i & 0x02) && !(fExtFlags & kAxisOneZero))
                corners[i] += fAxes[1];
            if (!(i & 0x04) && !(fExtFlags & kAxisTwoZero))
                corners[i] += fAxes[2];
        }
        return corners;
    }
}

void hsBounds3Ext::unalign()
{
    fCorner = fMins;
    fExtFlags = 0;

    float x = fMaxs.X - fMins.X;
    if (x < 0.00001) {
        fExtFlags |= kAxisZeroZero;
        x = 1.0;
    }
    fAxes[0] = hsVector3(x, 0.0, 0.0);

    float y = fMaxs.Y - fMins.Y;
    if (y < 0.00001) {
        fExtFlags |= kAxisOneZero;
        y = 1.0;
    }
    fAxes[1] = hsVector3(0.0, y, 0.0);

    float z = fMaxs.Z - fMins.Z;
    if (z < 0.00001) {
        fExtFlags |= kAxisTwoZero;
        z = 1.0;
    }
    fAxes[2] = hsVector3(0.0, 0.0, z);
}


/* hsBoundsOriented */
hsBoundsOriented::hsBoundsOriented(const hsBoundsOriented& src)
    : hsBounds(src), fCenterValid(src.fCenterValid),
      fCenter(src.fCenter), fNumPlanes(src.fNumPlanes)
{
    fPlanes = new hsPlane3[fNumPlanes];
    for (size_t i=0; i<fNumPlanes; i++)
        fPlanes[i] = src.fPlanes[i];
}

hsBoundsOriented::~hsBoundsOriented()
{
    delete[] fPlanes;
}

void hsBoundsOriented::read(hsStream* S)
{
    hsBounds::read(S);
    fCenter.read(S);
    fCenterValid = S->readInt();
    fNumPlanes = S->readInt();
    delete[] fPlanes;
    fPlanes = new hsPlane3[fNumPlanes];
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].read(S);
}

void hsBoundsOriented::write(hsStream* S)
{
    hsBounds::write(S);
    fCenter.write(S);
    S->writeInt(fCenterValid);
    S->writeInt(fNumPlanes);
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].write(S);
}

void hsBoundsOriented::IPrcWrite(pfPrcHelper* prc)
{
    hsBounds::IPrcWrite(prc);
    prc->startTag("Center");
    prc->writeParam("IsValid", fCenterValid);
    prc->endTag();
      fCenter.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Planes");
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].prcWrite(prc);
    prc->closeTag();
}

void hsBoundsOriented::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "Center") {
        fCenterValid = tag->getParam("IsValid", "false").to_bool();
        if (tag->hasChildren())
            fCenter.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Planes") {
        delete[] fPlanes;
        fNumPlanes = tag->countChildren();
        fPlanes = new hsPlane3[fNumPlanes];
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumPlanes; i++) {
            fPlanes[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        hsBounds::IPrcParse(tag);
    }
}

void hsBoundsOriented::setPlanes(unsigned int numPlanes, const hsPlane3* planes)
{
    delete[] fPlanes;
    fNumPlanes = numPlanes;
    if (fNumPlanes > 0) {
        fPlanes = new hsPlane3[fNumPlanes];
        for (size_t i=0; i<fNumPlanes; i++)
            fPlanes[i] = planes[i];
    } else {
        fPlanes = nullptr;
    }
}
