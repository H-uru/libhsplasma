package Plamsa.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnKeyedObject.*;
import Plasma.NucleusLib.pnNetCommon.plSynchedObject;

public class plSceneObject extends plSynchedObject {
    public plKey DrawIntf = new plKey();
    public plKey SimIntf = new plKey();
    public plKey CoordIntf = new plKey();
    public plKey AudioIntf = new plKey();
    public hsTArray<plKeyRef> Interfaces = new hsTArray<plKeyRef>();
    public hsTArray<plKeyRef> Modifiers = new hsTArray<plKeyRef>();
    public plKey SceneNode = new plKey();;

    public void read(hsStream S) throws IOException {
        super.read(S);

        DrawIntf.readRef(S);
        SimIntf.readRef(S);
        CoordIntf.readRef(S);
        AudioIntf.readRef(S);
        Interfaces.read(S);
        Modifiers.read(S);
        SceneNode.readRef(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        DrawIntf.writeRef(S);
        SimIntf.writeRef(S);
        CoordIntf.writeRef(S);
        AudioIntf.writeRef(S);
        Interfaces.write(S);
        Modifiers.write(S);
        SceneNode.writeRef(S);
    }
}

