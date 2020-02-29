#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "monitoring_errors.h"

class VertexArray{
private:
	ui m_renderID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

