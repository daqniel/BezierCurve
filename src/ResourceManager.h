#pragma once
#include "Shader.h"
//#include "Texture.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using std::string;
using std::vector;
#define MAX_NUM_TEXTURES 64
#define MAX_NUM_SHADERS 32
#define MAX_NUM_BLOCKGRIDS 32
class ResourceManager {

public:

	ResourceManager()
	{
	};

	~ResourceManager()
	{
		// prevent memory leaks
		for (auto s : loadedShaders)
		{
			if (s) delete s;
		}
	};

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		TCS,
		TES
	};
	static unsigned int compileShader(const GLchar* path, ShaderType type)
	{
		int success;
		char* infoLog = new char[512];

		std::string shaderCode;
		std::ifstream shaderFile;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::" << path << std::endl;
			return -1;
		}

		const char* shaderCodeStr = shaderCode.c_str();

		// compile
		unsigned int shader = -1;
		std::string typeStr;
		switch (type)
		{
		case ShaderType::VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			typeStr = "VERTEX";
			break;
		case ShaderType::FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			typeStr = "FRAGMENT";
			break;
		case ShaderType::GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			typeStr = "GEOMETRY";
			break;
		case ShaderType::TCS:
			shader = glCreateShader(GL_TESS_CONTROL_SHADER);
			typeStr = "TCS";
			break;
		case ShaderType::TES:
			shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			typeStr = "TES";
			break;

		}
		glShaderSource(shader, 1, &shaderCodeStr, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << typeStr <<"::COMPILE_FAILED\n" << infoLog << std::endl;
			return -1;
		}

		return shader;
	}


	static Shader* loadShader(const GLchar* vertexPath, const GLchar* fragPath, const GLchar* geomPath = nullptr, const GLchar* tcsPath = nullptr, const GLchar* tesPath = nullptr)
	{
		int success;
		char* infoLog = new char[512];
		GLuint vertex, frag, geom, tcs, tes;
		vertex = frag = geom = tcs = tes = 0;

		vertex = compileShader(vertexPath, VERTEX);
		frag = compileShader(fragPath, FRAGMENT);

		if (geomPath)
			geom = compileShader(geomPath, GEOMETRY);
		if (tcsPath)
			tcs = compileShader(tcsPath, TCS);
		if (tesPath)
			tes = compileShader(tesPath, TES);

		/* Step 3: Create program */
		Shader* newShader = nullptr;
		newShader = new Shader(&success, infoLog, vertex, frag, geom, tcs, tes);

		if (!success)
		{
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED::" << vertexPath << "|" << fragPath << "|" <<  "|" << tcsPath << "|" << tesPath << std::endl;
			return nullptr;
		}

		//loadedShaders.push_back(newShader);
		return newShader;
		//shaders[numShaders] = newShader;
		//numShaders++;
	}
private:
	vector<Shader*> loadedShaders;
};
