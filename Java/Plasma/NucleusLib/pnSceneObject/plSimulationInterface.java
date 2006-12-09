package Plasma.NucleusLib.pnSceneObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsBitVector;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plSimulationInterface extends plObjInterface {
    protected hsBitVector SimFlags = new hsBitVector();
    protected int Unknown = 0;
    protected plKey Physical = new plKey();

    public void read(hsStream S) throws IOException {
        super.read(S);

        SimFlags.read(S);
        Unknown = S.readInt();
        Physical.readRef(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        SimFlags.write(S);
        S.writeInt(Unknown);
        Physical.writeRef(S);
    }
}

