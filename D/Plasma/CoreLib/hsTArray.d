module Plasma.CoreLib.hsTArray;

import Plasma.CoreLib.hsStream;

const int TARR_CAP_INCREMENT = 32;

class hsTArray(T) {
    private int count = 0, max = TARR_CAP_INCREMENT;
    private T[] data;

    private void ensureCap(int cap) {
        if (max < cap) {
            while (cap > max) max += TARR_CAP_INCREMENT;
            data.length = max;
        }
    }

    public this() {
        data.length = TARR_CAP_INCREMENT;
    }
    public ~this() { }

    void clear() {
        count = 0;
        data.length = TARR_CAP_INCREMENT;
    }

    void add(T item) {
        ensureCap(count+1);
        data[count++] = item;
    }

    T addNew() {
        ensureCap(count+1);
        data[count] = new T();
        return data[count++];
    }

    T del(int idx) {
        T dItm = data[idx];
        for (int i=idx; i<count; i++)
            data[i] = data[i+1];
        count--;
        return dItm;
    }

    T opIndex(size_t idx) {
        return data[idx];
    }
    T opIndexAssign(T value, size_t idx) {
        return data[idx] = value;
    }

    private void baseRead(hsStream S) {
        ensureCap(count);
        for (int i=0; i<count; i++) {
            data[i] = new T();
            data[i].read(S);
        }
    }

    private void baseWrite(hsStream S) {
        for (int i=0; i<count; i++)
            data[i].write(S);
    }

    public void read(hsStream S) {
        count = S.readInt();
        baseRead(S);
    }

    public void write(hsStream S) {
        S.writeInt(count);
        baseWrite(S);
    }

    public void read16(hsStream S) {
        count = S.readShort();
        baseRead(S);
    }

    public void write16(hsStream S) {
        S.writeShort(count);
        baseWrite(S);
    }
}

