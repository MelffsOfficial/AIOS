#include <stdint.h>

typedef struct {
    uint8_t  e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
} bokj_elf_t;

void bokj_load_elf(void* data) {
    bokj_elf_t* elf = (bokj_elf_t*)data;
    if (elf->e_ident[0] == 0x7F && elf->e_ident[1] == 'E') {
        void (*entry)() = (void (*)())elf->e_entry;
        entry();
    }
}
