package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plDrawInterface extends plObjInterface {
    public hsTArray<plDrawableKeyRef> Drawables = new hsTArray<plDrawableKeyRef>();
    public hsTArray<plKeyRef> Objects = new hsTArray<plKeyRef>();

    public void read(hsStream S) throws IOException {
        super.read(S);
        Drawables.read(S);
        Objects.read(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        Drawables.write(S);
        Objects.write(S);
    }
}

