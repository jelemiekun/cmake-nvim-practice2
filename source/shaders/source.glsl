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
out vec3 v_FragPos;

void main() {
    mat4 mvp = u_Projection * u_View * u_Model;
    gl_Position = mvp * vec4(L_coordinate, 1.0f);

    v_Normal = mat3(transpose(inverse(u_Model))) * L_normal;
    v_TexCoord = L_texCoord;
    v_FragPos = vec3(u_Model * vec4(L_coordinate, 1.0f));
}

#shader fragment
#version 410 core

struct Material {
    vec3 ambient;
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

uniform Material material;
uniform Light light;

uniform vec3 u_ViewPos;

out vec4 FragColor;

vec3 getAmbient() {
    return material.ambient * light.ambient;
}

vec3 getDiffuse() {
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(light.position - v_FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * material.texture_diffuse1;
    return diffuse;
}

vec3 getSpecular() {
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(light.position - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular = light.specular * spec * material.texture_specular1;

    return specular;
}

void main() {
    vec3 phong = getAmbient() + getDiffuse() + getSpecular();

    FragColor = vec4(phong, 1.0f);
}
