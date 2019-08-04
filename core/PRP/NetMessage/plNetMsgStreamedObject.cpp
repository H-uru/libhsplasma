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

#include "plNetMsgStreamedObject.h"

/* plNetMsgStreamedObject */
void plNetMsgStreamedObject::read(hsStream* S, plResManager* mgr)
{
    plNetMsgObject::read(S, mgr);

    plNetMsgStreamHelper helper;
    helper.read(S, mgr);
    fStream.setVer(S->getVer());
    fStream.copyFrom(helper.getStream(), helper.getStreamLength());
    fCompressionType = helper.getCompressionType();
    // TODO: Decompression
}

void plNetMsgStreamedObject::write(hsStream* S, plResManager* mgr)
{
    plNetMsgObject::write(S, mgr);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.setCompressionType(fCompressionType);
    // TODO: Compression
    helper.write(S, mgr);
    delete[] buf;
}

void plNetMsgStreamedObject::IPrcWrite(pfPrcHelper* prc)
{
    plNetMsgObject::IPrcWrite(prc);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.prcWrite(prc);
    delete[] buf;
}

void plNetMsgStreamedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plNetMsgStreamHelper") {
        plNetMsgStreamHelper helper;
        helper.prcParse(tag, mgr);
        fStream.copyFrom(helper.getStream(), helper.getStreamLength());
        fCompressionType = helper.getCompressionType();
    } else {
        plNetMsgObject::IPrcParse(tag, mgr);
    }
}
