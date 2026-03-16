#include "initrd.h"
#include <string.h>

static bokj_node_t *initrd_root;
static bokj_node_t *initrd_dev;
static bokj_node_t *root_nodes;
static uint32_t n_root_nodes;

// Вспомогательная функция: перевод восьмеричного текста в число
static uint32_t oct2bin(char *str, int size) {
    uint32_t n = 0;
    char *c = str;
    while (size-- > 0 && *c) {
        n <<= 3;
        n += *c - '0';
        c++;
    }
    return n;
}

// Реализация функции чтения для VFS
static uint32_t initrd_read(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    bokj_tar_header_t *header = (bokj_tar_header_t*)node->ptr;
    uint32_t file_size = oct2bin(header->size, 11);
    
    if (offset >= file_size) return 0;
    if (offset + size > file_size) size = file_size - offset;
    
    // Данные файла находятся сразу после заголовка (512 байт)
    uint8_t *file_data = (uint8_t*)header + 512;
    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = file_data[offset + i];
    }
    return size;
}

bokj_node_t* bokj_initrd_init(uint32_t location) {
    uint32_t address = location;
    initrd_root = (bokj_node_t*)0; // Здесь должна быть логика аллокации из твоего ядра
    
    // Временный массив для хранения найденных файлов (для дистрибутива)
    // В реальном ядре здесь используется kmalloc
    static bokj_node_t bokj_nodes[64]; 
    uint32_t node_count = 0;

    while (1) {
        bokj_tar_header_t *header = (bokj_tar_header_t*)address;
        
        // Проверка на конец архива (пустой заголовок)
        if (header->name[0] == '\0') break;

        uint32_t size = oct2bin(header->size, 11);
        
        // Создаем узел VFS для каждого файла
        for(int i=0; i<100; i++) bokj_nodes[node_count].name[i] = header->name[i];
        
        bokj_nodes[node_count].mask = 0;
        bokj_nodes[node_count].uid = 0;
        bokj_nodes[node_count].gid = 0;
        bokj_nodes[node_count].length = size;
        bokj_nodes[node_count].flags = BOKJ_FS_FILE;
        bokj_nodes[node_count].read = &initrd_read;
        bokj_nodes[node_count].write = 0;
        bokj_nodes[node_count].ptr = (struct bokj_node*)header;

        node_count++;
        
        // Переходим к следующему заголовку (заголовок 512 + данные, выровненные по 512)
        address += ((size / 512) + 1) * 512;
        if (size % 512 != 0) address += 512;
        
        if (node_count >= 64) break; // Лимит демо-версии
    }

    n_root_nodes = node_count;
    return &bokj_nodes[0];
}
