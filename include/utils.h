#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Mutiny {
    std::vector<std::string> split(const std::string &str, char splitter);
    void print(glm::vec3& vec);

}

#endif
