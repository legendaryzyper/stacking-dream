#version 420 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec4 in_tangent;

layout (location = 0) out vec2 out_v_uv;

uniform mat4 model, view, proj;

void main() {
    gl_Position = proj * view * model * vec4(in_position, 1.0);
    out_v_uv = in_uv;
}
