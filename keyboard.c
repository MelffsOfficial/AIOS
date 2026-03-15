#include <stdint.h>

#define BOKJ_KBD_DATA 0x60
#define BOKJ_KBD_STAT 0x64

extern uint8_t inb(uint16_t port);

static const char bokj_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' '	/* Space bar */
};

char bokj_kbd_read() {
    if (inb(BOKJ_KBD_STAT) & 0x01) {
        uint8_t scancode = inb(BOKJ_KBD_DATA);
        if (scancode < 128) {
            return bokj_map[scancode];
        }
    }
    return 0;
}
