#version 400
#define MAX_LIGHTS 4

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

struct Light {
    vec4 position;
    vec4 diffuse;
    float attenuation;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 viewPos;
uniform vec3 materialDiffuse; 

void main(void) {
    vec3 normal = normalize(ex_worldNormal);
    vec3 viewDir = normalize(viewPos - vec3(ex_worldPosition));
    vec4 result = vec4(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(vec3(lights[i].position) - vec3(ex_worldPosition));
        float distance = length(vec3(lights[i].position) - vec3(ex_worldPosition));
        float attenuation = 1.0 / (1.0 + lights[i].attenuation * distance * distance);

       
        float diff = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diff * vec4(materialDiffuse, 1.0) * lights[i].diffuse * attenuation; 

        
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
        vec4 specular = spec * lights[i].diffuse * attenuation;

        result += diffuse + specular;
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + result;
}