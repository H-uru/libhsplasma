package Plasma;

// Just so everyone knows, this class is completely useless in Java :)

public class hsRefCount {
    protected static int refCount = 1;

    int getRefCount() { return refCount; }
    int removeRef() { return --refCount; }
    void addRef() { refCount++; }
}

