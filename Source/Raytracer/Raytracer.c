#include "Raytracer.h"

#include "../Util/Array.h"

static inline float computeIntensity(float intensity, Vector3 lightDir,
                                     Vector3 normal) {
  float dot = Vector3DotProduct(lightDir, normal);
  return (dot > 0)
             ? intensity *
                   (dot / (Vector3Length(lightDir) * Vector3Length(normal)))
             : 0;
}

float computeLighting(Rt_Scene* scene, Vector3 point, Vector3 normal) {
  float intensity = 0.0;

  // ambient
  intensity += scene->ambientLight;

  // point
  for (int i = 0; i < arrSize(scene->pointLights); ++i) {
    Rt_PointLight* light = &scene->pointLights[i];
    Vector3 lightDir = Vector3Subtract(light->position, point);
    intensity += computeIntensity(light->intensity, lightDir, normal);
  }

  // directional
  for (int i = 0; i < arrSize(scene->directionalLights); ++i) {
    Rt_DirectionalLight* light = &scene->directionalLights[i];
    intensity += computeIntensity(light->intensity, light->direction, normal);
  }

  return intensity;
}

unsigned int Rt_TraceRay(Rt_Scene* scene, Vector3 origin, Vector3 direction,
                         float minT, float maxT) {
  float closestT = INFINITY;
  Rt_Sphere* closestSphere = NULL;

  for (int i = 0; i < arrSize(scene->spheres); ++i) {
    Vector2 t = Rt_IntersectRaySphere(origin, direction, scene->spheres[i]);
    if (t.x < closestT && t.x > minT && t.x < maxT) {
      closestT = t.x;
      closestSphere = &scene->spheres[i];
    }
    if (t.y < closestT && t.y > minT && t.y < maxT) {
      closestT = t.y;
      closestSphere = &scene->spheres[i];
    }
  }
  if (!closestSphere) {
    return 0xffffffff;
  }

  Vector3 point = Vector3Add(origin, Vector3Scale(direction, closestT));
  Vector3 normal = Vector3Subtract(point, closestSphere->center);
  normal = Vector3Normalize(normal);

  return SetColorBrightness(closestSphere->color,
                            computeLighting(scene, point, normal));
}
