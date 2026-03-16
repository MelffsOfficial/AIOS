#include "vfs.h"

uint32_t null_read(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    return 0; // /dev/null всегда возвращает 0 байт
}

uint32_t null_write(bokj_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    return size; // Принимает любые данные и "сжигает" их
}

void bokj_init_null() {
    // Регистрация устройства в дереве VFS
    // Это позволит программам в дистрибутивах писать в никуда
}
