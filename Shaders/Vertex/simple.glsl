#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 uv;


layout (location = 0) out vec3 fragColor;

layout (push_constant) uniform Push {
    mat4 tranform;
    mat4 normalMatrix;
} push;

const vec3 DIRECTION_TO_LIGHT = normalize(vec3(1.0f, -3.0f, -1.0f));
const float AMBIENT = 0.02f;

void main()
{
    gl_Position = push.tranform * vec4(position, 1.0f);

    // mat3 normalMatrix = transpose(inverse(mat3(push.modelMatrix)));
    // vec3 normalWorldSpace = normalize(normalMatrix * normal);

    vec3 normalWorldSpace = normalize(mat3(push.normalMatrix) * normal);
    float lightIntensity = AMBIENT + max(dot(normalWorldSpace, DIRECTION_TO_LIGHT), 0);

    fragColor = lightIntensity * color;
}
