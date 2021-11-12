#include "Raytracer.h"

Vector3 Rt_origin = {0, 0, 0};
Rt_IntRect Rt_canvas;
Rectangle Rt_viewport = (Rectangle){-.5, -.5, 1, 1};
Rt_Scene Rt_scene;

Vector3 Rt_CanvasToViewport(int canvasX, int canvasY) {
  return (Vector3){canvasX * (Rt_viewport.width / Rt_canvas.width),
                   canvasY * (Rt_viewport.height / Rt_canvas.height), 1};
}

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

static inline float computeIntensity(float intensity, Vector3 lightDir,
                                     Vector3 normal) {
  float dot = Vector3DotProduct(lightDir, normal);
  return (dot > 0)
             ? intensity *
                   (dot / (Vector3Length(lightDir) * Vector3Length(normal)))
             : 0;
}

float ComputeLighting(Vector3 point, Vector3 normal) {
  float intensity = 0.0;

  // ambient
  intensity += Rt_scene.ambientLight;

  // point
  for (int i = 0; i < arrSize(Rt_scene.pointLights); ++i) {
    Rt_PointLight* light = &Rt_scene.pointLights[i];
    Vector3 lightDir = Vector3Subtract(light->position, point);
    intensity += computeIntensity(light->intensity, lightDir, normal);
  }

  // directional
  for (int i = 0; i < arrSize(Rt_scene.directionalLights); ++i) {
    Rt_DirectionalLight* light = &Rt_scene.directionalLights[i];
    intensity += computeIntensity(light->intensity, light->direction, normal);
  }

  return intensity;
}

unsigned int Rt_TraceRay(Vector3 origin, Vector3 direction, float minT,
                         float maxT) {
  float closestT = INFINITY;
  Rt_Sphere* closestSphere = NULL;

  for (int i = 0; i < arrSize(Rt_scene.spheres); ++i) {
    Vector2 t = Rt_IntersectRaySphere(origin, direction, Rt_scene.spheres[i]);
    if (t.x < closestT && t.x > minT && t.x < maxT) {
      closestT = t.x;
      closestSphere = &Rt_scene.spheres[i];
    }
    if (t.y < closestT && t.y > minT && t.y < maxT) {
      closestT = t.y;
      closestSphere = &Rt_scene.spheres[i];
    }
  }
  if (!closestSphere) {
    return 0xffffffff;
  }

  Vector3 point = Vector3Add(origin, Vector3Scale(direction, closestT));
  Vector3 normal = Vector3Subtract(point, closestSphere->center);
  normal = Vector3Normalize(normal);

  return SetColorBrightness(closestSphere->color,
                            ComputeLighting(point, normal));
}

void Rt_Init(int scrW, int scrH) {
  Rt_canvas.x = -scrW / 2;
  Rt_canvas.y = -scrH / 2;
  Rt_canvas.width = scrW;
  Rt_canvas.height = scrH;

  Rt_scene.spheres = arrCreate(4, sizeof(Rt_Sphere));
  Rt_scene.directionalLights = arrCreate(2, sizeof(Rt_DirectionalLight));
  Rt_scene.pointLights = arrCreate(4, sizeof(Rt_PointLight));
}

void Rt_Draw() {
  for (int x = Rt_canvas.x; x < Rt_canvas.x + Rt_canvas.width; x++) {
    for (int y = Rt_canvas.y; y < Rt_canvas.y + Rt_canvas.height; y++) {
      Vector3 direction = Rt_CanvasToViewport(x, y);
      unsigned int color = Rt_TraceRay(Rt_origin, direction, 1, INFINITY);
      SetPixel(x + Rt_canvas.width / 2,
               (Rt_canvas.height - 1) - (y + Rt_canvas.height / 2), color);
    }
  }
}
