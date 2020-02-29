#pragma once
#include "GL/glew.h"
#include "string" 
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include "monitoring_errors.h"
#include "unordered_map"
#include "glm/glm.hpp"

typedef unsigned int ui;
using namespace std;

struct shader_source {
	string vertexshader;
	string fragmentshader;
};

class Shader
{
private:
	string m_filename;
	ui m_renderID;
	unordered_map<string, int> m_uniformLocationCache;
public:
	Shader(const string filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUnifor1i(const string& name, int value);
	void SetUnifor4f(const string& name, float v0, float v1, float v2, float v3);
	void SetUniforMat4f(const string& name, const glm::mat4& matrix);
private:
	shader_source ParseShaders(const string& filename);
	ui CompileShader(const string& source, ui type);
	ui CreateShader(string& ves, string& fas);
	int GetUniformLocation(const string& name);
};

