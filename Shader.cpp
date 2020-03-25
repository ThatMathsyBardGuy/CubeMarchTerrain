#include "Shader.h"

#include "Mesh.h"

#include <iostream>
#include <fstream>

namespace rendering {
	const char* DEBUG_VERT_SHADER_SRC = ""
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 2) in vec4 colour;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"out vec4 vertexcolour;\n"
		"void main()\n"
		"{\n"
		"   mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;\n"
		"   gl_Position = mvp*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   vertexcolour = vec4(colour.r, colour.g, colour.b, colour.a);\n"
		"}\0";

	const char* DEBUG_FRAG_SHADER_SRC = ""
		"#version 330 core\n"
		"in vec4 vertexcolour;\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"    fragColor = vertexcolour;\n"
		"}\0";

	Shader::Shader() : Shader(DEBUG_VERT_SHADER_SRC, DEBUG_FRAG_SHADER_SRC) {
	}

	Shader::Shader(const char* vertexsource, const char* fragmentsource) {
		LoadShaderCode(vertexsource, fragmentsource);

		SetDefaultAttributes();
	}

	Shader::Shader(std::string vertexfile, std::string fragmentfile) {
		std::string vertexSource;
		std::string fragmentSource;
		if (!LoadShaderFile(vertexfile, vertexSource) || !LoadShaderFile(fragmentfile, fragmentSource)) {
			std::cout << "Compiling Failed, reverting to debug shader" << std::endl;
			LoadShaderCode(DEBUG_VERT_SHADER_SRC, DEBUG_FRAG_SHADER_SRC);
		}
		else {
			const char* vertexCode = vertexSource.c_str();
			const char* fragmentCode = fragmentSource.c_str();

			LoadShaderCode(vertexCode, fragmentCode);
		}
	}

	Shader::Shader(std::string vertexfile, std::string fragmentfile, std::string geometryfile) {
		std::string vertexSource;
		std::string fragmentSource;
		std::string geometrySource;
		if (!LoadShaderFile(vertexfile, vertexSource) || !LoadShaderFile(fragmentfile, fragmentSource) || !LoadShaderFile(geometryfile, geometrySource)) {
			std::cout << "Compiling Failed, reverting to debug shader" << std::endl;
			LoadShaderCode(DEBUG_VERT_SHADER_SRC, DEBUG_FRAG_SHADER_SRC);
		}
		else {
			const char* vertexCode = vertexSource.c_str();
			const char* fragmentCode = fragmentSource.c_str();
			const char* geometryCode = geometrySource.c_str();

			LoadShaderCode(vertexCode, fragmentCode, geometryCode);
		}
	}

	Shader::~Shader() {
		for (GLuint shader : m_ShaderStages) {
			glDeleteShader(shader);
		}
	}

	void Shader::SetDefaultAttributes() {
	}

	void Shader::LoadShaderCode(const char* vertexsource, const char* fragmentsource, const char* geometrysource) {
		m_ShaderStages[VERTEX] = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_ShaderStages[VERTEX], 1, &vertexsource, NULL);
		glCompileShader(m_ShaderStages[VERTEX]);

		m_ShaderStages[FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_ShaderStages[FRAGMENT], 1, &fragmentsource, NULL);
		glCompileShader(m_ShaderStages[FRAGMENT]);

		if (geometrysource != "") {
			m_ShaderStages[GEOMETRY] = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(m_ShaderStages[GEOMETRY], 1, &geometrysource, NULL);
			glCompileShader(m_ShaderStages[GEOMETRY]);
		}

		int success;
		char infoLog[512];
		for (int i = 0; i < MAX_STAGES; i++) {
			glGetShaderiv(m_ShaderStages[i], GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(m_ShaderStages[i], 512, NULL, infoLog);
				std::cout << "ERROR: Shader failed to compile" << std::endl;
				return;
			}
		}

		m_Program = glCreateProgram();
		glAttachShader(m_Program, m_ShaderStages[VERTEX]);
		glAttachShader(m_Program, m_ShaderStages[FRAGMENT]);

		if (geometrysource != "") {
			glAttachShader(m_Program, m_ShaderStages[GEOMETRY]);
		}

		glLinkProgram(m_Program);

		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
			std::cout << "ERROR: Program failed to link" << std::endl;
		}
	}

	bool Shader::LoadShaderFile(std::string from, std::string& into) {
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
}