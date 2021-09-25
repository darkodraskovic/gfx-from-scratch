#include "Chip8/Chip8.h"
#include "Renderer/Renderer.h"

Vector2 pos = {0, 0};
int count = 0;

void Update() {
    pos.x = (int)(++pos.x) % CHIP8_WIDTH;
    pos.y = (int)(++pos.y) % CHIP8_HEIGHT;
}

void PostUpdate() {
    
};

void Draw() {
    SetPixel(pos.x, pos.y, 0xffff00ff);
}

void PostDraw() {
    DrawFPS(32, 32);    
};
