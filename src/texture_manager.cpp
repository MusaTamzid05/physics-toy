#include "texture_manager.h"
#include <GL/glew.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Mutiny {

    TextureData::TextureData(const std::string& path,
                const std::string& name,
                int width,
                int height,
                int channels,
                int id
                ):
        name(name),
        path(path),
        width(width),
        height(height),
        channels(channels),
        id(id) {}

    TextureData::TextureData(const TextureData& texture_data) {
        name = texture_data.name;
        path = texture_data.path;
        width = texture_data.width;
        height = texture_data.height;
        channels = texture_data.channels;
        id = texture_data.id;
    }

    TextureManager* TextureManager::instance = nullptr;

    TextureManager* TextureManager::get_instance() {
        if(instance == nullptr)
            instance = new TextureManager();
        return instance;
    }

    bool TextureManager::add(const std::string& path, const std::string& name) {
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << path <<  "\n";
            return false;
        }

        textures.insert(std::pair<std::string, TextureData>(
                    name, 
                    TextureData(
                        path,
                        name,
                        width,
                        height,
                        nrChannels,
                        id
                        )
                    ));

        stbi_image_free(data);

        return true;
    }

}
