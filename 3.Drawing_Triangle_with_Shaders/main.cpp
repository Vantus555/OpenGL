#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "string" 
#include "iostream"
typedef unsigned int ui;
using namespace std;

ui CompileShader(const string& source, ui type) {
	ui id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;

	}
	return id;
}

ui createshader(string& ves, string& fas) {
	ui program = glCreateProgram();
	ui vs = CompileShader(ves, GL_VERTEX_SHADER);
	ui fs = CompileShader(fas, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

float triangle[] = {
	0,0,0,
	0.5,0.5,0,
	1,0,0
};


int main() {

	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Drawing_Triangle_with_Shaders", NULL, NULL);
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

	ui buffer;// Название нашего буфера
	glGenBuffers(1, &buffer);// Создание буфера
	glBindBuffer(GL_ARRAY_BUFFER, buffer);// Говорим какие данные там хранятся
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, triangle, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"	
		"{\n"
		"gl_Position = position;\n"
		"}\n";

	string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"color = vec4(0.4, 0, 0.9, 1);\n"
		"}\n";

	ui program = createshader(vertexShader, fragmentShader);
	glUseProgram(program);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);//Черный цвет
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &buffer);
	glDeleteProgram(program);
	glfwTerminate();
	return 0;
}