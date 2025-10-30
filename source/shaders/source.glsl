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
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

uniform Material material;

uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform float u_SpecularShininess;

out vec4 FragColor;

vec4 getModelColor() {
    return texture(material.texture_diffuse1, v_TexCoord);
}

vec3 getAmbient() {
    return u_AmbientStrength * u_LightColor;
}

vec3 getDiffuse() {
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * u_LightColor;
    return diffuse;
}

vec3 getSpecular() {
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_SpecularShininess);

    vec3 specular = u_SpecularStrength * spec * u_LightColor;

    return specular;
}

void main() {
    vec4 modelColor = getModelColor();
    vec4 phong = vec4(getAmbient() + getDiffuse() + getSpecular(), 1.0f);

    vec4 result = modelColor * phong;
    FragColor = result;
}
