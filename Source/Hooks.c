#include "Raytracer/Hooks.h"

#include "Config.h"
#include "Renderer/Hooks.h"

void Init() { Rt_Init(displayConfig.width, displayConfig.height); }

void Update() {}

void PostUpdate(){

};

int x = 0;
int y = 0;
void Draw() {
  Rt_Draw();
  /* SetPixel(x++ % displayConfig.width, y++ % displayConfig.height,
   * 0xff0000ff); */
}

void PostDraw() { DrawFPS(32, 32); };

void Close(){};
