#version 460 core

layout (location = 0) in vec2 fragOffset;

layout (location = 0) out vec4 outColor;

layout (push_constant) uniform Push {
    vec4 color; // w == intensity
    vec4 position; // w == radius
} push;

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

void main()
{
    const float dist = sqrt(dot(fragOffset, fragOffset));
    if (dist >= 1.0f) {
        discard;
    }
    outColor = vec4(push.color.xyz, 1.0f);
}
