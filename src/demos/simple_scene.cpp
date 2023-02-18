#include "demos/simple_scene.h"
#include "scene.h"
#include "cube.h"
#include "plane.h"
#include "texture_manager.h"

namespace Demo {
    SimpleScene::SimpleScene(const std::string& title, int width, int height):Scene(title, width, height){
        Mutiny::TextureManager::get_instance()->add("../textures/container.jpg", "container");
        Mutiny::TextureManager::get_instance()->add("../textures/wall.jpg", "wall");

        Mutiny::Cube* cube = new Mutiny::Cube("container");
        cube->position = glm::vec3(0.0f, 10.0f, 0.0f);

        game_objects.push_back(cube);

        Mutiny::Plane* plane = new Mutiny::Plane("wall");
        plane->position = glm::vec3(-2.0f, -3.0f, 0.0f);
        game_objects.push_back(plane);
    }
}
