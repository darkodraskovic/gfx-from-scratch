#include <raylib.h>

#include "Display.h"
#include "Hooks.h"

int pixelSize;
int screenWidth = 320;
int screenHeight = 200;

Image image;
unsigned int* buffer;
Texture2D texture;


void InitRenderer() {
    pixelSize = 3;
    InitWindow(screenWidth * pixelSize, screenHeight * pixelSize, "Renderer");
    
    SetTargetFPS(60);

    image = GenImageColor(screenWidth, screenHeight, BLACK);
    buffer = image.data;
    texture = LoadTextureFromImage(image);
}

void SetPixel(unsigned int x, unsigned int y, unsigned int color) {
    *(buffer + y * screenWidth + x) = color;
}

int Run() {
    Init(); // hook
    InitRenderer();
    PostInit(); // hook

    while (!WindowShouldClose()) {
        Update(); // hook
        PostUpdate(); // hook
        
        BeginDrawing();

        // clear buffer
        ImageClearBackground(&image, BLACK);

        Draw(); // hook

        // draw buffer
        UpdateTexture(texture, buffer);
        DrawTextureEx(texture, (Vector2){0, 0}, 0, pixelSize, WHITE);

        PostDraw(); // hook
        
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
