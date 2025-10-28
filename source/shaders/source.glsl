#shader vertex
#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 u_Transform;

out vec3 color;

void main() {
    color = aColor;
    gl_Position = u_Transform * vec4(aPos, 1.0f);
}

#shader fragment
#version 410 core

in vec3 color;

out vec4 Fragcolor;

void main() {
    Fragcolor = vec4(color, 1.0f);
}
