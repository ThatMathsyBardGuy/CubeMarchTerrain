#include "ComputeShader.h"

#include <iostream>
#include <fstream>

namespace rendering {
    const char* DEBUG_COMPUTE_SHADER_SRC = "";

    ComputeShader::ComputeShader(const std::string filepath, const size_t ssbosize, void* ssbodata) {
        std::string computeSource;
        if (!LoadShaderFile(filepath, computeSource)) {
            std::cout << "Compiling Failed, reverting to debug compute shader" << std::endl;
            LoadShaderCode(DEBUG_COMPUTE_SHADER_SRC);
        } else {
            LoadShaderCode(computeSource.c_str());
        }
        m_DataSize = ssbosize;
        glGenBuffers(1, &m_SSBO);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, m_DataSize, ssbodata, GL_DYNAMIC_COPY);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        glGenBuffers(1, &m_AtomicBuffer);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, m_AtomicBuffer);
        glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
    }

    void ComputeShader::Dispatch(const uint32_t numgroupsx, const uint32_t numgroupsy, const uint32_t numgroupsz) {
        glUseProgram(m_Program);
        glDispatchCompute(numgroupsx, numgroupsy, numgroupsz);
    }

    void ComputeShader::BufferData(void* data) {
        glUseProgram(m_Program);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBO);
        GLvoid* buffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        memcpy(buffer, data, m_DataSize);
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        ///@TODO Merge this with the SSBO using an offset in the shader
        glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 1, m_AtomicBuffer);

        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, m_AtomicBuffer);
        GLuint* ptr = (GLuint*)glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint),
            GL_MAP_WRITE_BIT |
            GL_MAP_INVALIDATE_BUFFER_BIT |
            GL_MAP_UNSYNCHRONIZED_BIT);
        ptr[0] = 0;
        glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
        glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
        
        //GLuint blockindex = 0;
        //blockindex = glGetProgramResourceIndex(m_Program, GL_SHADER_STORAGE_BLOCK, "SSBO");
        //glShaderStorageBlockBinding(m_Program, blockindex, 2);
    }

    void ComputeShader::GetData(void* output) {
        glUseProgram(m_Program);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBO);
        GLvoid* buffer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
        memcpy(output, buffer, m_DataSize);
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    //TODO this is a copy of Shader::LoadShaderFile - should there be a new inheritance hierarchy?
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
            std::cout << "ERROR: Compute shader failed to compile : " << std::endl << infoLog << std::endl;
            return;
        }

        m_Program = glCreateProgram();
        glAttachShader(m_Program, m_ShaderStage);

        glLinkProgram(m_Program);

        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
            std::cout << "ERROR: Compute program failed to link" << std::endl << infoLog << std::endl;
        }
    }
}