#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, ui size){
	GLCall(glGenBuffers(1, &this->m_renderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_renderID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer(){
	GLCall(glDeleteBuffers(1, &this->m_renderID));
}

void VertexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_renderID));
}

void VertexBuffer::Unbind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
