#ifndef CUBE_H
#define CUBE_H


#include "game_object.h"
#include "shader.h"

namespace Mutiny {
    struct Cube : GameObject {
        Cube(const std::string& texture_name = "");
        virtual ~Cube();
        void update(float delta_time);
        void render();

        unsigned int VAO;
        unsigned int VBO;

        unsigned int texture_id;
        bool using_texture;


    };
}

#endif
