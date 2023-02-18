#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>

namespace cyclone {
    struct Particle {
        Particle(float dumping = 0.95f);
        virtual ~Particle() {}

        void integrate(float duration, glm::vec3& position);

        glm::vec3 velocity;
        glm::vec3 acceleration;

        glm::vec3 force_accum;
        float inverse_mass;
        float dumping;

    };
}

#endif
