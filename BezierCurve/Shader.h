#ifndef _DQ_SHADER_
#define _DQ_SHADER_
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
class Shader
{
public:
	unsigned int ID;

	// Import shaders from file, compile, and link them.
	Shader(int* success, char* infoLog, unsigned int vertex, unsigned int fragment, unsigned int geometry = -1)
	{
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometry != -1)
		{
			glAttachShader(ID, geometry);
		}
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, success);
	}

	~Shader()
	{

	}

	void use()
	{
		glUseProgram(ID);
	}

	void setUniform4f(const std::string name, const glm::vec4 &value)
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setUniform4f(const std::string name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void setVect3f(const std::string name, const glm::vec3 &value)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVect3f(const std::string name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec2f(const std::string name, const glm::vec2 &value)
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2f(const std::string name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setInt(const std::string name, int i)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), i);
	}
	void setMatrix4f(const std::string name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void setFloat(const std::string name, float f)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), f);
	}
};

#endif
