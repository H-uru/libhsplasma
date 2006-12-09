package Plasma.PubUtilLib.plDrawable;

import java.io.IOException;
import Plasma.CoreLib.*;
import Plasma.hsMatrix44;

public class plSpan {
    protected int DrawableType, MatIndex;
    protected hsMatrix44 LocalToWorld = new hsMatrix44();
    protected hsMatrix44 WorldToLocal = new hsMatrix44();
    protected int Flags;
    protected hsBounds3Ext bounds1, bounds2;
    protected int c98, i94;
    protected short s9A, s9C, s9E;
    protected float Dist1, Dist2;
    protected float f1B0;

    public void read(hsStream S) throws IOException {
        DrawableType = S.readInt();
        MatIndex = S.readInt();
        LocalToWorld.read(S);
        WorldToLocal.read(S);
        Flags = S.readInt();
        bounds1.read(S);
        bounds2.read(S);
        c98 = S.readInt();
        i94 = S.readInt();
        s9A = S.readShort();
        s9C = S.readShort();
        s9E = S.readShort();
        Dist1 = S.readFloat();
        Dist2 = S.readFloat();
        if ((Flags & 0x10) != 0)
            f1B0 = S.readFloat();
        else
            f1B0 = 0.0f;
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(DrawableType);
        S.writeInt(MatIndex);
        LocalToWorld.write(S);
        WorldToLocal.write(S);
        S.writeInt(Flags);
        bounds1.write(S);
        bounds2.write(S);
        S.writeInt(c98);
        S.writeInt(i94);
        S.writeShort(s9A);
        S.writeShort(s9C);
        S.writeShort(s9E);
        S.writeFloat(Dist1);
        S.writeFloat(Dist2);
        if ((Flags & 0x10) != 0)
            S.writeFloat(f1B0);
    }
}

