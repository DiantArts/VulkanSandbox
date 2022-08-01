#version 460 core

layout (location = 0) in vec3 fragOffset;

layout (location = 0) out vec4 outColor;

layout (set = 0, binding = 0) uniform Ubo {
    mat4 projection;
    mat4 view;
    vec4 ambientLightColor;
    vec3 lightPosition;
    vec4 lightColor;
} ubo;

void main()
{
    outColor = vec4(ubo.lightColor.xyz, 1.0f);
}
