package Plasma.PubUtilLib.plAvatar;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.CoreLib.hsTArray;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plClothingItem extends hsKeyedObject {
    protected String ItemName;
    protected byte ClothingGroup, ClothingType, ClosetCategory;
    protected boolean Unknown;

    protected String AttrList;
    protected String FriendlyName;

    public hsTArray<ClothingFeatureSet> Features = new hsTArray<ClothingFeatureSet>();

    protected plKey Icon, HQMesh, MQMesh, LQMesh;
    protected plKey ClothingItem = new plKey();

    protected short[] Extra = new short[3];

    public void read(hsStream S) throws IOException {
        super.read(S);

        ItemName = S.readSafeString();
        ClothingGroup = S.readByte();
        ClothingType = S.readByte();
        ClosetCategory = S.readByte();
        Unknown = S.readBool();

        AttrList = S.readSafeString();
        FriendlyName = S.readSafeString();

        Icon = null;
        if (S.readBool())
            Icon.readRef(S);

        Features.read(S);

        HQMesh = null;
        MQMesh = null;
        LQMesh = null;
        if (S.readBool())
            HQMesh.readRef(S);
        if (S.readBool())
            MQMesh.readRef(S);
        if (S.readBool())
            LQMesh.readRef(S);
        
        ClothingItem.readRef(S);

        for (int i=0; i<3; i++)
            Extra[i] = S.readShort();
    }

    public void write(hsStream S) throws IOException {
        super.write(S);

        S.writeSafeString(ItemName);
        S.writeByte(ClothingGroup);
        S.writeByte(ClothingType);
        S.writeByte(ClosetCategory);
        S.writeBool(Unknown);

        S.writeSafeString(AttrList);
        S.writeSafeString(FriendlyName);

        if (Icon != null) {
            S.writeBool(true);
            Icon.writeRef(S);
        } else
            S.writeBool(false);

        Features.write(S);

        if (HQMesh != null) {
            S.writeBool(true);
            HQMesh.writeRef(S);
        } else
            S.writeBool(false);
        if (MQMesh != null) {
            S.writeBool(true);
            MQMesh.writeRef(S);
        } else
            S.writeBool(false);
        if (LQMesh != null) {
            S.writeBool(true);
            LQMesh.writeRef(S);
        } else
            S.writeBool(false);

        ClothingItem.writeRef(S);

        for (int i=0; i<3; i++)
            S.writeShort(Extra[i]);
    }
}

