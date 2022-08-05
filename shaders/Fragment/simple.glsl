#version 460 core

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec3 fragPosWorld;
layout (location = 2) in vec3 fragNormalWorld;

layout (location = 0) out vec4 outColor;

struct PointLight {
    vec4 color; // w == intensity
    vec4 position; // w == radius
};

#define MAX_LIGHTS 10

layout (set = 0, binding = 0) uniform Ubo {
    mat4 projection;
    mat4 view;
    vec4 ambientLightColor;
    PointLight pointLights[MAX_LIGHTS];
    int numOfLights;
} ubo;

layout (push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main()
{
    vec3 diffuseLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
    const vec3 surfaceNormal = normalize(fragNormalWorld);

    for (int i = 0; i < ubo.numOfLights; ++i) {
        const vec3 directionToLight = ubo.pointLights[i].position.xyz - fragPosWorld;
        const float attenuation = 1.0f / dot(directionToLight, directionToLight);
        const float cosAngIncidence = max(dot(surfaceNormal, normalize(directionToLight)), 0);
        const vec3 intensity = ubo.pointLights[i].color.xyz * ubo.pointLights[i].color.w * attenuation;

        diffuseLight += intensity * cosAngIncidence;
    }

    outColor = vec4(diffuseLight * fragColor, 1.0);
}
