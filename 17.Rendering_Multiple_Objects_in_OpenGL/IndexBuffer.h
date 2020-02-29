#pragma once
#include "GL/glew.h"
#include "monitoring_errors.h"

typedef unsigned int ui;

class IndexBuffer
{
private:
	ui m_renderID;
	ui m_count;
public:
	IndexBuffer(const ui* data,ui count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	inline ui getcount() const { return this->m_count; }
};

