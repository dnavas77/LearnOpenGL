#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// main
int main(void)
{
	/* Initialize the library */
	if (!glfwInit()) { return -1; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment to compile on osx
#endif

	// GLFW window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << "\n";

	{
		// Setup vertex data (and buffer(s)) and configure vertex attributes
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {
			0, 1, 3,	// first triangle
			1, 2, 3		// second triangle
		};
		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		// Build and compile our shader program
		Shader shader("resources/shaders/Basic.shader");
		Renderer renderer;

		while (!glfwWindowShouldClose(window)) {
			// Process input
			processInput(window);

			renderer.Clear();

			// Draw calls
			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers and poll for IO events (keys, mouse, ect) */
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// Terminate GLFW (clears all GLFW allocated resources)
	glfwTerminate();

	return 0;
}

// GLFW: whenever the window size is changed (by OS or user) this callback executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on a retina displays.
	GLCall(glViewport(0, 0, width, height));
}

// Process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
