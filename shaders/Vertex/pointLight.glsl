#version 460 core

layout (location = 0) out vec2 fragOffset;

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

const vec2 offsets[6] = vec2[](
    vec2(-1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, -1.0),
    vec2(1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, 1.0)
);

void main()
{
    fragOffset = offsets[gl_VertexIndex];
    const vec3 cameraRightWorld = { ubo.view[0][0], ubo.view[1][0], ubo.view[2][0] };
    const vec3 cameraUpWorld = { ubo.view[0][1], ubo.view[1][1], ubo.view[2][1] };
    const vec3 positionWorld = push.position.xyz
        + push.position.w * fragOffset.x * cameraRightWorld
        + push.position.w * fragOffset.y * cameraUpWorld;
    gl_Position = ubo.projection * ubo.view * vec4(positionWorld, 1.0f);
}
