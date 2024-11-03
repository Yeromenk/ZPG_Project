#version 400
in vec3 ex_worldNormal;

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

void main(void) {
    vec3 lightVector = normalize(lightPosition - vec3(gl_FragCoord));
    float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0) * lightIntensity;
    out_Color = diffuse;
}