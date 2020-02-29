#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "monitoring_errors.h"
#include "Renderer.h"
#include "stb_image.h"
#include "Texture.h"

typedef unsigned int ui;
using namespace std;

int main() {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Textures_in_Classes", NULL, NULL);
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
		//Вершины		Текстура
		-0.5, -0.5,		0.0, 0.0,
		0.5, -0.5,		1.0, 0.0,
		0.5, 0.5,		1.0, 1.0,
		-0.5, 0.5,		0.0, 1.0
	};

	ui index[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	VertexBuffer vb(rectangle, sizeof(float) * 4 * 4);
	VertexBufferLayout layout;
	layout.push<float>(2); // Координаты
	layout.push<float>(2); // Текстуры
	vao.AddBuffer(vb, layout);

	IndexBuffer ib(index, 6);

	Shader shader("basic.shader");

	//////////////////////////////////////////////////////////////////////////////////////

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Texture texture("img_ln_14_texture.png");
	texture.Bind();

	shader.Bind();
	shader.SetUnifor1i("u_Texture", 0);

	//////////////////////////////////////////////////////////////////////////////////////

	shader.Unbind();
	vao.Unbind();
	vb.Unbind();
	ib.Unbind();

	Renderer render;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		render.Clear();

		shader.Bind();

		render.Draw(vao, ib, shader);
		glfwSwapInterval(2);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}