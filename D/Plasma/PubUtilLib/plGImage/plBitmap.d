module Plasma.PubUtilLib.plGImage.plBitmap;

import Plasma.NucleusLib.pnKeyedObject.hsKeyedObject;
import Plasma.CoreLib.hsStream;

const byte IMG_ARGB = 0;
const byte IMG_DXT  = 1;
const byte IMG_JPEG = 2;

class plBitmap : hsKeyedObject {
    protected byte ver;
    protected byte BPP, CPB;
    protected short flags;
    protected byte imgType;
    protected byte texelSize, texelType;
    protected short Unk1, Unk2;

    public this() { }
    public ~this() { }

    public void read(hsStream S) {
        super.read(S);

        ver = S.readByte();
        BPP = S.readByte();
        CPB = S.readByte();
        flags = S.readShort();
        imgType = S.readByte();
        if (imgType && (imgType != IMG_JPEG))
            texelSize = S.readByte();
        else texelSize = 0;
        texelType = S.readByte();
        Unk1 = S.readShort();
        Unk2 = S.readShort();
    }

    public void write(hsStream S) {
        super.write(S);

        S.writeByte(ver);
        S.writeByte(BPP);
        S.writeByte(CPB);
        S.writeByte(flags);
        S.writeByte(imgType);
        if (imgType && (imgType != IMG_JPEG))
            S.writeByte(texelSize);
        S.writeByte(texelType);
        S.writeShort(Unk1);
        S.writeShort(Unk2);
    }

    public char[] getTypeName() { return "plBitmap"; }
    public int getTypeNum() { return 3; }
}

