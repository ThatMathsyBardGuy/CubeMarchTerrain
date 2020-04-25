#pragma once

#include <string>
#include <GL/glew.h>

namespace rendering {
    class ComputeShader {
    public:
        ComputeShader(const std::string filepath, const size_t ssbosize, void* ssbodata = nullptr);

        void Dispatch(const uint32_t numgroupsx, const uint32_t numgroupsy = 1, const uint32_t numgroupsz = 1);

        GLuint GetProgram() { return m_Program; }

        void BufferData(void* data);

        void GetData(void* output);

    protected:
        void LoadShaderCode(const char* computesource);
        bool LoadShaderFile(std::string from, std::string& into);

        GLuint m_ShaderStage;
        GLuint m_Program;

        size_t m_DataSize;
        GLuint m_SSBO;
    };
}


