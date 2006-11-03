
import Plasma.CoreLib.hsTArray;
import Plasma.DynLib.PageID;
import Plasma.hsMatrix44;
import std.stdio;

int main(char[][] argv) {
    hsTArray!(hsMatrix44) mar = new hsTArray!(hsMatrix44);
    mar.addNew();
    mar.addNew();
    hsMatrix44 mat1 = mar[0];
    hsMatrix44 mat2 = mar[1];
    
    mat2 = mat1 * .5f;
    writef("%s\n\n%s\n", mar[0].toString(), mar[1].toString());
    
    mar.add(mat1 * mat2);
    writef("\n%s\n", mar[2].toString());
    
    mar.add(mat1.scale(2.0f, 1.5f, .5f));
    writef("\n%s\n", mar[3].toString());

    hsMatrix44 mat3;
    hsMatrix44 mat4;

    mat3[0, 0] = 2.0f;
    mat3[0, 1] = -3.0f;
    mat3[0, 2] = 5.0f;
    mat3[0, 3] = -7.0f;
    mat3[1, 0] = 1.0f;
    mat3[1, 1] = 0;
    mat3[1, 2] = -4.0f;
    mat3[1, 3] = 8.0f;
    mat3[2, 0] = 3.0f;
    mat3[2, 1] = 7.0f;
    mat3[2, 2] = -5.0f;
    mat3[2, 3] = -9.0f;
    mat3[3, 0] = -2.0f;
    mat3[3, 1] = 9.0f;
    mat3[3, 2] = -1.0f;
    mat3[3, 3] = 4.0f;

    mat4 = mat3 * .5f;
    writef("----\n%s\n\n%s\n", mat3.toString(), mat4.toString());

    getchar();
    return 0;
}

