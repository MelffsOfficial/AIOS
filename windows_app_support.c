typedef struct {
    uint16_t signature;
    uint16_t machine;
    uint16_t num_sections;
    uint32_t timestamp;
    uint32_t sym_table;
    uint32_t num_sym;
    uint16_t opt_header_size;
    uint16_t characteristics;
} bokj_pe_header;

void bokj_exec_exe(void* file_data) {
    uint32_t pe_offset = *(uint32_t*)((uint8_t*)file_data + 0x3C);
    bokj_pe_header* pe = (bokj_pe_header*)((uint8_t*)file_data + pe_offset);

    if (pe->signature != 0x4550) return; // "PE\0\0"

    uint32_t entry_addr = *(uint32_t*)((uint8_t*)pe + 24 + 16); 
    void (*entry)() = (void (*)())(entry_addr);
    entry();
}
