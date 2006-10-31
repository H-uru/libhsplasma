package Plasma.PubUtilLib.plGImage;

import Plasma.NucleusLib.pnKeyedObject.*;
import Plasma.CoreLib.*;
import java.io.IOException;

public class plBitmap extends hsKeyedObject {
    public static final byte IMG_ARGB = 0;
    public static final byte IMG_DXT  = 1;
    public static final byte IMG_JPEG = 2;

    protected byte version;
    protected byte BPP, CPB;
    protected short flags;
    protected byte imgType;
    protected byte texelSize, texelType;
    protected short Unk1, Unk2;

    public plBitmap() { }

    public void read(hsStream S) throws IOException {
        super.read(S);

        version = S.readByte();
        BPP = S.readByte();
        CPB = S.readByte();
        flags = S.readShort();
        imgType = S.readByte();
        if (imgType != 0 && imgType != IMG_JPEG)
            texelSize = S.readByte();
        else texelSize = 0;
        texelType = S.readByte();
        Unk1 = S.readShort();
        Unk2 = S.readShort();
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        S.writeByte(version);
        S.writeByte(BPP);
        S.writeByte(CPB);
        S.writeShort(flags);
        S.writeByte(imgType);
        if (imgType != 0 && imgType != IMG_JPEG)
            S.writeByte(texelSize);
        S.writeByte(texelType);
        S.writeShort(Unk1);
        S.writeShort(Unk2);
    }

    public int getTypeNum() { return 3; }
    public String getTypeName() { return "plBitmap"; }
}

