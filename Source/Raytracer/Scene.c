#include "Scene.h"

#include <stdlib.h>

#include "../Util/Array.h"

Rt_Scene* Rt_CreateScene() {
  Rt_Scene* scene = (Rt_Scene*)malloc(sizeof(Rt_Scene));
  scene->balls = arrCreate(0, sizeof(Rt_Sphere));
  scene->directionalLights = arrCreate(0, sizeof(Rt_DirectionalLight));
  scene->pointLights = arrCreate(0, sizeof(Rt_PointLight));
  return scene;
}

void Rt_DestroyScene(Rt_Scene* scene) {
  arrDestroy(scene->balls);
  arrDestroy(scene->pointLights);
  arrDestroy(scene->directionalLights);
  free(scene);
}
