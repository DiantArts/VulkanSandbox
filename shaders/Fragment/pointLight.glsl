#version 460 core

layout (location = 0) in vec2 fragOffset;

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
    const float dist = sqrt(dot(fragOffset, fragOffset));
    if (dist >= 1.0f) {
        discard;
    }
    outColor = vec4(ubo.lightColor.xyz, 1.0f);
}
