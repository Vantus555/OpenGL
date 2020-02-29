#pragma once
#include "iostream"
#include "string"
#include "GL/glew.h"

using namespace std;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLCheackError(#x,__FILE__,__LINE__));

string geterrorstring(GLenum error);
void GLClearError();
bool GLCheackError(const char* function, const char* file, int line);