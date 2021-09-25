#ifndef DISPLAY_H
#define DISPLAY_H

#include <raylib.h>

extern int pixelSize;
extern int screenWidth;
extern int screenHeight;

void InitRenderer();
int Run();
void SetPixel(unsigned int x, unsigned int y, unsigned int color);

#endif /* DISPLAY_H */

