#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

layout (push_constant) uniform Push {
    mat2 tranform;
    vec2 offset;
    vec3 color;
} push;

void main()
{
    gl_Position = vec4(push.tranform * position + push.offset, 0.0f, 1.0f);
}
