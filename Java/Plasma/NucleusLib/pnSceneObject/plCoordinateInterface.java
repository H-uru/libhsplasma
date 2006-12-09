package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnKeyedObject.*;
import Plasma.hsMatrix44;

public class plCoordinateInterface extends plObjInterface {
    hsMatrix44 LocalToParent = new hsMatrix44();
    hsMatrix44 ParentToLocal = new hsMatrix44();
    hsMatrix44 LocalToWorld = new hsMatrix44();
    hsMatrix44 WorldToLocal = new hsMatrix44();
    hsTArray<plKeyRef> SceneObjects = new hsTArray<plKeyRef>();

    //short Member60;
    //hsTArray<plSceneObject> Children
    plCoordinateInterface Parent;

    public plCoordinateInterface getRoot() {
        plCoordinateInterface cur = this;
        while (cur.Parent != null)
            cur = cur.Parent;
        return cur;
    }

    public void read(hsStream S) throws IOException {
        super.read(S);

        LocalToParent.read(S);
        ParentToLocal.read(S);
        LocalToWorld.read(S);
        WorldToLocal.read(S);
        SceneObjects.read(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        LocalToParent.write(S);
        ParentToLocal.write(S);
        LocalToWorld.write(S);
        WorldToLocal.write(S);
        SceneObjects.write(S);
    }
}

