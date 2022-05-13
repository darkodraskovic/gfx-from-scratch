#include "Viewport.h"

#include "../Renderer/display.h"
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

Vector2 viewportCanvasRatio;
Vector3 eye = {-2, 2, -5};

static inline Vector3 canvasToViewport(int canvasX, int canvasY) {
  return (Vector3){canvasX * viewportCanvasRatio.x,
                   canvasY * viewportCanvasRatio.y, 1.0};
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

  // viewport left/bottom = -.5, right/top = .5
  viewportCanvasRatio.x = 1.0 / canvas.width;
  viewportCanvasRatio.y = 1.0 / canvas.height;
}

void Rt_Render(Rt_Scene* scene) {
  static float angle = 0;
  angle = angle + 0.001;
  eye.z += angle * .1;

  for (int x = canvas.left; x < canvas.right; x++) {
    for (int y = canvas.top; y < canvas.bottom; y++) {
      Quaternion q = QuaternionFromEuler(PI / 8, angle, 0);
      Vector3 direction = Vector3RotateByQuaternion(canvasToViewport(x, y), q);

      Color color = Rt_TraceRay(scene, eye, direction, 1, INFINITY, 3);
      SetPixel(x + canvas.halfWidth,
               canvas.heightMinusOne - (y + canvas.halfHeight),
               ColorToUnsignedInt(color));
    }
  }
}
