#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 uv;

layout (location = 0) out vec3 fragColor;
layout (location = 1) out vec3 fragPosWorld;
layout (location = 2) out vec3 fragNormalWorld;

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
    const vec4 positionWorld = push.modelMatrix * vec4(position, 1.0f);
    gl_Position = ubo.projection * ubo.view * positionWorld;
    fragNormalWorld = normalize(mat3(push.normalMatrix) * normal);
    fragPosWorld = positionWorld.xyz;
    fragColor = color;
}
