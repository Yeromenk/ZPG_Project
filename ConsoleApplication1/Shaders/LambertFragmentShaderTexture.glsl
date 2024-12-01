#version 400
#define MAX_LIGHTS 4

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_TexCoord;

out vec4 out_Color;

struct Light {
    int type;  
    vec4 position;  
    vec4 direction;  
    vec4 diffuse;  
    float attenuation;  
    float cutoff;  
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPos;
uniform Material material;
uniform sampler2D textureUnitID;

vec3 calculatePointLight(Light light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (1.0 + light.attenuation * distance * distance);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * vec3(light.diffuse) * attenuation;

    return diffuse;
}

vec3 calculateDirectionalLight(Light light, vec3 normal) {
    vec3 lightDir = normalize(-vec3(light.direction));

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * vec3(light.diffuse);

    return diffuse;
}

vec3 calculateSpotLight(Light light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(vec3(light.position) - fragPos);
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (1.0 + light.attenuation * distance * distance);

    float theta = dot(lightDir, normalize(-vec3(light.direction)));
    float epsilon = light.cutoff - 0.05;  
    float intensity = clamp((theta - light.cutoff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * vec3(light.diffuse) * attenuation * intensity;

    return diffuse;
}

void main(void) {
    vec3 normal = normalize(ex_worldNormal);
    vec3 result = vec3(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        if (lights[i].type == 0) {
            result += calculatePointLight(lights[i], normal, ex_worldPosition);
        } else if (lights[i].type == 1) {
            result += calculateDirectionalLight(lights[i], normal);
        } else if (lights[i].type == 2) {
            result += calculateSpotLight(lights[i], normal, ex_worldPosition);
        }
    }

    vec3 ambient = material.ambient;
    vec3 texColor = texture(textureUnitID, ex_TexCoord).rgb;
    out_Color = vec4((ambient + result) * texColor, 1.0);
}