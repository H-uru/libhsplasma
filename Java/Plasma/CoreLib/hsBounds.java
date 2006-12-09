package Plasma.CoreLib;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class hsBounds {
    int Unknown = 0;

    public void read(hsStream S) throws IOException {
        Unknown = S.readInt();
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(Unknown);
    }
}

