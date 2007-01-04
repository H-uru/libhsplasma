package Plasma.CoreLib;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.hsScalarTriple;

public class hsBounds3Ext extends hsBounds3 {
    protected int Flags = 0;
    protected hsScalarTriple ST34 = new hsScalarTriple();
    protected hsScalarTriple[] ST40 = new hsScalarTriple[3];
    protected float[] f64 = new float[6];

    public void read(hsStream S) throws IOException {
        Flags = S.readInt();
        super.read(S);

        if ((Flags & 0x01) != 0) {
            ST34.read(S);
            for (int i=0; i<3; i++) {
                ST40[i].read(S);
                f64[2*i] = S.readFloat();
                f64[(2*i)+1] = S.readFloat();
            }
        }
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(Flags);
        super.write(S);

        if ((Flags & 0x01) != 0) {
            ST34.write(S);
            for (int i=0; i<3; i++) {
                ST40[i].write(S);
                S.writeFloat(f64[2*i]);
                S.writeFloat(f64[(2*i)+1]);
            }
        }
    }
}

