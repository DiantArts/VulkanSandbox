#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

layout (location = 0) out vec3 fragColor;

layout (push_constant) uniform Push {
    mat4 tranform;
    vec3 color;
} push;

void main()
{
    gl_Position = push.tranform * vec4(position, 1.0f);
    fragColor = color;
}
