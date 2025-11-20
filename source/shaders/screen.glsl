#shader vertex
#version 410 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}

#shader fragment
#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_ScreenTexture;

void main() {
    FragColor = texture(u_ScreenTexture, TexCoords);
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0f);
}
