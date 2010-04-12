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

#include "plLayerMovie.h"

/* plLayerMovie */
void plLayerMovie::read(hsStream* S, plResManager* mgr) {
    plLayerAnimation::read(S, mgr);

    int len = S->readInt();
    fMovieName = S->readStr(len);
}

void plLayerMovie::write(hsStream* S, plResManager* mgr) {
    plLayerAnimation::write(S, mgr);

    S->writeInt(fMovieName.len());
    S->writeStr(fMovieName);
}

void plLayerMovie::IPrcWrite(pfPrcHelper* prc) {
    plLayerAnimation::IPrcWrite(prc);

    prc->startTag("Movie");
    prc->writeParam("Name", fMovieName);
    prc->endTag(true);
}

void plLayerMovie::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Movie") {
        fMovieName = tag->getParam("Name", "");
    } else {
        plLayerAnimation::IPrcParse(tag, mgr);
    }
}
