package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class hsScalarTriple {
    private float a, b, c;
    
    public hsScalarTriple() {
        this(0.0f, 0.0f, 0.0f);
    }
    public hsScalarTriple(float f1, float f2, float f3) {
        a = f1;
        b = f2;
        c = f3;
    }
    
    public void read(hsStream S) throws IOException {
        a = S.readFloat();
        b = S.readFloat();
        c = S.readFloat();
    }
    
    public void write(hsStream S) throws IOException {
        S.writeFloat(a);
        S.writeFloat(b);
        S.writeFloat(c);
    }
}

