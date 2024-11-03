#version 400
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 viewPos;

void main(void) {
    vec3 lightVector = normalize(lightPosition - ex_worldPosition);
    float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0) * lightIntensity;
    
    vec3 viewDir = normalize(viewPos - ex_worldPosition);
    vec3 halfwayDir = normalize(lightVector + viewDir);
    float spec = pow(max(dot(normalize(ex_worldNormal), halfwayDir), 0.0), 32);
    vec4 specular = vec4(lightColor, 1.0) * spec * lightIntensity;
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse + specular;
}