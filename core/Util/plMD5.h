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

#include "Stream/hsStream.h"
#include <string_theory/string>

class PLASMA_DLL plMD5Hash
{
public:
    unsigned int fHash[4];

public:
    plMD5Hash();
    plMD5Hash(const char* hex) { fromHex(hex); }
    bool operator==(const plMD5Hash& cmp) const;
    bool operator!=(const plMD5Hash& cmp) const;

    ST::string toHex() const;
    void fromHex(const char* hex);
    void read(hsStream* S);
    void write(hsStream* S) const;
};

class PLASMA_DLL plMD5
{
private:
    static const unsigned int kShiftArray[4][4];
    static const unsigned int kBaseArray[64];
    static const unsigned char kPadArray[64];

    unsigned int fA, fB, fC, fD;

public:
    static plMD5Hash hashStream(hsStream* S);
    static plMD5Hash hashFile(const char* filename);
    static plMD5Hash hashString(const ST::string& str);

private:
    plMD5();
    void processBlock(const unsigned char* block);
};
