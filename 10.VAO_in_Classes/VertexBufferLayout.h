#pragma once
#include <vector>
#include "GL/glew.h"
#include "monitoring_errors.h"

typedef unsigned int ui;

struct VertexBufferElemet {
	ui type;
	ui count;
	unsigned char normolize;

	static ui getsizeoftype(ui type) {
		switch (type){
			case GL_FLOAT: return 4; 
			case GL_UNSIGNED_INT: return 4; 
			case GL_UNSIGNED_BYTE: return 1; 
		}
		ASSERT(false);	
		return 0;
	}
};

class VertexBufferLayout{
private:
	std::vector<VertexBufferElemet> m_elements;
	ui m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) {}

	template<typename T>
	void push(ui count) {
		static_assert(false);
	}

	template<>
	void push<float>(ui count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexBufferElemet::getsizeoftype(GL_FLOAT);
	}

	template<>
	void push<ui>(ui count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferElemet::getsizeoftype(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(ui count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexBufferElemet::getsizeoftype(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElemet> getelements() { return m_elements; }
	inline ui getstride() const { return m_stride; }
};

