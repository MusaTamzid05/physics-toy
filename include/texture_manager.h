#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>


namespace Mutiny {

    struct TextureData {

        TextureData() {}
        TextureData(const std::string& path,
                const std::string& name,
                int width,
                int height,
                int channels,
                int id
                );
        TextureData(const TextureData& texture_data);

        std::string name;
        std::string path;
        int width;
        int height;
        int channels;
        unsigned int id;

    };
    class TextureManager {

        public:
            bool add(const std::string& path, const std::string& name);
            std::map<std::string, TextureData> textures;
            static TextureManager* get_instance();


        private:
            TextureManager() {}
            static TextureManager* instance;

    };
}

#endif
