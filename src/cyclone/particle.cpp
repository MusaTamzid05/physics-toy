#include "cyclone/particle.h"

namespace cyclone {
    Particle::Particle(float dumping):
        dumping(dumping)
    {
        inverse_mass = 1.0f;
        velocity = glm::vec3(0.0f, -0.3f, 0.0f);
        acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    }


    void Particle::integrate(float duration, glm::vec3& position) {
        position += (velocity * duration);
        glm::vec3 resulting_acc = acceleration;
        resulting_acc += (force_accum * inverse_mass);

        velocity *= powf(dumping, duration);
        force_accum = glm::vec3(0.0f, 0.0f, 0.0f);


    }
}
