#ifndef VIEWPORT_RT_H
#define VIEWPORT_RT_H

#include "Scene.h"

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Rt_IntRect;

void Rt_InitCanvas(int scrW, int scrH);

Vector3 Rt_CanvasToViewport(int canvasX, int canvasY);
void Rt_Render(Rt_Scene* scene);

#endif /* VIEWPORT_RT_H */
