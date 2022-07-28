#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 uv;

layout (location = 0) out vec3 fragColor;

layout (set = 0, binding = 0) uniform Ubo {
    mat4 projectionView;
    vec4 ambientLightColor; // w is intensity

    // vec3 directionToLight;
    vec3 lightPosition;
    vec4 lightColor; // w is intensity
} ubo;

layout (push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main()
{
    const vec4 positionWorld = push.modelMatrix * vec4(position, 1.0f);
    gl_Position = ubo.projectionView * positionWorld;

    const vec3 normalWorldSpace = normalize(mat3(push.normalMatrix) * normal);
    const vec3 directionToLight = ubo.lightPosition - positionWorld.xyz;
    const float attenuation = 1.0f / dot(directionToLight, directionToLight);

    // intensity
    const vec3 lightColor = ubo.lightColor.xyz * ubo.lightColor.w * attenuation;
    const vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w * attenuation;
    const vec3 diffuseLight = lightColor * max(dot(normalWorldSpace, normalize(directionToLight)), 0);

    fragColor = (diffuseLight + ambientLight) * color;
}
