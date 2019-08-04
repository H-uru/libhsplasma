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

#ifndef _PLASMA_VERSIONS_H
#define _PLASMA_VERSIONS_H

#include "PlasmaDefs.h"

//#define PlasmaVer unsigned int

/* PlasmaVer represents a specific or arbitrary Plasma version, sorted
 *   by Plasma version (e.g. 2.0) and engine revision (e.g. 63.12).
 * Arbitrary versions can be specified by client applications or suplemental
 *   add-on libraries, as well as via integer comparison, using the
 *   MAKE_VERSION macro.
 *
 * Current Plasma Versioning Range Limits:
 *   Plasma Major: 0-15 (4 bits)
 *   Plasma Minor: 0-15 (4 bits)
 *   Rev Major: 0-4096 (12 bits)
 *   Rev Minor: 0-4096 (12 bits)
 */

/* Utility stuff */
/*#define PLASMA_VER(ver) \
public:\
    void setEngineMajorVer(short maj) {\
        ver = (ver & 0x00FFFFFF) | ((maj & 0xFF) << 24);\
    }\
    void setEngineMinorVer(short min) {\
        ver = (ver & 0xFF00FFFF) | ((min & 0xFF) << 16);\
    }\
    void setMajorVer(short maj) {\
        short tmp = ((maj/10)<<4)+(maj%10);\
        ver = (ver & 0xFFFF00FF) | ((tmp & 0xFF) << 8);\
    }\
    void setMinorVer(short min) {\
        short tmp = ((min/10)<<4)+(min%10);\
        ver = (ver & 0xFFFFFF00) | (tmp & 0xFF);\
    }\
    bool safeVer() const {\
        switch(ver) {\
            case pvPrime:\
            case pvPots:\
            case pvLive:\
            case pvEoa:\
            case pvHex:\
            case pvUniversal:\
                return true;\
            default:\
                return false;\
        }\
    }\
    PlasmaVer getVer() const {\
        return ver;\
    }\
    virtual void setVer(PlasmaVer pv) {\
        ver = pv;\
    }
*/

#define MAKE_VERSION(plsMaj, plsMin, revMaj, revMin) \
    ((plsMaj << 28) | (plsMin << 24) | (revMaj << 12) | revMin)

class PLASMA_DLL PlasmaVer
{
public:
    /* These MUST remain in order for version matching to work */
    enum
    {
        pvUnknown   = 0,
        pvPrime     = MAKE_VERSION(2, 0, 63, 11),
        pvPots      = MAKE_VERSION(2, 0, 63, 12),
        pvMoul      = MAKE_VERSION(2, 0, 70,  0),
        pvEoa       = MAKE_VERSION(2, 1,  6, 10),
        pvHex       = MAKE_VERSION(3, 0,  0,  0),
        pvUniversal = -1,

        MASK_PLSMAJ = 0xF0000000,
        MASK_PLSMIN = 0xFF000000,
        MASK_REVMAJ = 0xFFFFF000,
        MASK_REVMIN = 0xFFFFFFFF,
    };

    PlasmaVer(int version = pvUnknown) : fVersion(version) { }
    void set(int version) { fVersion = version; }

    PlasmaVer& operator=(int version)
    {
        fVersion = version;
        return *this;
    }
    operator int() const { return fVersion; }

    int plsMajor() const { return (fVersion >> 28) & 0xF; }
    int plsMinor() const { return (fVersion >> 24) & 0xF; }
    int revMajor() const { return (fVersion >> 12) & 0xFFF; }
    int revMinor() const { return fVersion & 0xFFF; }

    bool isValid() const { return fVersion != pvUnknown; }
    bool isUniversal() const { return fVersion == pvUniversal; }

    bool isPrime() const { return fVersion == pvPrime; }
    bool isPots() const { return fVersion == pvPots; }
    bool isMoul() const { return fVersion == pvMoul; }
    bool isEoa() const { return fVersion == pvEoa; }
    bool isHexIsle() const { return fVersion == pvHex; }

    bool isUru() const { return (fVersion & MASK_PLSMIN) == MAKE_VERSION(2, 0, 0, 0); }
    bool isUruSP() const { return (fVersion & MASK_REVMAJ) <= MAKE_VERSION(2, 0, 63, 0) && isValid(); }
    bool isLive() const { return isUru() && !isUruSP(); }
    bool isNewPlasma() const { return (fVersion >= MAKE_VERSION(2, 1, 0, 0)) && !isUniversal(); }

    bool isSafeVer() const
    {
        return fVersion == pvPrime || fVersion == pvPots || fVersion == pvMoul
            || fVersion == pvEoa || fVersion == pvHex;
    }

    static const char* GetVersionName(PlasmaVer ver);
    static PlasmaVer GetSafestVersion(PlasmaVer ver);

private:
    int fVersion;
};

#endif
