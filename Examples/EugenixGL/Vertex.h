#pragma once

struct VertexAttribute final
{
	enum struct Usage : uint16_t
	{
		None,
		Position,
		Uv,
		Normal,
		Tangent,
		Binormal,
		Color,

		Count
	};

	enum struct Type : uint16_t
	{
		None,
		Float,
		Float2,
		Float3,
		Float4
	};

	VertexAttribute() = default;
	VertexAttribute(Usage usage, Type type, bool norm) : _usage(usage), _type(type), _normalized(norm) {}

	inline Usage GetAttribUsage() const { return _usage; }
	inline Type GetAttribType() const { return _type; }

	inline bool IsNormalized() const { return _normalized; }

	inline int32_t GetByteSize() const { return GetTypeSize(_type); }

	static uint16_t GetAttribSize(Type type)
	{
		switch (type)
		{
		case Type::Float:
			return 1;
		case Type::Float2:
			return 2;
		case Type::Float3:
			return 3;
		case Type::Float4:
			return 4;
		default:
			printf("'type' is invalid");
			return 0;
		}
	}

	static uint16_t GetTypeSize(Type type)
	{
		return GetAttribSize(type) * sizeof(float);
	}

	static GLenum GetAttribType(Type type)
	{
		switch (type)
		{
		case Type::Float:
		case Type::Float2:
		case Type::Float3:
		case Type::Float4:
			return GL_FLOAT;
		default:
			printf("'type' is invalid");
			return GL_INVALID_ENUM;
		}
	}

private:
	Usage _usage = Usage::None;
	Type _type = Type::None;

	bool _normalized = false;
};

class VertexPosUv
{
public:
	static const std::vector<VertexAttribute> ATTRIBUTES;

	VertexPosUv() = default;
	VertexPosUv(const glm::vec3& pos, const glm::vec2& uv);

	glm::vec3 position;
	glm::vec2 textcoord;
};