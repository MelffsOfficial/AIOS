void kernel_print(const char* str, int x, int y, uint32_t color) {
    int i = 0;
    while (str[i] != '\0') {
        draw_char(str[i], x + (i * 8), y, color, 0x000000); // 0x000000 - черный фон
        i++;
    }
}
