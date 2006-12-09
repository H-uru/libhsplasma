package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plAudioInterface extends plObjInterface {
    protected plKey Audible = new plKey();

    public void read(hsStream S) throws IOException {
        super.read(S);
        Audible.readRef(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        Audible.writeRef(S);
    }
}

