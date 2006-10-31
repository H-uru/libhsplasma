package Plasma;

import Plasma.plCreatable;
import Plasma.NucleusLib.pnKeyedObject.plKey;
import Plasma.NucleusLib.pnMessage.plMessage;
import Plasma.CoreLib.hsStream;
import java.io.IOException;

public class plReceiver extends plCreatable {
    protected plKey key = new plKey();

    public plReceiver() { }

    public plKey getKey() { return key; }
    public void setKey(plKey k) { key = k; }

    public boolean msgReceive(plMessage msg) { return false; }

    public void read(hsStream S) throws IOException { }
    public void write(hsStream S) throws IOException { }

    public int getTypeNum() { return -1; }
    public String getTypeName() { return ""; }
}

