package Plasma.CoreLib;

import java.io.*;
import Plasma.CoreLib.hsStream;

public class hsElfStream extends hsStream {
    public hsElfStream(String fileName, int mode) throws FileNotFoundException {
        super(fileName, mode);
    }

    private void decipher(byte[] v, byte key) {
        byte a, b, c, d;

        b = key;
        d = (byte)((v[0] ^ b) >> 5);
        for (int i=v.length-1; i>=0; i--) {
            a = (byte)(v[i] ^ b);
            c = a;
            a = (byte)((a << 3) | d);
            d = a;
            d >>= 6;
            a <<= 2;
            d |= a;
            c >>= 5;
            v[i] = d;
            d = c;
        }
    }

    public String readLine() throws IOException {
        long p = pos();
        short segHead = readShort();
        short segSize = (short)(segHead ^ (p & 0xFFFF));
        byte key = (byte)(p & 0xFF);

        byte[] ln = readString(segSize).getBytes();
        decipher(ln, key);
        return new String(ln);
    }
    //public void writeLine(String ln);
}

