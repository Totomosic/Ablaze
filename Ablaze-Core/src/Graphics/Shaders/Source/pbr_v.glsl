R"(#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;
layout(location = 4) in vec3 tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

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

	vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));	
	vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));
	vec3 B = cross(T, N);
	mat3 TBN = transpose(mat3(T, B, N));

	f_TexCoord = texCoord;
	f_Color = color;
	f_WorldPosition = worldPosition.xyz;
	f_WorldNormal = N;
	f_CameraPosition = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz;
	f_TBN = TBN;
})"