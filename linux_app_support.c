#include <stdint.h>

typedef struct {
    uint8_t  e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
} bokj_elf_header;

void bokj_exec_elf(void* file_data) {
    bokj_elf_header* header = (bokj_elf_header*)file_data;

    if (header->e_ident[0] != 0x7F || header->e_ident[1] != 'E') return;

    void (*entry)() = (void (*)())header->e_entry;
    entry();
}
