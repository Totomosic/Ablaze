R"(#version 330 core

struct Material
{
	vec3 Albedo;
	float Metallic;
	float Roughness;
	float AmbientOcclusion;
};

struct Light
{
	vec3 Color;
	vec3 Position;
};

in vec2 f_TexCoord;
in vec4 f_Color;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec3 f_CameraPosition;
in mat3 f_TBN;

uniform Material material;
uniform Light Lights[10];
uniform vec4 color;
uniform int lightCount;

uniform sampler2D albedo;
uniform sampler2D roughness;
uniform sampler2D metallic;
uniform sampler2D ao;
uniform sampler2D normalMap;

const float PI = 3.14159265359;

layout(location = 0) out vec4 finalColor;

vec3 GetNormalFromNormalMap()
{
	//vec3 normal = texture(normalMap, f_TexCoord).rgb;
	//normal = normalize(normal * 2.0 - 1.0);
	//normal = normalize(f_TBN * normal);
	//return normal;
	return f_WorldNormal;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

void main()
{		

	vec3 albedo = texture(albedo, f_TexCoord).xyz * color.xyz * f_Color.xyz;
	albedo = pow(albedo, vec3(2.2));
	float roughness = texture(roughness, f_TexCoord).r;
	float metallic = texture(metallic, f_TexCoord).r;
	float ambientOcclusion = texture(ao, f_TexCoord).r;

	vec3 N = GetNormalFromNormalMap();
    vec3 V = normalize(f_CameraPosition - f_WorldPosition);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < lightCount; i++) 
    {
        // calculate per-light radiance
        vec3 L = normalize(Lights[i].Position - f_WorldPosition);
        vec3 H = normalize(V + L);
        //float distance    = length(Lights[i].Position - f_WorldPosition);
        //float attenuation = 1.0 / (distance * distance);
		float attenuation = 1.0;
        vec3 radiance     = Lights[i].Color * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, clamp(roughness, 0.03, 1.0));        
        float G   = GeometrySmith(N, V, L, clamp(roughness, 0.03, 1.0));      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.1), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 nominator    = NDF * G * F;
        float denominator = lightCount * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; 
        vec3 specular     = nominator / denominator;
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
    }
  
    vec3 ambient = vec3(0.03) * albedo * ambientOcclusion;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    finalColor = vec4(color, 1.0);
})"