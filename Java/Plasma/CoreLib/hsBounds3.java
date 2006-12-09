package Plasma.CoreLib;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.Vertex3;

public class hsBounds3 extends hsBounds {
    Vertex3 min, max;

    public hsBounds3() {
        min = new Vertex3();
        max = new Vertex3();
    }

    public void read(hsStream S) throws IOException {
        super.read(S);
        min.read(S);
        max.read(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        min.write(S);
        max.write(S);
    }
}

