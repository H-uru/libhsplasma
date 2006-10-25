package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public abstract class plCreatable {
    public abstract void read(hsStream S);
    public abstract void write(hsStream S);

    public abstract int getTypeID();
    public abstract String getTypeName();
}

