R"(#version 330 core

in vec2 f_TexCoord;
in vec4 f_Color;

uniform sampler2D tex;

layout (location = 0) out vec4 finalColor;

void main()
{
	finalColor = texture(tex, f_TexCoord);
})"