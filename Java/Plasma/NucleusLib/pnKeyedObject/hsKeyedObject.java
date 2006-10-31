package Plasma.NucleusLib.pnKeyedObject;

import Plasma.plReceiver;
import Plasma.CoreLib.hsStream;
import java.io.IOException;

public class hsKeyedObject extends plReceiver {
    public hsKeyedObject() { }

    public void read(hsStream S) throws IOException {
        key.read(S);
    }

    public void write(hsStream S) throws IOException {
        key.write(S);
    }

    public int getTypeNum() { return 2; }
    public String getTeypeName() { return "hsKeyedObject"; }
}

