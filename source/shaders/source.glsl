#shader vertex
#version 410 core

layout(location = 0) in vec3 L_coordinate;
layout(location = 1) in vec3 L_normal;
layout(location = 2) in vec2 L_texCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec3 v_Normal;
out vec2 v_TexCoord;

void main() {
    mat4 mvp = u_Projection * u_View * u_Model;
    gl_Position = mvp * vec4(L_coordinate, 1.0f);

    v_Normal = mat3(transpose(inverse(u_Model))) * L_normal;
    v_TexCoord = L_texCoord;
}

#shader fragment
#version 410 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform Material material;

out vec4 FragColor;

void main() {
    vec4 diffuseColor = texture(material.texture_diffuse1, v_TexCoord);
    vec4 specularColor = texture(material.texture_specular1, v_TexCoord);

    // Example: just output the diffuse texture for simplicity
    FragColor = diffuseColor;
}
