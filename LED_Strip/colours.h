#define COL_RED 0xff0000
#define COL_GREEN 0x00ff00
#define COL_BLUE 0x0000ff

#define HEX_TO_RED(colour) (uint8_t)(colour >> 16)
#define HEX_TO_GREEN(colour) (uint8_t)(colour >> 8) & 0xff
#define HEX_TO_BLUE(colour) (uint8_t)colour & 0x0000ff