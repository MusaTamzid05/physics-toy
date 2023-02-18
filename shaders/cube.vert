#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

out vec4 outputColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    outputColor = vec4(color.x, color.y, color.z, 1.0);
}
