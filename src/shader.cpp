#include "shader.h"


namespace Mutiny {



    Shader::Shader(const char* vertexPath,const char* fragmentPath) {
      


        if(!read_source_from(vertexPath , fragmentPath))
            return;

        const char* vShaderCode = vertex_shader_src.c_str();
        const char* fShaderCode = fragment_shader_src.c_str();

        // compile the shader.

        unsigned int vertex , fragment;
        compileShader(GL_VERTEX_SHADER , vertex , vShaderCode , "VERTEX");
        compileShader(GL_FRAGMENT_SHADER , fragment , fShaderCode , "FRAGMENT");


        link_program(vertex, fragment);;

        glDeleteShader(vertex);
        glDeleteShader(fragment);;

    }


    void Shader::compileShader(GLenum  shader_type , unsigned int& shader_index , const char* code , const std::string&  shader_name) {


        shader_index = glCreateShader(shader_type);

        glShaderSource(shader_index, 1 , &code , nullptr);
        glCompileShader(shader_index);
        check_compile_error(shader_index , shader_name);




    }


    void Shader::link_program(unsigned int vertex_shader_index , unsigned fragment_shader_index) {


        this->ID = glCreateProgram();
        glAttachShader(ID , vertex_shader_index);
        glAttachShader(ID , fragment_shader_index);
        glLinkProgram(ID);
        check_compile_error(ID , "PROGRAM");

        std::cout << "Program linked sucessfully.\n";
    }


    void Shader::check_compile_error(unsigned int& shader_index , const std::string& type) {

        int success;
        char infoLog[512];

        if(type != "PROGRAM") {
            
            glGetShaderiv(shader_index , GL_COMPILE_STATUS , &success);


            if(!success) {

                glGetShaderInfoLog(shader_index, 512 , nullptr , infoLog);
                std::cerr << "Shader " << type << " compilation error :"<< ":" << infoLog << "\n";
                exit(1);
            } else
                std::cout << type << " compile successfully.\n";

        } else {

            glGetProgramiv(shader_index , GL_LINK_STATUS , &success);


            if(!success) {

                glGetProgramInfoLog(shader_index, 512 , nullptr , infoLog);
                std::cerr << "program linking compilation error :"<< ":" << infoLog << "\n";
                exit(1);
            }
        }

    }

    void Shader::use() {

        glUseProgram(ID);
    }


    bool Shader::read_source_from(const std::string& vertex_shader_path , const std::string& fragment_shader_path) {


        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::fstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::fstream::badbit);

        try {

            vShaderFile.open(vertex_shader_path);
            fShaderFile.open(fragment_shader_path);




            std::stringstream vShaderStream , fShaderStream;


            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertex_shader_src = vShaderStream.str();
            fragment_shader_src = fShaderStream.str();
            return true;

        } catch(std::ifstream::failure& e)  {

            std::cout << "Failed to open shader files.\n";
            std::cerr << e.what() << "\n";

            return false;
        }
    }
};

