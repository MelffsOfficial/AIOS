#include "font.h"

// Данные о видеорежиме (передаются из загрузчика)
uint32_t* framebuffer = (uint32_t*)0xFD000000; 
int screen_pitch = 1024; // Ширина экрана в пикселях

void draw_char(unsigned short int c, int cx, int cy, uint32_t fg, uint32_t bg) {
    psf1_header_t* font_hdr = (psf1_header_t*)_binary_font_psf_start;
    
    // Получаем адрес начала битмапа символа
    // charsize обычно 16 байт на символ для шрифта 8x16
    unsigned char* glyph = (unsigned char*)_binary_font_psf_start + 
                           sizeof(psf1_header_t) + 
                           (c * font_hdr->charsize);

    for (int y = 0; y < font_hdr->charsize; y++) {
        for (int x = 0; x < 8; x++) {
            // Проверяем бит (слева направо)
            if ((*glyph & (0b10000000 >> x))) {
                framebuffer[(cy + y) * screen_pitch + (cx + x)] = fg;
            } else {
                framebuffer[(cy + y) * screen_pitch + (cx + x)] = bg;
            }
        }
        glyph++; // Переходим к следующему байту (строке пикселей)
    }
}
