module Plasma.plCreatable;

import Plasma.CoreLib.hsStream;

class plCreatable {
    protected abstract char[] getTypeName() { return ""; }
    protected abstract int getTypeNum() { return -1; }

    public this() { }
    public ~this() { }

    public abstract void read(hsStream S) { }
    public abstract void write(hsStream S) { }
}

