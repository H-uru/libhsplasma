module Plasma.CoreLib.hsStream;

import std.stream;
import std.file;
import Plasma.DynLib.PlasmaVersions;

static const char eoaStrKey[8] = ['m','y','s','t','n','e','r','d'];

/**
 * Generic file-based stream -- don't mess with the other stream types for now
 **/
class hsStream {
    protected PlasmaVer ver;
    protected File F;

    this(char[] filename, FileMode mode) {
        F = new File(filename, mode);
    }
    
    ~this() {
        F.close();
        delete F;
    }

    public void setVer(PlasmaVer pv) { ver = pv; }
    public PlasmaVer getVer() { return ver; }

    public ulong size() { return F.size(); }
    public ulong pos() { return F.position(); }
    public bool eof() { return F.eof(); }
    
    public void seek(ulong pos) { F.seekSet(pos); }
    public void fastForward(ulong count) { F.seekCur(count); }
    public void rewind(ulong count) { F.seekCur(0-count); }

    byte readByte() {
        byte v;
        F.read(v);
        return v;
    }
    short readShort() {
        short v;
        F.read(v);
        return v;
    }
    int readInt() {
        int v;
        F.read(v);
        return v;
    }
    long readLong() {
        long v;
        F.read(v);
        return v;
    }
    float readFloat() {
        float v;
        F.read(v);
        return v;
    }
    double readDouble() {
        double v;
        F.read(v);
        return v;
    }
    bool readBool() {
        byte v;
        F.read(v);
        return (v != 0);
    }
    char readChar() {
        return cast(char)readByte();
    }
    
    char[] readStr(int len) {
        return F.readString(len);
    }
    
    char[] readSafeStr() {
        ushort ssInfo = cast(ushort)readShort();
        char[] buf;
        if (ver == PlasmaVer.EOA) {
            buf = readStr(ssInfo);
            for (int i=0; i<ssInfo; i++)
                buf[i] ^= eoaStrKey[i%8];
        } else {
            if (!(ssInfo & 0xF000)) readByte(); // Discarded - debug
            buf = readStr(ssInfo & 0x0FFF);
            if (ssInfo & 0xF000) {
                for (int i=0; i<(ssInfo & 0x0FFF); i++)
                    buf[i] = ~buf[i];
            }
        }
        return buf;
    }

    void writeByte(byte v) { F.write(v); }
    void writeShort(short v) { F.write(v); }
    void writeInt(int v) { F.write(v); }
    void writeLong(long v) { F.write(v); }
    void writeFloat(float v) { F.write(v); }
    void writeDouble(double v) { F.write(v); }
    void writeBool(bool v) {
        if (v) F.write(cast(byte)1);
        else F.write(cast(byte)0);
    }
    void writeChar(char v) { writeByte(cast(byte)v); }
    
    void writeStr(in char[] buf, int len) {
        if (len != buf.length) {
            int l = buf.length;
            buf.length = len;
            if (l < len)
                buf[l .. len-1] = '\0';
        }
        F.writeString(buf[0 .. len-1]);
    }
    void writeStr(char[] buf) {
        F.writeString(buf);
    }
    
    void writeSafeStr(char[] buf) {
        ushort ssInfo = cast(ushort)buf.length;
        char[] wbuf;
        if (ver == PlasmaVer.EOA) {
            writeShort(ssInfo);
            wbuf.length = ssInfo;
            for (int i=0; i<ssInfo; i++)
                wbuf[i] = buf[i] ^ eoaStrKey[i%8];
            writeStr(wbuf);
        } else {
            ssInfo = (ssInfo & 0x0FFF) | 0xF000;
            writeShort(ssInfo);
            wbuf.length = (ssInfo & 0x0FFF);
            for (int i=0; i<(ssInfo & 0x0FFF); i++)
                wbuf[i] = ~buf[i];
            writeStr(wbuf);
        }
    }
}

