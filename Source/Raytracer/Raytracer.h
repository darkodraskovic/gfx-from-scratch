#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"

unsigned int Rt_TraceRay(Rt_Scene* scene, Vector3 origin, Vector3 direction,
                         float minT, float maxT);

#endif /* RAYTRACER_H */
