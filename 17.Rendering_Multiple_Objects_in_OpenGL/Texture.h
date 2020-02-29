#pragma once
#include "monitoring_errors.h"

typedef unsigned int ui;

class Texture
{
private:
	ui m_RenderID;
	std::string m_filename;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(std::string filename);
	~Texture();

	void Bind(ui slot = 0) const;
	void Unbind() const;

	int GetWidth() { return m_Width; }
	int GetHight() { return m_Height; }
};

