#ifndef PLANE_H
#define PLANE_H


#include "cube.h"

namespace Mutiny {
    struct Plane : public Cube {
        Plane(const std::string& texture_name = "");
    };
}
#endif
