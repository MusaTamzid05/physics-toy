#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/System/Vector3.hpp>
#include "shader.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Mutiny {

    struct GameObject {
        GameObject();
        virtual ~GameObject();
        virtual void update(float delta_time);
        virtual void render();

        glm::vec3 position;
        glm::vec3 scale;
        glm::quat orientation;

        glm::mat4 model;

        sf::Vector3f  color;
        Shader* shader;



    };
}

#endif
