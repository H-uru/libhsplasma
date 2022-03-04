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

#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <cstdint>

#ifdef _MSC_VER
    #define ENDSWAP16(val) _byteswap_ushort(val)
    #define ENDSWAP32(val) _byteswap_ulong(val)
    #define ENDSWAP64(val) _byteswap_uint64(val)
#elif defined(__llvm__) || (defined(__GNUC__) && ((__GNUC__ * 100) + __GNUC_MINOR__) >= 408)
    #define ENDSWAP16(val) __builtin_bswap16(val)
    #define ENDSWAP32(val) __builtin_bswap32(val)
    #define ENDSWAP64(val) __builtin_bswap64(val)
#else
    inline uint16_t ENDSWAP16(uint16_t val) {
        return ((val & 0x00FFU) << 8 | (val & 0xFF00U) >> 8);
    }
    inline uint32_t ENDSWAP32(uint32_t val) {
        return ((val & 0x000000FFU) << 24 | (val & 0x0000FF00U) << 8 |
                (val & 0x00FF0000U) >> 8  | (val & 0xFF000000U) >> 24);
    }
    inline uint64_t ENDSWAP64(uint64_t val) {
        return ((val & UINT64_C(0x00000000000000FF)) << 56 |
                (val & UINT64_C(0x000000000000FF00)) << 40 |
                (val & UINT64_C(0x0000000000FF0000)) << 24 |
                (val & UINT64_C(0x00000000FF000000)) << 8  |
                (val & UINT64_C(0x000000FF00000000)) >> 8  |
                (val & UINT64_C(0x0000FF0000000000)) >> 24 |
                (val & UINT64_C(0x00FF000000000000)) >> 40 |
                (val & UINT64_C(0xFF00000000000000)) >> 56 );
    }
#endif

inline float ENDSWAPF(float val)
{
    union
    {
        float fv;
        uint32_t fb;
    } conv;
    conv.fv = val;
    conv.fb = ENDSWAP32(conv.fb);
    return conv.fv;
}

inline double ENDSWAPD(double val)
{
    union
    {
        double fv;
        uint64_t fb;
    } conv;
    conv.fv = val;
    conv.fb = ENDSWAP64(conv.fb);
    return conv.fv;
}

#if defined(MACOSX) && defined(__BIG_ENDIAN__)
    #define WORDS_BIGENDIAN
#endif

#ifdef WORDS_BIGENDIAN
    #define LESWAP16(val) ENDSWAP16(val)
    #define BESWAP16(val) (val)
    #define LESWAP32(val) ENDSWAP32(val)
    #define BESWAP32(val) (val)
    #define LESWAP64(val) ENDSWAP64(val)
    #define BESWAP64(val) (val)
    #define LESWAPF(val)  ENDSWAPF(val)
    #define BESWAPF(val)  (val)
    #define LESWAPD(val)  ENDSWAPD(val)
    #define BESWAPD(val)  (val)
#else
    #define LESWAP16(val) (val)
    #define BESWAP16(val) ENDSWAP16(val)
    #define LESWAP32(val) (val)
    #define BESWAP32(val) ENDSWAP32(val)
    #define LESWAP64(val) (val)
    #define BESWAP64(val) ENDSWAP64(val)
    #define LESWAPF(val)  (val)
    #define BESWAPF(val)  ENDSWAPF(val)
    #define LESWAPD(val)  (val)
    #define BESWAPD(val)  ENDSWAPD(val)
#endif

#ifdef _MSC_VER
    #define snprintf _snprintf
    #define strcasecmp _stricmp
    #define wcscasecmp _wcsicmp
    #define PATHSEP '\\'
    #define PATHSEPSTR "\\"
#else
    #define PATHSEP '/'
    #define PATHSEPSTR "/"
#endif

enum plKeyDef
{
    KEY_A = 'A', KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
    KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
    KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
    KEY_0 = '0', KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_F1 = 0x70, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
    KEY_F9, KEY_F10, KEY_F11, KEY_F12,
    KEY_ESCAPE = 0x1B, KEY_TAB = 0x9, KEY_SHIFT = 0x10, KEY_CTRL, KEY_ALT,
    KEY_UP = 0x26, KEY_DOWN = 0x28, KEY_LEFT = 0x25, KEY_RIGHT = 0x27,
    KEY_BACKSPACE = 0x8, KEY_ENTER = 0xD, KEY_PAUSE = 0x13, KEY_CAPSLOCK = 0x14,
    KEY_PAGEUP = 0x21, KEY_PAGEDOWN = 0x22, KEY_END = 0x23, KEY_HOME = 0x24,
    KEY_PRINTSCREEN = 0x2C, KEY_INSERT = 0x2D, KEY_DELETE = 0x2E,
    KEY_NUMPAD0 = 0x60, KEY_NUMPAD1, KEY_NUMPAD2, KEY_NUMPAD3, KEY_NUMPAD4,
    KEY_NUMPAD5, KEY_NUMPAD6, KEY_NUMPAD7, KEY_NUMPAD8, KEY_NUMPAD9,
    KEY_NUMPAD_MULTIPLY = 0x6A, KEY_NUMPAD_ADD = 0x6B,
    KEY_NUMPAD_SUBTRACT = 0x6D, KEY_NUMPAD_PERIOD = 0x6E,
    KEY_NUMPAD_DIVIDE = 0x6F, KEY_SPACE = ' ', KEY_COMMA = 0xBC,
    KEY_PERIOD = 0xBE, KEY_DASH = 0xBD, KEY_EQUAL = 0xBB, KEY_SEMICOLON = 0xBA,
    KEY_SLASH = 0xBF, KEY_TILDE = 0xC0, KEY_LBRACKET = 0xDB,
    KEY_BACKSLASH = 0xDC, KEY_RBRACKET = 0xDD, KEY_QUOTE = 0xDE,
    KEY_UNMAPPED = 0xFF
};

#endif
