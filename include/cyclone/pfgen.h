#ifndef PFGEN_H
#define PFGEN_H

#include <vector>
#include <glm/glm.hpp>

namespace cyclone {
    struct Particle;

    struct ParticleForceGenerator {
        ParticleForceGenerator() {}
        virtual ~ParticleForceGenerator() {}
        virtual void update_force(Particle* particle, float duration) = 0;
    };

    struct ParticleGravity : public ParticleForceGenerator {
        ParticleGravity();
        void update_force(Particle* particle, float duration);

        glm::vec3 gravity;

    };

    struct ParticleForceRegistry {

        struct ParticleForceRegistration {
            Particle* particle;
            ParticleForceGenerator* force_generator;


        };

        void add(Particle* particle, ParticleForceGenerator* force_generator);
        void clear();
        void update_forces(float duration);

        std::vector<ParticleForceRegistration> registrations;


    };
}

#endif
