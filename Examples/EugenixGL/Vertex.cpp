#include "Includes.h"

#include "Vertex.h"

//-----------------------------------------------------------------------
const std::vector<VertexAttribute> VertexPosUv::ATTRIBUTES =
{
	VertexAttribute(VertexAttribute::Usage::Position, VertexAttribute::Type::Float3, false),
	VertexAttribute(VertexAttribute::Usage::Uv , VertexAttribute::Type::Float2, false)
};
//-----------------------------------------------------------------------
VertexPosUv::VertexPosUv(const glm::vec3& pos, const glm::vec2& uv) : position(pos), textcoord(uv) {}