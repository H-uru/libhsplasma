package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsBitVector;
import Plasma.NucleusLib.pnKeyedObject.*;
import Plasma.NucleusLib.pnNetCommon.plSynchedObject;
import Plasma.NucleusLib.pnMessage.*;

public class plObjInterface extends plSynchedObject {
    private plKey Owner = new plKey();
    private hsBitVector Properties = new hsBitVector();

    public boolean msgReceive(plMessage msg) { return false; }

    public void read(hsStream S) throws IOException {
        super.read(S);
        Owner.readRef(S);
        Properties.read(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        Owner.writeRef(S);
        Properties.write(S);
    }
}

