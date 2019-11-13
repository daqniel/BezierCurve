#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "CubicBezier.h"
#include "Grid3D.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	const float SCR_WIDTH = 1200;
	const float SCR_HEIGHT = 1200;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	Camera camera = Camera(glm::vec3(1.0, 1.0, 2.0));
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
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::failed to load init GLAD" << std::endl;
	}


	glEnable(GL_DEPTH_TEST);

	Shader* linesegmentshader = ResourceManager::loadShader("Shaders/linesegment.vert", "Shaders/linesegment.frag");
	Shader* gridshader = ResourceManager::loadShader("Shaders/grid.vert", "Shaders/grid.frag");

	glClearColor(.7, .7, .7, 1.0);

	CubicBezier bezier1;
	bezier1.setControlPoints(glm::vec3(1, 1, 1), glm::vec3(2, 1, 1), glm::vec3(4, 1, 0), glm::vec3(3.75, 1.25, 0));
	CubicBezier bezier2;
	bezier2.setControlPoints(glm::vec3(3.75, 1.25, 0), glm::vec3(3.5, 1.5, 0), glm::vec3(1, 2, 1), glm::vec3(1, 1, 1));

	Grid3D grid;

	float deltaTime = 0;
	float lastFrame = 0;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
		glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.f);

		grid.draw(gridshader, view , projection);

		view = camera.GetViewMatrix();
		bezier1.draw(linesegmentshader, view, projection);
		bezier2.draw(linesegmentshader, view, projection);



		//linesegmentshader->setVec2f("Viewport", glm::vec2(SCR_WIDTH, SCR_HEIGHT));

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(DOWN, deltaTime);
		

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
