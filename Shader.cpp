#include "Shader.h"

#include "Mesh.h"

#include <iostream>
#include <fstream>

namespace rendering {
	const char* DEBUG_VERT_SHADER_SRC = ""
		"#version 330 core\n"
		"in Vertex {\n"
		"    vec4 colour;\n"
		"    vec3 worldPos;\n"
		"} IN;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(IN.worldPos.x, IN.worldPos.y, IN.worldPos.z, 1.0);\n"
		"}\0";

	const char* DEBUG_FRAG_SHADER_SRC = ""
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	Shader::Shader() : Shader(DEBUG_VERT_SHADER_SRC, DEBUG_FRAG_SHADER_SRC) {
	}

	Shader::Shader(const char* vertexsource, const char* fragmentsource) {
		m_ShaderStages[VERTEX] = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_ShaderStages[VERTEX], 1, &vertexsource, NULL);
		glCompileShader(m_ShaderStages[VERTEX]);

		m_ShaderStages[FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_ShaderStages[FRAGMENT], 1, &fragmentsource, NULL);
		glCompileShader(m_ShaderStages[FRAGMENT]);

		int success;
		char infoLog[512];
		for (int i = 0; i < MAX_STAGES; i++) {
			glGetShaderiv(m_ShaderStages[i], GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(m_ShaderStages[i], 512, NULL, infoLog);
				std::cout << "ERROR: Shader failed to compile" << std::endl;
			}
		}
		
		m_Program = glCreateProgram();
		glAttachShader(m_Program, m_ShaderStages[VERTEX]);
		glAttachShader(m_Program, m_ShaderStages[FRAGMENT]);
		glLinkProgram(m_Program);

		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
			std::cout << "ERROR: Program failed to link" << std::endl;
		}

		SetDefaultAttributes();
	}

	Shader::Shader(std::string vertexfile, std::string fragmentfile) {
		std::string vertexSource;
		std::string fragmentSource;
		if (!LoadShaderFile(vertexfile, vertexSource) || !LoadShaderFile(fragmentfile, fragmentSource)) {
			std::cout << "Compiling Failed, reverting to debug shader" << std::endl;
			vertexSource = DEBUG_VERT_SHADER_SRC;
			fragmentSource = DEBUG_FRAG_SHADER_SRC;
		}
	
		Shader(vertexSource.c_str(), fragmentSource.c_str());

	}

	Shader::~Shader() {
		for (GLuint shader : m_ShaderStages) {
			glDeleteShader(shader);
		}
	}

	void Shader::SetDefaultAttributes() {
	}

	bool Shader::LoadShaderFile(std::string from, std::string& into) {
		std::ifstream file;
		std::string temp;

		std::cout << "Loading shader text from " << from << std::endl << std::endl;

		file.open(from.c_str());
		if (!file.is_open()) {
			std::cout << "File does not exist!" << std::endl;
			return false;
		}

		while (!file.eof()) {
			getline(file, temp);
			into += temp + "\n";
		}

		file.close();
		std::cout << into << std::endl << std::endl;
		std::cout << "Loaded shader text!" << std::endl << std::endl;
		return true;
	}
}