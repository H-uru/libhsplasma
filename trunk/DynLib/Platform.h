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
