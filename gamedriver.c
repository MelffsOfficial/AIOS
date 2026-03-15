#include <stdint.h>

#define BOKJ_VENDOR_ID 0x10EC
#define BOKJ_DEVICE_ID 0x8139

#define BOKJ_REG_RBSTART 0x30
#define BOKJ_REG_COMMAND 0x37
#define BOKJ_REG_IMR     0x3C
#define BOKJ_REG_ISR     0x3E
#define BOKJ_REG_RCR     0x44
#define BOKJ_REG_CONFIG1 0x52

#define BOKJ_CMD_RESET   0x10
#define BOKJ_CMD_RE      0x08
#define BOKJ_CMD_TE      0x04

static uint16_t bokj_io_port;
static uint8_t  bokj_rx_buffer[8192 + 16 + 1500] __attribute__((aligned(4)));

extern void     outb(uint16_t port, uint8_t data);
extern void     outw(uint16_t port, uint16_t data);
extern void     outl(uint16_t port, uint32_t data);
extern uint8_t  inb(uint16_t port);
extern uint16_t inw(uint16_t port);

void bokj_driver_init(uint16_t pci_bar) {
    bokj_io_port = pci_bar;

    outb(bokj_io_port + BOKJ_REG_CONFIG1, 0x00);

    outb(bokj_io_port + BOKJ_REG_COMMAND, BOKJ_CMD_RESET);
    while ((inb(bokj_io_port + BOKJ_REG_COMMAND) & BOKJ_CMD_RESET) != 0);

    outl(bokj_io_port + BOKJ_REG_RBSTART, (uint32_t)&bokj_rx_buffer);

    outw(bokj_io_port + BOKJ_REG_IMR, 0x0005);
    outl(bokj_io_port + BOKJ_REG_RCR, 0xf | (1 << 7));

    outb(bokj_io_port + BOKJ_REG_COMMAND, BOKJ_CMD_RE | BOKJ_CMD_TE);
}

void bokj_transmit_packet(void* packet_data, uint32_t packet_len) {
    static uint8_t tx_id = 0;
    uint16_t tsad_reg[4] = {0x20, 0x24, 0x28, 0x2C};
    uint16_t tsd_reg[4]  = {0x10, 0x14, 0x18, 0x1C};

    outl(bokj_io_port + tsad_reg[tx_id], (uint32_t)packet_data);
    outl(bokj_io_port + tsd_reg[tx_id], packet_len | 0x003F0000);

    tx_id = (tx_id + 1) % 4;
}

uint16_t bokj_check_status() {
    uint16_t status = inw(bokj_io_port + BOKJ_REG_ISR);
    outw(bokj_io_port + BOKJ_REG_ISR, status); 
    return status;
}
