#include "ComputeShader.h"

#include <iostream>
#include <fstream>

namespace rendering {
    const char* DEBUG_COMPUTE_SHADER_SRC = "";

    ComputeShader::ComputeShader(const std::string& filepath) {
        std::string computeSource;
        if (!LoadShaderFile(filepath, computeSource)) {
            std::cout << "Compiling Failed, reverting to debug compute shader" << std::endl;
            LoadShaderCode(DEBUG_COMPUTE_SHADER_SRC);
        }
    }

    //TODO this is a copy of Shader::LoadShaderFile - should there be a new inheritance heirarchy?
    bool ComputeShader::LoadShaderFile(std::string from, std::string& into) {
        std::ifstream file;
        std::string line;

        std::cout << "Loading shader text from " << from << std::endl << std::endl;

        file.open(from.c_str());
        if (!file.is_open()) {
            std::cout << "File does not exist!" << std::endl;
            return false;
        }

        while (!file.eof()) {
            getline(file, line);
            into += line + "\n";
        }

        file.close();
        std::cout << into << std::endl << std::endl;
        std::cout << "Loaded shader text!" << std::endl << std::endl;
        return true;
    }

    void ComputeShader::LoadShaderCode(const char* computesource) {
        m_ShaderStage = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(m_ShaderStage, 1, &computesource, NULL);
        glCompileShader(m_ShaderStage);

        int success;
        char infoLog[512];
        glGetShaderiv(m_ShaderStage, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_ShaderStage, 512, NULL, infoLog);
            std::cout << "ERROR: Compute shader failed to compile" << std::endl;
            return;
        }

        m_Program = glCreateProgram();
        glAttachShader(m_Program, m_ShaderStage);

        glLinkProgram(m_Program);

        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
            std::cout << "ERROR: Compute program failed to link" << std::endl;
        }
    }
}