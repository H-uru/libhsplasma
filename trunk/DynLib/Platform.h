#ifndef _PLATFORM_H
#define _PLATFORM_H

#define ENDSWAP32(val) \
    ((val & 0x000000FF) << 24 | (val & 0x0000FF00) << 8 | \
     (val & 0x00FF0000) >> 8  | (val & 0xFF000000) >> 24)
#define ENDSWAP16(val) \
    ((val & 0x00FF) << 8 | (val & 0xFF00) >> 8)

#ifdef WORDS_BIGENDIAN
    #define LESWAP32(val) ENDSWAP32(val)
    #define BESWAP32(val) (val)
    #define LESWAP16(val) ENDSWAP16(val)
    #define BESWAP16(val) (val)
#else
    #define LESWAP32(val) (val)
    #define BESWAP32(val) ENDSWAP32(val)
    #define LESWAP16(val) (val)
    #define BESWAP16(val) ENDSWAP16(val)
#endif

#ifdef WIN32
	#define snprintf _snprintf
    #define PATHSEP '\\'   
#else
    #define PATHSEP '/'
#endif

enum plKeyDef {
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
