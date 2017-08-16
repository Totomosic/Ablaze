R"(#version 330 core

in vec2 f_TexCoord;
in vec4 f_Color;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;

uniform vec4 color;

layout (location = 0) out vec4 finalColor;

void main()
{
	finalColor = f_Color * color;
})"