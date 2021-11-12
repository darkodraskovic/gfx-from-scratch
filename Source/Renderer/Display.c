#include "Display.h"

#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#include "Hooks.h"

/* Image image; */
unsigned int* drawBuffer;
unsigned int* clearBuffer;
Texture2D texture;
int width;
int scale;
int bufferSize;

void InitRenderer(DisplayConfig displayConfig) {
  InitWindow(displayConfig.width * displayConfig.scale,
             displayConfig.height * displayConfig.scale,
             displayConfig.windowTitle);

  SetTargetFPS(60);

  Image image = GenImageColor(displayConfig.width, displayConfig.height, BLACK);
  drawBuffer = image.data;
  image = GenImageColor(displayConfig.width, displayConfig.height, BLACK);
  clearBuffer = image.data;
  texture = LoadTextureFromImage(image);

  width = displayConfig.width;
  scale = displayConfig.scale;
  bufferSize = width * displayConfig.height * sizeof(unsigned int);
}

void SetPixel(unsigned int x, unsigned int y, unsigned int color) {
  *(drawBuffer + y * width + x) = color;
}

static inline void clearBackground() {
  memcpy(drawBuffer, clearBuffer, bufferSize);
}

int Run(DisplayConfig displayConfig) {
  InitRenderer(displayConfig);
  Init();

  while (!WindowShouldClose()) {
    Update();      // hook
    PostUpdate();  // hook

    clearBackground();

    BeginDrawing();

    // set buffer values
    Draw();  // hook

    // draw buffer
    UpdateTexture(texture, drawBuffer);
    DrawTextureEx(texture, (Vector2){0, 0}, 0, scale, WHITE);

    PostDraw();  // hook

    EndDrawing();
  }

  Close();
  CloseWindow();  // Close window and OpenGL context

  return 0;
}
