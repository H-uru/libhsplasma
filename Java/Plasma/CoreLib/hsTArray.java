package Plasma.CoreLib;

public class hsTArray<T> {
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

    public void empty() {
        count = 0;
        data = (T[]) new Object[szInc];
    }

    public boolean isEmtpy() {
        return (count == 0);
    }

    private void ensureCapacity(int cap) {
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
}
