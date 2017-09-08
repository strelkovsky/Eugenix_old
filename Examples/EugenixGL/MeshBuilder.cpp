#include "Includes.h"

#include "Buffer.h"
#include "Mesh.h"
#include "Vertex.h"

#include "MeshBuilder.h"

namespace MeshBuilder
{
	MeshPtr CreateCube()
	{
		static const std::vector<GLfloat> cubeVerts =
		{
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f
		};

		static const std::vector<unsigned int> cubeIdxs =
		{
			0, 2, 1, 0, 3, 2, // Right
			4, 5, 6, 4, 6, 7, // Left
			0, 7, 3, 0, 4, 7, // Top
			1, 6, 2, 1, 5, 6, // Bottom
			0, 5, 1, 0, 4, 5, // Front
			3, 7, 6, 3, 6, 2  // Back
		};

		auto vertexBuffer = std::make_shared<Buffer>(BufferTarget::ArrayBuffer);
		vertexBuffer->UploadData(cubeVerts.data(), GetVectorSize(cubeVerts));
		auto indexBuffer = std::make_shared<Buffer>(BufferTarget::ElementArrayBuffer);
		indexBuffer->UploadData(cubeIdxs.data(), GetVectorSize(cubeIdxs));

		return std::make_shared<Mesh>(vertexBuffer, VertexPosUv::ATTRIBUTES, indexBuffer, sizeof(GLuint), 36);
	}
} // namespace MeshBuilder