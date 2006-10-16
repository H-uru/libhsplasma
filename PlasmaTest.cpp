#include <stdio.h>
#include "hsMatrix44.h"

int main(int argc, char** argv) {
    hsMatrix44 mat1;
    hsMatrix44 mat2;
    
    mat1(0, 0) = 2.0f;
    mat1(0, 1) = -3.0f;
    mat1(0, 2) = 5.0f;
    mat1(0, 3) = -7.0f;
    mat1(1, 0) = 1.0f;
    mat1(1, 1) = 0;
    mat1(1, 2) = -4.0f;
    mat1(1, 3) = 8.0f;
    mat1(2, 0) = 3.0f;
    mat1(2, 1) = 7.0f;
    mat1(2, 2) = -5.0f;
    mat1(2, 3) = -9.0f;
    mat1(3, 0) = -2.0f;
    mat1(3, 1) = 9.0f;
    mat1(3, 2) = -1.0f;
    mat1(3, 3) = 4.0f;
    
    mat2 = mat1 * .5f;
    printf("%s\n\n%s\n", mat1.toString(), mat2.toString());
    
    mat1 = mat1 * mat2;
    printf("\n%s\n", mat1.toString());

    getchar();
    return 0;
}
