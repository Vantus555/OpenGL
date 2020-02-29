#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "monitoring_errors.h"
#include "Renderer.h"
#include "stb_image.h"
#include "Texture.h"

#include "glm/glm.hpp" // объекты для работы с матрицами и векторами
#include "glm/gtc/matrix_transform.hpp" // Математические функции для манипуляций с объектами
typedef unsigned int ui;
using namespace std;

int main() {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(940, 540, "Projection_Matrices_in_OpenGL", NULL, NULL);
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
		100, 100,		0.0, 0.0,
		300, 100,		1.0, 0.0,
		300, 300,		1.0, 1.0,
		100, 300,		0.0, 1.0
	};

	ui index[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	VertexBuffer vb(rectangle, sizeof(float) * 4 * 4);
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	vao.AddBuffer(vb, layout);

	IndexBuffer ib(index, 6);

	Shader shader("basic.shader");
	shader.Bind();

	glm::mat4 proj = glm::ortho(0.0, 940.0, 0.0, 540.0, -1.0, 1.0);
	glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(300, 0, 0));

	glm::mat4 mvp = proj * view;
	shader.SetUniforMat4f("u_MVP", mvp);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Texture texture("img_ln_15_texture.png");
	texture.Bind();

	shader.SetUnifor1i("u_Texture", 0);

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