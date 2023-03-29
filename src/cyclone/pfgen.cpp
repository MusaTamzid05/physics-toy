#include "cyclone/pfgen.h"
#include "cyclone/particle.h"
#include <iostream>

namespace cyclone {

    ParticleGravity::ParticleGravity() {
        gravity = glm::vec3(0.0f, -1.0f, 0.0f);
    }

    void ParticleGravity::update_force(Particle* particle, float duration) {
        particle->force_accum += (gravity);
    }

    void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* force_generator) {
        ParticleForceRegistration registration;
        registration.particle = particle;
        registration.force_generator = force_generator;
        registrations.push_back(registration);
    }

    void ParticleForceRegistry::update_forces(float duration) {
        for(ParticleForceRegistration registration : registrations) 
            registration.force_generator->update_force(registration.particle, duration);

    }

    void ParticleForceRegistry::clear() {
        registrations.clear();
    }

}
