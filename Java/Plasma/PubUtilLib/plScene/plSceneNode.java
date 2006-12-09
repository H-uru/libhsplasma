package Plasma.PubUtilLib.plScene;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plSceneNode extends hsKeyedObject {
    public hsTArray<plKeyRef> SceneObjects = new hsTArray<plKeyRef>();
    public hsTArray<plKeyRef> OtherObjects = new hsTArray<plKeyRef>();

    public void read(hsStream S) throws IOException {
        super.read(S);
        SceneObjects.read(S);
        OtherObjects.read(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        SceneObjects.write(S);
        OtherObjects.write(S);
    }
}

