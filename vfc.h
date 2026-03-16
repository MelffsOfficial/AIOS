#ifndef BOKJ_VFS_H
#define BOKJ_VFS_H

#include <stdint.h>

#define BOKJ_FS_FILE 0x01
#define BOKJ_FS_DIR  0x02

struct bokj_node;

typedef uint32_t (*read_type_t)(struct bokj_node*, uint32_t, uint32_t, uint8_t*);
typedef uint32_t (*write_type_t)(struct bokj_node*, uint32_t, uint32_t, uint8_t*);

typedef struct bokj_node {
    char name[128];
    uint32_t mask;
    uint32_t uid;
    uint32_t gid;
    uint32_t flags;
    uint32_t length;
    read_type_t read;
    write_type_t write;
    struct bokj_node *ptr; // Для вложенных структур
} bokj_node_t;

extern bokj_node_t *fs_root; 

uint32_t read_fs(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
uint32_t write_fs(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

#endif
