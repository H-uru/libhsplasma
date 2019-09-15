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

#include "plParticleEmitter.h"

plParticleEmitter::~plParticleEmitter()
{
    delete fGenerator;
}

void plParticleEmitter::read(hsStream* S, plResManager* mgr)
{
    setGenerator(mgr->ReadCreatableC<plParticleGenerator>(S));

    fSpanIndex = S->readInt();
    fMaxParticles = S->readInt();
    fMiscFlags = S->readInt();
    fColor.read(S);
}

void plParticleEmitter::write(hsStream* S, plResManager* mgr)
{
    mgr->WriteCreatable(S, fGenerator);

    S->writeInt(fSpanIndex);
    S->writeInt(fMaxParticles);
    S->writeInt(fMiscFlags);
    fColor.write(S);
}

void plParticleEmitter::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Generator");
    fGenerator->prcWrite(prc);
    prc->closeTag();

    prc->startTag("EmitterParams");
    prc->writeParam("SpanIndex", fSpanIndex);
    prc->writeParam("MaxParticles", fMaxParticles);
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);

    prc->writeSimpleTag("Color");
    fColor.prcWrite(prc);
    prc->closeTag();
}

void plParticleEmitter::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Generator") {
        if (tag->hasChildren())
            setGenerator(mgr->prcParseCreatableC<plParticleGenerator>(tag->getFirstChild()));
    } else if (tag->getName() == "EmitterParams") {
        fSpanIndex = tag->getParam("SpanIndex", "0").to_uint();
        fMaxParticles = tag->getParam("MaxParticles", "0").to_uint();
        fMiscFlags = tag->getParam("MiscFlags", "0").to_uint();
    } else if (tag->getName() == "Color") {
        if (tag->hasChildren())
            fColor.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plParticleEmitter::setGenerator(plParticleGenerator* generator)
{
    delete fGenerator;
    fGenerator = generator;
}
