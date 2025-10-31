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

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;

uniform vec3 u_ViewPos;

out vec4 FragColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    // Ambient Lighting
    vec3 diffTexColor = vec3(texture(material.texture_diffuse1, v_TexCoord));
    vec3 ambient = light.ambient * diffTexColor;

    // Diffuse Lighting
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffTexColor;

    // Specular Lighting
    vec3 specTexColor = vec3(texture(material.texture_specular1, v_TexCoord));
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specTexColor;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    // Attenuation
    float distance = length(light.position - v_FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Ambient Lighting
    vec3 diffTexColor = vec3(texture(material.texture_diffuse1, v_TexCoord));
    vec3 ambient = light.ambient * diffTexColor;

    // Diffuse Lighting
    vec3 lightDir = normalize(light.position - v_FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffTexColor * attenuation;

    // Specular Lighting
    vec3 specTexColor = vec3(texture(material.texture_specular1, v_TexCoord));
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specTexColor * attenuation;

    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    vec3 result = vec3(0.0f);

    result += CalcDirLight(dirLight, norm, viewDir);
    result += CalcPointLight(pointLight, norm, viewDir);

    FragColor = vec4(result, 1.0f);
}
