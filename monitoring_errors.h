#pragma once
#include "iostream"
#include "string"
#include "GL/glew.h"

using namespace std;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLCheackError(#x,__FILE__,__LINE__));

string geterrorstring(GLenum error) {
	switch (error)
	{
	case 1280:
		return "GL_INVALID_ENUM";
	case 1281:
		return "GL_INVALID_VALUE";
	case 1282:
		return "GL_INVALID_OPERATION";
	case 1283:
		return "GL_STACK_OVERFLOW";
	case 1284:
		return "GL_STACK_UNDERFLOW";
	case 1285:
		return "GL_OUT_OF_MEMORY";
	case 1286:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	default:
		return "I do not know this error";
	}
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLCheackError(const char* function, const char* file, int line) {
	if (GLenum error = glGetError()) {
		cout << "Error: " << geterrorstring(error) << endl;
		cout << "File: " << file << endl;
		cout << "Function: " << function << endl;
		cout << "Line: " << line << endl;
		return false;
	}
	return true;
}