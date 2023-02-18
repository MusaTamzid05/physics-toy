#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "scene.h"

namespace Demo {
    struct SimpleScene : public Mutiny::Scene {
        SimpleScene(const std::string& title, int width = 1024, int height = 768);

    };
}
#endif
