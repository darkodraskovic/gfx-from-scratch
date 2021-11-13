#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct {
  int scale;
  int width;
  int height;
  char* windowTitle;
} DisplayConfig;

int Run();

void SetPixel(unsigned int x, unsigned int y, unsigned int color);

#endif /* DISPLAY_H */
