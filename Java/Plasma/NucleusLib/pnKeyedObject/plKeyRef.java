package Plasma.NucleusLib.pnKeyedObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class plKeyRef extends plKey {
    public plKeyRef() { }
    public plKeyRef(plKeyRef init) {
        super((plKey)init);
    }
    public plKeyRef(plKey init) {
        super(init);
    }

    public void read(hsStream S) throws IOException {
        super.readRef(S);
    }

    public void write(hsStream S) throws IOException {
        super.writeRef(S);
    }
}

