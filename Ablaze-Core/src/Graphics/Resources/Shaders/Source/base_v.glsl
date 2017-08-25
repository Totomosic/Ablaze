R"(#version 330 core

struct ClipPlane
{
    vec3 clipNormal;
    float clipHeight;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec4 color;
layout (location = 4) in vec3 tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform ClipPlane ClippingPlane;

out vec2 f_TexCoord;
out vec4 f_Color;
out vec3 f_WorldPosition;
out vec3 f_WorldNormal;

void main()
{
	vec4 worldPosition = modelMatrix * vec4(position, 1);
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;

	gl_ClipDistance[0] = dot(worldPosition, vec4(ClippingPlane.clipNormal, ClippingPlane.clipHeight));

	f_Color = color;
	f_TexCoord = texCoord;
	f_WorldPosition = worldPosition.xyz;
	f_WorldNormal = (modelMatrix * vec4(normal, 0.0)).xyz;
})"