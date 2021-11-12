#include "Hooks.h"

#include "../Util/Array.h"
#include "Scene.h"
#include "Viewport.h"

Rt_Scene* scene;

void Rt_Init(int scrW, int scrH) {
  Rt_InitCanvas(scrW, scrH);
  scene = Rt_CreateScene();

  // objects
  Rt_Sphere sphere1 = ((Rt_Sphere){(Vector3){0, -1, 3}, 1, 0xff0000ff});
  Rt_Sphere sphere2 = ((Rt_Sphere){(Vector3){2, 0, 4}, 1, 0xffff0000});
  Rt_Sphere sphere3 = ((Rt_Sphere){(Vector3){-2, 0, 4}, 1, 0xff00ff00});
  Rt_Sphere sphere4 = ((Rt_Sphere){(Vector3){0, -5001, 0}, 5000, 0xff00ffff});
  arrPush(scene->spheres, sphere1);
  arrPush(scene->spheres, sphere2);
  arrPush(scene->spheres, sphere3);
  arrPush(scene->spheres, sphere4);

  // lights
  scene->ambientLight = .2;
  Rt_DirectionalLight dirLight1 = {.2, {1, 4, 4}};
  arrPush(scene->directionalLights, dirLight1);
  Rt_PointLight pointLight1 = {.6, {2, 1, 0}};
  arrPush(scene->pointLights, pointLight1);
}

void Rt_Draw() { Rt_Render(scene); }

void Rt_Close() { Rt_DestroyScene(scene); }
