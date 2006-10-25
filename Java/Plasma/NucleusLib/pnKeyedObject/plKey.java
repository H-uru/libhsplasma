package Plasma.NucleusLib.pnKeyedObject;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.DynLib.*;
import Plasma.plCreatable;
import Plasma.PlasmaConstants;

// Not really a plCreatable, but it makes hsTArray happy...
public class plKey extends plCreatable {
    private byte flags;
    private PageID pageID = new PageID();
    private short pageType = PlasmaConstants.PAGE_NORMAL;
    private byte extra1;
    private short objType = -1;
    private int objID = -1;
    private String objName = "";
    private int someID, clientID;
    private byte eoaExtra2;

    public boolean exists = true;

    public plKey() { }

    public plKey(plKey init) {
        this.flags = init.flags;
        this.pageID = new PageID(init.pageID);
        this.pageType = init.pageType;
        this.extra1 = init.extra1;
        this.objType = init.objType;
        this.objID = init.objID;
        this.objName = new String(init.objName);
        this.someID = init.someID;
        this.clientID = init.clientID;
        this.eoaExtra2 = init.eoaExtra2;
        this.exists = init.exists;
    }

    public PageID getPageID() { return pageID; }
    public void setPageID(PageID pid) { pageID = new PageID(pid); }
    public short getPageType() { return pageType; }
    public void setPageType(short pt) { pageType = pt; }
    public short getObjType() { return objType; }
    public void setObjType(short ot) { objType = ot; }
    public int getObjID() { return objID; }
    public void setObjID(int id) { objID = id; }
    public String getObjName() { return new String(objName); }
    public void setObjName(String name) { objName = new String(name); }

    public void read(hsStream S) throws IOException {
        flags = S.readByte();
        pageID.read(S);
        pageType = S.readShort();
        if ((flags & 0x02) != 0 || S.getVer() == PlasmaVer.EOA)
            extra1 = S.readByte();
        else extra1 = 0;
        objType = S.readShort();
        if (S.getVer() == PlasmaVer.EOA || S.getVer() == PlasmaVer.LIVE)
            objID = S.readInt();
        objName = S.readSafeString();
        if ((flags & 0x01) != 0 && S.getVer() != PlasmaVer.EOA) {
            someID = S.readInt();
            clientID = S.readInt();
        } else {
            someID = 0;
            clientID = 0;
        }
        if ((flags & 0x06) != 0 && S.getVer() == PlasmaVer.EOA)
            eoaExtra2 = S.readByte();
        else eoaExtra2 = 0;
        exists = true;
    }

    public void write(hsStream S) throws IOException {
        S.writeByte(flags);
        pageID.write(S);
        S.writeShort(pageType);
        if ((flags & 0x02) != 0 || S.getVer() == PlasmaVer.EOA)
            S.writeByte(extra1);
        S.writeShort(objType);
        if (S.getVer() == PlasmaVer.EOA || S.getVer() == PlasmaVer.LIVE)
            S.writeInt(objID);
        S.writeSafeString(objName);
        if ((flags & 0x01) != 0 && S.getVer() != PlasmaVer.EOA) {
            S.writeInt(someID);
            S.writeInt(clientID);
        }
        if ((flags & 0x06) != 0 && S.getVer() == PlasmaVer.EOA)
            S.writeByte(eoaExtra2);
    }

    public void readRef(hsStream S) throws IOException {
        exists = true;
        if (S.getVer() != PlasmaVer.EOA)
            exists = S.readBool();
        if (exists) read(S);
    }

    public void writeRef(hsStream S) throws IOException {
        if (S.getVer() != PlasmaVer.EOA)
            S.writeBool(exists);
        if (exists) write(S);
    }

    public int getTypeID() { return -1; }
    public String getTypeName() { return "plKey"; }
}

