#include "Config.h"
#include "Raytracer/Raytracer.h"
#include "Renderer/Renderer.h"
#include "Util/Util.h"

void Init() {
  Rt_Init(displayConfig.width, displayConfig.height);

  // objects
  Rt_Sphere sphere1 = ((Rt_Sphere){(Vector3){0, -1, 3}, 1, 0xff0000ff});
  Rt_Sphere sphere2 = ((Rt_Sphere){(Vector3){2, 0, 4}, 1, 0xffff0000});
  Rt_Sphere sphere3 = ((Rt_Sphere){(Vector3){-2, 0, 4}, 1, 0xff00ff00});
  Rt_Sphere sphere4 = ((Rt_Sphere){(Vector3){0, -5001, 0}, 5000, 0xff00ffff});
  arrPush(Rt_scene.spheres, sphere1);
  arrPush(Rt_scene.spheres, sphere2);
  arrPush(Rt_scene.spheres, sphere3);
  arrPush(Rt_scene.spheres, sphere4);

  // lights
  Rt_scene.ambientLight = .2;
  Rt_DirectionalLight dirLight1 = {.2, {1, 4, 4}};
  arrPush(Rt_scene.directionalLights, dirLight1);
  Rt_PointLight pointLight1 = {.6, {2, 1, 0}};
  arrPush(Rt_scene.pointLights, pointLight1);
}

void Update() {}

void PostUpdate(){

};

void Draw() { Rt_Draw(); }

void PostDraw() { DrawFPS(32, 32); };
