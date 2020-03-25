#pragma once

#include <string>
#include <GL/glew.h>

namespace rendering {
    class ComputeShader {
    public:
        ComputeShader(const std::string& filepath);
    protected:
        void LoadShaderCode(const char* computesource);
        bool LoadShaderFile(std::string from, std::string& into);

        GLuint m_ShaderStage;
        GLuint m_Program;
    };
}


