#shader vertex
#version 410 core

layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0f);
}

#shader fragment
#version 410 core

uniform vec3 u_Color;

out vec4 Fragcolor;

void main() {
    Fragcolor = vec4(u_Color, 1.0f);
}
