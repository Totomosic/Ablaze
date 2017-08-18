R"(#version 330 core

struct Light
{
	vec3 Color;
	vec3 Position;
};

in vec2 f_TexCoord;
in vec4 f_Color;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;

uniform vec4 color;
uniform sampler2D Tex0;
uniform Light Lights[4];

layout (location = 0) out vec4 finalColor;

void main()
{
	vec3 toLightVector = Lights[0].Position - f_WorldPosition;
	vec3 unitToLightVector = normalize(toLightVector);
	vec3 unitNormal = normalize(f_WorldNormal);
	float NdotL = max(dot(unitToLightVector, unitNormal), 0.2);
	finalColor = texture(Tex0, f_TexCoord) * f_Color * color;
	finalColor.xyz *= NdotL;
})"