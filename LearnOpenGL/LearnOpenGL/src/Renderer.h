#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

// macros
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// function declarations
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;
};
