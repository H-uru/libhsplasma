package Plasma.DynLib;

import Plasma.plCreatable;
import Plasma.CoreLib.hsStream;
import java.io.IOException;

public class plString extends plCreatable {
    public String str;

    public plString() { str = ""; }
    public plString(plString init) { str = new String(init.str); }
    public plString(String init) { str = new String(init); }

    public void read(hsStream S) throws IOException {
        str = S.readSafeString();
    }
    public void write(hsStream S) throws IOException {
        S.writeSafeString(str);
    }

    public int getTypeNum() { return -1; }
    public String getTypeName() { return ""; }
}

