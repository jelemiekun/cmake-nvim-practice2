#shader vertex
#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

void main() {
    gl_Position = vec4(aPos, 1.0f);

    vertexColor = aColor;
    texCoord = aTexCoord;
}

#shader fragment
#version 410 core

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texture1;

out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor, 0.1f) * texture(texture1, texCoord);
}
