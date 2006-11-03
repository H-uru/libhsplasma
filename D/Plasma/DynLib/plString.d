module Plasma.DynLib.plString;

import Plasma.plCreatable;
import Plasma.CoreLib.hsStream;

class plString : plCreatable {
    private char[] str;

    public this() { str = ""; }
    public this(plString init) { str[] = init.str[]; }
    public this(char[] init) { str[] = init[]; }
    public ~this() { }

    char[] value() { return str[]; }
    void set(char[] value) { str[] = value[]; }

    int length() { return str.length; }

    void read(hsStream S) { str = S.readSafeStr(); }
    void write(hsStream S) { S.writeSafeStr(str); }

    char[] getTypeName() { return ""; }
    int getTypeNum() { return -1; }
}

