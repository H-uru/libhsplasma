package Plasma;

public class hsRefCount {
    protected static int refCount = 1;

    int getRefCount() { return refCount; }
    int removeRef() { return --refCount; }
    void addRef() { refCount++; }
}

