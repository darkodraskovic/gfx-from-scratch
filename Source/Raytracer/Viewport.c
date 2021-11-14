#include "Viewport.h"

#include "../Renderer/Display.h"
#include "Raytracer.h"

struct {
  int left;
  int right;
  int top;
  int bottom;
  int width;
  int height;
  int heightMinusOne;
  int halfWidth;
  int halfHeight;
} canvas;

/* Rectangle viewport = (Rectangle){-.5, -.5, 1, 1}; */
Vector2 viewportCanvasRatio;
Vector3 origin = (Vector3){0, 0, 0};
Vector3 direction = {0, 0, 1};

static inline void canvasToViewport(int canvasX, int canvasY) {
  direction.x = canvasX * viewportCanvasRatio.x;
  direction.y = canvasY * viewportCanvasRatio.y;
}

void Rt_InitCanvas(int scrW, int scrH) {
  canvas.left = -scrW / 2;
  canvas.top = -scrH / 2;
  canvas.right = canvas.left + scrW;
  canvas.bottom = canvas.top + scrH;
  canvas.width = scrW;
  canvas.height = scrH;
  canvas.heightMinusOne = scrH - 1;
  canvas.halfWidth = scrW / 2;
  canvas.halfHeight = scrH / 2;

  /* viewportCanvasRatio.x = viewport.width / canvas.width; */
  /* viewportCanvasRatio.y = viewport.height / canvas.height; */
  viewportCanvasRatio.x = 1.0 / canvas.width;
  viewportCanvasRatio.y = 1.0 / canvas.height;
}

void Rt_Render(Rt_Scene* scene) {
  for (int x = canvas.left; x < canvas.right; x++) {
    for (int y = canvas.top; y < canvas.bottom; y++) {
      canvasToViewport(x, y);
      Color color = Rt_TraceRay(scene, origin, direction, 1, INFINITY, 2);
      SetPixel(x + canvas.halfWidth,
               canvas.heightMinusOne - (y + canvas.halfHeight),
               ColorToUnsignedInt(color));
    }
  }
}
