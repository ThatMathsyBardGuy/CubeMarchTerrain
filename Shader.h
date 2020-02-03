#pragma once

#include <GL/glew.h>
#include <string>


namespace rendering {
	enum ShaderStages {
		VERTEX, FRAGMENT, MAX_STAGES
	};
	class Shader {
	public:
		Shader();
		Shader(const char* vertexsource, const char* fragmentsource);
		Shader(std::string vertexfile, std::string fragmentfile);
		~Shader();

		GLuint GetProgram() { return m_Program; }

	protected:
		void LoadShaderCode(const char* vertexsource, const char* fragmentsource);

		void SetDefaultAttributes();

		bool LoadShaderFile(std::string from, std::string& into);

		GLuint m_ShaderStages[MAX_STAGES];
		GLuint m_Program;
	};
}