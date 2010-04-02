#ifndef _PNBIGINTEGER_H
#define _PNBIGINTEGER_H

#include "PlasmaDefs.h"
#include <openssl/bn.h>

DllClass pnBigInteger {
protected:
    BIGNUM* fValue;
    BN_CTX* fContext;

public:
    pnBigInteger();
    pnBigInteger(const pnBigInteger& init);
    pnBigInteger(unsigned int init);
    pnBigInteger(const unsigned char* data, size_t count);
    ~pnBigInteger();

    pnBigInteger& operator=(const pnBigInteger& init);
    pnBigInteger& operator=(unsigned int init);

    void set(const pnBigInteger& init) { BN_copy(fValue, init.fValue); }
    void set(unsigned int init) { BN_set_word(fValue, init); }
    void set(const unsigned char* data, size_t count);
    void setBit(size_t bit, bool on);

    size_t getByteSize() const { return BN_num_bytes(fValue); }
    size_t getBitSize() const { return BN_num_bits(fValue); }
    void getData(unsigned char* data, size_t bytes) const;
    bool getBit(size_t bit) const { return BN_is_bit_set(fValue, bit) != 0; }

    // Comparison
    bool operator==(const pnBigInteger& num) const;
    bool operator==(unsigned int num) const;
    bool operator!=(const pnBigInteger& num) const;
    bool operator!=(unsigned int num) const;
    bool operator<(const pnBigInteger& num) const;
    bool operator<(unsigned int num) const;
    bool operator>(const pnBigInteger& num) const;
    bool operator>(unsigned int num) const;
    bool operator<=(const pnBigInteger& num) const;
    bool operator<=(unsigned int num) const;
    bool operator>=(const pnBigInteger& num) const;
    bool operator>=(unsigned int num) const;

    // Math
    pnBigInteger& operator++();
    pnBigInteger& operator--();
    pnBigInteger operator+(const pnBigInteger& num) const;
    pnBigInteger operator-(const pnBigInteger& num) const;
    pnBigInteger operator*(const pnBigInteger& num) const;
    pnBigInteger operator/(const pnBigInteger& num) const;
    pnBigInteger operator%(const pnBigInteger& num) const;
    pnBigInteger operator+(unsigned int num) const;
    pnBigInteger operator-(unsigned int num) const;
    pnBigInteger operator*(unsigned int num) const;
    pnBigInteger operator/(unsigned int num) const;
    pnBigInteger operator%(unsigned int num) const;
    pnBigInteger operator<<(size_t amt) const;
    pnBigInteger operator>>(size_t amt) const;
    pnBigInteger& operator+=(const pnBigInteger& num);
    pnBigInteger& operator-=(const pnBigInteger& num);
    pnBigInteger& operator*=(const pnBigInteger& num);
    pnBigInteger& operator/=(const pnBigInteger& num);
    pnBigInteger& operator%=(const pnBigInteger& num);
    pnBigInteger& operator+=(unsigned int num);
    pnBigInteger& operator-=(unsigned int num);
    pnBigInteger& operator*=(unsigned int num);
    pnBigInteger& operator/=(unsigned int num);
    pnBigInteger& operator%=(unsigned int num);
    pnBigInteger& operator<<=(size_t amt);
    pnBigInteger& operator>>=(size_t amt);

    pnBigInteger PowMod(const pnBigInteger& b, const pnBigInteger& m) const;
    pnBigInteger DivMod(const pnBigInteger& div, pnBigInteger& r) const;

    static pnBigInteger Random(size_t bits);
};

/* OpenSSL uses big-endian for their binary buffers... */
#define BYTESWAP_BUFFER(x, size) \
    { \
        hsUbyte temp; \
        for (size_t i = 0; i < (size / 2); i++) { \
            temp = x[i]; \
            x[i] = x[size-1-i]; \
            x[size-1-i] = temp; \
        } \
    }

#endif
