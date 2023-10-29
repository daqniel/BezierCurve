#ifndef _DELTATIME_H
#define _DELTATIME_H
#include "Shader.h"
#include "ResourceManager.h"
#include "Light.h"
#include <map>
struct Global
{
	//static float deltaTime;
	//static ResourceManager resource_mgr;
	//static std::map<std::string, Shader*> shaders;
	static std::vector<Light> lights;
};
#endif // !_DELTATIME_H
