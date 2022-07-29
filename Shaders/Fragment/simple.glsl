#version 460 core

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec3 fragPosWorld;
layout (location = 2) in vec3 fragNormalWorld;

layout (location = 0) out vec4 outColor;

layout (set = 0, binding = 0) uniform Ubo {
    mat4 projectionView;
    vec4 ambientLightColor;
    vec3 lightPosition;
    vec4 lightColor;
} ubo;

layout (push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main()
{
    const vec3 directionToLight = ubo.lightPosition - fragPosWorld.xyz;
    const float attenuation = 1.0f / dot(directionToLight, directionToLight);

    // intensity
    const vec3 lightColor = ubo.lightColor.xyz * ubo.lightColor.w * attenuation;
    const vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w * attenuation;
    const vec3 diffuseLight = lightColor * max(dot(normalize(fragNormalWorld), normalize(directionToLight)), 0);

    outColor = vec4((diffuseLight + ambientLight) * fragColor, 1.0);
}
