#include "Raytracer.h"

#include "../Util/Array.h"
#include "raymath.h"

typedef struct {
  Rt_Ball* ball;
  float t;
} Closest;

static inline Closest closestIntersection(Rt_Scene* scene, Vector3 origin,
                                          Vector3 direction, float minT,
                                          float maxT) {
  Closest closest = {NULL, INFINITY};

  for (int i = 0; i < arrSize(scene->balls); ++i) {
    Vector2 t =
        Rt_IntersectRaySphere(origin, direction, scene->balls[i].sphere);
    if (t.x < closest.t && t.x > minT && t.x < maxT) {
      closest.t = t.x;
      closest.ball = &scene->balls[i];
    }
    if (t.y < closest.t && t.y > minT && t.y < maxT) {
      closest.t = t.y;
      closest.ball = &scene->balls[i];
    }
  }
  return closest;
}

static inline float computeDiffuse(float intensity, Vector3 light,
                                   Vector3 normal) {
  float dot = Vector3DotProduct(light, normal);
  if (dot < 0) return 0;

  /* intensity times cosine of light-normal angle */
  return intensity *
         (dot / sqrtf(Vector3LengthSqr(light) * Vector3LengthSqr(normal)));
  /* (dot / (Vector3Length(light) * Vector3Length(normal))); */
}

static inline float computeSpecular(float intensity, Vector3 light,
                                    Vector3 normal, Vector3 view,
                                    float specular) {
  if (specular == -1) return 0;

  Vector3 reflect = Vector3Reflect(light, normal);

  float dot = Vector3DotProduct(reflect, view);
  if (dot < 0) return 0;

  return intensity *
         powf(dot / sqrtf(Vector3LengthSqr(reflect) * Vector3LengthSqr(view)),
              /* powf(dot / (Vector3Length(reflect) * Vector3Length(view)), */
              specular);
}

static inline Rt_Ball* inShadow(Rt_Scene* scene, Vector3 point, Vector3 light,
                                float t) {
  Closest closest = closestIntersection(scene, point, light, 0.001, t);
  return closest.ball;
}

float computeLighting(Rt_Scene* scene, Vector3 point, Vector3 normal,
                      float specuar) {
  float intensity = 0.0;
  // TODO: make fixed camera/eye origin movable
  Vector3 view = Vector3Scale(point, -1);

  // ambient
  intensity += scene->ambientLight;

  // point
  for (int i = 0; i < arrSize(scene->pointLights); ++i) {
    Rt_PointLight* light = &scene->pointLights[i];
    Vector3 lightDir = Vector3Subtract(light->position, point);

    if (inShadow(scene, point, lightDir, 1)) continue;

    intensity += computeDiffuse(light->intensity, lightDir, normal);
    intensity +=
        computeSpecular(light->intensity, lightDir, normal, view, specuar);
  }

  // directional
  for (int i = 0; i < arrSize(scene->directionalLights); ++i) {
    Rt_DirectionalLight* light = &scene->directionalLights[i];

    if (inShadow(scene, point, light->direction, INFINITY)) continue;

    intensity += computeDiffuse(light->intensity, light->direction, normal);
    intensity += computeSpecular(light->intensity, light->direction, normal,
                                 view, specuar);
  }

  return intensity;
}

unsigned int Rt_TraceRay(Rt_Scene* scene, Vector3 origin, Vector3 direction,
                         float minT, float maxT, int depth) {
  Closest closest = closestIntersection(scene, origin, direction, minT, maxT);

  if (!closest.ball) {
    /* return 0xffffffff; */
    return 0xff000000;
  }

  // sphere-ray intersection point
  Vector3 point = Vector3Add(origin, Vector3Scale(direction, closest.t));
  // intersection point normal
  Vector3 normal = Vector3Subtract(point, closest.ball->sphere.center);

  unsigned int localColor = SetColorBrightness(
      closest.ball->color,
      computeLighting(scene, point, normal, closest.ball->specular));

  float reflective = closest.ball->reflective;
  if (depth < 1 || reflective <= 0) return localColor;

  Vector3 reflection = Vector3Reflect(direction, normal);
  unsigned int reflectedColor =
      Rt_TraceRay(scene, point, reflection, 0.001, INFINITY, depth - 1);

  return BelendColors(localColor, reflectedColor, reflective);
}
