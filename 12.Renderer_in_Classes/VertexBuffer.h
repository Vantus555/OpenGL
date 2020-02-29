#pragma once
#include "GL/glew.h"
#include "monitoring_errors.h"

typedef unsigned int ui;

class VertexBuffer
{
private:
	ui m_renderID;
public:
	VertexBuffer(const void* data,ui size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

