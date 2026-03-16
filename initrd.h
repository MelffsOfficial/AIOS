#ifndef BOKJ_INITRD_H
#define BOKJ_INITRD_H

#include <stdint.h>
#include "vfs.h"

// Структура заголовка TAR (UStar)
typedef struct {
    char name[100];     // Имя файла
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];     // Размер в восьмеричном формате
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];      // "ustar"
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
} __attribute__((packed)) bokj_tar_header_t;

typedef struct {
    uint32_t n_files;
    bokj_node_t* root_node;
} bokj_initrd_t;

// Инициализация системы из адреса в памяти
bokj_node_t* bokj_initrd_init(uint32_t location);

#endif
