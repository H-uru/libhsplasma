module Plasma.NucleusLib.pnKeyedObject.hsKeyedObject;

import Plasma.plReceiver;

class hsKeyedObject : plReceiver {
    public this() { }
    public ~this() { }

    public char[] getTypeName() { return "hsKeyedObject"; }
    public int getTypeNum() { return 2; }

    public void read(hsStream S) {
        key.read(S);
    }

    public void write(hsStream S) {
        key.write(S);
    }
}

