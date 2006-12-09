package Plasma.CoreLib;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class hsBitVector {
    private int[] bits;
    private int bLen = 0;

    private static final int BVMASK = 0x1F;
    
    public hsBitVector() {
        bits = new int[0];
    }

    public boolean get(int idx) {
        if ((idx >> 5) < bLen)
            return (bits[idx >> 5] & (1 << (idx & BVMASK))) != 0;
        else return false;
    }

    public void set(int idx, boolean b) {
        if ((idx >> 5) < bLen) {
            bLen = (idx >> 5) + 1;
            int[] newBits = new int[bLen];
            System.arraycopy(newBits, 0, bits, 0, bits.length);
            bits = newBits;
        }
        if (b) bits[idx >> 5] |=  (1 << (idx & BVMASK));
        else   bits[idx >> 5] &= ~(1 << (idx & BVMASK));
    }

    public boolean isEmpty() { return (bLen == 0); }
    public void clear() {
        bits = new int[0];
        bLen = 0;
    }

    public void deleteBit(int idx) {
        int b = idx >> 5;
        idx &= BVMASK;
        int mask = (1 << idx) - 1;
        bits[b] = (bits[b] & mask) | ((bits[b] & ~mask) >> 1);
        for (int i = b+1; i<bLen; i++) {
            bits[i-1] |= bits[i] << BVMASK;
            bits[i] >>= 1;
        }
    }

    public void read(hsStream S) throws IOException {
        bLen = S.readInt();
        bits = new int[bLen];
        for (int i=0; i<bLen; i++)
            bits[i] = S.readInt();
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(bLen);
        for (int i=0; i<bLen; i++)
            S.writeInt(bits[i]);
    }
}

