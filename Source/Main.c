#include "Chip8/Chip8.h"
#include "Renderer/Renderer.h"

int main(void) {
    DisplayConfig displayConfig = {
        .scale = 10,
        .width = CHIP8_WIDTH,
        .height = CHIP8_HEIGHT,
        .windowTitle = "Chip8 Emulator",
    };
    
    return Run(displayConfig);
}

