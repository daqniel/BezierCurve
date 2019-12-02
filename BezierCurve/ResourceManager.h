#pragma once
#include "Shader.h"
//#include "Texture.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stb_image/stb_image.h>
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

	//int loadTexture(string imagePath)
	//{
	//	int width, height, nrChannels;

	//	Texture newTexture;
	//	newTexture.setMaxFilter(GL_LINEAR);
	//	newTexture.setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
	//	newTexture.setTextureWrapS(GL_REPEAT);
	//	newTexture.setTextureWrapT(GL_REPEAT);
	//	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
	//	if (data)
	//	{
	//		newTexture.generate(width, height, nrChannels, data);
	//	}
	//	else
	//	{
	//		std::cout << "ERROR::TEXTURE::IMAGE_LOAD_FAILED" << std::endl;
	//		return -1;
	//	}
	//	stbi_image_free(data);
	//	return newTexture.ID;
	//}
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
		unsigned int shader;
		switch (type)
		{
		case ShaderType::VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case ShaderType::GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case ShaderType::TCS:
			shader = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		case ShaderType::TES:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;

		}



		glShaderSource(shader, 1, &shaderCodeStr, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
			return nullptr;
		}

	}


	static Shader* loadShader(const GLchar* vertexPath, const GLchar* fragPath, const GLchar* geomPath = nullptr, const GLchar* tcsPath = nullptr, const GLchar* tesPath = nullptr)
	{
		/*if (numShaders == MAX_NUM_SHADERS)
		{
			std::cout << "ERROR::SHADER::SHADER_NUM_LIMIT_REACHED\n" << "Try modifying MAX_NUM_SHADERS" << std::endl;
			return -1;
		}*/
		int success;
		char* infoLog = new char[512];

		/* Step 1: Retrieve source code from filepath */
		std::string vertexCode;
		std::string fragCode;
		std::string geomCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;

		// ensure ifstream objs can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		// read from files
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragPath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vShaderStream.str();
			fragCode = fShaderStream.str();

			if (geomPath)
			{
				gShaderFile.open(geomPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geomCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragCode.c_str();
		const char* gShaderCode = nullptr;
		if (geomPath)
		{
			gShaderCode = geomCode.c_str();
		}

		/* Step 2: Compile shaders */
		unsigned int vertex, fragment, geometry;

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
			return nullptr;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << std::endl;
			return nullptr;
		}

		// geometry shader

		if (geomPath)
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(geometry, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::GEOMETRY::COMPILE_FAILED\n" << infoLog << std::endl;
				return nullptr;
			}
		}

		/* Step 3: Create program */
		Shader* newShader = nullptr;
		if (geomPath)
			newShader = new Shader(&success, infoLog, vertex, fragment, geometry, tcs, tes);
		else
			newShader = new Shader(&success, infoLog, vertex, fragment);

		if (!success)
		{
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
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
