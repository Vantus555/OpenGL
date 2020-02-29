#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "monitoring_errors.h"
#include "Renderer.h"
#include "stb_image.h"

typedef unsigned int ui;
using namespace std;

int main() {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Textures_in_OpenGL", NULL, NULL);
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

	stbi_set_flip_vertically_on_load(1);
	int img_width = 0, img_height = 0;
	unsigned char* img = stbi_load("img_ln_13_logo.png", &img_width, &img_height, NULL, 4);

	ui texture;
	GLCall(glGenTextures(1, &texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (img) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Error img load!" << endl;
	}

	GLCall(glActiveTexture(GL_TEXTURE0));
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.Bind();
	shader.SetUnifor1i("u_Texture", 0);

	stbi_image_free(img);

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