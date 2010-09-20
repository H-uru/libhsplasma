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

#include "hs3DDevice.h"

hsG3DDeviceMode::hsG3DDeviceMode()
    : fFlags(0), fWidth(0), fHeight(0), fDepth(0),
      fCanRenderToCubics(false) { }

hsG3DDeviceMode::~hsG3DDeviceMode() { }

void hsG3DDeviceMode::read(hsStream* S, int version) {
    fFlags = S->readInt();
    fWidth = S->readInt();
    fHeight = S->readInt();
    fDepth = S->readInt();

    if (version >= 11) {
        fZStencilDepths.clear();
        unsigned char count = S->readByte();
        for (unsigned char i = 0; i < count; i++) {
            fZStencilDepths.append(S->readShort());
        }

        fFSAATypes.clear();
        count = S->readByte();
        for (unsigned char i = 0; i < count; i++) {
            fFSAATypes.append(S->readByte());
        }

        fCanRenderToCubics = S->readBool();
    }
}

void hsG3DDeviceMode::write(hsStream* S, int version) {
    S->writeInt(fFlags);
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fDepth);

    if (version >= 11) {
        S->writeByte(fZStencilDepths.getSize());
        for (size_t i = 0; i < fZStencilDepths.getSize(); i++) {
            S->writeShort(fZStencilDepths[i]);
        }

        S->writeByte(fFSAATypes.getSize());
        for (size_t i = 0; i < fFSAATypes.getSize(); i++) {
            S->writeByte(fFSAATypes[i]);
        }

        S->writeBool(fCanRenderToCubics);
    }
}

hsG3DDeviceRecord::hsG3DDeviceRecord() 
    : fRecordVersion(11), fFlags(kInvalid), fDeviceType(0),
      fLayersAtOnce(0), fMemoryBytes(0), fZBiasRating(0.0),
      fLODBiasRating(0.0), fFogExpApproxStart(0.0),
      fFogExp2ApproxStart(0.0), fFogEndBias(0.0),
      fAASetting(0), fMaxAnisotropicSamples(0) { }

hsG3DDeviceRecord::~hsG3DDeviceRecord() { }

void hsG3DDeviceRecord::read(hsStream* S) {
    fRecordVersion = S->readInt();
    fFlags = S->readInt();
    fDeviceType = S->readInt();

    if (fRecordVersion >= 0) {
        size_t len = S->readInt();
        fDriverDesc = S->readStr(len);
        len = S->readInt();
        fDriverName = S->readStr(len);
        len = S->readInt();
        fDriverVersion = S->readStr(len);
        len = S->readInt();
        fDeviceDesc = S->readStr(len);

        fCaps.read(S);

        fLayersAtOnce = S->readInt();
        fMemoryBytes = S->readInt();

        size_t count = S->readInt();
        for (size_t i = 0; i < count; i++) {
            fModes[i].read(S, fRecordVersion);
        }

        fZBiasRating = S->readFloat();
        fLODBiasRating = S->readFloat();
        fFogExpApproxStart = S->readFloat();
        fFogExp2ApproxStart = S->readFloat();
        fFogEndBias = S->readFloat();
    }
    if (fRecordVersion >= 7) {
        fFogKnees[0].fFogKnee = S->readFloat();
        fFogKnees[0].fFogKneeVal = S->readFloat();

        fFogKnees[1].fFogKnee = S->readFloat();
        fFogKnees[1].fFogKneeVal = S->readFloat();
    }

    if (fRecordVersion >= 11) {
        fAASetting = S->readByte();
        fMaxAnisotropicSamples = S->readByte();
    }
}
