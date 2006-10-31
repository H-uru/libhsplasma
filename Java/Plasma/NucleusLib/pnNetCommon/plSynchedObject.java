package Plasma.NucleusLib.pnNetCommon;

import Plasma.NucleusLib.pnKeyedObject.*;
import Plasma.CoreLib.*;
import Plasma.DynLib.*;
import java.io.IOException;

public class plSynchedObject extends hsKeyedObject {
    protected int flags;
    protected hsTArray<plString> SDLKeys;
    protected hsTArray<plString> SDLKeys2;

    public plSynchedObject() { }

    public void read(hsStream S) throws IOException {
        super.read(S);
        SDLKeys.clear();
        SDLKeys2.clear();
        flags = S.readInt();

        if ((flags & 0x10) != 0)
            SDLKeys.read16(S);
        if ((flags & 0x40) != 0)
            SDLKeys2.read16(S);
    }
    public void write(hsStream S) throws IOException {
        super.write(S);
        S.writeInt(flags);
        if ((flags & 0x10) != 0)
            SDLKeys.write16(S);
        if ((flags & 0x40) != 0)
            SDLKeys.write16(S);
    }

    public int getTypeNum() { return 0x28; }
    public String getTypeName() { return "plSynchedObject"; }
}

