#include "Viewport.h"

#include "../Renderer/Display.h"
#include "Raytracer.h"

Rt_IntRect canvas;
Rectangle viewport = (Rectangle){-.5, -.5, 1, 1};

Vector3 Rt_CanvasToViewport(int canvasX, int canvasY) {
  return (Vector3){canvasX * (viewport.width / canvas.width),
                   canvasY * (viewport.height / canvas.height), 1};
}

void Rt_InitCanvas(int scrW, int scrH) {
  canvas.x = -scrW / 2;
  canvas.y = -scrH / 2;
  canvas.width = scrW;
  canvas.height = scrH;
}

void Rt_Render(Rt_Scene* scene) {
  for (int x = canvas.x; x < canvas.x + canvas.width; x++) {
    for (int y = canvas.y; y < canvas.y + canvas.height; y++) {
      Vector3 direction = Rt_CanvasToViewport(x, y);
      unsigned int color =
          Rt_TraceRay(scene, (Vector3){0, 0, 0}, direction, 1, INFINITY);
      SetPixel(x + canvas.width / 2,
               (canvas.height - 1) - (y + canvas.height / 2), color);
    }
  }
}
