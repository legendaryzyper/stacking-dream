#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 v_uv;

uniform mat4 model, view, proj;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0);
	v_uv = uv;
}