#include "Math.h"

Vector2 Rt_IntersectRaySphere(Vector3 origin, Vector3 direction,
                              Rt_Sphere sphere) {
  float r = sphere.radius;
  Vector3 CO = Vector3Subtract(origin, sphere.center);

  // t^2⟨D,D⟩ + t(2⟨CO,D⟩) + ⟨CO,CO⟩ - r^2 = 0
  float a = Vector3DotProduct(direction, direction);
  float b = 2 * Vector3DotProduct(CO, direction);
  float c = Vector3DotProduct(CO, CO) - r * r;

  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return (Vector2){INFINITY, INFINITY};
  float t1 = (-b + sqrt(discriminant)) / (2 * a);
  float t2 = (-b - sqrt(discriminant)) / (2 * a);

  return (Vector2){t1, t2};
}
