#define BOKJ_SYSCALL_ETH_SEND 1

static inline void bokj_api_send(void* data, uint32_t size) {
    asm volatile ("int $0x80" : : "a"(BOKJ_SYSCALL_ETH_SEND), "b"(data), "c"(size));
}
