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

#define PlasmaVer unsigned int

/* Utility stuff */
#define PLASMA_VER(ver) \
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

/* These MUST remain in order for version matching to work */
enum SafePlasmaVer {
    pvUnknown   = 0,
    pvPrime     = 0x02006311,   // 2.0 r63.11
    pvPots      = 0x02006312,   // 2.0 r63.12
    pvLive      = 0x02007000,   // 2.0 r70
    pvEoa       = 0x02010610,   // 2.1 r6.10
    pvHex       = 0x03000000,   // 3.0
    pvUniversal = 0x7FFFFFFF,   // Maps 1:1 with libHSPlasma mappings
};

const char* GetVersionName(PlasmaVer ver);

PlasmaVer GetSafestVersion(PlasmaVer ver);

#endif
