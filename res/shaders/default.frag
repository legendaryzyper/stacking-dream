#version 420 core

layout (location = 0) in vec2 in_v_uv;

out vec4 FragColor;
uniform sampler2D tex;

void main() {
	FragColor = texture(tex, in_v_uv);
}
