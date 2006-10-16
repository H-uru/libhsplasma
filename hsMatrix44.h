#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

class hsMatrix44 {
private:
    float data[4][4];

public:
    hsMatrix44();
    hsMatrix44(hsMatrix44 * init);
    ~hsMatrix44();
    
    void Identity();
    
    float& operator()(int y, int x);
    const hsMatrix44& operator+(const hsMatrix44 &other);
    const hsMatrix44& operator*(const hsMatrix44 &other);
    const hsMatrix44& operator*(const float mult);
    //const hsMatrix44& operator+=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const hsMatrix44 &other);
    //const hsMatrix44& operator*=(const float mult);
    
    const char* toString();
};

#endif
