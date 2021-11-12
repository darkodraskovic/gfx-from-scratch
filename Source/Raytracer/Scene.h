#ifndef SCENE_RT_H
#define SCENE_RT_H

#include "Math.h"

typedef struct {
  float intensity;
  Vector3 position;
} Rt_PointLight;

typedef struct {
  float intensity;
  Vector3 direction;
} Rt_DirectionalLight;

typedef struct {
  Rt_Sphere* spheres;
  Rt_PointLight* pointLights;
  Rt_DirectionalLight* directionalLights;
  float ambientLight;
} Rt_Scene;

Rt_Scene* Rt_CreateScene();
void Rt_DestroyScene(Rt_Scene* scene);

#endif /* SCENE_RT_H */
