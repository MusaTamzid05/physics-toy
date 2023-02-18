#include "scene.h"
#include "camera.h"
#include "consts.h"
#include <SFML/OpenGL.hpp>
#include <iostream>

namespace  Mutiny {
    Scene::Scene(const std::string& title, int width, int height):
        window(sf::VideoMode(width, height), title, sf::Style::Default,
                sf::ContextSettings(24, 8, 4, 3, 0)),
        width(width),
        height(height),
        title(title),
        accumulator(0.0f)
    {
            window.setActive(true);
            running = true;
            window.setVerticalSyncEnabled(true);

            glewExperimental = GL_TRUE;

            if (glewInit() != GLEW_OK) {
                std::cerr << "glew error.\n";
                exit(1);
            }


            glEnable(GL_DEPTH_TEST);
            previous_time = std::chrono::system_clock::now();
            Camera::initialize(width, height, get_scene_data_path());
    }

    Scene::~Scene() {
        Camera::get_instance()->save(get_scene_data_path());
    }

    void Scene::start() {

        while(running) {
            handle_event();
            update();
            render();
        }
    }

    void Scene::handle_event() {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                running = false;

            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
                    Camera::get_instance()->process_keyboard(CameraMovement::FORWARD);
                

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    Camera::get_instance()->process_keyboard(CameraMovement::BACKWARD);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    Camera::get_instance()->process_keyboard(CameraMovement::LEFT);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    Camera::get_instance()->process_keyboard(CameraMovement::RIGHT);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    Camera::get_instance()->process_keyboard(CameraMovement::UP);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    Camera::get_instance()->process_keyboard(CameraMovement::DOWN);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
                       Camera::get_instance()->rotate(-Camera::keyboard_rotation_speed, 0.0f, true);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
                       Camera::get_instance()->rotate(Camera::keyboard_rotation_speed, 0.0f, true);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
                       Camera::get_instance()->rotate(0.0f, Camera::keyboard_rotation_speed, true);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
                       Camera::get_instance()->rotate(0.0f, -Camera::keyboard_rotation_speed, true);
            }
        }
    }

    void Scene::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(GameObject* game_object : game_objects)
            game_object->render();

        window.display();
    }

    void Scene::update() {
        std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
        std::chrono::duration<float> elasped_seconds = current_time - previous_time;
        float delta_time = elasped_seconds.count();
        previous_time = current_time;

        accumulator += delta_time;

        while(accumulator >= TIME_STEP) {
            Camera::get_instance()->update(TIME_STEP);
            for(GameObject* game_object : game_objects)
                game_object->update(delta_time);

            accumulator -= TIME_STEP;
        }


    }

    std::string Scene::get_scene_data_path() const {
        return  "../scenes/" + title + ".txt";
    }

}
