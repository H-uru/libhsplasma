#include "Stream/hsStream.h"
#include "plString.h"

DllClass plMD5Hash {
public:
    unsigned int fHash[4];

public:
    plMD5Hash();
    plMD5Hash(const plMD5Hash& cpy);
    plMD5Hash(const char* hex);
    plMD5Hash& operator=(const plMD5Hash& cpy);
    bool operator==(const plMD5Hash& cmp);
    bool operator!=(const plMD5Hash& cmp);

    plString toHex() const;
    void fromHex(const char* hex);
    void read(hsStream* S);
    void write(hsStream* S);
};

DllClass plMD5 {
private:
    static const unsigned int kShiftArray[4][4];
    static const unsigned int kBaseArray[64];
    static const unsigned char kPadArray[64];

    unsigned int fA, fB, fC, fD;

public:
    static plMD5Hash hashStream(hsStream* S);
    static plMD5Hash hashFile(const char* filename);
    static plMD5Hash hashString(const plString& str);

private:
    plMD5();
    void processBlock(const unsigned char* block);
};
