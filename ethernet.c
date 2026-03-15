#include <stdint.h>

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139

#define REG_RBSTART 0x30
#define REG_COMMAND 0x37
#define REG_IMR     0x3C
#define REG_ISR     0x3E
#define REG_RCR     0x44
#define REG_CONFIG1 0x52

#define CMD_RESET   0x10
#define CMD_RE      0x08
#define CMD_TE      0x04

static uint16_t io_addr;
static uint8_t rx_buffer[8192 + 16 + 1500]; 

extern void outb(uint16_t port, uint8_t data);
extern void outl(uint16_t port, uint32_t data);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);

void rtl8139_init(uint16_t pci_io_addr) {
    io_addr = pci_io_addr;

    outb(io_addr + REG_CONFIG1, 0x00);

    outb(io_addr + REG_COMMAND, CMD_RESET);
    while ((inb(io_addr + REG_COMMAND) & CMD_RESET) != 0);

    outl(io_addr + REG_RBSTART, (uint32_t)&rx_buffer);

    outw(io_addr + REG_IMR, 0x0005); 
    outl(io_addr + REG_RCR, 0xf | (1 << 7)); 

    outb(io_addr + REG_COMMAND, CMD_RE | CMD_TE);
}

void rtl8139_send_packet(void* data, uint32_t len) {
    static uint8_t tx_num = 0;
    uint16_t tsad_array[4] = {0x20, 0x24, 0x28, 0x2C};
    uint16_t tsd_array[4]  = {0x10, 0x14, 0x18, 0x1C};

    outl(io_addr + tsad_array[tx_num], (uint32_t)data);
    outl(io_addr + tsd_array[tx_num], len | 0x003F0000);

    tx_num++;
    if (tx_num > 3) tx_num = 0;
}
