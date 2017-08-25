R"(#version 330 core

struct ClipPlane
{
    vec3 clipNormal;
    float clipHeight;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;
layout(location = 4) in vec3 tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float tiling = 1;
uniform ClipPlane ClippingPlane;

out vec2 f_TexCoord;
out vec4 f_Color;
out vec3 f_WorldPosition;
out vec3 f_WorldNormal;
out vec3 f_CameraPosition;
out mat3 f_TBN;

void main()
{
	vec4 worldPosition = modelMatrix * vec4(position, 1);
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;

	gl_ClipDistance[0] = dot(worldPosition, vec4(ClippingPlane.clipNormal, ClippingPlane.clipHeight));

	vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));	
	vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));
	vec3 B = cross(T, N);
	mat3 TBN = transpose(mat3(T, B, N));

	f_TexCoord = texCoord * tiling;
	f_Color = color;
	f_WorldPosition = worldPosition.xyz;
	f_WorldNormal = N;
	f_CameraPosition = inverse(viewMatrix)[3].xyz;
	f_TBN = TBN;
})"