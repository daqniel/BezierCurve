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

void QuadraticBezierPatch::generate(float interval)
{/*
	QuadraticBezier row1, row2, row3;
	row1.setInterval(.01);
	row2.setInterval(.01);
	row3.setInterval(.01);
	row1.setControlPoints(glm::vec3(-2, -2, 2), glm::vec3(-3, 0, 3), glm::vec3(-2, 2, 2));
	row2.setControlPoints(glm::vec3(0, -3, 3), glm::vec3(0, 0, 7), glm::vec3(0, 3, 3));
	row3.setControlPoints(glm::vec3(2, -2, 2), glm::vec3(3, 0, 3), glm::vec3(2, 2, 2));

	const glm::vec4* controlpoints = row1.getControlPoints();
	for (int i = 0; i < 3; i++)
	{
		controlNet.push_back(controlpoints[i]);
	}
	controlpoints = row2.getControlPoints();
	for (int i = 0; i < 3; i++)
	{
		controlNet.push_back(controlpoints[i]);
	}
	controlpoints = row3.getControlPoints();
	for (int i = 0; i < 3; i++)
	{
		controlNet.push_back(controlpoints[i]);
	}

	std::vector<glm::vec4> row1points = row1.getPoints();
	std::vector<glm::vec4> row2points = row2.getPoints();
	std::vector<glm::vec4> row3points = row3.getPoints();

	for (int i = 0; i < row1points.size(); i++)
	{
		QuadraticBezier bezier;
		bezier.setInterval(.01);
		bezier.setControlPoints(glm::vec3(row1points[i]), glm::vec3(row2points[i]), glm::vec4(row3points[i]));

		std::vector<glm::vec4> bezierPoints = bezier.getPoints();
		points.insert(points.end(), bezierPoints.begin(), bezierPoints.end());
	}*/

	std::cout << "hi";
}

void QuadraticBezierPatch::draw(Shader* s, glm::mat4 view, glm::mat4 projection)
{
	//glm::mat4 model(1.0);
	//s->use();
	//s->setMatrix4f("model", glm::mat4(1.0));
	//s->setMatrix4f("view", view);
	//s->setMatrix4f("projection", projection);

	//std::cout << "hi" << std::endl;
	//glBindVertexArray(triangleVAO);

	//glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * points.size(), points.data(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

	//s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(0, 1, 0)));
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

	//s->setMatrix4f("model", glm::rotate(model, glm::radians(180.f), glm::vec3(0, 1, 0)));
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

	//s->setMatrix4f("model", glm::rotate(model, glm::radians(270.f), glm::vec3(0, 1, 0)));
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

	//s->setMatrix4f("model", glm::rotate(model, glm::radians(90.f), glm::vec3(1, 0, 0)));
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

	//s->setMatrix4f("model", glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0)));
	//glDrawArrays(GL_LINE_STRIP, 0, points.size());

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
