#include "Color.h"

color_t SetColorBrightness(color_t color, float percent) {
  if (percent < 0) return 0x000000 | (color & COL_MASK_A);
  if (percent > 1) return color;

  // return RGB * percent  + alpha (don't affect alpha)
  color_t r = (color & COL_MASK_R) * percent;
  color_t g = (color & COL_MASK_G) * percent;
  color_t b = (color & COL_MASK_B) * percent;
  return (color & COL_MASK_A) | (b & COL_MASK_B) | (g & COL_MASK_G) |
         (r & COL_MASK_R);
}

color_t BelendColors(color_t color1, color_t color2, float ratio) {
  color_t r =
      (color1 & COL_MASK_R) * (1 - ratio) + (color2 & COL_MASK_R) * ratio;
  color_t g =
      (color1 & COL_MASK_G) * (1 - ratio) + (color2 & COL_MASK_G) * ratio;
  color_t b =
      (color1 & COL_MASK_B) * (1 - ratio) + (color2 & COL_MASK_B) * ratio;

  return (color1 & COL_MASK_A) | (b & COL_MASK_B) | (g & COL_MASK_G) |
         (r & COL_MASK_R);
}
