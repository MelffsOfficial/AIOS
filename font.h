// font.h
typedef struct {
    unsigned char magic[2];     // 0x36, 0x04 для PSF1
    unsigned char mode;
    unsigned char charsize;     // Высота символа (например, 16)
} psf1_header_t;

// В реальности это будет огромный массив данных в отдельном файле
extern unsigned char _binary_font_psf_start[];
