#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_renderID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_renderID));
}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout) {
	this->Bind();
	vb.Bind();
	const auto& elements = layout.getelements();
	ui offset = 0;

	for (ui i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i)); 
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normolize, layout.getstride(), (const void*)offset));
		offset += element.count * VertexBufferElemet::getsizeoftype(element.type);
	}

	this->Unbind();
	vb.Unbind();
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_renderID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}
