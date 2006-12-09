package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class hsScalarTriple {
    private float x, y, z;
    
    public hsScalarTriple() {
        this(0.0f, 0.0f, 0.0f);
    }
    public hsScalarTriple(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }
    
    public void read(hsStream S) throws IOException {
        x = S.readFloat();
        y = S.readFloat();
        z = S.readFloat();
    }
    
    public void write(hsStream S) throws IOException {
        S.writeFloat(x);
        S.writeFloat(y);
        S.writeFloat(z);
    }
}
