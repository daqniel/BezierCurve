#include "CubicBezierPatch.h"

CubicBezierPatch::CubicBezierPatch()
{
	glGenVertexArrays(1, &controlNetVAO);
	glGenBuffers(1, &controlNetVBO);

	controlNet.emplace_back(glm::vec3(3, 0, 0), 0);
	controlNet.emplace_back(glm::vec3(3, 2, 0), .5633);
	controlNet.emplace_back(glm::vec3(3, 0, 2), .5633);
	controlNet.emplace_back(glm::vec3(2, 3, 0), .5633);
	controlNet.emplace_back(glm::vec3(3, 3, 3), 1.69);
	controlNet.emplace_back(glm::vec3(2, 0, 3), .5633);
	controlNet.emplace_back(glm::vec3(0, 3, 0), 0);
	controlNet.emplace_back(glm::vec3(0, 3, 2), .5633);
	controlNet.emplace_back(glm::vec3(0, 2, 3), .5633);
	controlNet.emplace_back(glm::vec3(0, 0, 3), 0);

	glBindVertexArray(controlNetVAO);
	glBindBuffer(GL_ARRAY_BUFFER, controlNetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * controlNet.size(), controlNet.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); //vertex positions
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)offsetof(Vertex, norm)); //vertex positions
}

CubicBezierPatch::~CubicBezierPatch()
{

}

void CubicBezierPatch::generate(float interval)
{


}

void CubicBezierPatch::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 model(1.0);
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	for (auto& light : Global::lights)
		light.set(s);

	s->setFloat("maxCurvature", 1.69);
	glBindVertexArray(controlNetVAO);
	glPatchParameteri(GL_PATCH_VERTICES, 10);

	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());


	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(1, 0, -1)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());
	
	}

void CubicBezierPatch::drawControlNet(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 model(1.0);
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	glBindVertexArray(controlNetVAO);
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());


	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(1, 0, -1)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());
	


}
