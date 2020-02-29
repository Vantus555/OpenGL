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

typedef unsigned int ui;
using namespace std;

struct shader_source {
	string vertexshader;
	string fragmentshader;
};

shader_source ParseShaders(const string& filename) {
	ifstream streamf(filename);

	if (!streamf.is_open())
		cout << "Error File Open" << endl;

	enum class shadertype {
		none = -1, vertex = 0, fragment = 1
	};

	string line;
	stringstream ss[2];
	shadertype t = shadertype::none;

	while (getline(streamf, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				t = shadertype::vertex;
			}
			else if (line.find("fragment") != string::npos) {
				t = shadertype::fragment;
			}
		}
		else {
			ss[(int)t] << line << '\n';
		}
	}

	return { ss[0].str() , ss[1].str() };
}

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
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(ves, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fas, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main() {

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "VAO_in_Classes", NULL, NULL);
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
	VertexBuffer vb(rectangle, sizeof(float) * 4 * 2); // Класс VertexBuffer
	VertexBufferLayout layout;
	layout.push<float>(2);
	vao.AddBuffer(vb, layout);

	IndexBuffer ib(index, 6); // Класс IndexBuffer

	// Очищаем конвеер состояний OpenGL
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	shader_source shader = ParseShaders("basic.shader");

	ui program = createshader(shader.vertexshader, shader.fragmentshader);
	GLCall(glUseProgram(program));

	GLCall(int location = glGetUniformLocation(program, "u_Color"));
	ASSERT(location != -1);
	GLCall(glUniform4f(location, 0.2, 0.5, 0.8, 1));

	float g = 0.0;
	float increment = 0.05;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		GLCall(glUniform4f(location, 0.2, 0.5, g, 1));

		GLCall(glUseProgram(program));

		vao.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.getcount(), GL_UNSIGNED_INT, nullptr));
		glfwSwapInterval(2);

		if (g >= 1)
			increment = -0.05;
		else if (g <= 0)
			increment = 0.05;

		g += increment;

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}