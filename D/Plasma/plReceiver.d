module Plasma.plReceiver;

import Plasma.plCreatable;
import Plasma.NucleusLib.pnKeyedObject.plKey;
//import Plasma.NucleusLib.pnMessage.plMessage;

class plReceiver : plCreatable {
    protected plKey key;

    //protected abstract void read(hsStream S);
    //protected abstract void write(hsStream S);

    public this() { key = new plKey; }
    public ~this() { delete key; }

    plKey getKey() { return key; }
    void setKey(plKey k) { key = k; }

    //public abstract bool msgReceive(plMessage msg) { return false; }

    //public abstract char[] getTypeName();
    //public abstract int getTypeNum();
}

