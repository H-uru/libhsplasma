module Plasma.NucleusLib.pnNetCommon.plSynchedObject;

import Plasma.NucleusLib.pnKeyedObject.hsKeyedObject;
import Plasma.CoreLib.hsTArray;
import Plasma.DynLib.plString;

class plSynchedObject : hsKeyedObject {
    protected int flags;
    protected hsTArray!(plString) SDLKeys;
    protected hsTArray!(plString) SDLKeys2;

    public this() {
        SDLKeys = new hsTArray!(plString)();
        SDLKeys2 = new hsTArray!(plString)();
    }

    public ~this() {
        delete SDLKeys;
        delete SDLKeys2;
    }

    public void read(hsStream S) {
        super.read(S);
        SDLKeys.clear();
        SDLKeys2.clear();
        flags = S.readInt();

        if (flags & 0x10)
            SDLKeys.read16(S);
        if (flags & 0x40)
            SDLKeys.read16(S);
    }

    public void write(hsStream S) {
        super.write(S);
        S.writeInt(flags);
        
        if (flags & 0x10)
            SDLKeys.write16(S);
        if (flags & 0x40)
            SDLKeys.write16(S);
    }

    public char[] getTypeName() { return "plSynchedObject"; }
    public int getTypeNum() { return 0x28; }
}

