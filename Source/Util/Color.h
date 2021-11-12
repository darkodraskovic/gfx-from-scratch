#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// 0xAABBGGRR
typedef uint32_t color_t;

#define COL_MASK_R 0x000000FF
#define COL_MASK_G 0x0000FF00
#define COL_MASK_B 0x00FF0000
#define COL_MASK_A 0xFF000000

// #define BLACK (color_t)0xFF000000
// #define WHITE (color_t)0xFFFFFFFF
// #define GREY (color_t)0xFF777777
// #define RED (color_t)0xFF0000FF
// #define GREEN (color_t)0xFF00FF00
// #define BLUE (color_t)0xFFFF0000
// #define YELLOW (color_t)0xFF00FFFF
// #define MAGENTA (color_t)0xFFFF00FF
// #define CYAN (color_t)0xFFFFFF00

color_t SetColorBrightness(color_t color, float percent);

#endif /* COLOR_H */
