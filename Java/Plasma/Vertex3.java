package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class Vertex3 {
    private float X, Y, Z;
    
    public Vertex3() {
        this(0.0f, 0.0f, 0.0f);
    }
    public Vertex3(float x, float y, float z) {
        X = x;
        Y = y;
        Z = z;
    }
    
    public float getX() { return X; }
    public float getY() { return Y; }
    public float getZ() { return Z; }
    public void setX(float x) { X = x; }
    public void setY(float y) { Y = y; }
    public void setZ(float z) { Z = z; }
    
    public void read(hsStream S) throws IOException {
        X = S.readFloat();
        Y = S.readFloat();
        Z = S.readFloat();
    }
    
    public void write(hsStream S) throws IOException {
        S.writeFloat(X);
        S.writeFloat(Y);
        S.writeFloat(Z);
    }
}
