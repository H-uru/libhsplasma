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

#include "plATCEaseCurves.h"

/* plATCEaseCurve */
void plATCEaseCurve::read(hsStream* S, plResManager* )
{
    fMinLength = S->readFloat();
    fMaxLength = S->readFloat();
    fLength = S->readFloat();
    fStartSpeed = S->readFloat();
    fSpeed = S->readFloat();
    fBeginWorldTime = S->readDouble();
}

void plATCEaseCurve::write(hsStream* S, plResManager* )
{
    S->writeFloat(fMinLength);
    S->writeFloat(fMaxLength);
    S->writeFloat(fLength);
    S->writeFloat(fStartSpeed);
    S->writeFloat(fSpeed);
    S->writeDouble(fBeginWorldTime);
}

void plATCEaseCurve::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Lengths");
    prc->writeParam("Min", fMinLength);
    prc->writeParam("Max", fMaxLength);
    prc->writeParam("Norm", fLength);
    prc->endTag(true);

    prc->startTag("Timing");
    prc->writeParam("StartSpeed", fStartSpeed);
    prc->writeParam("Speed", fSpeed);
    prc->writeParam("BeginWorldTime", fBeginWorldTime);
    prc->endTag(true);
}

void plATCEaseCurve::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Lengths") {
        fMinLength = tag->getParam("Min", "0").to_float();
        fMaxLength = tag->getParam("Max", "0").to_float();
        fLength = tag->getParam("Norm", "0").to_float();
    } else if (tag->getName() == "Timing") {
        fStartSpeed = tag->getParam("StartSpeed", "0").to_float();
        fSpeed = tag->getParam("Speed", "0").to_float();
        fBeginWorldTime = tag->getParam("BeginWorldTime", "0").to_float();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plSplineEaseCurve */
void plSplineEaseCurve::read(hsStream* S, plResManager* mgr)
{
    plATCEaseCurve::read(S, mgr);

    fCoef[0] = S->readFloat();
    fCoef[1] = S->readFloat();
    fCoef[2] = S->readFloat();
    fCoef[3] = S->readFloat();
}

void plSplineEaseCurve::write(hsStream* S, plResManager* mgr)
{
    plATCEaseCurve::write(S, mgr);

    S->writeFloat(fCoef[0]);
    S->writeFloat(fCoef[1]);
    S->writeFloat(fCoef[2]);
    S->writeFloat(fCoef[3]);
}

void plSplineEaseCurve::IPrcWrite(pfPrcHelper* prc)
{
    plATCEaseCurve::IPrcWrite(prc);

    prc->writeTagNoBreak("SplineCoefficients");
    prc->directWrite(ST::format("{f} {f} {f} {f}",
                     fCoef[0], fCoef[1], fCoef[2], fCoef[3]));
    prc->closeTagNoBreak();
}

void plSplineEaseCurve::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SplineCoefficients") {
        std::list<ST::string> coefList = tag->getContents();
        if (coefList.size() != 4)
            throw pfPrcParseException(__FILE__, __LINE__, "plSplineEaseCurve expects exactly 4 coefficients");
        size_t i = 0;
        for (auto coef = coefList.begin(); coef != coefList.end(); ++coef)
            fCoef[i++] = coef->to_float();
    } else {
        plATCEaseCurve::IPrcParse(tag, mgr);
    }
}
