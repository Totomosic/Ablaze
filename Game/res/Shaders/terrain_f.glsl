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

uniform int lightCount;
uniform Light Lights[MAX_LIGHTS];
uniform float moveFactor;
uniform vec4 color;

uniform sampler2D Tex0; //Texture

layout(location = 0) out vec4 finalFragColor;

const float MATERIAL_REFLECT = 0.0;
const float MATERIAL_SHINE_DAMPER = 10.0;

void main(void)
{
    vec3 unitNormal = normalize(f_WorldNormal);
    vec3 unitToCameraVector = normalize(f_ToCameraVector);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < lightCount; i++) {
        vec3 toLightVector = Lights[i].Position - f_WorldPosition;
        float distanceToLight = length(toLightVector);
        float attenuationFactor = 1.0;

        vec3 unitToLightVector = normalize(toLightVector);
        vec3 lightDirection = -unitToLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = max(dot(reflectedLightDirection, unitToCameraVector), 0.0);
        float dampedSpecularFactor = pow(specularFactor, MATERIAL_SHINE_DAMPER);        

        float nDotl = dot(unitNormal, unitToLightVector);
        float brightness = max(nDotl, 0.3);

        vec3 finalDiffuse = Lights[i].Color * (color.xyz * f_Color.xyz) * texture(Tex0, f_TextureCoord).xyz * brightness;
        vec3 finalSpecular = MATERIAL_REFLECT * dampedSpecularFactor * Lights[i].Color;

        totalDiffuse = totalDiffuse + (finalDiffuse / attenuationFactor);
        totalSpecular = totalSpecular + (finalSpecular / attenuationFactor);
    }
    finalFragColor = vec4(totalDiffuse + totalSpecular, (color * f_Color).a);
}