/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pnBigInteger.h"
#include <cstring>

pnBigInteger::pnBigInteger()
{
    fValue = BN_new();
    fContext = BN_CTX_new();
}

pnBigInteger::pnBigInteger(const pnBigInteger& init)
{
    fValue = BN_new();
    fContext = BN_CTX_new();
    BN_copy(fValue, init.fValue);
}

pnBigInteger::pnBigInteger(unsigned int init)
{
    fValue = BN_new();
    fContext = BN_CTX_new();
    BN_set_word(fValue, init);
}

pnBigInteger::pnBigInteger(const unsigned char* data, size_t count, bool le)
{
    fValue = BN_new();
    fContext = BN_CTX_new();
    unsigned char* buf = new unsigned char[count];
    memcpy(buf, data, count);
    if (le)
        BYTESWAP_BUFFER(buf, count)
    BN_bin2bn(buf, count, fValue);
    delete[] buf;
}

pnBigInteger::~pnBigInteger()
{
    BN_CTX_free(fContext);
    BN_free(fValue);
}

pnBigInteger& pnBigInteger::operator=(const pnBigInteger& init)
{
    BN_copy(fValue, init.fValue);
    return *this;
}

pnBigInteger& pnBigInteger::operator=(unsigned int init)
{
    BN_set_word(fValue, init);
    return *this;
}

void pnBigInteger::set(const unsigned char* data, size_t count, bool le)
{
    unsigned char* buf = new unsigned char[count];
    memcpy(buf, data, count);
    if (le)
        BYTESWAP_BUFFER(buf, count)
    BN_bin2bn(buf, count, fValue);
    delete[] buf;
}

void pnBigInteger::setBit(size_t bit, bool on)
{
    if (on)
        BN_set_bit(fValue, bit);
    else
        BN_clear_bit(fValue, bit);
}

void pnBigInteger::getData(unsigned char* data, size_t bytes, bool le) const
{
    if (bytes != 0 && data != nullptr) {
        BN_bn2bin(fValue, data);
        if (le)
            BYTESWAP_BUFFER(data, bytes)
    }
}

bool pnBigInteger::operator==(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) == 0;
}

bool pnBigInteger::operator==(unsigned int num) const
{
    return BN_is_word(fValue, num) != 0;
}

bool pnBigInteger::operator!=(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) != 0;
}

bool pnBigInteger::operator!=(unsigned int num) const
{
    return BN_is_word(fValue, num) == 0;
}

bool pnBigInteger::operator<(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) < 0;
}

bool pnBigInteger::operator<(unsigned int num) const
{
    return BN_get_word(fValue) < num;
}

bool pnBigInteger::operator>(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) > 0;
}

bool pnBigInteger::operator>(unsigned int num) const
{
    if (BN_num_bits(fValue) > 32)
        return true;
    return BN_get_word(fValue) > num;
}

bool pnBigInteger::operator<=(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) <= 0;
}

bool pnBigInteger::operator<=(unsigned int num) const
{
    if (BN_num_bits(fValue) > 32)
        return false;
    return BN_get_word(fValue) <= num;
}

bool pnBigInteger::operator>=(const pnBigInteger& num) const
{
    return BN_cmp(fValue, num.fValue) >= 0;
}

bool pnBigInteger::operator>=(unsigned int num) const
{
    return BN_get_word(fValue) >= num;
}

pnBigInteger& pnBigInteger::operator++()
{
    BN_add_word(fValue, 1);
    return *this;
}

pnBigInteger& pnBigInteger::operator--()
{
    BN_sub_word(fValue, 1);
    return *this;
}

pnBigInteger pnBigInteger::operator+(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_add(r.fValue, fValue, num.fValue);
    return r;
}

pnBigInteger pnBigInteger::operator-(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_sub(r.fValue, fValue, num.fValue);
    return r;
}

pnBigInteger pnBigInteger::operator*(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_mul(r.fValue, fValue, num.fValue, fContext);
    return r;
}

pnBigInteger pnBigInteger::operator/(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_div(r.fValue, nullptr, fValue, num.fValue, fContext);
    return r;
}

