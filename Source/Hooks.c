#include <raylib.h>

#include "Hooks.h"
#include "Display.h"

Vector2 pos = {0, 0};
int count = 0;

void Init() {
    
}

void PostInit() {
    
}

void Update() {
    pos.x = (int)(++pos.x) % screenHeight;
    pos.y = (int)(++pos.y) % screenHeight;
}

void PostUpdate() {
    
};

void Draw() {
    SetPixel(pos.x, pos.y, 0xffff00ff);
}

void PostDraw() {
    DrawFPS(32, 32);    
};
