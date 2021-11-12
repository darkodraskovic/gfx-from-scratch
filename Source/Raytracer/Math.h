#ifndef MATH_RT_H
#define MATH_RT_H

#include "../Util/Color.h"
#include "raymath.h"

typedef struct {
  Vector3 center;
  float radius;
  color_t color;
} Rt_Sphere;

Vector2 Rt_IntersectRaySphere(Vector3 origin, Vector3 direction,
                              Rt_Sphere sphere);

#endif /* MATH_RT_H */
