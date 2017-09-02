#version 330 core

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
uniform ClipPlane ClippingPlane;

out vec3 f_WorldPosition;
out vec3 f_WorldNormal;
out vec3 f_ToCameraVector;
out vec2 f_TextureCoord;
out vec4 f_ClipSpace;
out vec4 f_Color;

const float tiling = 40.0;

void main(void)
{
    vec4 worldPosition = modelMatrix * vec4(position,1.0);
    vec4 viewPosition = viewMatrix * worldPosition;
    vec4 clipPosition = projectionMatrix * viewPosition;

    gl_ClipDistance[0] = dot(worldPosition, vec4(ClippingPlane.clipNormal, ClippingPlane.clipHeight));

    gl_Position = clipPosition; //Upload final position of vertex to OpenGL

    //Normal calculations
    f_WorldNormal = (modelMatrix * vec4(normal, 0.0)).xyz;
    vec3 f_CameraPosition = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz;
    f_ToCameraVector = f_CameraPosition - worldPosition.xyz;
    f_WorldPosition = worldPosition.xyz;
    f_TextureCoord = texCoord * tiling;
    f_ClipSpace = clipPosition;
    f_Color = color;
}