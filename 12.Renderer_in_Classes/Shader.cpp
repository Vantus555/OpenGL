#include "Shader.h"

Shader::Shader(const string filename)
	: m_filename(filename), m_renderID(0){

	shader_source shader = ParseShaders(filename);
	m_renderID = CreateShader(shader.vertexshader, shader.fragmentshader);
}

Shader::~Shader(){
	GLCall(glDeleteProgram(m_renderID));
}

shader_source Shader::ParseShaders(const string& filename) {
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

ui Shader::CompileShader(const string& source, ui type) {
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

ui Shader::CreateShader(string& ves, string& fas) {
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

void Shader::Bind() const{
	GLCall(glUseProgram(m_renderID));
}

void Shader::Unbind() const{
	GLCall(glUseProgram(0));
}

void Shader::SetUnifor4f(const string name, float v0, float v1, float v2, float v3){
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const string& name){
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name]; // Если переменная уже исползована последней

	GLCall(int location = glGetUniformLocation(m_renderID, name.c_str()));
	if (location == -1)
		cout << "Warning uniform: " << name << endl;
	else {
		m_uniformLocationCache[name] = location;
		return location;
	}
}
