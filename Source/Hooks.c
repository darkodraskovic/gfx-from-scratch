#include "Raytracer/Hooks.h"

#include "Config.h"
#include "Renderer/Hooks.h"

void Init() { Rt_Init(displayConfig.width, displayConfig.height); }

void Update() {}

void PostUpdate(){

};

void Draw() { Rt_Draw(); }

void PostDraw() { DrawFPS(32, 32); };

void Close(){};
