#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iterator>
#include <vector>
#include <map>

#include "Shader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "CubicBezier.h"
#include "Grid3D.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool drawGridLines = false;
bool drawControlPolygon = false;
int controlPolygonEvalLevel = 0;
bool drawControlPoints = true;
bool drawEvalPoint = true;
std::map<std::string, std::vector<CubicBezier>> images;

int main()
{
	const float SCR_WIDTH = 1600;
	const float SCR_HEIGHT = 1400;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	Camera camera = Camera(glm::vec3(0.0, 0.0, 3.0));
	camera.faceOrigin();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bezier Curves", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR::GLFW::FAILED TO CREATE WINDOW" << std::endl;
		return -1;
	}

	glfwSetWindowUserPointer(window, &camera);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::failed to load init GLAD" << std::endl;
	}


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);

	Shader* linesegmentshader = ResourceManager::loadShader("Shaders/linesegment.vert", "Shaders/linesegment.frag");
	Shader* controlpolygonshader = ResourceManager::loadShader("Shaders/controlpolygon.vert", "Shaders/controlpolygon.frag");
	Shader* gridshader = ResourceManager::loadShader("Shaders/grid.vert", "Shaders/grid.frag");
	Shader* gridtickshader = ResourceManager::loadShader("Shaders/gridticks.vert", "Shaders/gridticks.frag", "Shaders/gridticks.geom");
	Shader* gridlineshader = ResourceManager::loadShader("Shaders/gridticks.vert", "Shaders/gridlines.frag", "Shaders/gridlines.geom");
	Shader* bezierpointshader = ResourceManager::loadShader("Shaders/bezierpoint.vert", "Shaders/bezierpoint.frag");
	Shader* frenetshader = ResourceManager::loadShader("Shaders/frenet.vert", "Shaders/frenet.frag", "Shaders/frenet.geom");

	glClearColor(.3, .3, .3, 1.0);
	CubicBezier lefteye1;
	lefteye1.setControlPoints(glm::vec3(1, 3, 2), glm::vec3(1, 4, 2), glm::vec3(1.5f, 4, 2), glm::vec3(1.5f, 3, 2));
	CubicBezier lefteye2;
	lefteye2.setControlPoints(glm::vec3(1, 3, 2), glm::vec3(1, 2, 2), glm::vec3(1.5, 2, 2), glm::vec3(1.5, 3, 2));
	CubicBezier righteye1;
	righteye1.setControlPoints(glm::vec3(2, 3, 2), glm::vec3(2, 4, 2), glm::vec3(2.5, 4, 2), glm::vec3(2.5, 3, 2));
	CubicBezier righteye2;
	righteye2.setControlPoints(glm::vec3(2, 3, 2), glm::vec3(2, 2, 2), glm::vec3(2.5, 2, 2), glm::vec3(2.5, 3, 2));
	CubicBezier smile;
	smile.setControlPoints(glm::vec3(.5, 2, 2), glm::vec3(1.75, 1, 2), glm::vec3(2.375, 1, 2), glm::vec3(3, 2, 2));
	images["smile"].push_back(lefteye1);
	images["smile"].push_back(lefteye2);
	images["smile"].push_back(righteye1);
	images["smile"].push_back(righteye2);
	images["smile"].push_back(smile);

	CubicBezier bezier1;
	bezier1.setControlPoints(glm::vec3(1, 1, 1), glm::vec3(2, 1, 1), glm::vec3(4, 1, 0), glm::vec3(3.75, 1.25, 0));
	bezier1.setControlColor(glm::vec4(0,1,1,1));
	CubicBezier bezier2;
	bezier2.setControlPoints(glm::vec3(3.75, 1.25, 0), glm::vec3(3.5, 1.5, 0), glm::vec3(1, 2, 1), glm::vec3(1, 1, 1));
	bezier2.setControlColor(glm::vec4(1, 0, 1, 1));

	images["partb"].push_back(bezier1);
	images["partb"].push_back(bezier2);

	CubicBezier bezier3;
	CubicBezier bezier4;
	bezier3.setControlPoints(glm::vec3(0), glm::vec3(1), glm::vec3(2), glm::vec3(3));
	bezier3.setControlColor(glm::vec4(0,1,1,1));
	bezier4.setControlPoints(glm::vec3(3), glm::vec3(3.5, 2.5, 3.5), glm::vec3(3, 1.5, 3), glm::vec3(2.25, .75, 2.25));
	bezier4.setControlColor(glm::vec4(1, 0, 1, 1));
	images["idk"].push_back(bezier3);
	images["idk"].push_back(bezier4);



	Grid3D grid;
	glm::vec3 pos(4);
	glm::vec3 neg(0);
	grid.setGridBoundaries(pos, neg);

	camera.origin = glm::vec3((pos.x + neg.x) / 2, (pos.y + neg.y) / 2, -(pos.z + neg.z) / 2);

	float deltaTime = 0;
	float lastFrame = 0;

	float time = 0;
	std::vector<CubicBezier> image;
	camera.reset();
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(1.0, 1.0, -1.0));
		glm::mat4 view = camera.GetViewMatrix();
		view = glm::scale(view, glm::vec3(1.0, 1.0, -1.0));
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.f);


		if (drawGridLines)
		{
			grid.drawticklines(gridlineshader, view, projection);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		glLineWidth(3);
		grid.draw(gridshader, view, projection);
		grid.drawticks(gridtickshader, view, projection);


		for (auto& curve : image)
		{
			curve.draw(linesegmentshader, view, projection);
			curve.drawFrenetFrame(frenetshader, view, projection);
			if (drawControlPolygon)
				curve.drawControlPolygon(controlpolygonshader, view, projection, controlPolygonEvalLevel);
			if(drawEvalPoint)
				curve.drawEvalPoint(bezierpointshader, view, projection);
			if(drawControlPoints)
				curve.drawControlPoints(bezierpointshader, view, projection);
		}

		glLineWidth(1);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			time -= .75 * deltaTime;
			if (time < 0) time = 0;
			for (auto& curve : image)
			{
				curve.evaluate(time);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			time += .75 * deltaTime;
			if (time > 1) time = 1;
			for (auto& curve : image)
			{
				curve.evaluate(time);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			camera.reset();
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			time = 0;
			image = images["partb"];
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			time = 0;
			image = images["idk"];
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			time = 0;
			image = images["smile"];
		}



		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Camera* c = (Camera*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		drawGridLines = !drawGridLines;

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		drawControlPolygon = !drawControlPolygon;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		drawControlPoints = !drawControlPoints;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		drawEvalPoint = !drawEvalPoint;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if(controlPolygonEvalLevel > 0)
			controlPolygonEvalLevel--;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if(controlPolygonEvalLevel < 2)
			controlPolygonEvalLevel++;
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	((Camera*)glfwGetWindowUserPointer(window))->ProcessMouseScroll(yoffset);
}

// from https://learnopengl.com/code_viewer_gh.php?code=src/3.model_loading/1.model_loading/model_loading.cpp
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double lastX, lastY;
	static bool firstMouse = true;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	((Camera*)glfwGetWindowUserPointer(window))->ProcessMouseMovement(xoffset, yoffset);
}
