#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

#include "CoreLib/hsStream.h"
#include "hsRefCount.h"

class hsMatrix44 : public hsRefCount {
private:
    float data[4][4];

public:
    hsMatrix44();
    hsMatrix44(hsMatrix44& init);
    ~hsMatrix44();
    
    void Identity();
    
    float& operator()(int y, int x);
    hsMatrix44& operator+(const hsMatrix44& other);
    hsMatrix44& operator*(const hsMatrix44& other);
    hsMatrix44& operator*(const float mult);
    //const hsMatrix44& operator+=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const float mult);
    hsMatrix44& operator=(const hsMatrix44& other);
    bool operator==(const hsMatrix44& other);
    
    hsMatrix44& translate(float x, float y, float z);
    hsMatrix44& scale(float x, float y, float z);
    hsMatrix44& rotate(float x, float y, float z);
    
    void read(hsStream *S);
    void write(hsStream *S);

    const char* toString();
};

#endif
