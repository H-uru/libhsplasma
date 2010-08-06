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

#ifndef _PLLAYERMOVIE_H
#define _PLLAYERMOVIE_H

#include "plLayerAnimation.h"

DllClass plLayerMovie : public virtual plLayerAnimation {
    CREATABLE(plLayerMovie, kLayerMovie, plLayerAnimation)

protected:
    plString fMovieName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getMovieName() const { return fMovieName; }
    void setMovieName(const plString& name) { fMovieName = name; }
};


DllClass plLayerAVI : public virtual plLayerMovie {
    CREATABLE(plLayerAVI, kLayerAVI, plLayerMovie)
};


DllClass plLayerBink : public virtual plLayerMovie {
    CREATABLE(plLayerBink, kLayerBink, plLayerMovie)
};

#endif
