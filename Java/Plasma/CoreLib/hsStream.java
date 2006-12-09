package Plasma.CoreLib;

import java.io.*;
import Plasma.DynLib.*;

public class hsStream {
    public static final int MODE_READ = 1;
    public static final int MODE_WRITE = 2;

    // "mystnerd"
    private static final byte[] eoaStrKey = {109,121,115,116,110,101,114,100};

    private RandomAccessFile F;
    private PlasmaVer ver;
    
    public hsStream(String fileName, int mode) throws FileNotFoundException {
        String modes = "";
        if ((mode & MODE_READ) != 0) modes += "r";
        if ((mode & MODE_WRITE) != 0) modes += "w";
        F = new RandomAccessFile(fileName, modes);
    }
    public hsStream(String fileName) throws FileNotFoundException {
        this(fileName, MODE_READ & MODE_WRITE);
    }

    public PlasmaVer getVer() { return ver; }
    public void setVer(PlasmaVer pv) { ver = pv; }

    public long pos() throws IOException { return F.getFilePointer(); }

    public byte readByte() throws IOException {
        return F.readByte();
    }
    public short readShort() throws IOException {
        return F.readShort();
    }
    public int readInt() throws IOException {
        return F.readInt();
    }
    public long readLong() throws IOException {
        return F.readLong();
    }
    public float readFloat() throws IOException {
        return F.readFloat();
    }
    public double readDouble() throws IOException {
        return F.readDouble();
    }
    public boolean readBool() throws IOException {
        return (F.readByte() != 0);
    }
    public char readChar() throws IOException {
        return (char) F.readByte();
    }
    public String readString(int len) throws IOException {
        byte[] str = new byte[len];
        if (F.read(str) != len)
            throw new EOFException();
        return new String(str);
    }
    public String readSafeString() throws IOException {
        short ssInfo = (short)(F.readShort() & 0xFFFF);
        byte[] buf;
        if (ver == PlasmaVer.EOA) {
            buf = readString(ssInfo).getBytes();
            for (int i=0; i<ssInfo; i++)
                buf[i] ^= eoaStrKey[i%8];
        } else {
            if ((ssInfo & 0xF000) == 0) readByte(); // Discarded - debug
            buf = readString(ssInfo & 0x0FFF).getBytes();
            if ((ssInfo & 0xF000) != 0) {
                for (int i=0; i<(ssInfo & 0x0FFF); i++)
                    buf[i] = (byte) ~buf[i];
            }
        }
        return new String(buf);
    }

    public void writeByte(byte v) throws IOException {
        F.writeByte(v);
    }
    public void writeShort(short v) throws IOException {
        F.writeShort(v);
    }
    public void writeInt(int v) throws IOException {
        F.writeInt(v);
    }
    public void writeLong(long v) throws IOException {
        F.writeLong(v);
    }
    public void writeFloat(float v) throws IOException {
        F.writeFloat(v);
    }
    public void writeDouble(double v) throws IOException {
        F.writeDouble(v);
    }
    public void writeBool(boolean v) throws IOException {
        F.writeByte(v ? 1 : 0);
    }
    public void writeChar(char v) throws IOException {
        F.writeByte((byte)v);
    }
    public void writeString(int len, String str) throws IOException {
        byte[] buf = str.getBytes();
        F.write(buf, 0, len);
    }
    public void writeString(String str) throws IOException {
        writeString(str.length(), str);
    }
    public void writeSafeString(String str) throws IOException {
        short ssInfo = (short)str.length();
        byte[] wbuf;
        byte[] buf = str.getBytes();
        if (ver == PlasmaVer.EOA) {
            writeShort(ssInfo);
            wbuf = new byte[ssInfo];
            for (int i=0; i<ssInfo; i++)
                wbuf[i] = (byte)(buf[i] ^ eoaStrKey[i%8]);
        } else {
            ssInfo = (short)((ssInfo & 0x0FFF) | 0xF000);
            writeShort(ssInfo);
            wbuf = new byte[ssInfo & 0x0FFF];
            for (int i=0; i<(ssInfo & 0x0FFF); i++)
                wbuf[i] = (byte) ~buf[i];
        }
        writeString(new String(wbuf));
    }
}

