#include "game_object.h"
#include "camera.h"

namespace Mutiny {

    GameObject::GameObject() {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
        orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        
    }

    GameObject::~GameObject() {
        delete shader;
    }

    void GameObject::update(float delta_time) {
        model = glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)) * glm::mat4_cast(orientation) * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));


    }

    void GameObject::render() {

        if(shader != nullptr) {
            shader->use();
            shader->setMat4("projection", Camera::get_instance()->projection);
            shader->setMat4("view", Camera::get_instance()->get_view_matrix());

        }

    }
}
