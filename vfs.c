#include "vfs.h"

bokj_node_t *fs_root = 0;

uint32_t read_fs(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    if (node->read != 0) {
        return node->read(node, offset, size, buffer);
    }
    return 0;
}

uint32_t write_fs(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    if (node->write != 0) {
        return node->write(node, offset, size, buffer);
    }
    return 0;
}
