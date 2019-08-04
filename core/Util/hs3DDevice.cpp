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

void hsG3DDeviceMode::read(hsStream* S, int version)
{
    fFlags = S->readInt();
    fWidth = S->readInt();
    fHeight = S->readInt();
    fDepth = S->readInt();

    if (version >= 11) {
        fZStencilDepths.resize(S->readByte());
        for (size_t i = 0; i < fZStencilDepths.size(); i++)
            fZStencilDepths[i] = S->readShort();

        fFSAATypes.resize(S->readByte());
        for (size_t i = 0; i < fFSAATypes.size(); i++)
            fFSAATypes[i] = S->readByte();

        fCanRenderToCubics = S->readBool();
    }
}

void hsG3DDeviceMode::write(hsStream* S, int version)
{
    S->writeInt(fFlags);
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fDepth);

    if (version >= 11) {
        S->writeByte(fZStencilDepths.size());
        for (size_t i = 0; i < fZStencilDepths.size(); i++)
            S->writeShort(fZStencilDepths[i]);

        S->writeByte(fFSAATypes.size());
        for (size_t i = 0; i < fFSAATypes.size(); i++)
            S->writeByte(fFSAATypes[i]);

        S->writeBool(fCanRenderToCubics);
    }
}

void hsG3DDeviceRecord::read(hsStream* S)
{
    fRecordVersion = S->readInt();
    fFlags = S->readInt();
    fDeviceType = S->readInt();

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

void hsG3DDeviceRecord::write(hsStream* S)
{
    S->writeInt(fRecordVersion);
    S->writeInt(fFlags);
    S->writeInt(fDeviceType);

    S->writeInt(fDriverDesc.size());
    S->writeStr(fDriverDesc);
    S->writeInt(fDriverName.size());
    S->writeStr(fDriverName);
    S->writeInt(fDriverVersion.size());
    S->writeStr(fDriverVersion);
    S->writeInt(fDeviceDesc.size());
    S->writeStr(fDeviceDesc);

    fCaps.write(S);

    S->writeInt(fLayersAtOnce);
    S->writeInt(fMemoryBytes);

    S->writeInt(fModes.size());
    for (size_t i = 0; i < fModes.size(); i++)
        fModes[i].write(S, fRecordVersion);

    S->writeFloat(fZBiasRating);
    S->writeFloat(fLODBiasRating);
    S->writeFloat(fFogExpApproxStart);
    S->writeFloat(fFogExp2ApproxStart);
    S->writeFloat(fFogEndBias);

    if (fRecordVersion >= 7) {
        S->writeFloat(fFogKnees[0].fFogKnee);
        S->writeFloat(fFogKnees[0].fFogKneeVal);

        S->writeFloat(fFogKnees[1].fFogKnee);
        S->writeFloat(fFogKnees[1].fFogKneeVal);
    }

    if (fRecordVersion >= 11) {
        S->writeByte(fAASetting);
        S->writeByte(fMaxAnisotropicSamples);
    }
}

void hsG3DDeviceModeRecord::read(hsStream* S)
{
    fRecord.read(S);
    fMode.read(S, fRecord.getVersion());

    fTextureQuality = S->readShort();
}

void hsG3DDeviceModeRecord::write(hsStream* S)
{
    fRecord.write(S);
    fMode.write(S, fRecord.getVersion());

    S->writeShort(fTextureQuality);
}
