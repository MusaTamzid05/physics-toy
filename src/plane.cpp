#include "plane.h"


namespace Mutiny {
    Plane::Plane(const std::string& texture_name):
        Cube(texture_name) {
            scale = glm::vec3(30.0f, 2.0f, 30.0f);
        }
}
