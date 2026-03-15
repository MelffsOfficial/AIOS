#include <stdint.h>

typedef struct {
    uint32_t signature;
    uint16_t machine;
    uint16_t sections;
    uint32_t timestamp;
    uint32_t symbols;
    uint32_t num_symbols;
    uint16_t opt_size;
    uint16_t flags;
} bokj_pe_t;

void bokj_load_exe(void* data) {
    uint32_t offset = *(uint32_t*)((uint8_t*)data + 0x3C);
    bokj_pe_t* pe = (bokj_pe_t*)((uint8_t*)data + offset);
    
    if (pe->signature == 0x4550) {
        uint32_t entry = *(uint32_t*)((uint8_t*)pe + 24 + 16);
        void (*start)() = (void (*)())(entry);
        start();
    }
}
