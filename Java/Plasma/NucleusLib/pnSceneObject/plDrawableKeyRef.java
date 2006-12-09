package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plDrawableKeyRef extends plKeyRef {
    public int DrawKey = 0;

    public void read(hsStream S) throws IOException {
        DrawKey = S.readInt();
        super.read(S);
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(DrawKey);
        super.write(S);
    }
}

