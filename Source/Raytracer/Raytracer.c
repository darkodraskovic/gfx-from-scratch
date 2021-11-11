#include "Raytracer.h"

#include "../Util/Util.h"

Vector3 Rt_origin = {0, 0, 0};
Rt_IntRect Rt_canvas;
Rectangle Rt_viewport = (Rectangle){-.5, -.5, 1, 1};
Rt_Scene Rt_scene;

Vector3 Rt_CanvasToViewport(int canvasX, int canvasY) {
  return (Vector3){canvasX * (Rt_viewport.width / Rt_canvas.width),
                   canvasY * (Rt_viewport.height / Rt_canvas.height), 1};
}

Vector2 Rt_IntersectRaySphere(Vector3 origin, Vector3 direction,
                              Rt_Sphere sphere) {
  float r = sphere.radius;
  Vector3 CO = Vector3Subtract(origin, sphere.center);

  float a = Vector3DotProduct(direction, direction);
  float b = 2 * Vector3DotProduct(CO, direction);
  float c = Vector3DotProduct(CO, CO) - r * r;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return (Vector2){INFINITY, INFINITY};
  float t1 = (-b + sqrt(discriminant)) / (2 * a);
  float t2 = (-b - sqrt(discriminant)) / (2 * a);

  return (Vector2){t1, t2};
}

unsigned int Tr_TraceRay(Vector3 origin, Vector3 direction, float minT,
                         float maxT) {
  float closestT = INFINITY;
  Rt_Sphere* closestSphere = NULL;

  for (int i = 0; i < arrSize(Rt_scene.spheres); ++i) {
    Vector2 t = Rt_IntersectRaySphere(origin, direction, Rt_scene.spheres[i]);
    if (t.x < closestT && t.x > minT && t.x < maxT) {
      closestT = t.x;
      closestSphere = &Rt_scene.spheres[i];
    }
    if (t.y < closestT && t.y > minT && t.y < maxT) {
      closestT = t.y;
      closestSphere = &Rt_scene.spheres[i];
    }
  }
  if (!closestSphere) {
    return 0xffffffff;
  }
  return closestSphere->color;
}

void Rt_Init(int scrW, int scrH) {
  Rt_canvas.x = -scrW / 2;
  Rt_canvas.y = -scrH / 2;
  Rt_canvas.width = scrW;
  Rt_canvas.height = scrH;

  Rt_scene.spheres = arrCreate(3, sizeof(Rt_Sphere));
}

void Rt_Draw() {
  for (int x = Rt_canvas.x; x < Rt_canvas.x + Rt_canvas.width; x++) {
    for (int y = Rt_canvas.y; y < Rt_canvas.y + Rt_canvas.height; y++) {
      Vector3 direction = Rt_CanvasToViewport(x, y);
      unsigned int color = Tr_TraceRay(Rt_origin, direction, 1, INFINITY);
      SetPixel(x + Rt_canvas.width / 2,
               (Rt_canvas.height - 1) - (y + Rt_canvas.height / 2), color);
    }
  }
}
