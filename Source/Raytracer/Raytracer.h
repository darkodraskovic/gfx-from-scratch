#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"

Color Rt_TraceRay(Rt_Scene* scene, Vector3 origin, Vector3 direction,
                  float minT, float maxT, int depth);

#endif /* RAYTRACER_H */
