#include <raylib.h>
#include <stdlib.h>

#include "Display.h"
#include "Hooks.h"

Image image;
unsigned int* buffer;
Texture2D texture;
int width;
int scale;


void InitRenderer(DisplayConfig displayConfig) {
    InitWindow(displayConfig.width * displayConfig.scale,
               displayConfig.height * displayConfig.scale,
               displayConfig.windowTitle);
    
    SetTargetFPS(60);

    image = GenImageColor(displayConfig.width, displayConfig.height, BLACK);
    buffer = image.data;
    texture = LoadTextureFromImage(image);

    width = displayConfig.width;
    scale = displayConfig.scale;
}

void SetPixel(unsigned int x, unsigned int y, unsigned int color) {
    *(buffer + y * width + x) = color;
}

int Run(DisplayConfig displayConfig) {
    InitRenderer(displayConfig);

    while (!WindowShouldClose()) {
        Update(); // hook
        PostUpdate(); // hook
        
        BeginDrawing();

        // clear buffer
        ImageClearBackground(&image, BLACK);

        Draw(); // hook

        // draw buffer
        UpdateTexture(texture, buffer);
        DrawTextureEx(texture, (Vector2){0, 0}, 0, scale, WHITE);

        PostDraw(); // hook
        
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
