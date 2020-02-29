#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const ui* data, ui count) 
	: m_count(count){
	GLCall(glGenBuffers(1, &this->m_renderID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_renderID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(ui), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
	GLCall(glDeleteBuffers(1, &this->m_renderID));
}

void IndexBuffer::Bind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_renderID));
}

void IndexBuffer::Unbind() const{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
