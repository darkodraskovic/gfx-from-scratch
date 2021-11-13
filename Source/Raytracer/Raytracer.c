#include "Raytracer.h"

#include "../Util/Array.h"

static inline float computeDiffuse(float intensity, Vector3 light,
                                   Vector3 normal) {
  float dot = Vector3DotProduct(light, normal);
  if (dot < 0) return 0;

  /* intensity times cosine of light-normal angle */
  return intensity *
         (dot / sqrtf(Vector3LengthSqr(light) * Vector3LengthSqr(normal)));
}

static inline float computeSpecular(float intensity, Vector3 light,
                                    Vector3 normal, Vector3 view, float s) {
  if (s == -1) return 0;

  Vector3 reflect = Vector3Scale(normal, 2 * Vector3DotProduct(normal, light));
  reflect = Vector3Subtract(reflect, light);

  float dot = Vector3DotProduct(reflect, view);
  if (dot < 0) return 0;

  return intensity *
         powf(dot / sqrtf(Vector3LengthSqr(reflect) * Vector3LengthSqr(view)),
              s);
}

float computeLighting(Rt_Scene* scene, Vector3 point, Vector3 normal,
                      float specuar) {
  float intensity = 0.0;
  Vector3 view = Vector3Subtract((Vector3){0, 0, 0}, point);

  // ambient
  intensity += scene->ambientLight;

  // point
  for (int i = 0; i < arrSize(scene->pointLights); ++i) {
    Rt_PointLight* ptLight = &scene->pointLights[i];
    Vector3 light = Vector3Subtract(ptLight->position, point);
    intensity += computeDiffuse(ptLight->intensity, light, normal);
    intensity +=
        computeSpecular(ptLight->intensity, light, normal, view, specuar);
  }

  // directional
  for (int i = 0; i < arrSize(scene->directionalLights); ++i) {
    Rt_DirectionalLight* dirLight = &scene->directionalLights[i];
    intensity +=
        computeDiffuse(dirLight->intensity, dirLight->direction, normal);
    intensity += computeSpecular(dirLight->intensity, dirLight->direction,
                                 normal, view, specuar);
  }

  return intensity;
}

unsigned int Rt_TraceRay(Rt_Scene* scene, Vector3 origin, Vector3 direction,
                         float minT, float maxT) {
  float closestT = INFINITY;
  Rt_Ball* closestBall = NULL;

  for (int i = 0; i < arrSize(scene->balls); ++i) {
    Vector2 t =
        Rt_IntersectRaySphere(origin, direction, scene->balls[i].sphere);
    if (t.x < closestT && t.x > minT && t.x < maxT) {
      closestT = t.x;
      closestBall = &scene->balls[i];
    }
    if (t.y < closestT && t.y > minT && t.y < maxT) {
      closestT = t.y;
      closestBall = &scene->balls[i];
    }
  }
  if (!closestBall) {
    return 0xffffffff;
  }

  // sphere-ray intersection point
  Vector3 point = Vector3Add(origin, Vector3Scale(direction, closestT));
  // intersection point normal
  Vector3 normal = Vector3Subtract(point, closestBall->sphere.center);

  return SetColorBrightness(
      closestBall->color,
      computeLighting(scene, point, normal, closestBall->specular));
}
