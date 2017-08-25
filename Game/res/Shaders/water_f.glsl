#version 330 core

struct Light
{
    vec3 Position;
    vec3 Color;
};

const int MAX_LIGHTS = 10;

in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec3 f_ToCameraVector;
in vec2 f_TextureCoord;
in vec4 f_ClipSpace;
in vec4 f_Color;

uniform int numUsedLights;
uniform Light Lights[MAX_LIGHTS];
uniform float moveFactor;
uniform vec4 color;

uniform sampler2D Tex0; //Reflection
uniform sampler2D Tex1; //Refraction
uniform sampler2D Tex2; //DuDv map
uniform sampler2D Tex3; //Normal map

layout(location = 0) out vec4 finalFragColor;

const float waveStrength = 0.02;
const float MATERIAL_REFLECT = 1.0;
const float MATERIAL_SHINE_DAMPER = 10.0;

void main(void)
{
    vec3 unitNormal = normalize(f_WorldNormal);
    vec3 unitToCameraVector = normalize(f_ToCameraVector);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    vec2 ndc = f_ClipSpace.xy / f_ClipSpace.w;
    vec2 texCoords = ndc / 2.0 + 0.5;
    vec2 reflectCoords = vec2(texCoords.x, 1.0 - texCoords.y);
    vec2 refractCoords = vec2(texCoords.x, texCoords.y);

    vec2 distortedTexCoords = texture(Tex2, vec2(f_TextureCoord.x + moveFactor,f_TextureCoord.y)).rg * 0.1;
    distortedTexCoords = f_TextureCoord + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
    vec2 totalDistortion = (texture(Tex2, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

    vec4 normalMapColor = texture(Tex3, distortedTexCoords);
    vec3 worldNormal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b * 3.0, normalMapColor.g * 2.0 - 1.0);
    unitNormal = normalize(worldNormal);

    float refractiveFactor = dot(unitToCameraVector, f_WorldNormal);
    refractiveFactor = pow(refractiveFactor, MATERIAL_REFLECT / 3.0);

    refractCoords += totalDistortion;
    refractCoords = clamp(refractCoords, 0.001, 0.999);
    reflectCoords += totalDistortion;
    reflectCoords = clamp(reflectCoords, 0.001, 0.999);

    for (int i = 0; i < numUsedLights; i++) {
        vec3 toLightVector = Lights[i].Position - f_WorldPosition;
        float distanceToLight = length(toLightVector);
        float attenuationFactor = 1.0;

        vec3 unitToLightVector = normalize(toLightVector);
        vec3 lightDirection = -unitToLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = max(dot(reflectedLightDirection, unitToCameraVector), 0.0);
        float dampedSpecularFactor = pow(specularFactor, MATERIAL_SHINE_DAMPER);        

        float nDotl = dot(unitNormal, unitToLightVector);
        float brightness = max(nDotl, 0.1);

        vec3 finalDiffuse = Lights[i].Color * (color.xyz * f_Color.xyz) * mix(texture(Tex0, reflectCoords), texture(Tex1, refractCoords), clamp(refractiveFactor, 0.0, 1.0)).xyz * brightness;
        vec3 finalSpecular = MATERIAL_REFLECT * dampedSpecularFactor * Lights[i].Color;

        totalDiffuse = totalDiffuse + (finalDiffuse / attenuationFactor);
        totalSpecular = totalSpecular + (finalSpecular / attenuationFactor);
    }
    finalFragColor = vec4(totalDiffuse + totalSpecular, (color * f_Color).a);
}