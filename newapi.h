#ifndef BOKJ_API_H
#define BOKJ_API_H

void bokj_load_elf(void* data);
void bokj_load_exe(void* data);
extern void bokj_context_switch(uint32_t entry);

#endif
