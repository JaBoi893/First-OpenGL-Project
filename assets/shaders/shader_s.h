#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader 
{
    public:
        // Program ID
        unsigned int ID;

        // Constructor reads and builds the shaders
        Shader(const char* vertexPath, const char* fragmentPath)
        {
            // Set up strings to hold the shader source code
            string vertexCode;
            string fragmentCode;

            // Input file stream objects for reading the files
            ifstream vShaderFile;
            ifstream fShaderFile;

            // Make sure the ifstreams have exceptions
            vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
            fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

            try
            {
                // Open the files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                stringstream vShaderStream, fShaderStream;

                // Copy file buffer contents into the streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                // Close the file handlers
                vShaderFile.close();
                fShaderFile.close();

                // Convert the streams into strings
                vertexCode   = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (ifstream::failure e)
            {
                cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
            }
            // Convert the strings into null-terminated character pointers
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // Compile the shaders
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            // Vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);

            // Print compilation errors if necessary
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            };

            // Fragment shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);

            // Print compilation errors if necessary
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            };

            // Create the shader program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            // Print linking errors if necessary
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }

            // Delete shaders. Now that they are linked, they are no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void use() {
            glUseProgram(ID);
        }

        void setBool(const string &name, bool value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        void setInt(const string &name, int value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setFloat(const string &name, float value) {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setVec2(const std::string &name, const glm::vec2 &value) const
        { 
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        void setVec2(const std::string &name, float x, float y) const
        { 
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value) const
        { 
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        void setVec3(const std::string &name, float x, float y, float z) const
        { 
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value) const
        { 
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
        }
        void setVec4(const std::string &name, float x, float y, float z, float w) const
        { 
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

};

#endif