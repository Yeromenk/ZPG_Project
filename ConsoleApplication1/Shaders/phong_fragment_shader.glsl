#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 viewPos;

void main(void) {
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));
    float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0) * lightIntensity;
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}