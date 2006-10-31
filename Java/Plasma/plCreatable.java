package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public abstract class plCreatable {
    public abstract void read(hsStream S) throws IOException;
    public abstract void write(hsStream S) throws IOException;

    public abstract int getTypeNum();
    public abstract String getTypeName();
}

