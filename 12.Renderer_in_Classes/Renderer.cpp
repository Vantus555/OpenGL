#include "Renderer.h"

void Renderer::Clear() const{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.getcount(), GL_UNSIGNED_INT, nullptr));
}
