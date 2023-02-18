#include "camera.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <vector>

#include "consts.h"
#include "utils.h"

namespace Mutiny {
    Camera* Camera::instance = nullptr;
    float Camera::zoom = 45.0f;
    float Camera::sensitivity = 0.1f;
    bool Camera::update_projection = false;
    float Camera::yaw = -180.0f;
    float Camera::pitch = 0.0f;
    float Camera::keyboard_rotation_speed = 4.0f;

    glm::vec3 Camera::world_up = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Camera::front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Camera::right = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);


    Camera::Camera(const glm::vec3& position, int width, int height):
        position(position) {
            speed = 2.5f;
            world_up = glm::vec3(0.0f, 1.0f, 0.0f);
            update_camera_vector();

            screen_width = width;
            screen_height = height;
            init_projection();

        }

    void Camera::initialize(int width, int height, const std::string& scene_path) {
        glm::vec3 position(3.0f, 0.0f, 0.0f);

        std::ifstream input_file;
        input_file.open(scene_path);

        if(input_file) {
            std::string line;
            while(std::getline(input_file, line)) {
                std::vector<std::string> line_data = split(line, ' ');
                std::cout << line_data[0] << "\n";

                if(line_data[0] == "position") {
                    std::cout << "Loading " << line << "\n";
                    position = glm::vec3(
                            std::stof(line_data[1]), 
                         std::stof(line_data[2]), 
                         std::stof(line_data[3]));
                } 
                else if(line_data[0] == "yaw") 
                    yaw =  std::stof(line_data[1]);

                else if(line_data[0] == "pitch") 
                    pitch =  std::stof(line_data[1]);

            }

        }


        /*

        if(Utils::file_exists(path)) {
            std::string line;
            std::vector<std::string> line_data;
            std::ifstream input_file(path);

            while(std::getline(input_file, line)) {
                line_data = Utils::split(line, ' ');
                std::cout << line_data[0] << "\n";

                if(line_data[0] == "position") {
                    std::cout << "Loading " << line << "\n";
                    position = Vector3
                        (std::stof(line_data[1]), 
                         std::stof(line_data[2]), 
                         std::stof(line_data[3]));
                } 
                else if(line_data[0] == "yaw") 
                    yaw =  std::stof(line_data[1]);

                else if(line_data[0] == "pitch") 
                    pitch =  std::stof(line_data[1]);

            }

        }

        */
        instance = new Camera(position, width, height);

    }

    Camera* Camera::get_instance() {
        if(instance == nullptr)
            throw std::runtime_error("Camera not set!!");

        return instance;
    }

    void Camera::update_camera_vector() {
        glm::vec3 front_;
        front_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front_.y = sin(glm::radians(pitch));
        front_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(front_);
        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));


    }


    glm::mat4 Camera::get_view_matrix() {
        glm::vec3 position_= glm::vec3(position.x, position.y, position.z);
        return glm::lookAt(position_, position_ + front, up);
    }

    void Camera::process_keyboard(CameraMovement direction) {
        //float velocity = speed * Time::get_instance()->delta_time;
        float velocity = speed * TIME_STEP;

        if(direction == FORWARD)
            position += front * velocity;

        if(direction == BACKWARD)
            position -= front * velocity;

        if(direction == LEFT)
            position -= right * velocity;

        if(direction == RIGHT)
            position += right * velocity;

        if(direction == UP)
            position += world_up * velocity;

        if(direction == DOWN)
            position -= world_up * velocity;

    }

    void Camera::process_mouse_scroll(float offset) {
        zoom -= (float)offset;


        if(zoom < 1.0f)
            zoom = 1.0f;
        if(zoom > 45.0f)
            zoom = 45.0f;

        update_projection = true;

    }

    void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch) {
        rotate(xoffset, yoffset, constrain_pitch);
    }

    void Camera::update(float delta_time) {
        if(update_projection) {
            init_projection();
            update_projection = false;
        }
    }

    void Camera::init_projection() {
        projection = glm::perspective(glm::radians(zoom), (float)screen_width/ (float)screen_height, 0.1f, 100.0f);

    }

    void Camera::rotate(float xoffset, float yoffset, bool constrain_pitch) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;


        yaw += xoffset;
        pitch += yoffset;

        if(constrain_pitch) {
            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;
        }
        update_camera_vector();

    }

    void Camera::save(const std::string& scene_path) const {
        std::cout << "Position: x = " << position.x << " y = " << position.y << " z = " << position.z << "\n";
        std::cout <<  "yaw " << yaw << " pitch " << pitch << "\n";

        std::ofstream out_data;
        out_data.open(scene_path);

        if(!out_data) {
            std::cerr << "Could open " << scene_path << " to save.\n";
            return;
        }

        out_data << "position " << position.x << " " << position.y << " " << position.z << "\n";
        out_data << "yaw " << yaw << "\n";
        out_data << "pitch " << pitch << "\n";

        out_data.close();
    }
}
