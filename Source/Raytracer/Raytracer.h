#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../Renderer/Renderer.h"

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Rt_IntRect;

typedef struct {
  Vector3 center;
  float radius;
  unsigned int color;
} Rt_Sphere;

typedef struct {
  Rt_Sphere* spheres;
} Rt_Scene;

extern Rt_Scene Rt_scene;
extern Vector3 Rt_origin;
extern Rt_IntRect Rt_canvas;
extern Rectangle Rt_viewport;

Vector3 Rt_CanvasToViewport(int canvasX, int canvasY);

Vector2 Rt_IntersectRaySphere(Vector3 origin, Vector3 direction,
                              Rt_Sphere sphere);

unsigned int Tr_TraceRay(Vector3 origin, Vector3 direction, float minT,
                         float maxT);

void Rt_Init(int scrW, int scrH);

void Rt_Draw();

#endif /* RAYTRACER_H */
