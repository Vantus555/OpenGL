#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "string" 
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "monitoring_errors.h"
#include "Shader.h"

typedef unsigned int ui;
using namespace std;

int main() {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Shader_in_Classes", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	cout << glGetString(GL_VERSION) << endl;
	float rectangle[] = {
		-0.5, -0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5
	};

	ui index[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	VertexBuffer vb(rectangle, sizeof(float) * 4 * 2);
	VertexBufferLayout layout;
	layout.push<float>(2);
	vao.AddBuffer(vb, layout);

	IndexBuffer ib(index, 6);

	Shader shader("basic.shader");
	shader.Bind();
	shader.SetUnifor4f("u_Color", 0.2, 0.5, 0.8, 1);

	shader.Unbind();
	vao.Unbind();
	vb.Unbind();
	ib.Unbind();

	float g = 0.0;
	float increment = 0.05;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		shader.SetUnifor4f("u_Color", 0.2, 0.5, g, 1);

		shader.Bind();
		vao.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.getcount(), GL_UNSIGNED_INT, nullptr));
		glfwSwapInterval(2);

		if (g > 1)
			increment = -0.05;
		else if (g < 0)
			increment = 0.05;

		g += increment;

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}