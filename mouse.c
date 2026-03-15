#include <stdint.h>

#define BOKJ_MS_DATA 0x60
#define BOKJ_MS_STAT 0x64
#define BOKJ_MS_CMD  0x64

extern void outb(uint16_t port, uint8_t data);
extern uint8_t inb(uint16_t port);

void bokj_ms_wait(uint8_t type) {
    uint32_t timeout = 100000;
    while (timeout--) {
        if (type == 0 && (inb(BOKJ_MS_STAT) & 1)) return;
        if (type == 1 && !(inb(BOKJ_MS_STAT) & 2)) return;
    }
}

void bokj_ms_write(uint8_t data) {
    bokj_ms_wait(1);
    outb(BOKJ_MS_CMD, 0xD4);
    bokj_ms_wait(1);
    outb(BOKJ_MS_DATA, data);
}

void bokj_mouse_init() {
    uint8_t status;
    bokj_ms_wait(1);
    outb(BOKJ_MS_CMD, 0xA8);
    bokj_ms_wait(1);
    outb(BOKJ_MS_CMD, 0x20);
    bokj_ms_wait(0);
    status = (inb(BOKJ_MS_DATA) | 2);
    bokj_ms_wait(1);
    outb(BOKJ_MS_CMD, 0x60);
    bokj_ms_wait(1);
    outb(BOKJ_MS_DATA, status);
    bokj_ms_write(0xF4);
}
