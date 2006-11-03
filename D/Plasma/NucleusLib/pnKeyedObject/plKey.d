module Plasma.NucleusLib.pnKeyedObject.plKey;

import Plasma.CoreLib.hsStream;
import Plasma.DynLib.PageID;
import Plasma.PlasmaConstants;

class plKey {
    protected byte flags;
    protected PageID pageID;
    protected short pageType = PAGE_NORMAL;
    protected byte extra1;
    protected short objType = -1;
    protected int objID = -1;
    protected char[] objName = "";
    protected int someID, clientID;
    protected byte eoaExtra2;
    public bool exists = true;

    public this() {
        pageID = new PageID;
    }
    
    public this(plKey init) {
        this.flags = init.flags;
        delete pageID;
        this.pageID = new PageID(init.pageID.getID(), init.pageID.getVer());
        this.pageType = init.pageType;
        this.extra1 = init.extra1;
        this.objType = init.objType;
        this.objID = init.objID;
        this.objName[] = init.objName[];
        this.someID = init.someID;
        this.clientID = init.clientID;
        this.eoaExtra2 = init.eoaExtra2;
        this.exists = init.exists;
    }
    
    public ~this() {
        if (pageID != null)
            delete pageID;
    }

    public PageID getPageID() { return pageID; }
    public short getPageType() { return pageType; }
    public short getObjType() { return objType; }
    public int getObjID() { return objID; }
    public char[] getObjName() { return objName[]; }
    
    public void setPageID(PageID pid) { pageID = pid; }
    public void setPageType(short pt) { pageType = pt; }
    public void setObjType(short ot) { objType = ot; }
    public void setObjID(int id) { objID = id; }
    public void setObjName(char[] name) { objName[] = name[]; }

    public void read(hsStream S) {
        flags = S.readByte();
        pageID.read(S);
        pageType = S.readShort();
        if ((flags & 0x02) || S.getVer == PlasmaVer.EOA)
            extra1 = S.readByte();
        else extra1 = 0;
        objType = S.readShort();
        if (S.getVer() == PlasmaVer.EOA || S.getVer == PlasmaVer.LIVE)
            objID = S.readInt();
        objName = S.readSafeStr();
        if ((flags & 0x01) && S.getVer() != PlasmaVer.EOA) {
            someID = S.readInt();
            clientID = S.readInt();
        } else {
            someID = clientID = 0;
        }
        if ((flags & 0x06) && S.getVer() == PlasmaVer.EOA)
            eoaExtra2 = S.readByte();
        else eoaExtra2 = 0;
        exists = true;
    }

    public void write(hsStream S) {
        S.writeByte(flags);
        pageID.write(S);
        S.writeShort(pageType);
        if ((flags & 0x02) || S.getVer() == PlasmaVer.EOA)
            S.writeByte(extra1);
        S.writeShort(objType);
        if (S.getVer() == PlasmaVer.EOA || S.getVer() == PlasmaVer.LIVE)
            S.writeInt(objID);
        S.writeSafeStr(objName);
        if ((flags & 0x01) && S.getVer() != PlasmaVer.EOA) {
            S.writeInt(someID);
            S.writeInt(clientID);
        }
        if ((flags & 0x06) && S.getVer() == PlasmaVer.EOA)
            S.writeByte(eoaExtra2);
    }
    
    public void readRef(hsStream S) {
        exists = true;
        if (S.getVer() != PlasmaVer.EOA)
            exists = S.readBool();
        if (exists) read(S);
    }

    public void writeRef(hsStream S) {
        if (S.getVer() != PlasmaVer.EOA)
            S.writeBool(exists);
        if (exists) write(S);
    }
}

