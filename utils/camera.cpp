#include "utils/camera.h"

v2 getCameraCoords(v2 coords, v2 camera) {
  return {
    coords.x - camera.x,
    coords.y - camera.y
  };
}
