#include "QuadraticBezierPatch.h"

QuadraticBezierPatch::QuadraticBezierPatch()
{
	glGenVertexArrays(1, &controlNetVAO);
	glGenBuffers(1, &controlNetVBO);

	controlNet.emplace_back(glm::vec3(-2, -2, 2), 0);
	controlNet.emplace_back(glm::vec3(-3, 0, 3), .5633);
	controlNet.emplace_back(glm::vec3(-2, 2, 2), .5633);
	controlNet.emplace_back(glm::vec3(0, -3, 3), .5633);
	controlNet.emplace_back(glm::vec3(0, 0, 7), 1.69);
	controlNet.emplace_back(glm::vec3(0, 3, 3), .5633);
	controlNet.emplace_back(glm::vec3(2, -2, 2), 0);
	controlNet.emplace_back(glm::vec3(3, 0, 3), .5633);
	controlNet.emplace_back(glm::vec3(2, 2, 2), .5633);

	QuadraticBezier u1, u2, u3, d;
	u1.setControlPoints(controlNet[0].pos, controlNet[1].pos, controlNet[2].pos);
	u2.setControlPoints(controlNet[3].pos, controlNet[4].pos, controlNet[5].pos);
	u3.setControlPoints(controlNet[6].pos, controlNet[7].pos, controlNet[8].pos);

	QuadraticBezier v1, v2, v3, h;
	v1.setControlPoints(controlNet[0].pos, controlNet[3].pos, controlNet[6].pos);
	v2.setControlPoints(controlNet[1].pos, controlNet[4].pos, controlNet[7].pos);
	v3.setControlPoints(controlNet[2].pos, controlNet[5].pos, controlNet[8].pos);

	controlNet[0].norm = -glm::normalize(glm::cross(u1.evaluateDerivative(0), v1.evaluateDerivative(0)));
	controlNet[1].norm = -glm::normalize(glm::cross(u1.evaluateDerivative(.5), v2.evaluateDerivative(0)));
	controlNet[2].norm = -glm::normalize(glm::cross(u1.evaluateDerivative(1), v3.evaluateDerivative(0)));

	controlNet[3].norm = -glm::normalize(glm::cross(u2.evaluateDerivative(0), v1.evaluateDerivative(.5)));
	controlNet[4].norm = -glm::normalize(glm::cross(u2.evaluateDerivative(.5), v2.evaluateDerivative(.5)));
	controlNet[5].norm = -glm::normalize(glm::cross(u2.evaluateDerivative(1), v3.evaluateDerivative(.5)));

	controlNet[6].norm = -glm::normalize(glm::cross(u3.evaluateDerivative(0), v1.evaluateDerivative(1)));
	controlNet[7].norm = -glm::normalize(glm::cross(u3.evaluateDerivative(.5), v2.evaluateDerivative(1)));
	controlNet[8].norm = -glm::normalize(glm::cross(u3.evaluateDerivative(1), v3.evaluateDerivative(1)));

	glBindVertexArray(controlNetVAO);
	glBindBuffer(GL_ARRAY_BUFFER, controlNetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * controlNet.size(), controlNet.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); //vertex positions
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)offsetof(Vertex, norm)); //vertex positions

}

QuadraticBezierPatch::~QuadraticBezierPatch()
{

}

void QuadraticBezierPatch::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
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
	glPatchParameteri(GL_PATCH_VERTICES, 9);

	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_PATCHES, 0, controlNet.size());

}

void QuadraticBezierPatch::drawControlNet(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	glm::mat4 model(1.0);
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	glBindVertexArray(controlNetVAO);

	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());

	s->setMatrix4f("model", glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0)));
	glDrawArrays(GL_POINTS, 0, controlNet.size());


}

void QuadraticBezierPatch::drawControlNormals(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	
	glm::mat4 model(1.0);
	s->use();
	s->setMatrix4f("model", glm::mat4(1.0));
	s->setMatrix4f("view", view);
	s->setMatrix4f("projection", projection);

	glBindVertexArray(controlNetVAO);

	glDrawArrays(GL_POINTS, 0, controlNet.size());
}
