package Plasma.CoreLib;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.plCreatable;

public class hsTArray<T extends plCreatable> {
    private static final int INIT_CAPACITY = 10;

    private T[] data;
    private int szInc = INIT_CAPACITY;
    private int count = 0;

    public hsTArray() {
        data = (T[]) new Object[szInc];
    }
    public hsTArray(int sizeInc) {
        data = (T[]) new Object[sizeInc];
        szInc = sizeInc;
    }

    public void clear() {
        count = 0;
        data = (T[]) new Object[szInc];
    }

    public boolean isEmtpy() {
        return (count == 0);
    }

    public void ensureCapacity(int cap) {
        int curCap = data.length;
        while (cap > curCap) curCap += szInc;
        if (curCap != data.length) {
            T[] newData = (T[]) new Object[curCap];
            System.arraycopy(data, 0, newData, 0, count);
            data = newData;
        }
    }

    public void add(T item) {
        ensureCapacity(count+1);
        data[count] = item;
        count++;
    }

    public T addNew() {
        ensureCapacity(count+1);
        data[count] = (T)(new Object());
        count++;
        return data[count-1];
    }

    public void remove(int idx) {
        if (idx >= count)
            throw new ArrayIndexOutOfBoundsException();
        for (int i=idx; i<count; i++)
            data[i] = data[i+1];
        count--;
    }

    public T get(int idx) {
        if (idx >= count)
            throw new ArrayIndexOutOfBoundsException();
        return data[idx];
    }

    public int size() { return count; }

    private void readBase(hsStream S) throws IOException {
        data = (T[]) new Object[count];
        for (int i=0; i<count; i++)
            data[i].read(S);
    }

    public void read(hsStream S) throws IOException {
        count = S.readInt();
        readBase(S);
    }

    public void read16(hsStream S) throws IOException {
        count = (int)S.readShort();
        readBase(S);
    }

    private void writeBase(hsStream S) throws IOException {
        for (int i=0; i<count; i++)
            data[i].write(S);
    }

    public void write(hsStream S) throws IOException {
        S.writeInt(count);
        writeBase(S);
    }

    public void write16(hsStream S) throws IOException {
        S.writeShort((short)count);
        writeBase(S);
    }
}