pnBigInteger pnBigInteger::operator%(const pnBigInteger& num) const
{
    pnBigInteger r;
    BN_div(nullptr, r.fValue, fValue, num.fValue, fContext);
    return r;
}

pnBigInteger pnBigInteger::operator+(unsigned int num) const
{
    pnBigInteger r(*this);
    BN_add_word(r.fValue, num);
    return r;
}

pnBigInteger pnBigInteger::operator-(unsigned int num) const
{
    pnBigInteger r(*this);
    BN_sub_word(r.fValue, num);
    return r;
}

pnBigInteger pnBigInteger::operator*(unsigned int num) const
{
    pnBigInteger r(*this);
    BN_mul_word(r.fValue, num);
    return r;
}

pnBigInteger pnBigInteger::operator/(unsigned int num) const
{
    pnBigInteger r(*this);
    BN_div_word(r.fValue, num);
    return r;
}

pnBigInteger pnBigInteger::operator%(unsigned int num) const
{
    return BN_mod_word(fValue, num);
}

pnBigInteger pnBigInteger::operator<<(size_t amt) const
{
    pnBigInteger r(*this);
    BN_lshift(r.fValue, fValue, amt);
    return r;
}

pnBigInteger pnBigInteger::operator>>(size_t amt) const
{
    pnBigInteger r(*this);
    BN_rshift(r.fValue, fValue, amt);
    return r;
}

pnBigInteger& pnBigInteger::operator+=(const pnBigInteger& num)
{
    BN_add(fValue, fValue, num.fValue);
    return *this;
}

pnBigInteger& pnBigInteger::operator-=(const pnBigInteger& num)
{
    pnBigInteger left(*this);
    BN_sub(fValue, left.fValue, num.fValue);
    return *this;
}

pnBigInteger& pnBigInteger::operator*=(const pnBigInteger& num)
{
    BN_mul(fValue, fValue, num.fValue, fContext);
    return *this;
}

pnBigInteger& pnBigInteger::operator/=(const pnBigInteger& num)
{
    pnBigInteger left(*this);
    BN_div(fValue, nullptr, left.fValue, num.fValue, fContext);
    return *this;
}

pnBigInteger& pnBigInteger::operator%=(const pnBigInteger& num)
{
    pnBigInteger left(*this);
    BN_div(nullptr, fValue, left.fValue, num.fValue, fContext);
    return *this;
}

pnBigInteger& pnBigInteger::operator+=(unsigned int num)
{
    BN_add_word(fValue, num);
    return *this;
}

pnBigInteger& pnBigInteger::operator-=(unsigned int num)
{
    BN_sub_word(fValue, num);
    return *this;
}

pnBigInteger& pnBigInteger::operator*=(unsigned int num)
{
    BN_mul_word(fValue, num);
    return *this;
}

pnBigInteger& pnBigInteger::operator/=(unsigned int num)
{
    BN_div_word(fValue, num);
    return *this;
}

pnBigInteger& pnBigInteger::operator%=(unsigned int num)
{
    unsigned int value = BN_mod_word(fValue, num);
    BN_set_word(fValue, value);
    return *this;
}

pnBigInteger& pnBigInteger::operator<<=(size_t amt)
{
    BN_lshift(fValue, fValue, amt);
    return *this;
}

pnBigInteger& pnBigInteger::operator>>=(size_t amt)
{
    BN_rshift(fValue, fValue, amt);
    return *this;
}

pnBigInteger pnBigInteger::PowMod(const pnBigInteger& b, const pnBigInteger& mod) const
{
    pnBigInteger r;
    BN_mod_exp(r.fValue, fValue, b.fValue, mod.fValue, fContext);
    return r;
}

pnBigInteger pnBigInteger::DivMod(const pnBigInteger& div, pnBigInteger& rem) const
{
    pnBigInteger r;
    BN_div(r.fValue, rem.fValue, fValue, div.fValue, fContext);
    return r;
}

pnBigInteger pnBigInteger::Random(size_t bits)
{
    pnBigInteger r;
    BN_rand(r.fValue, bits, 0, 0);
    return r;
}
