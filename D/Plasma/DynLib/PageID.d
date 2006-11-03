module Plasma.DynLib.PageID;

import Plasma.DynLib.PlasmaVersions;
import Plasma.CoreLib.hsStream;

class PageID {
    private int id;
    private PlasmaVer ver;

    public this() {
        this(-1);
    }
    public this(int pid, PlasmaVer pv=PlasmaVer.UNKNOWN) {
        id = pid;
        ver = pv;
    }
    public ~this() { }

    int getID() { return id; }
    void setID(int pid) { id = pid; }
    
    PlasmaVer getVer() { return ver; }
    void setVer(PlasmaVer pv, bool mutate = false) {
        int sp = getSeqPrefix();
        int pn = getPageNum();
        ver = pv;
        if (mutate) {
            setPageNum(pn);
            setSeqPrefix(sp);
        }
    }

    bool isGlobal() { return (id & 0x80000000) != 0; }

    int getPageNum() {
        if (isGlobal())
            return (ver == PlasmaVer.LIVE) ? (id & 0xFFFF) - 1 : (id & 0xFF) - 1;
        else
            return (ver == PlasmaVer.LIVE) ? (id & 0xFFFF) - 0x31 : (id & 0xFF) - 0x21;
   }

    int getSeqPrefix() {
        int sp = (ver == PlasmaVer.LIVE) ? (id >> 16) : (id >> 8);
        if (isGlobal())
            sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
        if (getPageNum() < 0) sp--;
        return sp;
    }

    void setPageNum(int pn) {
        if (isGlobal())
            if (ver == PlasmaVer.LIVE)
                id = (id & 0xFFFF0000) | ((pn & 0xFFFF) + 1);
            else
                id = (id & 0xFFFFFF00) | ((pn & 0xFF) + 1);
        else
            if (ver == PlasmaVer.LIVE)
                id = (id & 0xFFFF0000) | ((pn & 0xFFFF) + 0x31);
            else
                id = (id & 0xFFFFFF00) | ((pn & 0xFF) + 0x21);
    }

    void setSeqPrefix(int sp) {
        if (sp < 0)
            sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
        if (getPageNum() < 0) sp++;
        sp <<= (ver == PlasmaVer.LIVE) ? 16 : 8;
        id &= (ver == PlasmaVer.LIVE) ? 0xFFFF : 0xFF;
        id |= sp;
    }

    void read(hsStream S) {
        id = S.readInt();
        ver = S.getVer();
    }

    void write(hsStream S) {
        if (S.getVer() != PlasmaVer.UNKNOWN)
            setVer(S.getVer(), true);
        S.writeInt(id);
    }
}

