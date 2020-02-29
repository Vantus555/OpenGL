#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main() {

	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Drawing_Triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return -1;

	float triangle[] = {
		 0.0, 0.5,
		-0.5, -0.5,
		 0.5, -0.5
	};

	unsigned int buffer;// �������� ������ ������
	glGenBuffers(1, &buffer);// �������� ������
	glBindBuffer(GL_ARRAY_BUFFER, buffer);// ������� ����� ������ ��� ��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, triangle, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // �������� ������
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);// ����������� ������� ����� ������ ��������� ������

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);//������ ����
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &buffer);
	glfwTerminate();
	return 0;
}