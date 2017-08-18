R"(#version 330 core

in vec2 f_TexCoord;
in vec4 f_Color;

uniform vec4 color;
uniform sampler2D Tex0;

layout (location = 0) out vec4 finalColor;

void main()
{
	finalColor = vec4((f_Color * color).xyz, texture(Tex0, f_TexCoord).r);
})"