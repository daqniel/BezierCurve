#ifndef _GRID3D_H_
#define _GRID3D_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"
struct GridData
{
	glm::vec3 negx, posx;
	glm::vec3 negy, posy;
	glm::vec3 negz, posz;
};

class Grid3D
{
public:
	Grid3D();

	void draw(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawticks(Shader* s, glm::mat4 view, glm::mat4 projection);
	void drawticklines(Shader* s, glm::mat4 view, glm::mat4 projection);
	void setGridBoundaries(glm::vec3 pos, glm::vec3 neg);
	void setTickPrecision(float precision);
private:

	void generate();

	void generateTicks(float precision);

	float m_interval;
	float m_scale;
	float m_tick_precision;

	glm::vec3 origin;
	GridData grid;

	GLuint VAO;
	GLuint VBO;

	GLuint tickVAO, tickVBO;

	GLuint m_numticks;

	std::vector<glm::vec3> tickpoints;
};

#endif // !_GRID3D_H_
