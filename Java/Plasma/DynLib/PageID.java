package Plasma.DynLib;

import java.io.*;
import Plasma.CoreLib.hsStream;

public class PageID {
    private int id;
    private PlasmaVer ver;

    public PageID(int pid, PlasmaVer pv) {
        id = pid;
        ver = pv;
    }
    public PageID(PlasmaVer pv) {
        this(0, pv);
    }
    public PageID() {
        this(0, PlasmaVer.UNKNOWN);
    }

    private int getID() { return id; }
    private void setID(int pid) { id = pid; }

    public PlasmaVer getVer() { return ver; }
    public void setVer(PlasmaVer pv, boolean mutate) {
        int sp = getSeqPrefix();
        int pn = getPageNum();
        ver = pv;
        if (mutate) {
            setPageNum(pn);
            setSeqPrefix(sp);
        }
    }
    public void setVer(PlasmaVer pv) {
        setVer(pv, false);
    }

    public boolean isGlobal() {
        return (id & 0x80000000) != 0 ? true : false;
    }

    public int getPageNum() {
        if (isGlobal())
            return (ver == PlasmaVer.LIVE) ? (id & 0xFFFF) - 1 : (id & 0xFF) - 1;
        else
            return (ver == PlasmaVer.LIVE) ? (id & 0xFFFF) - 0x31 : (id & 0xFF) - 0x21;
    }

    public int getSeqPrefix() {
        int sp = (ver == PlasmaVer.LIVE) ? (id >> 16) : (id >> 8);
        if (isGlobal())
            sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
        if (getPageNum() < 0) sp--;
        return sp;
    }

    public void setPageNum(int pn) {
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

    public void setSeqPrefix(int sp) {
        if (sp < 0)
            sp = (sp & 0xFFFFFF00) | (~(sp & 0xFF)) + 1;
        if (getPageNum() < 0) sp++;
        sp <<= (ver == PlasmaVer.LIVE) ? 16 : 8;
        id &= (ver == PlasmaVer.LIVE) ? 0xFFFF : 0xFF;
        id |= sp;
    }

    public void read(hsStream S) throws IOException {
        id = S.readInt();
        ver = S.getVer();
    }

    public void write(hsStream S) throws IOException {
        if (S.getVer() != PlasmaVer.UNKNOWN)
            setVer(S.getVer(), true);
        S.writeInt(id);
    }
}

