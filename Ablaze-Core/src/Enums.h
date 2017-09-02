#pragma once
#include "AblazeGL.h"

namespace Ablaze
{

	enum class FileType
	{
		WaveFront,
		Collada,
		Text,
		PNG,
		JPG,
		TTFont,
		GLSL,
		Image
	};

	enum class Space
	{
		Local, World
	};

	enum class Angle
	{
		Radians, Degrees
	};

	enum class Position
	{
		TopLeft, BottomLeft
	};

	enum class Projection
	{
		Perspective, Orthographic
	};

	enum class Attachment
	{
		Color0 = GL_COLOR_ATTACHMENT0,
		Color1 = GL_COLOR_ATTACHMENT1,
		Color2 = GL_COLOR_ATTACHMENT2,
		Color3 = GL_COLOR_ATTACHMENT3,
		Color4 = GL_COLOR_ATTACHMENT4,
		Color5 = GL_COLOR_ATTACHMENT5,
		Color6 = GL_COLOR_ATTACHMENT6,
		Color7 = GL_COLOR_ATTACHMENT7,
		Color8 = GL_COLOR_ATTACHMENT8,
		Color9 = GL_COLOR_ATTACHMENT9,
		Depth0 = GL_DEPTH_ATTACHMENT
	};

	enum class LightType
	{
		Point,
		Directional,
		Spotlight
	};

	enum class CommandType
	{
		Render, Clear, Uniform, RTSwap, Other
	};

	enum class ClearBuffer
	{
		Color = GL_COLOR_BUFFER_BIT,
		Depth = GL_DEPTH_BUFFER_BIT,
		Stencil = GL_STENCIL_BUFFER_BIT
	};

	inline ClearBuffer operator|(ClearBuffer a, ClearBuffer b)
	{
		return static_cast<ClearBuffer>(static_cast<int>(a) | static_cast<int>(b));
	}

}