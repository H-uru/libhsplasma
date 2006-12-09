package Plasma.PubUtilLib.plSurface;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnNetCommon.plSynchedObject;
import Plasma.NucleusLib.pnKeyedObject.*;

public class hsGMaterial extends plSynchedObject {
    private int Unknown;
    private int LayerFlags;
    public hsTArray<plKeyRef> Layers1 = new hsTArray<plKeyRef>();
    public hsTArray<plKeyRef> Layers2 = new hsTArray<plKeyRef>();

    public void read(hsStream S) throws IOException {
        super.read(S);

        Unknown = S.readInt();
        LayerFlags = S.readInt();
        int l1Count = S.readInt();
        int l2Count = S.readInt();

        Layers1.clear();
        Layers1.ensureCapacity(l1Count);
        for (int i=0; i<l1Count; i++)
            Layers1.addNew().readRef(S);
        Layers2.clear();
        Layers2.ensureCapacity(l2Count);
        for (int i=0; i<l2Count; i++)
            Layers2.addNew().readRef(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        S.writeInt(Unknown);
        S.writeInt(LayerFlags);
        S.writeInt(Layers1.size());
        S.writeInt(Layers2.size());

        for (int i=0; i<Layers1.size(); i++)
            Layers1.get(i).write(S);
        for (int i=0; i<Layers2.size(); i++)
            Layers2.get(i).write(S);
    }
}

