#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>

#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <chrono>
#include "game_object.h"

namespace Mutiny {
    struct Scene {
        Scene(const std::string& title, int width = 1024, int height = 768);
        virtual ~Scene();

        void start();
        void handle_event();
        void render();
        void update();

        std::string get_scene_data_path() const;

        sf::Window window;
        bool running;

        int width;
        int height;
        std::string title;


        std::vector<GameObject*> game_objects;

        std::chrono::time_point<std::chrono::system_clock> previous_time;
        float accumulator;
    };
}


#endif
