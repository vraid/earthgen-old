#ifndef grid_util_h
#define grid_util_h

#include "../../math/vector2.h"
#include "../../math/quaternion.h"
#include <vector>

namespace earthgen {

class Quaternion;
class Tile;

Quaternion reference_rotation (const Tile*, Quaternion);
std::vector<Vector2> polygon (const Tile*, Quaternion);

}

#endif
